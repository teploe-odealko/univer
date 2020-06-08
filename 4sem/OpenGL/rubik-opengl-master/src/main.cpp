#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifdef __linux__
	#include <GL/glut.h>
#else
	#include <GLUT/glut.h>	
#endif

#include "RgbImage.h"
#include "rubikcube.hpp"
#include "main.hpp"
#include "particles.hpp"


#define frand()			((float)rand()/RAND_MAX)
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define PI		 3.14159

//================================================================================
//===========================================================Переменные и константы

//------------------------------------------------------------ Координаты
GLfloat	  skybox = 300.0;
GLfloat   xC=10.0f, yC=2.5, zC=30.0;
GLfloat	  xZ=30.0, yZ=30.0, zZ=0.0;
GLint     wScreen=800, hScreen=600;

//------------------------------------------------------------ Наблюдатель
GLint    defineView=0;
GLint    defineProj=1;
GLfloat  raio   = 30;
GLfloat  angulo = 0.35*PI;
GLfloat  obsP[] = {raio*cos(angulo), 5.5, raio*sin(angulo)};
GLfloat  incy   = 0.5;
GLfloat  inca   = 0.03;
GLfloat  angBule = 0;
GLfloat  incBule = 1;
GLfloat  cubeSize = 2.5;
GLint offset_reflect = 1;
GLint floorSize = 30;
GLint reflect = 0;
GLint rotateCube = 0, scale = 0;
//------------------------------------------------------------ Текстуры
GLint    msec=10;					

//================================================================================
//================================================================== Инициализация

//------------------------------------------------------------ Текстуры

GLuint cube_textures[6];
GLuint texture[10];
GLuint floor_texture[0];
GLuint skybox_textures[6];
GLuint particle_textures[6];

GLuint  tex;
int azulejo = 0;
RgbImage imag;

GLfloat sun_start[] = {skybox,(500-127), (500-142)};
GLfloat sun_end[] = {-skybox,(-500+127), (-500+142)};

RubikCube rubik(3);
float alpha = 1.0;

int explode_particles = 0;
int no_walls = 0;
int ortho_camera = 0;

char particles_assets[6][64] = {"../assets/texturas_cubo/amarelo.bmp",
			"../assets/texturas_cubo/verde.bmp", "../assets/texturas_cubo/vermelho.bmp",
			"../assets/texturas_cubo/laranja.bmp", "../assets/texturas_cubo/branco.bmp",
			"../assets/texturas_cubo/azul.bmp"};

