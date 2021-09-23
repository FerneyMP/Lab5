#include "bomba.h"

bomba::bomba()
{
    bomb.load(":/new/prefix1/imagenes/bomba.png");
}

void bomba::set_imagen(int a)
{
    imgBom = bomb.copy(16*a,0,16,16);
    setPixmap(imgBom.scaled(scalex,scaley));
}

void bomba::set_scale(int a, int b)
{
    scalex=a; //cantidad de pixeles que quiero
    scaley=b;
}
