#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
using namespace std;

GLfloat angle=0;
GLuint list = 0;
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


void init(void)
{ 
    glClearColor(1.0, 1.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    gluPerspective(60, 1, 1, 10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity( );

    AUX_RGBImageRec brick = loadBMP_custom("brick.bmp");
    glBindTexture(GL_TEXTURE_2D, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, brick.sizeX, brick.sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, brick.data);

    AUX_RGBImageRec water = loadBMP_custom("grass.bmp");
    glBindTexture(GL_TEXTURE_2D, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, water.sizeX, water.sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, water.data);

    AUX_RGBImageRec cell = loadBMP_custom("cellcolony.bmp");
    glBindTexture(GL_TEXTURE_2D, 2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, cell.sizeX, cell.sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, cell.data);
    
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);


    list = glGenLists(1); //Генерация незадействованного индекса списка
    glNewList(list, GL_COMPILE); //Создание списка и накопление команд

    // glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, -1);
    glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
    glTexCoord2f(0, 1); glVertex3f(2, 1, 0);
    glTexCoord2f(1, 0); glVertex3f(2, -1, 0);
    glEnd();
    // грань f1
    // glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1);
    glTexCoord2f(0, 0); glVertex3f(0.5, 0, 1);
    glTexCoord2f(0, 1); glVertex3f(1.5, 0.5, 1);
    glTexCoord2f(1, 0); glVertex3f(1.5, -0.5, 1);
    glEnd();
    // // грань f2
    // glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 2);
    glBegin(GL_POLYGON);
    glNormal3f(1, 2, 0.5);
    glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
    glTexCoord2f(0, 1); glVertex3f(2, 1, 0);
    glTexCoord2f(1, 1); glVertex3f(1.5, 0.5, 1);
    glTexCoord2f(1, 0); glVertex3f(0.5, 0, 1);

    glEnd();
    // грань f3
    glBindTexture(GL_TEXTURE_2D, 1);
    glBegin(GL_POLYGON);
    glNormal3f(0, -1, 0);
    glTexCoord2f(0, 0); glVertex3f(2, -1, 0);
    glTexCoord2f(0, 1); glVertex3f(1.5, -0.5, 1);
    glTexCoord2f(1, 1); glVertex3f(1.5, 0.5, 1);
    glTexCoord2f(1, 0); glVertex3f(2, 1, 0);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 2);
    glBegin(GL_POLYGON);
    glNormal3f(0, -1, 0);
    glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
    glTexCoord2f(0, 1); glVertex3f(0.5, 0, 1);
    glTexCoord2f(1, 1); glVertex3f(1.5, -0.5, 1);
    glTexCoord2f(1, 0); glVertex3f(2, -1, 0);
    glEnd();

    glEndList(); //Завершение накопления команд в списке
    // glDisable(GL_TEXTURE_2D);
    

}

void myDisplay( )

{ 
    glPushMatrix( ); //Сохраняем VM = 1

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    gluLookAt(1, 3, 3, 1, 0, 0, 0, 1, 0); // VM=Fwe
    GLfloat myLightPosition[] = {3.0, 3.0, 3.0, 1.0}; // Источник света в CK
    glLightfv(GL_LIGHT0, GL_POSITION, myLightPosition);

    GLfloat myAmbient[] = {0.19125, 0.0735, 0.0225, 1};
    GLfloat myDiffuse[] = {0.7038, 0.27048, 0.0828, 1};
    GLfloat mySpecular[] = {0.256777, 0.137622, 0.086014, 1};
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, myAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, myDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, mySpecular);
    glLightf(GL_LIGHT0, GL_SHININESS, 12.8);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glPushMatrix(); //Сохраняем VM=Fwe
        glRotatef(angle, 1, 0, 0); // VM=Fwe*R
        glCallList(list); //Вызов списка накопленных ранее команд
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

void myIdleMove( )
{ 
    angle+=2;
    if(angle > 360.0) angle=0;
    glutPostRedisplay( );
}

void myIdleStatic() { }

void onKeyboard(unsigned char key, int a, int b){
    cout << a << " " << b << endl;
    if (key == 'X'){
        glutIdleFunc(myIdleStatic);

    } else if (key == 'x'){
        glutIdleFunc(myIdleMove);
    }
    glutPostRedisplay( );

}

void onMouse(int button, int state, int x, int y){
    cout << x << " " << y << " " << state << endl;
    if(button == GLUT_LEFT_BUTTON){
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    } else if ( button == GLUT_RIGHT_BUTTON){
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
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

    glutMouseFunc(onMouse);
    glutKeyboardFunc(onKeyboard);

    glutIdleFunc(myIdleStatic);
    init( );
    glutMainLoop();
    return 0;

}