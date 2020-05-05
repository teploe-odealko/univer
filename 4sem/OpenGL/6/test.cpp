#include <GL/glut.h>
#include <math.h>
#include <math.h>
#include <stdio.h>
#include <iostream>

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



/*Структура для хранения заголовка файла изображения*/
struct Zagolovok
{
    GLint shirina; /*Ширина*/
    GLint vysota; /*Высота*/
    GLenum formatCveta; /*Формат представления цвета*/
    GLenum formatKomponenty; /*Формат данных компоненты цвета*/
    int kol_voKomponent; /*Количество компонент цвета*/
};

/*Структура для хранения изображения*/
struct Izobrajenie
{
    unsigned char *pikseli;
    Zagolovok zagolovok;
};

/*Функция чтения изображения из фалйа .kai*/
Izobrajenie *ChtenieIzobrajeniyaIzFaila(const char *szFileName)
{
    FILE *pFile; // Указатель файла
    Izobrajenie *iz=(Izobrajenie *)malloc(sizeof(Izobrajenie)); //Создание структуры для хранения изображения

    // Открытие файла
    pFile=fopen(szFileName, "rb");
    if(pFile == NULL) return NULL;

    // Считываем заголовок
    fread(&(iz->zagolovok), sizeof(Zagolovok), 1, pFile);

    //Создание массива для битов
    iz->pikseli=(unsigned char *)malloc(iz->zagolovok.shirina*iz->zagolovok.vysota*iz->zagolovok.kol_voKomponent);
    // Считывание битов
    fread(iz->pikseli, iz->zagolovok.shirina*iz->zagolovok.vysota*iz->zagolovok.kol_voKomponent, 1, pFile);
    // Работа с файлом завершается
    fclose(pFile);
    // Возвращает указатель на данные изображения
    return iz;
}

/*Функция записи изображения в файл .kai*/
GLint SohranenieIzobrajeniyaVfail(const char *szFileName)
{
    FILE *pFile; // Указатель файла

    //Создание структуры для хранения изображения
    Izobrajenie *iz=(Izobrajenie *)malloc(sizeof(Izobrajenie)); 

    GLint iViewport[4]; //Массив для хранения размеров порта просмотра

    // Получение размеров порта просмотра
    glGetIntegerv(GL_VIEWPORT, iViewport);

    // Считывание битов из буфера цвета
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ROW_LENGTH, 0);
    glPixelStorei(GL_PACK_SKIP_ROWS, 0);
    glPixelStorei(GL_PACK_SKIP_PIXELS, 0);

    // Переключение на передний буфер
    glReadBuffer(GL_FRONT);

    //Установка параметров изображения
    iz->zagolovok.shirina=iViewport[2];
    iz->zagolovok.vysota=iViewport[3];
    iz->zagolovok.formatCveta=GL_RGB;
    iz->zagolovok.formatKomponenty=GL_UNSIGNED_BYTE;
    iz->zagolovok.kol_voKomponent=3;

    //Выделение памяти для хранения битов

    iz->pikseli=(unsigned char *)malloc(iz->zagolovok.shirina*iz->zagolovok.vysota*iz->zagolovok.kol_voKomponent);

    //Чтение битов
    glReadPixels(0, 0, iz->zagolovok.shirina, iz->zagolovok.vysota, iz->zagolovok.formatCveta,iz->zagolovok.formatKomponenty, iz->pikseli);
    // Открытие файла
    pFile = fopen(szFileName, "wb");
    // Запись заголовка
    fwrite(&(iz->zagolovok), sizeof (Zagolovok), 1, pFile);
    // Запись данных об изображении
    fwrite(iz->pikseli, iz->zagolovok.shirina*iz->zagolovok.vysota*iz->zagolovok.kol_voKomponent, 1, pFile);
    //Закрытие файла
    fclose(pFile);
    // Успех
    return 1;
}


Izobrajenie *izobr; //Текущее изображение
Izobrajenie *izobr_bmp; //Изображение из файла .bmp
Izobrajenie *izobr_kai; //Изображение из файла .kai
Izobrajenie *izobr_ch_b; //Черно-белое изображение

