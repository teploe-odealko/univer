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

void myDisplayIcos( )

{ 
    glPushMatrix( ); //Сохраняем VM = 1
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    gluLookAt(3, 2, 1, 0, 0, 0, 0, 1, 0); // VM=Fwe
    GLfloat myLightPosition[] = {3.0, 3.0, 3.0, 1.0}; // Источник света в CKw
    glLightfv(GL_LIGHT0, GL_POSITION, myLightPosition); /*Позиция ис-точника света будет преобразована в CKe*/
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glPushMatrix(); //Сохраняем VM=Fwe
    glRotatef(angle, 1, 0, 0); // VM=Fwe*R
    // glRotatef(angle, 0, 1, 0); // VM=Fwe*R*R
    // glRotatef(angle, 0, 0, 1); // VM=Fwe*R*R*R

    glutSolidIcosahedron ();

    glPopMatrix( ); // Восстанавливаем VM=Fwe
    glDisable(GL_LIGHTING); //Выключаем освещение
    glBegin(GL_LINES);
    glColor3f(1,0,0 ); glVertex3f(0, 0, 0); glVertex3f(2, 0, 0);
    glColor3f(0,1,0 ); glVertex3f(0, 0, 0); glVertex3f(0, 2, 0);
    glColor3f(0,0,1 ); glVertex3f(0, 0, 0); glVertex3f(0, 0, 2);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1,1,1); glVertex3f(3, 3, 3); glVertex3f(0.0, 0.0, 0.0);
    glEnd();
    glPopMatrix( );
    glutSwapBuffers( );
}

void myDisplayDodec( )

{ 
    glPushMatrix( ); //Сохраняем VM = 1
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    gluLookAt(3, 2, 1, 0, 0, 0, 0, 1, 0); // VM=Fwe
    GLfloat myLightPosition[] = {3.0, 3.0, 3.0, 1.0}; // Источник света в CKw
    glLightfv(GL_LIGHT0, GL_POSITION, myLightPosition); /*Позиция ис-точника света будет преобразована в CKe*/
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glPushMatrix(); //Сохраняем VM=Fwe
    glRotatef(angle, 1, 0, 0); // VM=Fwe*R
    // glRotatef(angle, 0, 1, 0); // VM=Fwe*R*R
    // glRotatef(angle, 0, 0, 1); // VM=Fwe*R*R*R

    glutSolidDodecahedron ();

    glPopMatrix( ); // Восстанавливаем VM=Fwe
    glDisable(GL_LIGHTING); //Выключаем освещение
    glBegin(GL_LINES);
    glColor3f(1,0,0 ); glVertex3f(0, 0, 0); glVertex3f(2, 0, 0);
    glColor3f(0,1,0 ); glVertex3f(0, 0, 0); glVertex3f(0, 2, 0);
    glColor3f(0,0,1 ); glVertex3f(0, 0, 0); glVertex3f(0, 0, 2);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1,1,1); glVertex3f(3, 3, 3); glVertex3f(0.0, 0.0, 0.0);
    glEnd();
    glPopMatrix( );
    glutSwapBuffers( );
}

void myReshape(int width, int height)
{ 
    if(width/height<1) glViewport(0, 0, width, width);
    else glViewport(0, 0, height, height);
}

void myIdleMove( )
{ 
    angle+=0.5;
    if(angle > 360.0) angle=0;
    glutPostRedisplay( );
}

void myIdleStatic() { }

void onKeyboard(unsigned char key, int x, int){
    if (key == 'X'){
        glutIdleFunc(myIdleStatic);

    } else if (key == 'x'){
        glutIdleFunc(myIdleMove);
    }
    glutPostRedisplay( );

}

void onMouse(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON){
        glutDisplayFunc(myDisplayDodec);

    } else if ( button == GLUT_RIGHT_BUTTON){
        glutDisplayFunc(myDisplayIcos);
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
    glutDisplayFunc(myDisplayIcos);
    glutReshapeFunc(myReshape);

    glutKeyboardFunc(onKeyboard);
    glutMouseFunc(onMouse);

    glutIdleFunc(myIdleStatic);
    init( );
    glutMainLoop();
    return 0;

}