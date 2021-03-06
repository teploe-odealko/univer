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
    gluLookAt(2, 6, 6, 0, 0, 0, 0, 1, 0); // VM=Fwe
    GLfloat myLightPosition[] = {3.0, 3.0, 3.0, 1.0}; // Источник света в CK
    glLightfv(GL_LIGHT0, GL_POSITION, myLightPosition);

    GLfloat myAmbient[] = {0.19125, 0.0735, 0.0225, 1};
    GLfloat myDiffuse[] = {0.7038, 0.27048, 0.0828, 1};
    GLfloat mySpecular[] = {0.256777, 0.137622, 0.086014, 1};
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, myAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, myDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, mySpecular);
    glLightf(GL_LIGHT0, GL_SHININESS, 12.8);
    // glPushMatrix();
    //     glRotatef(angle, 0, 1, 0); // вращаем источник света
    //     // glTranslatef(); // перемещаем источник света
    //     glLightfv(GL_LIGHT0, GL_POSITION, myLightPosition);

    //     glBegin(GL_LINES);
    //         glColor3f(1,1,1); glVertex3f(3, 3, 3); glVertex3f(0.0, 0.0, 0.0);
    //     glEnd();
    // glPopMatrix();
    // glBegin(GL_LINES);
    //     glColor3f(1,1,1); glVertex3f(3, 3, 3); glVertex3f(0.0, 0.0, 0.0);
    // glEnd();

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glPushMatrix(); //Сохраняем VM=Fwe
    glRotatef(angle, 1, 0, 0); // VM=Fwe*R
    // glRotatef(angle, 0, 1, 0); // VM=Fwe*R*R
    // glRotatef(angle, 0, 0, 1); // VM=Fwe*R*R*R

    glBegin(GL_POLYGON);

    glNormal3f(0, 0, -1);
    glVertex3f(0, 0, 0);
    glVertex3f(2, 1, 0);
    glVertex3f(2, -1, 0);
    glEnd();
    // грань f1
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1);
    glVertex3f(0.5, 0, 1);
    glVertex3f(1.5, 0.5, 1);
    glVertex3f(1.5, -0.5, 1);
    glEnd();
    // // грань f2
    glBegin(GL_POLYGON);
    glNormal3f(1, 2, 0.5);
    glVertex3f(0, 0, 0);
    glVertex3f(2, 1, 0);
    glVertex3f(1.5, 0.5, 1);
    glVertex3f(0.5, 0, 1);

    glEnd();
    // грань f3
    glBegin(GL_POLYGON);
    glNormal3f(0, -1, 0);
    glVertex3f(2, -1, 0);
    glVertex3f(1.5, -0.5, 1);
    glVertex3f(1.5, 0.5, 1);
    glVertex3f(2, 1, 0);
    glEnd();


    glBegin(GL_POLYGON);
    glNormal3f(0, -1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0.5, 0, 1);
    glVertex3f(1.5, -0.5, 1);
    glVertex3f(2, -1, 0);
    glEnd();

    glPopMatrix( ); // Восстанавливаем VM=Fwe
    glDisable(GL_LIGHTING); //Выключаем освещение

    
    glBegin(GL_LINES);
    glColor3f(1,0,0 ); glVertex3f(0, 0, 0); glVertex3f(2, 0, 0);
    glColor3f(0,1,0 ); glVertex3f(0, 0, 0); glVertex3f(0, 2, 0);
    glColor3f(0,0,1 ); glVertex3f(0, 0, 0); glVertex3f(0, 0, 2);
    glEnd();


    // glBegin(GL_LINES);
    // glColor3f(1,1,1); glVertex3f(3, 3, 3); glVertex3f(0.0, 0.0, 0.0);
    // glEnd();
    // glPopMatrix( );
    glutSwapBuffers( );
}



void myReshape(int width, int height)
{ 
    if(width/height<1) glViewport(0, 0, width, width);
    else glViewport(0, 0, height, height);
}

void myIdleMove( )
{ 
    angle+=2;
    if(angle > 360.0) angle=0;
    glutPostRedisplay( );
}

void myIdleStatic() { }

void onKeyboard(unsigned char key, int, int){
    if (key == 'X'){
        glutIdleFunc(myIdleStatic);

    } else if (key == 'x'){
        glutIdleFunc(myIdleStatic);
    }
    glutPostRedisplay( );

}

int main(int argc, char* argv[])

{ 
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("my window");
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(myReshape);

    glutKeyboardFunc(onKeyboard);
    // glutMouseFunc(onMouse);

    glutIdleFunc(myIdleStatic);
    init( );
    glutMainLoop();
    return 0;

}