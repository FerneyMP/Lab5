#include "explosion.h"

explosion::explosion()
{
    explosionHor.load(":/imagenes/explosion_horizontal.png");
    explosionVer.load(":/imagenes/explosion_vertical.png");
}

void explosion::set_imagen(int a)
{
    if (a<=2){
    img = explosionHor.copy(16*a,0,16,16);

    }
    else {
    img = explosionVer.copy(0,16*(a-3),16,16);

    }
    setPixmap(img.scaled(scalex,scaley));

}

void explosion::set_scale(int a, int b)
{
    scalex=a; //cantidad de pixeles que quiero
    scaley=b;
}
