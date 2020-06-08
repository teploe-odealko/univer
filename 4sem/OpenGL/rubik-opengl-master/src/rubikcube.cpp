#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifdef __linux__
	#include <GL/glut.h>
#else
	#include <GLUT/glut.h>	
#endif

#include "rubikcube.hpp"
#include "main.hpp"


RubikCube::RubikCube(int cube_size) {	// Constructor
	this->cube_size = cube_size;
	this->rotationAngle = 0;

	cube_color = new int**[6];

	for (int i=0; i < 6; i++) {
		cube_color[i] = new int*[cube_size];

		for (int j=0; j < cube_size; j++)
			cube_color[i][j] = new int[cube_size];
	}

	resetColors();
}

RubikCube::~RubikCube() {	// Destructor
	for (int i=0; i<6; i++) {
		for (int j=0; j<cube_size; j++) {
			delete[] cube_color[i][j];
		}

		delete[] cube_color[i];
	}

	delete[] cube_color;
}

void RubikCube::resetColors() {
	for (int k=0; k<6; k++) {
		for (int i=0; i < cube_size; i++) {
			for (int j=0; j < cube_size; j++) {
				cube_color[k][i][j] = k;
			}
		}
	}
}
		
void RubikCube::glDisplay() {
	glDisable(GL_TEXTURE_2D);

	int highdim = highlight / cube_size;
	int highnr = highlight % cube_size;
	bool enlight;

	for (int x=0; x<cube_size; x++) {
		for (int y=0; y<cube_size; y++) {
			for (int z=0; z<cube_size; z++) {

				enlight = (highdim==0 && highnr == x) ||
							(highdim==1 && highnr == y) ||
							(highdim==2 && highnr == z);

				glPushMatrix();

				//Rotate highlighted slice
				if (enlight) {
					if (highdim == 0)
						glRotatef(-rotationAngle, 1, 0, 0);
					if (highdim == 1)
						glRotatef(-rotationAngle, 0, -1, 0);
					if (highdim == 2)
						glRotatef(-rotationAngle, 0, 0, 1);
				}


				//glEnable(GL_BLEND);
				//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				//glColor4f(1, 1, 1, 0.5);

				if (rotateCube) {
					glRotatef(60,1,0,1);
				}

				glDrawCube(x, y, z,
					cube_color[0][x][y],
					cube_color[1][x][y],
					cube_color[2][y][z],
					cube_color[3][y][z],
					cube_color[4][x][z],
					cube_color[5][x][z]);

				glPopMatrix();

				//glDisable(GL_BLEND);
			}
		}
	}
}

/*
	BACK -> 0
	FRONT -> 1
	LEFT -> 2
	RIGHT -> 3
	BOTTOM -> 4
	TOP -> 5
	------------
	DIRECTION:
	ANTI CLOCKWISE = 0
	CLOCKWISE = 1
*/

void RubikCube::rotateColors()
{
	int size = cube_size;

	//Get the dimension - its orthogonal complement is parallel to the highlighted slice
	int highdim = highlight / size;
	//The number of slice in this dimension
	int highnr = highlight % size;

	//Rotate in x-direction (Rotate back, front, ., ., bottom, top)
	//x-coord is highnr
	if( highdim == 0 ) {
		int* save = new int[size];
		memcpy(save, cube_color[4][highnr], sizeof(int)*size);

		//Back --> Bottom
		for( int i=0; i< size; i++ )
			cube_color[4][highnr][i] = cube_color[0][highnr][size-1-i];

		//Top --> Back
		for( int i=0; i< size; i++ )
			cube_color[0][highnr][i] = cube_color[5][highnr][i];

		//Front --> Top
		for( int i=0; i< size; i++ )
			cube_color[5][highnr][i] = cube_color[1][highnr][size-1-i];

		//Bottom --> Front
		for( int i=0; i< size; i++ )
			cube_color[1][highnr][i] = save[i];

		delete [] save;
	}

	//Rotate in y-direction (Rotate back, front, left, right, ., .)
	//y-coord is highnr
	if( highdim == 1 ) {
		int* save = new int[size];
		memcpy(save, cube_color[3][highnr], sizeof(int)*size);

		//Front --> Right
		for( int i=0; i< size; i++ )
			cube_color[3][highnr][i] = cube_color[1][size-1-i][highnr];

		//Left --> Front
		for( int i=0; i< size; i++ )
			cube_color[1][i][highnr] = cube_color[2][highnr][i];

		//Back --> Left
		for( int i=0; i< size; i++ )
			cube_color[2][highnr][i] = cube_color[0][size-1-i][highnr];

		//Right --> Back
		for( int i=0; i< size; i++ )
			cube_color[0][i][highnr] = save[i];


		delete [] save;
	}

	//Rotate in z-direction (Rotate ., ., left, right, bottom, top)
	//z-coord is highnr
	if( highdim == 2 ) {
		int* save = new int[size];
		
		for( int i=0; i< size; i++ )
			save[i] = cube_color[5][i][highnr];

		//Left --> Top
		for( int i=0; i< size; i++ )
			cube_color[5][i][highnr] = cube_color[2][i][highnr];

		//Bottom --> Left
		for( int i=0; i< size; i++ )
			cube_color[2][i][highnr] = cube_color[4][size-1-i][highnr];

		//Right --> Bottom
		for( int i=0; i< size; i++ )
			cube_color[4][i][highnr] = cube_color[3][i][highnr];

		// Top --> Right
		for( int i=0; i< size; i++ )
			cube_color[3][i][highnr] = save[size-1-i];

		delete [] save;
	}

	//Rotate a side of cube
	if( highnr == 0 || highnr == size-1 ) {
		int side;

		//Get the side
		if( highdim==0 )
			side = highnr == 0 ? 2 : 3;
		if( highdim==1 )
			side = highnr == 0 ? 4 : 5;
		if( highdim==2 )
			side = highnr == 0 ? 0 : 1;


		//Save old values
		int** save = new int*[size];			

		//Save content
		for(int i=0; i<size; i++)
		{
			save[i] = new int[size];
			for(int j=0; j<size; j++)
				save[i][j] = cube_color[side][i][j];
		}
				
		//Rotate data
		for( int j=0; j<size; j++)
		{
			for( int i=0; i<size; i++)
				cube_color[side][i][j] = save[size-1-j][i];

			delete[] save[size-1-j];
		}

		delete[] save;
	}
}

