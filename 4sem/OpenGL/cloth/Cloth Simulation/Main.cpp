//////////////////////////////////////////////////////////////////////////////////////////
//	Main.cpp
//	Cloth Simulation
//	Downloaded from: www.paulsprojects.net
//	Created:	12th January 2003
//
//	Copyright (c) 2006, Paul Baker
//	Distributed under the New BSD Licence. (See accompanying file License.txt or copy at
//	http://www.paulsprojects.net/NewBSDLicense.txt)
//////////////////////////////////////////////////////////////////////////////////////////	
#define WIN32_LEAN_AND_MEAN
#include "Maths/Maths.h"
#include "Log/LOG.h"
#include "Fps Counter/FPS_COUNTER.h"
#include "Window/WINDOW.h"
#include "Bitmap Font/BITMAP_FONT.h"
#include "Image/IMAGE.h"
#include "BALL.h"
#include "SPRING.h"
#include "Main.h"

//link to libraries
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "winmm.lib")

TIMER timer;
FPS_COUNTER fpsCounter;
BITMAP_FONT font;

COLOR backgroundColor(0.0f, 0.0f, 0.0f, 0.0f);

//Grid complexity. This is the number of balls across and down in the model
const int gridSize=13;

//2 arrays of balls
int numBalls;
BALL * balls1=NULL;
BALL * balls2=NULL;

//Pointers to the arrays. One holds the balls for the current frame, and one holds those
//for the next frame
BALL * currentBalls=NULL;
BALL * nextBalls=NULL;

//Gravity
VECTOR3D gravity(0.0f,-0.98f, 0.0f);

//Values given to each spring
float springConstant=15.0f;
float naturalLength=1.0f;

//Values given to each ball
float mass=0.01f;

//Damping factor. Velocities are multiplied by this
float dampFactor=0.9f;

//Array of springs
int numSprings;
SPRING * springs=NULL;

//What do we want to draw?
bool drawBalls=false, drawSprings=false;
bool drawTriangles=false, drawPatches=true;

//Sphere
float sphereRadius=4.0f;

//Floor texture
GLuint floorTexture;

//How tesselated is the patch?
int patchTesselation=5;

//Set up GL
bool GLInit()
{
	//Init window
	if(!WINDOW::Instance()->Init("Cloth Simulation", 640, 480, 8, 8, 8, 8, 24, 8, false, false))
		return false;
	
	//Check for OpenGL version/extensions
	//if(!extgl_Extensions.OpenGL14)
	//{
		//LOG::Instance()->OutputError("I require OpenGL 1.4 support");
		//return false;
	//}

	//Init font
	if(!font.Init())
		return false;

	//set viewport
	int height=WINDOW::Instance()->height;
	if(height==0)
		height=1;

	glViewport(0, 0, WINDOW::Instance()->width, height);

	//Set up projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)WINDOW::Instance()->width/WINDOW::Instance()->height, 1.0f, 100.0f);

	//Load identity modelview
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Shading states
	glShadeModel(GL_SMOOTH);
	glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//Depth states
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	//Set up light
	glLightfv(GL_LIGHT1, GL_POSITION, VECTOR4D(1.0f, 1.0f, 1.0f, 0.0f));
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT1, GL_AMBIENT, white*0.2f);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white);
	glEnable(GL_LIGHT1);

	//Use 2-sided lighting
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, true);

	return true;
}

