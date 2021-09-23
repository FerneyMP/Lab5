#include "puerta.h"

Puerta::Puerta()
{
    door.load(":/new/prefix1/imagenes/puerta.png");
}

void Puerta::set_imagen(int a)
{
    imgn = door.copy(16*a,0,16,16);
    setPixmap(imgn.scaled(scalex,scaley));
}

void Puerta::set_scale(int a, int b)
{
    scalex=a;
    scaley=b;
}
