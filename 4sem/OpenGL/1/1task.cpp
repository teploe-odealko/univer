#include <GL/glut.h>

void init();
void draw();
int main(int argc, char **argv) { 
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(610, 610);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Myprog");
    init( );
    glutDisplayFunc(draw);
    glutMainLoop( );
    return 0;
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    gluOrtho2D(-300,300.0,-300,300.0);
}

void draw() { 
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glViewport(0, 0,  600, 600);


    glPointSize(3);
    glBegin(GL_POINTS);
    glVertex2f(-290 , 260.0); 
    glVertex2f(-280, 270); 
    glVertex2f(-270, 280.0); 
    glVertex2f(-260.0, 255.0); 
    glEnd( );

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(-230 , 260.0); 
    glVertex2f(-220, 270); 
    glVertex2f(-210, 280.0); 
    glVertex2f(-200.0, 255.0); 
    glEnd( );

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-170 , 260.0); 
    glVertex2f(-160, 270); 
    glVertex2f(-150, 280.0); 
    glVertex2f(-140.0, 255.0); 
    glEnd( );

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-170 , 260.0); 
    glVertex2f(-160, 270); 
    glVertex2f(-150, 280.0); 
    glVertex2f(-140.0, 255.0); 
    glEnd( );

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-110 , 260.0); 
    glVertex2f(-100, 270); 
    glVertex2f(-90, 280.0); 
    glVertex2f(-80.0, 255.0); 
    glEnd( );

    glColor3f(0.0, 1.0, 1.0);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(-290 , 200.0); 
    glVertex2f(-280, 180); 
    glVertex2f(-270, 200.0); 
    glVertex2f(-260, 180.0); 
    glVertex2f(-250, 193.0); 
    glVertex2f(-240, 185.0); 
    glEnd( );

    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-290 , 100.0); 
    glVertex2f(-260, 140); 
    glVertex2f(-240, 120.0); 
    glVertex2f(-230, 95.0); 
    glVertex2f(-240, 80.0); 
    glEnd( );
    glFlush( );


    glColor3f(1.0, 0.5, 1.0);
    glBegin(GL_QUADS);
    glVertex2f(-290 , 0.0); 
    glVertex2f(-250, 60); 
    glVertex2f(-240, 50.0); 
    glVertex2f(-280, -10.0); 
    glVertex2f(-220, -10.0); 
    glVertex2f(-170, 0.0); 
    glVertex2f(-180, 60.0); 
    glVertex2f(-220, 55.0); 
    glEnd( );
    glFlush( );

    glColor3f(0.5, 0.5, 1.0);
    glBegin(GL_QUAD_STRIP);
    glVertex2f(-90 , 0.0); 
    glVertex2f(-80, 66.0); 
    glVertex2f(-20, 0); 
    glVertex2f(-10, 66.0); 
    glVertex2f(30, -10.0); 
    glVertex2f(30, 35.0); 
    glVertex2f(70, -20.0); 
    glVertex2f(60, 60.0); 
    glEnd( );
    glFlush( );

    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_POLYGON);
    glVertex2f(110 , 0.0);
    glVertex2f(180, 0);
    glVertex2f(230, -10.0); 
    glVertex2f(270, -20.0);
    glVertex2f(260, 60.0);
    glVertex2f(230, 35.0); 
    glVertex2f(190, 66.0);
    glVertex2f(120, 66.0); 
     
    
    glEnd( );
    glFlush( );




}