//Set up variables
bool DemoInit()
{
	//Calculate number of balls
	numBalls=gridSize*gridSize;
		
	//Calculate number of springs
	//There is a spring pointing right for each ball which is not on the right edge, 
	//and one pointing down for each ball not on the bottom edge
	numSprings=(gridSize-1)*gridSize*2;

	//There is a spring pointing down & right for each ball not on bottom or right,
	//and one pointing down & left for each ball not on bottom or left
	numSprings+=(gridSize-1)*(gridSize-1)*2;

	//There is a spring pointing right (to the next but one ball)
	//for each ball which is not on or next to the right edge, 
	//and one pointing down for each ball not on or next to the bottom edge
	numSprings+=(gridSize-2)*gridSize*2;

	//Create space for balls & springs
	balls1=new BALL[numBalls];
	balls2=new BALL[numBalls];
	springs=new SPRING[numSprings];
	if(!balls1 || !balls2 || !springs)
	{
		LOG::Instance()->OutputError("Unable to allocate space for balls & springs");
		return false;
	}

	//Reset cloth
	ResetCloth();

	//Load floor texture
	IMAGE floorImage;
	if(!floorImage.Load("floor.tga"))
		return false;
	if(floorImage.paletted)
		floorImage.ExpandPalette();

	glGenTextures(1, &floorTexture);
	glBindTexture(GL_TEXTURE_2D, floorTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	gluBuild2DMipmaps(	GL_TEXTURE_2D, GL_RGBA8, floorImage.width, floorImage.height,
						floorImage.format, GL_UNSIGNED_BYTE, floorImage.data);
	
	//reset timer
	timer.Reset();

	return true;
}

//Reset the cloth
void ResetCloth()
{
	//Initialise the balls in an evenly spaced grid in the x-z plane
	for(int i=0; i<gridSize; ++i)
	{
		for(int j=0; j<gridSize; ++j)
		{
			balls1[i*gridSize+j].position.Set(	 float(j)-float(gridSize-1)/2,
												 8.5f,
												 float(i)-float(gridSize-1)/2);
			balls1[i*gridSize+j].velocity.LoadZero();
			balls1[i*gridSize+j].mass=mass;
			balls1[i*gridSize+j].fixed=false;
		}
	}

	//Fix the top left & top right balls in place
	balls1[0].fixed=true;
	balls1[gridSize-1].fixed=true;
	
	//Fix the bottom left & bottom right balls
	balls1[gridSize*(gridSize-1)].fixed=true;
	balls1[gridSize*gridSize-1].fixed=true;

	//Copy the balls into the other array
	for(int i=0; i<numBalls; ++i)
		balls2[i]=balls1[i];

	//Set the currentBalls and nextBalls pointers
	currentBalls=balls1;
	nextBalls=balls2;


	//Initialise the springs
	SPRING * currentSpring=&springs[0];

	//The first (gridSize-1)*gridSize springs go from one ball to the next,
	//excluding those on the right hand edge
	for(int i=0; i<gridSize; ++i)
	{
		for(int j=0; j<gridSize-1; ++j)
		{
			currentSpring->ball1=i*gridSize+j;
			currentSpring->ball2=i*gridSize+j+1;

			currentSpring->springConstant=springConstant;
			currentSpring->naturalLength=naturalLength;
			
			++currentSpring;
		}
	}

	//The next (gridSize-1)*gridSize springs go from one ball to the one below,
	//excluding those on the bottom edge
	for(int i=0; i<gridSize-1; ++i)
	{
		for(int j=0; j<gridSize; ++j)
		{
			currentSpring->ball1=i*gridSize+j;
			currentSpring->ball2=(i+1)*gridSize+j;

			currentSpring->springConstant=springConstant;
			currentSpring->naturalLength=naturalLength;
			
			++currentSpring;
		}
	}

	//The next (gridSize-1)*(gridSize-1) go from a ball to the one below and right
	//excluding those on the bottom or right
	for(int i=0; i<gridSize-1; ++i)
	{
		for(int j=0; j<gridSize-1; ++j)
		{
			currentSpring->ball1=i*gridSize+j;
			currentSpring->ball2=(i+1)*gridSize+j+1;

			currentSpring->springConstant=springConstant;
			currentSpring->naturalLength=naturalLength*sqrt(2.0f);
			
			++currentSpring;
		}
	}

	//The next (gridSize-1)*(gridSize-1) go from a ball to the one below and left
	//excluding those on the bottom or right
	for(int i=0; i<gridSize-1; ++i)
	{
		for(int j=1; j<gridSize; ++j)
		{
			currentSpring->ball1=i*gridSize+j;
			currentSpring->ball2=(i+1)*gridSize+j-1;

			currentSpring->springConstant=springConstant;
			currentSpring->naturalLength=naturalLength*sqrt(2.0f);
			
			++currentSpring;
		}
	}

	//The first (gridSize-2)*gridSize springs go from one ball to the next but one,
	//excluding those on or next to the right hand edge
	for(int i=0; i<gridSize; ++i)
	{
		for(int j=0; j<gridSize-2; ++j)
		{
			currentSpring->ball1=i*gridSize+j;
			currentSpring->ball2=i*gridSize+j+2;

			currentSpring->springConstant=springConstant;
			currentSpring->naturalLength=naturalLength*2;
			
			++currentSpring;
		}
	}

	//The next (gridSize-2)*gridSize springs go from one ball to the next but one below,
	//excluding those on or next to the bottom edge
	for(int i=0; i<gridSize-2; ++i)
	{
		for(int j=0; j<gridSize; ++j)
		{
			currentSpring->ball1=i*gridSize+j;
			currentSpring->ball2=(i+2)*gridSize+j;

			currentSpring->springConstant=springConstant;
			currentSpring->naturalLength=naturalLength*2;
			
			++currentSpring;
		}
	}
}

//Perform per-frame updates
void UpdateFrame()
{
	//set currentTime and timePassed
	static double lastTime=timer.GetTime();
	double currentTime=timer.GetTime();
	double timePassed=currentTime-lastTime;
	lastTime=currentTime;

	//Update window
	WINDOW::Instance()->Update();

	//Release corners
	if(WINDOW::Instance()->IsKeyPressed('1'))
		currentBalls[0].fixed=false;
	
	if(WINDOW::Instance()->IsKeyPressed('2'))
		currentBalls[gridSize-1].fixed=false;
	
	if(WINDOW::Instance()->IsKeyPressed('3'))
		currentBalls[gridSize*(gridSize-1)].fixed=false;
	
	if(WINDOW::Instance()->IsKeyPressed('4'))
		currentBalls[gridSize*gridSize-1].fixed=false;

	//Toggle drawing modes
	if(WINDOW::Instance()->IsKeyPressed('P'))
	{
		drawPatches=!drawPatches;
		drawTriangles=false;
		WINDOW::Instance()->SetKeyReleased('P');
	}

	if(WINDOW::Instance()->IsKeyPressed('T'))
	{
		drawTriangles=!drawTriangles;
		drawPatches=false;
		WINDOW::Instance()->SetKeyReleased('T');
	}

	if(WINDOW::Instance()->IsKeyPressed('B'))
	{
		drawBalls=!drawBalls;
		WINDOW::Instance()->SetKeyReleased('B');
	}

	if(WINDOW::Instance()->IsKeyPressed('S'))
	{
		drawSprings=!drawSprings;
		WINDOW::Instance()->SetKeyReleased('S');
	}

	//Change patch tesselation
	if(WINDOW::Instance()->IsKeyPressed(VK_UP) && patchTesselation<10)
	{
		++patchTesselation;
		WINDOW::Instance()->SetKeyReleased(VK_UP);
	}

	if(WINDOW::Instance()->IsKeyPressed(VK_DOWN) && patchTesselation>5)
	{
		--patchTesselation;
		WINDOW::Instance()->SetKeyReleased(VK_DOWN);
	}

	//Reset cloth
	if(WINDOW::Instance()->IsKeyPressed(' '))
		ResetCloth();

	//Update the physics in intervals of 10ms to prevent problems
	//with different frame rates causing different damping
	static double timeSinceLastUpdate=0.0;
	timeSinceLastUpdate+=timePassed;

	bool updateMade=false;	//did we update the positions etc this time?
	
	while(timeSinceLastUpdate>10.0)
	{
		timeSinceLastUpdate-=10.0;
		float timePassedInSeconds=0.01f;
		updateMade=true;

		//Calculate the tensions in the springs
		for(int i=0; i<numSprings; ++i)
		{
			float springLength=(	currentBalls[springs[i].ball1].position-
									currentBalls[springs[i].ball2].position).GetLength();

			float extension=springLength-springs[i].naturalLength;
	
			springs[i].tension=springs[i].springConstant*extension/springs[i].naturalLength;
		}

		//Calculate the nextBalls from the currentBalls
		for(int i=0; i<numBalls; ++i)
		{
			//Transfer properties which do not change
			nextBalls[i].fixed=currentBalls[i].fixed;
			nextBalls[i].mass=currentBalls[i].mass;

			//If the ball is fixed, transfer the position and zero the velocity, otherwise calculate
			//the new values
			if(currentBalls[i].fixed)
			{
				nextBalls[i].position=currentBalls[i].position;
				nextBalls[i].velocity.LoadZero();
			}
			else
			{
				//Calculate the force on this ball
				VECTOR3D force=gravity;
	
				//Loop through springs
				for(int j=0; j<numSprings; ++j)
				{
					//If this ball is "ball1" for this spring, add the tension to the force
					if(springs[j].ball1==i)
					{
						VECTOR3D tensionDirection=	currentBalls[springs[j].ball2].position-
													currentBalls[i].position;
						tensionDirection.Normalize();
	
						force+=springs[j].tension*tensionDirection;
					}
	
					//Similarly if the ball is "ball2"
					if(springs[j].ball2==i)
					{
						VECTOR3D tensionDirection=	currentBalls[springs[j].ball1].position-
													currentBalls[i].position;
						tensionDirection.Normalize();
	
						force+=springs[j].tension*tensionDirection;
					}
				}

				//Calculate the acceleration
				VECTOR3D acceleration=force/currentBalls[i].mass;
			
				//Update velocity
				nextBalls[i].velocity=currentBalls[i].velocity+acceleration*
																	(float)timePassedInSeconds;

				//Damp the velocity
				nextBalls[i].velocity*=dampFactor;
			
				//Calculate new position
				nextBalls[i].position=currentBalls[i].position+
					(nextBalls[i].velocity+currentBalls[i].velocity)*(float)timePassedInSeconds/2;

				//Check against sphere (at origin)
				if(nextBalls[i].position.GetSquaredLength()<sphereRadius*1.08f*sphereRadius*1.08f)
					nextBalls[i].position=nextBalls[i].position.GetNormalized()*
																			sphereRadius*1.08f;

				//Check against floor
				if(nextBalls[i].position.y<-8.5f)
					nextBalls[i].position.y=-8.5f;
			}
		}

		//Swap the currentBalls and newBalls pointers
		BALL * temp=currentBalls;
		currentBalls=nextBalls;
		nextBalls=currentBalls;
	}

	//Calculate the normals if we have updated the positions
	if(updateMade)
	{
		//Zero the normals on each ball
		for(int i=0; i<numBalls; ++i)
			currentBalls[i].normal.LoadZero();

		//Calculate the normals on the current balls
		for(int i=0; i<gridSize-1; ++i)
		{
			for(int j=0; j<gridSize-1; ++j)
			{
				VECTOR3D & p0=currentBalls[i*gridSize+j].position;
				VECTOR3D & p1=currentBalls[i*gridSize+j+1].position;
				VECTOR3D & p2=currentBalls[(i+1)*gridSize+j].position;
				VECTOR3D & p3=currentBalls[(i+1)*gridSize+j+1].position;

				VECTOR3D & n0=currentBalls[i*gridSize+j].normal;
				VECTOR3D & n1=currentBalls[i*gridSize+j+1].normal;
				VECTOR3D & n2=currentBalls[(i+1)*gridSize+j].normal;
				VECTOR3D & n3=currentBalls[(i+1)*gridSize+j+1].normal;

				//Calculate the normals for the 2 triangles and add on
				VECTOR3D normal=(p1-p0).CrossProduct(p2-p0);
	
				n0+=normal;
				n1+=normal;
				n2+=normal;

				normal=(p1-p2).CrossProduct(p3-p2);
	
				n1+=normal;
				n2+=normal;
				n3+=normal;
			}
		}

		//Normalize normals
		for(int i=0; i<numBalls; ++i)
			currentBalls[i].normal.Normalize();
	}
	
	//Render frame
	RenderFrame(currentTime, timePassed);
}

//Render a frame
void RenderFrame(double currentTime, double timePassed)
{
	//Clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();										//reset modelview matrix
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glTranslatef(0.0f, 0.0f, -28.0f);

	//Draw sphere (at origin)
	static GLUquadricObj * sphere=gluNewQuadric();
	glEnable(GL_LIGHTING);
	glMaterialfv(GL_FRONT, GL_AMBIENT, COLOR(1.0f, 0.0f, 0.0f, 0.0f));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, COLOR(1.0f, 0.0f, 0.0f, 0.0f));
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, 32.0f);
	glEnable(GL_CULL_FACE);

	gluSphere(sphere, sphereRadius, 48, 24);
			
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, black);
	

	//Draw floor
	glColor4fv(white);
	glBindTexture(GL_TEXTURE_2D, floorTexture);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_TRIANGLE_STRIP);
	{
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-25.0f, -8.6f, 5.0f);
		glTexCoord2f(2.0f, 0.0f);
		glVertex3f( 25.0f, -8.6f, 5.0f);
		glTexCoord2f(0.0f, 2.0f);
		glVertex3f(-25.0f, -8.6f,-45.0f);
		glTexCoord2f(2.0f, 2.0f);
		glVertex3f( 25.0f, -8.6f,-45.0f);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);



	//Draw cloth as triangles
	if(drawTriangles)
	{
		glEnable(GL_LIGHTING);
		glMaterialfv(GL_FRONT, GL_AMBIENT, COLOR(0.8f, 0.0f, 1.0f));	//set material
		glMaterialfv(GL_FRONT, GL_DIFFUSE, COLOR(0.8f, 0.0f, 1.0f));
		glMaterialfv(GL_BACK, GL_AMBIENT, COLOR(1.0f, 1.0f, 0.0f));
		glMaterialfv(GL_BACK, GL_DIFFUSE, COLOR(1.0f, 1.0f, 0.0f));
		glBegin(GL_TRIANGLES);
		{
			for(int i=0; i<gridSize-1; ++i)
			{
				for(int j=0; j<gridSize-1; ++j)
				{
					glNormal3fv(currentBalls[i*gridSize+j].normal);
					glVertex3fv(currentBalls[i*gridSize+j].position);
					glNormal3fv(currentBalls[i*gridSize+j+1].normal);
					glVertex3fv(currentBalls[i*gridSize+j+1].position);
					glNormal3fv(currentBalls[(i+1)*gridSize+j].normal);
					glVertex3fv(currentBalls[(i+1)*gridSize+j].position);

					glNormal3fv(currentBalls[(i+1)*gridSize+j].normal);
					glVertex3fv(currentBalls[(i+1)*gridSize+j].position);
					glNormal3fv(currentBalls[i*gridSize+j+1].normal);
					glVertex3fv(currentBalls[i*gridSize+j+1].position);
					glNormal3fv(currentBalls[(i+1)*gridSize+j+1].normal);
					glVertex3fv(currentBalls[(i+1)*gridSize+j+1].position);
				}
			}
		}
		glEnd();
		glDisable(GL_LIGHTING);
	}



	//Draw cloth using OpenGL evaluators
	if(drawPatches)
	{
		glEnable(GL_LIGHTING);
		glMaterialfv(GL_FRONT, GL_AMBIENT, COLOR(0.8f, 0.0f, 1.0f));	//set material
		glMaterialfv(GL_FRONT, GL_DIFFUSE, COLOR(0.8f, 0.0f, 1.0f));
		glMaterialfv(GL_BACK, GL_AMBIENT, COLOR(1.0f, 1.0f, 0.0f));
		glMaterialfv(GL_BACK, GL_DIFFUSE, COLOR(1.0f, 1.0f, 0.0f));
		
		//Evaluators get front & back faces the opposite way, so change the front-face definition
		glFrontFace(GL_CW);

		glEnable(GL_MAP2_VERTEX_3);
		glEnable(GL_MAP2_NORMAL);
		
		for(int i=0; i<gridSize-1; i+=3)
		{
			for(int j=0; j<gridSize-1; j+=3)
			{
				glMap2f(GL_MAP2_VERTEX_3,	0.0f, 1.0f, sizeof(BALL)/sizeof(float), 4,
											0.0f, 1.0f, gridSize*sizeof(BALL)/sizeof(float), 4,
											currentBalls[i*gridSize+j].position);
				glMap2f(GL_MAP2_NORMAL,		0.0f, 1.0f, sizeof(BALL)/sizeof(float), 4,
											0.0f, 1.0f, gridSize*sizeof(BALL)/sizeof(float), 4,
											currentBalls[i*gridSize+j].normal);
				glMapGrid2f(patchTesselation, 0.0f, 1.0f, patchTesselation, 0.0f, 1.0f);
				glEvalMesh2(GL_FILL, 0, patchTesselation, 0, patchTesselation);
			}
		}
		
		glDisable(GL_LIGHTING);
		glFrontFace(GL_CCW);

		glDisable(GL_MAP2_VERTEX_3);
		glDisable(GL_MAP2_NORMAL);
	}


	//Draw balls
	if(drawBalls)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		glPointSize(5.0f);
		glBegin(GL_POINTS);
		{
			for(int i=0; i<numBalls; ++i)
				glVertex3fv(currentBalls[i].position);
		}
		glEnd();
	}

	//Draw springs
	if(drawSprings)
	{
		glColor3f(0.0f, 0.0f, 1.0f);
		
		//bring the lines closer to prevent z-fighting with triangles
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, 0.5f);

		glBegin(GL_LINES);
		{
			for(int i=0; i<numSprings; ++i)
			{
				//Check the spring has been initialised and the ball numbers are in bounds
				if(	springs[i].ball1!=-1 && springs[i].ball2!=-1	&&
					springs[i].ball1<numBalls && springs[i].ball2<numBalls)
				{
					glVertex3fv(currentBalls[springs[i].ball1].position);
					glVertex3fv(currentBalls[springs[i].ball2].position);
				}
			}
		}
		glEnd();
		
		glPopMatrix();
	}
	
	fpsCounter.Update();

	//Print text
	font.StartTextMode();
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	font.Print(0, 28, "FPS: %.2f", fpsCounter.GetFps());
	glColor3f(0.2f, 0.9f, 1.0f);
	if(drawTriangles)
		font.Print(0, 48, "Drawing Triangle Mesh");
	if(drawPatches)
		font.Print(0, 48, "Drawing Patches, Tesselation %d", patchTesselation);
	font.EndTextMode();

	WINDOW::Instance()->SwapBuffers();

	//Save a screenshot
	if(WINDOW::Instance()->IsKeyPressed(VK_F1))
	{
		WINDOW::Instance()->SaveScreenshot();
		WINDOW::Instance()->SetKeyReleased(VK_F1);
	}

	//Check for an openGL error
	WINDOW::Instance()->CheckGLError();

	//quit if necessary
	if(WINDOW::Instance()->IsKeyPressed(VK_ESCAPE))
		PostQuitMessage(0);
}

