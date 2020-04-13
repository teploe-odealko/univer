#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>
#include <stddef.h>
// #include <GL/glaux.h>
// #pragma comment(lib, "glaux.lib")
#include <stdio.h>
using namespace std;
GLfloat ratio = 4.0/3.0;
GLfloat angle = 0.0;
unsigned char header[54]; // Каждый BMP-файл начинается с заголовка, длиной в 54 байта
unsigned int dataPos;     // Смещение данных в файле (позиция данных)
unsigned int width, height;
unsigned int imageSize;   // Размер изображения = Ширина * Высота * 3
// RGB-данные, полученные из файла
unsigned char * data;

typedef struct _AUX_RGBImageRec {
   GLint sizeX, sizeY;
   unsigned char *data;
} AUX_RGBImageRec;

AUX_RGBImageRec loadBMP_custom(const char * imagepath)
{
    AUX_RGBImageRec image;

    FILE * file = fopen(imagepath,"rb");
    if (!file) 
    {
        printf("Изображение не может быть открытоn");
        return image;
    }
    if ( fread(header, 1, 54, file) != 54 ) 
    { // Если мы прочитали меньше 54 байт, значит возникла проблема
        printf("Некорректный BMP-файлn");
        return image;
    }
    if ( header[0]!='B' || header[1]!='M' )
    {
        printf("Некорректный BMP-файлn");
        return image;
    }
    
    // Читаем необходимые данные
    dataPos      = *(int*)&(header[0x0A]); // Смещение данных изображения в файле
    imageSize    = *(int*)&(header[0x22]); // Размер изображения в байтах
    image.sizeX = *(int*)&(header[0x12]); // Ширина
    image.sizeY = *(int*)&(header[0x16]); // Высота

    // Некоторые BMP-файлы имеют нулевые поля imageSize и dataPos, поэтому исправим их
    if (imageSize==0)    imageSize=width*height*3; // Ширину * Высоту * 3, где 3 - 3 компоненты цвета (RGB)
    if (dataPos==0)      dataPos=54; // В таком случае, данные будут следовать сразу за заголовком

    // Создаем буфер
    image.data = new unsigned char [imageSize];

    // Считываем данные из файла в буфер
    fread(image.data,1,imageSize,file);

    // Закрываем файл, так как больше он нам не нужен
    fclose(file);   
    return image;
}

void init()
{ 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();
    gluPerspective(60.0, ratio, 0.01f, 110.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 2.0, -2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    AUX_RGBImageRec brick = loadBMP_custom("brick.bmp");
    AUX_RGBImageRec water = loadBMP_custom("water.bmp");
    AUX_RGBImageRec cell = loadBMP_custom("cellcolony.bmp");
    // cout << "aaa" << endl;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, brick.sizeX, brick.sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, brick.data);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
}

void reshape(int width, int height)
{ 
    if (ratio > width/height) glViewport(0, 0, width, width/ratio);
    else glViewport(0, 0, height*ratio, height);
}

void display()

{ 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glRotatef(angle, 0.0, 1.0, 0.0);
    glBegin(GL_TRIANGLES);
    // грань 0
    glTexCoord2f(0, 0); glVertex3f(1, 0, 0);
    glTexCoord2f(0, 0.5); glVertex3f(0, 1, 0);
    glTexCoord2f(0.5, 0); glVertex3f(0, 0, 1);
    // грань 1
    glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
    glTexCoord2f(0, 1); glVertex3f(0, 1, 0);
    glTexCoord2f(0.5, 0); glVertex3f(1, 0, 0);
    // грань 2
    glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
    glTexCoord2f(1, 0); glVertex3f(0, 0, 1);
    glTexCoord2f(0, 1); glVertex3f(0, 1, 0);
    // грань 3
    glTexCoord2f(0, 0); glVertex3f(1, 0, 0);
    glTexCoord2f(0, 1); glVertex3f(0, 0, 1);
    glTexCoord2f(1, 0); glVertex3f(0, 0, 0);
    glEnd();
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void idle()
{ 
    angle += 0.5f;
    if (angle > 360.0) angle = 0.0;
    glutPostRedisplay();
}

int main(int argc, char* argv[])
{ 
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Пример текстурирования");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    init();
    glutMainLoop();
    return 0;

}