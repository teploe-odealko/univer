
#include<GL/glut.h>
#include <math.h>

void init();
void draw();

//------------------------
//	Главная функция
//------------------------
int main(int argc, char **argv)
{
	glutInit(&argc, argv); // инициализация библиотеки GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // устанавливается режим дисплея: использовать один буфер для кадра; цвета представлять как смесь RGB.
	glutInitWindowSize(640, 480); // установка размеров window
	glutInitWindowPosition(50, 50); // установка положения window
	glutCreateWindow("Myprog"); // инициализируется открытие экранного окна window
	init();
	glutDisplayFunc(draw); // функция draw( ) регистрируется как функция обратного вызова для события открытия или обновления экранного окна
	glutMainLoop(); // переводит программу в бесконечный цикл ожидания события
	return 0;
}
//---------------------------------
//	Функция инициализации
//---------------------------------
void init()
{
	glClearColor(0.9, 0.9, 1.9, 0.0);
	glMatrixMode(GL_PROJECTION); // в качестве текущей устанавливается матрица проецирования
	glLoadIdentity(); // текущая матрица устанавливается в единицу
	gluOrtho2D(-8.0, 8.0, -2.0, 2.0);//создание мирового окна
}
//---------------------------------
//	Функция рисования
//---------------------------------
void draw()
{
	GLfloat PI = 3.14, x = 1, y = 1, w = 1.2, A = 1.2, B = 1.8;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.2, 0.0);
	glViewport(10, 10, 600, 400);	//создание порта просмотра
	//glViewport(0, 0, 640, 480);
	//вывод графиков функции x(t) = Asin(wt); y(t) = Bcos(wt)       
	glBegin(GL_LINE_STRIP);
	for (x = -2 * PI - 2; x <= 2 * PI + 2; x += PI / 18)
	{
		y = x*x*x + x*x + x;
		glVertex2f(x, y);

	}
	glEnd();

	// glColor3f(1.0, 0.4, 1.1);
	// glBegin(GL_LINE_STRIP);
	// for (x = -2 * PI - 2; x <= 2 * PI + 2; x += PI / 18)
	// {
	// 	y = B*cos(w*x);
	// 	glVertex2f(x, y);

	// }
	// glEnd();



	// рисование осей
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex2f(-8.0, 0.0); glVertex2f(8.0, 0.0);
	glVertex2f(0.0, 2.0); glVertex2f(0.0, -2.0);
	glEnd();
	glFlush(); // принудительное выполнение накопленных команд OpenGL. Различные реализации OpenGL буферизируют команды в нескольких различных местах. Команда glFlush() освобождает все эти буферы, заставляя все вызванные команды выполниться
}
