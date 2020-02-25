#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#define PI 3.1459
GLfloat R=640.0/480; //Форматное соотношение
GLfloat w=40;  //Ширина мирового окна
GLfloat h; //Высота мирового окна
GLfloat l, r, b, t; //Параметры мирового окна
GLfloat f=45.0 ;
GLfloat size = 1.0, add = 0.1;
bool pulse_checker = true;
 
void init(void)
{   h=w/R; l=-w/2; r=w/2; b=-h/2; t=h/2; //Расчет параметров мирового окна
        glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(l, r, b, t);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

 

 
void fig0(void)
{   glColor3f(0.0,1.0,0.0);
 
 
     float x,y;
     glBegin(GL_LINE_STRIP);//последовательность вершин
            for(t=0.01;t<=360;t+=0.01)
            {
                x=sin(0.5*t);
                y=cos(0.5*t);
                glVertex2f(x,y);//точка с 32 бит , вещественное
            }
     glEnd();
     
}
 
void scene(void)
{   glClear(GL_COLOR_BUFFER_BIT);
    
    glPushMatrix();
    glTranslatef(10.0, 0.0, 0.0);
    glScalef(5 + size, 5 + size, 0.0);
    fig0();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10.0, 0.0, 0.0);
    glScalef(5-size, 5-size, 0.0);
    fig0();
    glPopMatrix( );

    glFlush();
    glutSwapBuffers();
    

    if (pulse_checker){
        size += 0.09;
        if (size > 1) pulse_checker = !pulse_checker;
    } else {
        size -= 0.09;
        if (size < -1) pulse_checker = !pulse_checker;
    }


    //f+=55; if(f==360) f=0;
    // sleep(0.1);
}
 
int main(int argc, char **argv)
{   glutInit(&argc, argv);
    //glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("Myprog");
    glRotatef(45, 0.0, 0.0, 1.0);
    glutDisplayFunc(scene);
    glutIdleFunc(scene);
    init();
    glutMainLoop();
    return 0;
}