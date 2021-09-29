#include "personaje.h"

personaje::personaje()
{
    Pprincipal.load(":/../../../Lab 5/Personaje_Principal/personaje.png");
    Principal_right_back.load(":/../../../Lab 5/Personaje_Principal/personaje_sec2.png");
    Principal_death.load(":/../../../Lab 5/Personaje_Principal/personaje_sec3.png");
}

void personaje::set_imagen(int a)
{
    //16 es el ancho para mi recorte, al estar en una sola fila puedo moverme en x, ya que y siempre toma el valor de 0
    imgn = Pprincipal.copy(16*a,0,16,16);
    //se carga la imagen


    setPixmap(imgn.scaled(scalex,scaley));
}

void personaje::set_scale(int a, int b) //cantidad de pixeles
{
    scalex=a;
    scaley=b;
}