void loadParticles() {
	for (int i=0; i < 6; i++) {
		glGenTextures(1, &particle_textures[i]);
		imag.LoadBmpFile(particles_assets[i]);
		glBindTexture(GL_TEXTURE_2D, particle_textures[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexImage2D(GL_TEXTURE_2D, 0, 3,
		            imag.GetNumCols(),
		            imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		            imag.ImageData());
	}
}

void loadSkybox() {

	// ВНИЗ
	glGenTextures(1, &skybox_textures[0]);
	glBindTexture(GL_TEXTURE_2D, skybox_textures[0]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		imag.LoadBmpFile("../assets/skybox/skybox_dn.bmp");
		// imag.LoadBmpFile("../assets/texturas_cubo/verde.bmp");
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 
				 imag.GetNumCols(),
				 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
				 imag.ImageData());	


	// ВВЕРХ
	glGenTextures(1, &skybox_textures[1]);
	glBindTexture(GL_TEXTURE_2D, skybox_textures[1]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		imag.LoadBmpFile("../assets/skybox/skybox_up.bmp");
		// imag.LoadBmpFile("../assets/texturas_cubo/verde.bmp");
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 
				 imag.GetNumCols(),
				 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
				 imag.ImageData());	
	

	// Влево
	glGenTextures(1, &skybox_textures[2]);
	glBindTexture(GL_TEXTURE_2D, skybox_textures[2]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		imag.LoadBmpFile("../assets/skybox/skybox_lf.bmp");
		// imag.LoadBmpFile("../assets/texturas_cubo/verde.bmp");
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 
				 imag.GetNumCols(),
				 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
				 imag.ImageData());	


	// ВПРАВО
	glGenTextures(1, &skybox_textures[3]);
	glBindTexture(GL_TEXTURE_2D, skybox_textures[3]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		imag.LoadBmpFile("../assets/skybox/skybox_rt.bmp");
		// imag.LoadBmpFile("../assets/texturas_cubo/verde.bmp");
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 
				 imag.GetNumCols(),
				 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
				 imag.ImageData());	


	// НАЗАД
	glGenTextures(1, &skybox_textures[4]);
	glBindTexture(GL_TEXTURE_2D, skybox_textures[4]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		imag.LoadBmpFile("../assets/skybox/skybox_bk.bmp");
		// imag.LoadBmpFile("../assets/texturas_cubo/verde.bmp");
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 
				 imag.GetNumCols(),
				 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
				 imag.ImageData());	


	// ВПЕРЕД
	glGenTextures(1, &skybox_textures[5]);
	glBindTexture(GL_TEXTURE_2D, skybox_textures[5]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		imag.LoadBmpFile("../assets/skybox/skybox_ft.bmp");
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 
				 imag.GetNumCols(),
				 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
				 imag.ImageData());		
}

void loadTextures() {
	loadSkybox();

	// ПОЛ
	glGenTextures(1, &floor_texture[0]);
	glBindTexture(GL_TEXTURE_2D, floor_texture[0]);
	imag.LoadBmpFile("../assets/floor_reflect.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 
				 imag.GetNumCols(),
				 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
				 imag.ImageData());

	// Желтый
	glGenTextures(1, &cube_textures[0]);
	glBindTexture(GL_TEXTURE_2D, cube_textures[0]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	imag.LoadBmpFile("../assets/texturas_cubo/amarelo.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
	imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	// Белый
	glGenTextures(1, &cube_textures[1]);
	glBindTexture(GL_TEXTURE_2D, cube_textures[1]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	imag.LoadBmpFile("../assets/texturas_cubo/branco.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
	imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	// Красный
	glGenTextures(1, &cube_textures[2]);
	glBindTexture(GL_TEXTURE_2D, cube_textures[2]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	imag.LoadBmpFile("../assets/texturas_cubo/vermelho.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
	imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	// Оранжевый
	glGenTextures(1, &cube_textures[3]);
	glBindTexture(GL_TEXTURE_2D, cube_textures[3]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	imag.LoadBmpFile("../assets/texturas_cubo/laranja.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
	imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	// Синий
	glGenTextures(1, &cube_textures[4]);
	glBindTexture(GL_TEXTURE_2D, cube_textures[4]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	imag.LoadBmpFile("../assets/texturas_cubo/azul.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
			imag.GetNumCols(),
			imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
			imag.ImageData());

	// Зеленый
	glGenTextures(1, &cube_textures[5]);
	glBindTexture(GL_TEXTURE_2D, cube_textures[5]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	imag.LoadBmpFile("../assets/texturas_cubo/verde.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
			imag.GetNumCols(),
			imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
			imag.ImageData());


	loadParticles();
}

void showParticles(Particle *particle) {
	for (int i=0; i < MAX_PARTICLES; i++) {

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, particle_textures[rand() % 6]);

		glBegin(GL_QUADS);
			glTexCoord2d(0,0); glVertex3f(particle[i].x - particle[i].size, particle[i].y - particle[i].size, particle[i].z);
			glTexCoord2d(1,0); glVertex3f(particle[i].x + particle[i].size, particle[i].y - particle[i].size, particle[i].z);
			glTexCoord2d(1,1); glVertex3f(particle[i].x + particle[i].size, particle[i].y + particle[i].size, particle[i].z);
			glTexCoord2d(0,1); glVertex3f(particle[i].x - particle[i].size, particle[i].y + particle[i].size, particle[i].z);
		glEnd();

		glDisable(GL_TEXTURE_2D);

		particle[i].x += particle[i].vx;
		particle[i].y += particle[i].vy;
		particle[i].z += particle[i].vz;
		particle[i].vx += particle[i].ax;
		particle[i].vy += particle[i].ay;
		particle[i].vz += particle[i].az;
		particle[i].life -= particle[i].fade;		
	}
}

void initParticles(Particle *particle, GLfloat x, GLfloat y, GLfloat z) {
	GLfloat v, theta, phi;
	GLfloat particle_size;

	particle_size = 0.75;

	for (int i=0; i < MAX_PARTICLES; i++) {
		v = 1 * frand() + 0.02;
		theta = frand() * PI;

		phi = frand() * PI;

		particle[i].size = particle_size;
		particle[i].x = x;
		particle[i].y = y;
		particle[i].z = z;

		particle[i].vx = v * cos(theta) * sin(phi);
		particle[i].vy = v * cos(phi);
		particle[i].vz = v * sin(theta) * sin(phi);	
		//printf("vx = %f / vy = %f / vz = %f\n", particle[i].vx, particle[i].vy, particle[i].vz);

		particle[i].ax = 0.02f;
		particle[i].ay = 0.02f;
		particle[i].az = 0.02f;

		particle[i].r = 1.0f;
		particle[i].g = 1.0f;
		particle[i].b = 1.0f;
		particle[i].life = 1.0f;
		particle[i].fade = 0.01f;
	}
}

void drawWalls(float trans_constant, float trans_j, float trans_k, int j, int k) {

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ y=0
	glPushMatrix();
		glTranslatef(trans_j, trans_constant*-1.0f, trans_k);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, cube_textures[rubik.cube_color[4][j][k]]);
		//glColor4f(1,1,1,0.25);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3f( -xC,  -xC, -xC );
			glTexCoord2f(1.0f,0.0f); glVertex3f( xC, -xC, -xC );
			glTexCoord2f(1.0f,1.0f); glVertex3f( xC, -xC, xC);
			glTexCoord2f(0.0f,1.0f); glVertex3f( -xC,  -xC,  xC);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ y=xC
	glPushMatrix();
		glTranslatef(trans_j, trans_constant, trans_k);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, cube_textures[rubik.cube_color[5][j][k]]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3f( -xC,  xC, -xC );
			glTexCoord2f(1.0f,0.0f); glVertex3f( xC, xC, -xC );
			glTexCoord2f(1.0f,1.0f); glVertex3f( xC, xC, xC);
			glTexCoord2f(0.0f,1.0f); glVertex3f( -xC,  xC,  xC);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//  z=0
	glPushMatrix();
		glTranslatef(-trans_constant, trans_k, trans_j);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, cube_textures[rubik.cube_color[2][k][j]]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f( -xC, -xC, -xC);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( -xC, xC, -xC);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( -xC, xC, xC);
			glTexCoord2f(0.0f, 1.0f); glVertex3f( -xC,  -xC, xC);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// z=xC
	glPushMatrix();
		glTranslatef(trans_constant, trans_k, trans_j);	
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, cube_textures[rubik.cube_color[3][k][j]]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3f( xC,  -xC, -xC);
			glTexCoord2f(1.0f,0.0f); glVertex3f( xC, xC, -xC);
			glTexCoord2f(1.0f,1.0f); glVertex3f( xC, xC, xC);
			glTexCoord2f(0.0f,1.0f); glVertex3f( xC,  -xC, xC);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// x=0
	glPushMatrix();
		glTranslatef(trans_k, trans_j, -trans_constant);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, cube_textures[rubik.cube_color[0][k][j]]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3f( -xC,  -xC, -xC);
			glTexCoord2f(1.0f,0.0f); glVertex3f( -xC, xC, -xC);
			glTexCoord2f(1.0f,1.0f); glVertex3f( xC, xC, -xC);
			glTexCoord2f(0.0f,1.0f); glVertex3f( xC,  -xC, -xC);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// x=xC
	glPushMatrix();
		glTranslatef(trans_k, trans_j, trans_constant);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, cube_textures[rubik.cube_color[1][k][j]]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3f( -xC, -xC, xC);
			glTexCoord2f(1.0f,0.0f); glVertex3f( -xC, xC, xC);
			glTexCoord2f(1.0f,1.0f); glVertex3f( xC, xC, xC);
			glTexCoord2f(0.0f,1.0f); glVertex3f( xC, -xC, xC);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void drawFloor() {
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(0.0,offset_reflect,0.0);
	glBindTexture(GL_TEXTURE_2D, floor_texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_QUADS);
	
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(-floorSize / 2, 0, floorSize / 2);
	glTexCoord2f(1, 0);
	glVertex3f(floorSize / 2, 0, floorSize / 2);
    glTexCoord2f(1, 1);
	glVertex3f(floorSize / 2, 0, -floorSize / 2);	
	glTexCoord2f(0, 1);
	glVertex3f(-floorSize / 2, 0, -floorSize / 2);
			
	glEnd();
	glPopMatrix();
}

void drawSkybox() {
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, skybox_textures[0]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3f( -skybox,  -skybox, -skybox );
			glTexCoord2f(0.0f,1.0f); glVertex3f( skybox, -skybox, -skybox );
			glTexCoord2f(1.0f,1.0f); glVertex3f( skybox, -skybox, skybox);
			glTexCoord2f(1.0f,0.0f); glVertex3f( -skybox,  -skybox,  skybox);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ y=xC
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, skybox_textures[1]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,1.0f); glVertex3f( -skybox,  skybox, -skybox );
			glTexCoord2f(0.0f,0.0f); glVertex3f( skybox, skybox, -skybox );
			glTexCoord2f(1.0f,0.0f); glVertex3f( skybox, skybox, skybox);
			glTexCoord2f(1.0f,1.0f); glVertex3f( -skybox,  skybox,  skybox);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// x=0
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, skybox_textures[2]);
		glBegin(GL_QUADS);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( -skybox, -skybox, -skybox);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( -skybox, skybox, -skybox);
			glTexCoord2f(0.0f, 1.0f); glVertex3f( -skybox, skybox, skybox);
			glTexCoord2f(0.0f, 0.0f); glVertex3f( -skybox,  -skybox, skybox);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//  x=xC
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, skybox_textures[3]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3f( skybox,  -skybox, -skybox);
			glTexCoord2f(0.0f,1.0f); glVertex3f( skybox, skybox, -skybox);
			glTexCoord2f(1.0f,1.0f); glVertex3f( skybox, skybox, skybox);
			glTexCoord2f(1.0f,0.0f); glVertex3f( skybox,  -skybox, skybox);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// z=0
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, skybox_textures[4]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3f( -skybox,  -skybox, -skybox);
			glTexCoord2f(0.0f,1.0f); glVertex3f( -skybox, skybox, -skybox);
			glTexCoord2f(1.0f,1.0f); glVertex3f( skybox, skybox, -skybox);
			glTexCoord2f(1.0f,0.0f); glVertex3f( skybox,  -skybox, -skybox);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// z=xC
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, skybox_textures[5]);
		glBegin(GL_QUADS);
			glTexCoord2f(1.0f,0.0f); glVertex3f( -skybox, -skybox, skybox);
			glTexCoord2f(1.0f,1.0f); glVertex3f( -skybox, skybox, skybox);
			glTexCoord2f(0.0f,1.0f); glVertex3f( skybox, skybox, skybox);
			glTexCoord2f(0.0f,0.0f); glVertex3f( skybox, -skybox, skybox);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void drawScene() {
	drawSkybox();

	glEnable(GL_BLEND);
	glPushMatrix();
		glColor4f(1,1,1,alpha);
		rubik.glDisplay();
	glPopMatrix();
	glDisable(GL_BLEND);
	
	float trans_constant = xC*2;
	float trans = xC*2;			

	for (int i=1; i >= -1; i--) {
		for (int j=1; j >= -1; j--) {
			// 1-i , 1-j

			glPushMatrix();
			if (!no_walls)
				drawWalls(trans_constant, trans*i, trans*j, (-1-i)*-1, (-1-j)*-1);
			glPopMatrix();
		}	
	}

}

void drawReflection(){
	glPushMatrix();
	glTranslatef(0,-cubeSize*2,0);

	glEnable(GL_STENCIL_TEST); //Активное использование буфера трафарета
    glColorMask(0, 0, 0, 0); 
    glDisable(GL_DEPTH_TEST); //Становится неактивным тест глубины
    glStencilFunc(GL_ALWAYS, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    //Помещает в 1 все пиксели без буфера трафарета, представляющие отражающую поверхность
    glColorMask(1, 1, 1, 1);
    drawFloor();
    glEnable(GL_DEPTH_TEST); //Включает тест глубины
    glStencilFunc(GL_EQUAL, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //Буфер трафарета только для чтения
    glPushMatrix();
    glTranslatef(0, -cubeSize*1.5, 0);
    glScalef(1, -1, 1);
    // Делает куб перейти к нижней части отражающие поверхности

    drawScene();
    //rubik.glDisplay();
    glPopMatrix();
    //НАРИСОВАТЬ ОТРАЖЕНИЕ ОБЪЕКТА
    glDisable(GL_STENCIL_TEST); //Отключает использование буфера трафарета

    //Blending
	glEnable(GL_BLEND);
	glColor4f(1, 1, 1, 0.25);
	drawFloor();
	glDisable(GL_BLEND);
	glPopMatrix();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glViewport (0,0, wScreen, hScreen);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	switch (defineProj) {
		case 1:	gluPerspective(88.0, wScreen/hScreen, 0.1, 1000); break;
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(obsP[0], obsP[1], obsP[2], 0,0,0, 0,1,0);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Объекты ]
	if(reflect == 1)
		drawReflection();

	drawScene();

	if (explode_particles) {
		showParticles(particle1);
		showParticles(particle2);
		showParticles(particle3);
		showParticles(particle4);
		showParticles(particle5);
		showParticles(particle6);
		if (particle1[0].life <= 0.6f) {
			no_walls = 1;
		}
		if (particle1[0].life <= 0) {
			initParticles(particle1, 0.0, xC*3, 0.0);
			initParticles(particle2, xC*3, -xC, 2.0);
			initParticles(particle3, 0.0, -xC*3.5, -xC/2);
			initParticles(particle4, -xC*3, xC, -xC);
			initParticles(particle5, xC-1.0, xC, xC*2.5);
			initParticles(particle6, -xC, -xC, -xC*3.5);
			explode_particles = 0;
		}
	}

	glutSwapBuffers();
}


void Timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(msec,Timer, 1);
}

//======================================================= СОБЫТИЕ
void keyboard(unsigned char key, int x, int y){
	switch (key) {
			case '1':
				if (!rotateCube) {
					rubik.highlight = 0;
					glutPostRedisplay();
					rubik.glRotate();	
				}
				break;
			case '2':
				if (!rotateCube) {
					rubik.highlight = 1;
					glutPostRedisplay();
					rubik.glRotate();	
				}			
				break;
			case '3':
				if (!rotateCube) {
					rubik.highlight = 2;
					glutPostRedisplay();
					rubik.glRotate();	
				}
				break;
			case '4':
				if (!rotateCube) {
					rubik.highlight = 3;
					glutPostRedisplay();
					rubik.glRotate();	
				}
				break;
			case '5':
				if (!rotateCube) {
					rubik.highlight = 4;
					glutPostRedisplay();
					rubik.glRotate();	
				}
				break;
			case '6':
				if (!rotateCube) {
					rubik.highlight = 5;
					glutPostRedisplay();
					rubik.glRotate();	
				}
				break;
			case '7': 
				if (!rotateCube) {
					rubik.highlight = 6;
					glutPostRedisplay();
					rubik.glRotate();	
				}
				break;
			case '8':
				if (!rotateCube) {
					rubik.highlight = 7;
					glutPostRedisplay();
					rubik.glRotate();	
				}
				break;
			case '9':
				if (!rotateCube) {
					rubik.highlight = 8;
					glutPostRedisplay();
					rubik.glRotate();	
				}
				break;
			case '0':
				break;	

		case 'w': case 'W':
			if (raio > 1) {
				raio -= 0.5;
				obsP[0] = raio * cos(angulo);
				obsP[2] = raio * sin(angulo);
				glutPostRedisplay();
			}
			break;
		case 's': case 'S':
			if (raio < 120) {
				raio += 0.5;
				obsP[0] = raio * cos(angulo);
				obsP[2] = raio * sin(angulo);
				glutPostRedisplay();
			}
			break;

		case 'b':
		case 'B':
			if(reflect != 1)
				reflect = 1;
			else
				reflect = 0;
			break;

		case 'e':
		case 'E':
			explode_particles = 1;
			break;

		case 't': case 'T':
			if (alpha < 1.0)
				alpha += 0.05f;
			break;	
		case 'r': case 'R':
			if (alpha >= 0.6f)
				alpha -= 0.05f;
			printf("alpha = %f\n", alpha);
			break;

		case 'P': case 'p':
			no_walls = !no_walls;
			break;

		case '+':
			rotateCube = 1;
			scale = 1;
			rubik.scale_factor += xC / 30;
			printf("rubik.scale_factor = %f\n", rubik.scale_factor);
			if (rubik.scale_factor >= 6 && rubik.scale_factor < 10 && !no_walls) {
				explode_particles = 1;
				//no_walls = 1;
			}
			break;

		case '-':
			if (rubik.scale_factor >= 1.0 + xC / 30)
				rubik.scale_factor -= xC / 30;
			else
				rotateCube = 0;
			if (rubik.scale_factor < 6)
				explode_particles = 0;

			break;

		case ' ':
			rubik.highlightNext();
			glutPostRedisplay();
			break;

		case 13:
			if (!rotateCube)
				rubik.glRotate();
			break;

		case 27:	// ESC
			exit(0);
			break;
  	}
}

void teclasNotAscii(int key, int x, int y){
    if(key == GLUT_KEY_UP)
		obsP[1] += incy*2;
	if(key == GLUT_KEY_DOWN)
		obsP[1] -= incy*2;
	if(key == GLUT_KEY_LEFT)
		angulo=angulo+inca;
	if(key == GLUT_KEY_RIGHT)
		angulo=angulo-inca;

	if (obsP[1] > yC*20)
		obsP[1] = yC*20;
    if (obsP[1] < -yC*20)
		obsP[1] = -yC*20;

    obsP[0] = raio*cos(angulo);
	obsP[2] = raio*sin(angulo);

	glutPostRedisplay();
}

void init(void)
{
	glClearColor(BLACK);
	glShadeModel(GL_SMOOTH);
	loadTextures();
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	initParticles(particle1, 0.0, xC*3, 0.0);
	initParticles(particle2, xC*3, -xC, 2.0);
	initParticles(particle3, 0.0, -xC*3.5, -xC/2);
	initParticles(particle4, -xC*3, xC, -xC);
	initParticles(particle5, xC-1.0, xC, xC*2.5);
	initParticles(particle6, -xC, -xC, -xC*3.5);
}

void resizeWindow(GLsizei w, GLsizei h)
{
 	wScreen=w;
	hScreen=h;
	glutPostRedisplay();
}

//======================================================= MAIN
int main(int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL );
	glutInitWindowSize (wScreen, hScreen);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("RUBIK CUBE - Antonio Simoes & Joao Lopes");

	init();

	glutSpecialFunc(teclasNotAscii);
	glutDisplayFunc(display);
	glutReshapeFunc(resizeWindow);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(msec, Timer, 1);

	glutMainLoop();

	return 0;
}
