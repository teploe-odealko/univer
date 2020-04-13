#include <GL/glut.h>
#include <math.h>

GLfloat angle=0;

void init(void)
{ 
    glClearColor(1.0, 1.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    gluPerspective(60, 1, 1, 10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity( );
}

void myDisplay( )
{ 
    glPushMatrix( ); //Сохраняем VM = 1
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    gluLookAt(3, 2, 1, 0, 0, 0, 0, 1, 0); // VM=Fwe
    GLfloat myLightPosition[] = {3.0, 3.0, 3.0, 1.0}; // Источник света в CKw

    glPushMatrix();
        glRotatef(angle, 0, 1, 0); // вращаем источник света
        // glTranslatef(); // перемещаем источник света
        glLightfv(GL_LIGHT0, GL_POSITION, myLightPosition);

        glBegin(GL_LINES);
            glColor3f(1,1,1); glVertex3f(3, 3, 3); glVertex3f(0.0, 0.0, 0.0);
        glEnd();
    glPopMatrix();

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glPushMatrix(); //Сохраняем VM=Fwe

    glBegin(GL_POLYGON);

    glNormal3f(0.577, 0.577, 0.577);
    glVertex3f(1, 0, 0);
    glVertex3f(0, 1, 0);
    glVertex3f(0, 0, 1);
    glEnd();
    // грань f1
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, -1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);
    glVertex3f(1, 0, 0);
    glEnd();
    // грань f2
    glBegin(GL_POLYGON);
    glNormal3f(-1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);
    glVertex3f(0, 1, 0);
    glEnd();
    // грань f3
    glBegin(GL_POLYGON);
    glNormal3f(0, -1, 0);
    glVertex3f(1, 0, 0);
    glVertex3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glEnd();


    glPopMatrix( ); // Восстанавливаем VM=Fwe
    glDisable(GL_LIGHTING); //Выключаем освещение

    
    glBegin(GL_LINES);
    glColor3f(1,0,0 ); glVertex3f(0, 0, 0); glVertex3f(2, 0, 0);
    glColor3f(0,1,0 ); glVertex3f(0, 0, 0); glVertex3f(0, 2, 0);
    glColor3f(0,0,1 ); glVertex3f(0, 0, 0); glVertex3f(0, 0, 2);
    glEnd();

    glPopMatrix( );
    glutSwapBuffers( );
}



void myReshape(int width, int height)
{ 
    if(width/height<1) glViewport(0, 0, width, width);
    else glViewport(0, 0, height, height);
}

void myIdle( )
{ 
    angle+=0.5;
    if(angle > 360.0) angle=0;
    glutPostRedisplay( );
}

void myIdleStatic() { }

int main(int argc, char* argv[])

{ 
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("my window");
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(myReshape);

    glutIdleFunc(myIdle);
    init( );
    glutMainLoop();
    return 0;

}