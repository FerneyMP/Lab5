#include "enemigo1.h"

enemigo1::enemigo1()
{
    enemy1.load(":/imagenes/enemigo1.png");
}

void enemigo1::set_imagen(int a)
{
    //16 es el ancho para mi recorte, al estar en una sola fila puedo moverme en x, ya que y siempre toma el valor de 0
    imgn = enemy1.copy(16*a,0,16,16);
    setPixmap(imgn.scaled(scalex,scaley));  //se carga la imagen
}

void enemigo1::set_scale(int a, int b) //cantidad de pixeles
{
    scalex=a;
    scaley=b;
}