void RubikCube::glRotate() {
	rotationAngle = 0;

	while (rotationAngle < 90.0) {
		rotationAngle += 5;
		display();
		glutPostRedisplay();
	}

	rotateColors();
	rotationAngle = 0;
} 

void RubikCube::glDrawCube(int x, int y, int z, int back, int front, int left, int right, int bottom, int top) {
	int size = 1;

	glPushMatrix();

	glScalef(scale_factor, scale_factor, scale_factor);

	glTranslatef(-size*2+x*(size*2), -size*2+y*(size*2), -size*2+z*(size*2));

	// YELLOW
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, cube_textures[front]);
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); 
			glVertex3f( size, -size, size);
			glTexCoord2f(1.0f,0.0f); 
			glVertex3f(  size, size, size);
			glTexCoord2f(1.0f,1.0f); 
			glVertex3f( -size, size, size);
			glTexCoord2f(0.0f,1.0f); 
			glVertex3f( -size, -size, size);
		glEnd();
	glPopMatrix();

	// Lado roxo - DIREITA
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,cube_textures[right]);
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); 
			glVertex3f( size, -size, -size );
			glTexCoord2f(1.0f,0.0f); 
			glVertex3f( size,  size, -size );
			glTexCoord2f(1.0f,1.0f);
			glVertex3f( size,  size,  size );
			glTexCoord2f(0.0f,1.0f); 
			glVertex3f( size, -size,  size );
		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	
	// Lado verde - ESQUERDA
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,cube_textures[left]);
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f);
			glVertex3f( -size, -size,  size );
			glTexCoord2f(1.0f,0.0f); 
			glVertex3f( -size,  size,  size );
			glTexCoord2f(1.0f,1.0f);
			glVertex3f( -size,  size, -size );
			glTexCoord2f(0.0f,1.0f); 
			glVertex3f( -size, -size, -size );
		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	// Lado azul - TOPO
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,cube_textures[top]);
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f);
			glVertex3f(  size,  size,  size );
			glTexCoord2f(1.0f,0.0f);
			glVertex3f(  size,  size, -size );
			glTexCoord2f(1.0f,1.0f);
			glVertex3f( -size,  size, -size );
			glTexCoord2f(0.0f,1.0f);
			glVertex3f( -size,  size,  size );
		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	// Lado vermelho - BASE
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,cube_textures[bottom]);
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f);
			glVertex3f(  size, -size, -size );
			glTexCoord2f(1.0f,0.0f);
			glVertex3f(  size, -size,  size );
			glTexCoord2f(1.0f,1.0f);
			glVertex3f( -size, -size,  size );
			glTexCoord2f(0.0f,1.0f);
			glVertex3f( -size, -size, -size );
		glEnd();
	glPopMatrix(); 
	glDisable(GL_TEXTURE_2D);


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,cube_textures[back]);
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f);
			glVertex3f(  size, -size, -size );
			glTexCoord2f(1.0f,0.0f);
			glVertex3f(  size,  size, -size );
			glTexCoord2f(1.0f,1.0f);
			glVertex3f( -size,  size, -size );
			glTexCoord2f(0.0f,1.0f);
			glVertex3f( -size, -size, -size );
		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}