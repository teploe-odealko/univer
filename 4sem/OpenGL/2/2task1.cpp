#include <GL/glut.h>
#include <stdlib.h> 
#include <math.h>
#include <unistd.h>
#define PI 3.1459

GLfloat R=640.0/480; //Форматное соотношение
GLfloat w=40; //Ширина мирового окна
GLfloat h; //Высота мирового окна
GLfloat l, r, b, t; //Параметры мирового окна
GLfloat f=180.0 ;
GLfloat s = 1.8;
bool pulse_count = true;
int isMirrored = -1; 
int angle = 0;
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

void showAxis(void){
    glColor3f(0.0f,0.0f,1.0f);
    glBegin(GL_LINES);
    glVertex2f(0,0);
    glVertex2f(0,t);
    glVertex2f(0,0);
    glVertex2f(r,0);
    glEnd();

}

void fig0(void){ 
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-4.0,-6.0);
    glVertex2f(-4.0,6.0);
    glVertex2f(4.0,6.0);
    glVertex2f(4.0,-6.0);
    glEnd();

}

void fig1(void){ 
    showAxis();
    glColor3f(0.7,0.1,0.5);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0,0.0);
    glVertex2f(0.0,6.0);
    glVertex2f(4.0,6.0);
    glVertex2f(4.0,0.0);
    glEnd();

}

void scene(void){ 
    

    glClear(GL_COLOR_BUFFER_BIT);
    showAxis();
    fig0();
    glPushMatrix();

    glRotatef(angle, 0, 0, 1);
    glScalef(isMirrored, 1, 0);


    glTranslatef(4, 6.0, 0.0);
    glRotatef(-30, 0.0, 0.0, .5);
    glTranslatef(-4, -6.0, 0.0);
    glTranslatef(4, 6.0, 0.0);
    glScalef(-1,1,0);




    // glScalef(s, s, 1.0);
    fig1();

    glPopMatrix( );
    glFlush();
    glutSwapBuffers();
    

    if ((isMirrored == -1) && (angle == 0)){
        isMirrored = -1;
        angle = 113;
    } else if ((isMirrored == -1) && (angle == 113)){
        isMirrored = 1;
        angle = -113;
    } else if ((isMirrored == 1) && (angle == -113)){
        isMirrored = 1;
        angle = 0;
    } else if ((isMirrored == 1) && (angle == 0)){
        isMirrored = -1;
        angle = 0;
    }
    sleep(1);
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