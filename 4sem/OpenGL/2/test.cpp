#include <GL/glut.h>
#include <stdlib.h> 
#include <math.h>
#define PI 3.1459

GLfloat R=640.0/480; //Форматное соотношение
GLfloat w=40; //Ширина мирового окна
GLfloat h; //Высота мирового окна
GLfloat l, r, b, t; //Параметры мирового окна
GLfloat f=180.0 ;
void init(void){
    h=w/R; l=-w/2; r=w/2; b=-h/2; t=h/2; //Расчет параметров миро-вого окна

    glClearColor(1.0,1.0,0.0,0.0);
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
    glVertex2f(0.0,0.0);
    glVertex2f(0.0,3.0);
    glVertex2f(5.0,2.0);
    glVertex2f(5.0,0.0);
    glEnd();

}

void scene(void){ 
    glClear(GL_COLOR_BUFFER_BIT);
    showAxis();
    fig0();
    //glPushMatrix();
    glTranslatef(4.5, 8.0, 0.0);
    glRotatef(f, 0.0, 0.0, 0.5);
    glScalef(1.0, -1.0, 1.0);
    fig0();
    //glPopMatrix( );
    glFlush();
    //glutSwapBuffers();
    //f+=30; if(f==360) f=0;
    //Sleep(200);
}

int main(int argc, char **argv)

{ 
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    //glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("Myprog");
    glutReshapeFunc(reshape);
    glutDisplayFunc(scene);
    //glutIdleFunc(scene);
    init();
    glutMainLoop();

    return 0;
}