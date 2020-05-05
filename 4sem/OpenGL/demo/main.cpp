#include <GL/glut.h>
#include <cmath>
using namespace std;

//const double PI = 3.141592653589793238463;
const float  PI_F = 3.14159265358979f;

// Window size
int width = 512;
int height = 512;

// Points
const int nPoinst = 100;
const int halfOfNPoints = nPoinst / 2;
float points[nPoinst];

void DrawAxes();
void DrawSinX();
void GeneratePoints(int amountOfPoinst, float xMin, float xMax);
void Enable2D(int width, int height);

void Init()
{
    // setup scene to 2d mode and set draw color to white
    Enable2D(width, height);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    GeneratePoints(halfOfNPoints, -2*PI_F, 2*PI_F);
}

void GeneratePoints(int amountOfPoints, float xMin, float xMax)
{
    float step = abs((xMax - xMin) / (float)amountOfPoints);
    float xScaleCof = 40.0f;
    float yScaleCof = 100.0f;
    
    float x = xMin;
    for (int i = 0, index = 0; i < amountOfPoints; ++i, index += 2)
    {
        points[index] = x * xScaleCof;
        points[index + 1] = sin(x) * yScaleCof;
        x += step;
    }
}

void Draw()
{
    // clear (has to be done at the beginning)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    DrawAxes();
    DrawSinX();
    
    // Swap buffers (has to be done at the end)
    glutSwapBuffers();
}

void DrawSinX()
{
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 0.0f);
    for (int i = 0, index = 0; i < halfOfNPoints; ++i, index += 2)
    {
        glVertex2f(points[index], points[index + 1]);
    }
    glEnd();
}

void DrawAxes()
{
    // Draw X axis
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-width / 2.0f, 0.0f);
    glVertex2f(width / 2.0f, 0.0f);
    glEnd();
    
    // Draw Y axis
    glBegin(GL_LINES);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(0.0f, -height / 2.0f);
    glVertex2f(0.0f, height / 2.0f);
    glEnd();
}

void Enable2D(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Program entry point
int main(int argc, char** argv)
{
    // Initialize opengl (via glut)
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("Axes");
    
    glutDisplayFunc(Draw);
    
    Init();
    
    // Start the whole thing
    glutMainLoop();
    return 0;
}


