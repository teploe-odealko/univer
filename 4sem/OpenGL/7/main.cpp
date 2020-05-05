#include <GL/glut.h>
#include <cmath>
#include <math.h>
#include <iostream>
using namespace std;


GLdouble X = 0, Y = 0, a, b, c, sp;

void init();
void draw();

//Главная функция
int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");
    cout << "Введите параметры для уравнения y = -ay\n";
    cout << "a = ";
    cin >> a;
    cout << "\nКаким способом (1 или 2) построить график? ";
    cin >> sp;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Работа с растром");
    init();
    glutDisplayFunc(draw);
    glutMainLoop();
}

//Функция инициализации
void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
}

//Функция рисования
void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(50, 50, 540, 540); //создание порта просмотра
    
    // рисование осей
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(-100.0, 0.0); glVertex2f(100.0, 0.0);
    glVertex2f(0.0, 100.0); glVertex2f(0.0, -100.0);
    glEnd();
    
    if (sp==1) {
        // Дуга окружности во второй четверти (1 способ)
        GLdouble X2 = 50*a, Y2 = -50;
        glColor3f(1.0, 0.0, 1.0);
        X = -50*a; Y = 50; // координаты растра
        glBegin(GL_LINE_STRIP);
        while (X < X2 && Y > Y2) {
            // glVertex2f(X, Y);
            if (X + a*Y < 0) {
                X = X + 1;
                
                
                glVertex2f(X, Y);
            }
            else if (X + a*Y > 0) {
                Y = Y - 1;
                glVertex2f(X, Y);
            }
            else {
                if (X > Y) X = X + 1;
                else Y = Y - 1;
                glVertex2f(X, Y);
            }
        }
        glEnd();
    } else {
        // Дуга окружности во второй четверти (2 способ)
        glColor3f(1.0, 0.0, 1.0);
        GLfloat X2 = 50*a, Y2 = -50, dX, dY;
        X = -50*a; Y = 50; // координаты растра
        glBegin(GL_LINE_STRIP);
        glVertex2f(X, Y);
        while (X < X2 && Y > Y2) {
            dX= (-a / sqrt(1 + a*a));
            dY= (1 / sqrt(1 + a*a));
            Y=Y-dY;
            X=X-dX;
            glVertex2f(X, Y);

        }

        glEnd();

    }
    glFlush();
    
}
