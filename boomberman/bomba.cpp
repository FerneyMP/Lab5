#include "bomba.h"

bomba::bomba()
{
    bomb.load(":/imagenes/bomba.png");
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(change()));//change, funcion para cambiar de imagen y generar el mov
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

void bomba::activar()
{
    timer-> start (250);//para palpitar
}

bomba::~bomba()
{

}

void bomba::change()
{
    set_imagen(contador);
    if (contador==2) contador=-1;
    contador++;
}

