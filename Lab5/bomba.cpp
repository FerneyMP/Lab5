#include "bomba.h"

bomba::bomba()
{
    bomb.load(":/new/prefix1/imagenes/bomba.png");

    /*timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(change())); AQUI PQ NO SIRVE?
    timer-> start (1000);*/

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

/*void bomba::change()
{
    set_imagen(contador+1);
    if (contador==2) contador=-1;
    contador++;

}*/
