#include <GL/glut.h>
#include <stdlib.h> 
#include <math.h>
#include <unistd.h>
#include <iostream>
#define PI 3.1459

GLfloat R=640.0/480; //Форматное соотношение
GLfloat w=40; //Ширина мирового окна
GLfloat h; //Высота мирового окна
GLfloat l, r, b, t; //Параметры мирового окна
GLfloat f=180.0 ;
GLfloat valX = 0;
float argX = 0;
float argY = 0;
float coef = 10;

GLfloat valY = 0;
bool PI_checker = true;
void init(void){
    h=w/R; l=-w/2; r=w/2; b=-h/2; t=h/2; //Расчет параметров миро-вого окна

    glClearColor(1.0,1.0,1.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(l, r, b, t);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void reshape(GLsizei W, GLsizei H){

    if(R>W/H) glViewport(0,0,W,W/R);
    else glViewport(0,0,H*R,H);
}

// void showAxis(void){
//     glColor3f(0.0f,0.0f,1.0f);
//     glBegin(GL_LINES);
//     glVertex2f(0,0);
//     glVertex2f(0,t);
//     glVertex2f(0,0);
//     glVertex2f(r,0);
//     glEnd();

// }

void fig0(void){ 
    glColor3f(0.0,1.0,0.0);
    glPointSize(10);

    glBegin(GL_POINTS);
    glVertex2f(0.0,0.0);

    glEnd();

}

void scene(void){ 
    

    glClear(GL_COLOR_BUFFER_BIT);
    // showAxis();
    // fig0();
    glPushMatrix();
    glTranslatef(valX, valY, 0.0);

    // glRotatef(f, 0, 0.0, 0.5);
    // glScalef(s+main_s, s+main_s, 1.0);
    fig0();
    glPopMatrix( );
    glFlush();
    glutSwapBuffers();


    argX += 0.06;
    argY += 0.06;
    

    valX = coef*sin(argX);
    valY = coef*cos(argY);
    if (coef > 0){
        coef -= 0.02;
    }

    // std::cout << valX;



    // sleep(0.3);
}

int main(int argc, char **argv)

{ 
    glutInit(&argc, argv);
    // glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("Myprog");
    // glutReshapeFunc(reshape);
    glutDisplayFunc(scene);
    glutIdleFunc(scene);
    init();
    glutMainLoop();

    return 0;
}