//Shut down demo
void DemoShutdown()
{
	font.Shutdown();
	WINDOW::Instance()->Shutdown();

	if(balls1)
		delete [] balls1;
	balls1=NULL;

	if(balls2)
		delete [] balls2;
	balls2=NULL;

	if(springs)
		delete [] springs;
	springs=NULL;
}

//WinMain
int WINAPI WinMain(	HINSTANCE	hInstance,			//Instance
					HINSTANCE	hPrevInstance,		//Previous Instance
					LPSTR		lpCmdLine,			//Command line params
					int			nShowCmd)			//Window show state
{
	//Save hInstance
	WINDOW::Instance()->hInstance=hInstance;

	//Init GL and variables
	if(!GLInit())
	{
		LOG::Instance()->OutputError("OpenGL Initiation Failed");
		return false;
	}
	else
		LOG::Instance()->OutputSuccess("OpenGL Initiation Successful");

	if(!DemoInit())
	{
		LOG::Instance()->OutputError("Demo Initiation Failed");
		return false;
	}
	else
		LOG::Instance()->OutputSuccess("Demo Initiation Successful");

	//Main Loop
	for(;;)
	{
		if(!(WINDOW::Instance()->HandleMessages()))	//quit if HandleMessages returns false
			break;

		UpdateFrame();
	}

	//Shutdown
	DemoShutdown();

	//Exit program
	LOG::Instance()->OutputSuccess("Exiting...");
	return 0;
}
