#include "enemigo2.h"

enemigo2::enemigo2()
{
    enemy2.load(":/imagenes/enemigo2.png");
}

void enemigo2::set_imagen(int a)
{
    imgn = enemy2.copy(16*a,0,16,16);
    setPixmap(imgn.scaled(scalex,scaley));
}

void enemigo2::set_scale(int a, int b) //cantidad de pixeles
{
    scalex=a;
    scaley=b;
}
