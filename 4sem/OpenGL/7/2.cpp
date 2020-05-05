#include <GL/glut.h>
#include <cmath>
#include <math.h>

void init();
void draw();
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Myprog");
    init();
    glutDisplayFunc(draw);
    glutMainLoop();
}
void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-5.0, 5.0, -5.0, 5.0);
}
void draw()
{
    GLfloat NewX = 5, NewY = 5, EndX = -5, EndY = -5, alpha = 1, X = 0, Y = 0;
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(10, 10, 600, 400);
    
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex2f(-5.0, 0.0); glVertex2f(5.0, 0.0);
    glVertex2f(0.0, 5.0); glVertex2f(0.0, -5.0);
    glEnd();
    
    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_LINE_STRIP);
    X = NewX;
    Y = NewY;
    while (X >= EndX && Y >= EndY) {
        glVertex2f(X, Y);
        if (X - alpha * Y < 0) {
            Y = Y - 0.001;
            glVertex2f(X, Y);
        }
        else if (X - alpha * Y > 0) {
            X = X - 0.001;
            glVertex2f(X, Y);
        }
        else {
            if (X > Y) X = X - 0.001;
            else Y = Y - 0.001;
            glVertex2f(X, Y);
        }
        
    }
    
    
    glEnd();
    glFlush();
}

