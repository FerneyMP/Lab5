#include "personaje.h"

personaje::personaje()
{
    Pprincipal.load(":/new/prefix1/imagenes/personaje.png");
    Principal_right_back.load(":/new/prefix1/imagenes/personaje_sec2.png");
    Principal_death.load(":/new/prefix1/imagenes/personaje_sec3.png");
}

void personaje::set_imagen(int a,int b)
{
    if (b==1){

        //12 es el ancho para mi recorte, al estar en una sola fila puedo moverme en x, ya que y siempre toma el valor de 0
        imgn = Pprincipal.copy(12*a,0,12,16);

        //se carga la imagen
        setPixmap(imgn.scaled(scalex,scaley));
    }
    if (b==2){
        imgn= Principal_right_back.copy(12*a,0,12,16);
        setPixmap(imgn.scaled(scalex,scaley));

    }
    if (b==3) {
        imgn= Principal_death.copy(12*a,0,12,16);
        setPixmap(imgn.scaled(scalex,scaley));
    }

}

void personaje::set_scale(int a, int b) //cantidad de pixeles
{
    scalex=a;
    scaley=b;
}

void personaje::change(char Tecla)
{
       if (Tecla=='s'){
          set_imagen(contador+3,1);
          if (contador==2) contador=-1;
       }
       if (Tecla=='a'){
          set_imagen(contador,1);
          if (contador==2) contador=-1;
       }
       if (Tecla=='w'){
          set_imagen(contador+3,2);
          if (contador==2) contador=-1;
       }
       if (Tecla=='d'){
          set_imagen(contador,2);
          if (contador==2) contador=-1;
       }
       contador++;

}