//Переменная для хранения режима рисования
static GLint rejim = 1;
// Должным образом обновляем флаги в ответ на выбор позиции из меню
void ObrabotkaMenu(int punktMenu)
{
    // меняем индекс режима визуализации на индекс,
    // соответствующий позиции меню
    rejim = punktMenu;
    // Активизируем перерисовывание изображения glutPostRedisplay(); }
    glutPostRedisplay();
}
int k;
int iz=0;
void Pererisovka(void)
{
    GLint iViewport[4];
    //GLbyte *pModifiedBytes = NULL;
    GLfloat invertMap[256];
    GLint i;
    // Очищаем окно текущим цветом очистки
    glClear(GL_COLOR_BUFFER_BIT);
    // Текущее растровое положение всегда соответствует левому нижнему углу окна
    glRasterPos2i(0, 0);
    // В зависимости от индекса режима визуализации выполняются необходимые операции с изображением
    switch(rejim)
    {
    case 0: /*Очистка экрана*/
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        break;
    case 1: /*Загрузка изображения из файла *.bmp*/
        {
        AUX_RGBImageRec pImage=loadBMP_custom("256.bmp");
        izobr_bmp=(Izobrajenie *)malloc(sizeof(Izobrajenie));
        izobr_bmp->zagolovok.shirina=pImage.sizeX;
        izobr_bmp->zagolovok.vysota=pImage.sizeY;
        izobr_bmp->pikseli=pImage.data;
        izobr_bmp->zagolovok.formatCveta=GL_RGB;
        izobr_bmp->zagolovok.formatKomponenty=GL_UNSIGNED_BYTE;
        izobr_bmp->zagolovok.kol_voKomponent=3;
        izobr=izobr_bmp;
        }
        break;
    case 2: /*Сохранение текущего буфера в файл*/
        {
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        SohranenieIzobrajeniyaVfail("123.kai");
        }
        break;
    case 3: /*Загрузка изображения из собственного файла*/
        izobr_kai=ChtenieIzobrajeniyaIzFaila("123.kai");
        izobr=izobr_kai;
        break;
    case 4: /*Инверсия цветов*/
        invertMap[0] = 1.0f;
        for(i = 1; i < 256; i++)
        invertMap[i] = 1.0f - (1.0f / 255.0f * (GLfloat)i);
        glPixelMapfv(GL_PIXEL_MAP_R_TO_R, 255, invertMap);
        glPixelMapfv(GL_PIXEL_MAP_G_TO_G, 255, invertMap);
        glPixelMapfv(GL_PIXEL_MAP_B_TO_B, 255, invertMap);
        glPixelTransferi(GL_MAP_COLOR, GL_TRUE);
        break;
    case 5: /*Получение черно-белого изображения*/
        // Вначале рисуем изображение в буфере цвета
        glDrawPixels(izobr->zagolovok.shirina, izobr->zagolovok.vysota, izobr->zagolovok.formatCveta, izobr->zagolovok.formatKomponenty, izobr->pikseli); 
        //Распределяем память для карты яркости
        izobr_ch_b=(Izobrajenie *)malloc(sizeof(Izobrajenie));
        izobr_ch_b->zagolovok.shirina=izobr->zagolovok.shirina;
        izobr_ch_b->zagolovok.vysota=izobr->zagolovok.vysota;
        izobr_ch_b->zagolovok.formatCveta=GL_LUMINANCE;
        izobr_ch_b->zagolovok.formatKomponenty=GL_UNSIGNED_BYTE;
        izobr_ch_b->zagolovok.kol_voKomponent=1;
        izobr_ch_b->pikseli=(unsigned char *) malloc(izobr_ch_b
        ->zagolovok.shirina*izobr_ch_b->zagolovok.vysota*izobr_ch_b
        ->zagolovok.kol_voKomponent);

        // Масштабируем цвета согласно стандарту NTSC
        glPixelTransferf(GL_RED_SCALE, 0.3f) ;
        glPixelTransferf(GL_GREEN_SCALE, 0.59f);
        glPixelTransferf(GL_BLUE_SCALE, 0.11f) ;

        // Считываем пиксели в буфер
        glReadPixels(0,0,izobr_ch_b->zagolovok.shirina, izobr_ch_b->zagolovok.vysota, izobr_ch_b
        ->zagolovok.formatCveta,
        izobr_ch_b->zagolovok.formatKomponenty, izobr_ch_b->pikseli);
        izobr=izobr_ch_b;

        // Масштабирование цвета возвращается в норму
        glPixelTransferf(GL_RED_SCALE, 1.0f) ;
        glPixelTransferf(GL_GREEN_SCALE, 1.0f);
        glPixelTransferf(GL_BLUE_SCALE, 1.0f);
        break;
    case 6:
        glPixelZoom(0.5, 0.5);
        break;
    case 7:
        glPixelTransferf(GL_GREEN_SCALE, 0.0f);
        break;

    case 8:
        invertMap[0] = 1.0f;
        for(i = 1; i < 256; i++)
        invertMap[i] = 1.0f - (1.0f / 255.0f * (GLfloat)i);
        glPixelMapfv(GL_PIXEL_MAP_R_TO_R, 255, invertMap);
        // glPixelMapfv(GL_PIXEL_MAP_G_TO_G, 255, invertMap);
        glPixelMapfv(GL_PIXEL_MAP_B_TO_B, 255, invertMap);
        glPixelTransferi(GL_MAP_COLOR, GL_TRUE);
        break;

    default:
        break; 
    }
    if (rejim!=0)
    // Рисуются пиксели
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glDrawPixels(izobr->zagolovok.shirina, izobr->zagolovok.vysota, izobr
        ->zagolovok.formatCveta, izobr->zagolovok.formatKomponenty, izobr->pikseli);
    }
    //Переключает буферы
    glutSwapBuffers();
}

void IzmenenieRazmera(int w, int h)
{
    //Предотвращает деление на ноль, когда окно слишком маленькое
    if (h==0)
    h=1;
    glViewport(0,0,w,h);
    //Система координат обновляется перед модификацией
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}


//Точка входа основной программы
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB|GL_DOUBLE);
    glutInitWindowSize(512,512);
    glutCreateWindow("Pixels operations");
    glutReshapeFunc(IzmenenieRazmera);
    glutDisplayFunc(Pererisovka);
    //Создается меню и добавляются опции выбора
    glutCreateMenu(ObrabotkaMenu);
    glutAddMenuEntry("Clear the display", 0);
    glutAddMenuEntry("load image .bmp", 1);
    glutAddMenuEntry("Save current image", 2);
    glutAddMenuEntry("Load image from .kai file", 3);
    glutAddMenuEntry("Color inversion", 4);
    glutAddMenuEntry("only black and white", 5);
    glutAddMenuEntry("reduce the size of images by 2 times", 6);
    glutAddMenuEntry("Show only R, B components", 7);
    glutAddMenuEntry("inversion R, B components", 8);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    gluOrtho2D(0,512,0,512);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    rejim=1;
    glutMainLoop();
    // Освобождаем исходные данные изображений
    free(izobr);
    free(izobr_ch_b);
    free(izobr_kai);
    free(izobr_bmp);
    // free(pImage);
    return 0;
}