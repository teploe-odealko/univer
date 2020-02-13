#include <GL/glut.h>

#include <GL/glut.h>

void init();

void draw();

int main(int argc, char **argv)

{ glutInit(&argc, argv);

glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

glutInitWindowSize(640, 480);

glutInitWindowPosition(50, 50);

glutCreateWindow("My program");

init();

glutDisplayFunc(draw);

glutMainLoop();
return 0;
}

void init() //Функция инициализации

{ glClearColor(1.0, 1.0, 0.0, 0.0); 
glMatrixMode(GL_PROJECTION);

glLoadIdentity( );

gluOrtho2D(0.0,2.0,0.0,1.0);

}

void draw(){ 
    GLfloat l = -100, r = 100, b = -100, t = 100;

    GLint x = 0, y = 0, w = 60, h = 60;

    glClear(GL_COLOR_BUFFER_BIT);

    gluOrtho2D(l, r, b, t);

    for(x = 0; x <= 600; x += w)

        for(y = 0; y <= 480; y += h){ 
        glViewport(x, y, w, h);
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINE_STRIP);

        glVertex2f(10.0, 0.5); glVertex2f(10, 0.5);

        glVertex2f(1.1, 6); glVertex2f(12, 0.6);

        glEnd( );
        }
    


    glFlush();

}