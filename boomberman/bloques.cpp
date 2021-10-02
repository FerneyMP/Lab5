#include "bloques.h"

bloques::bloques()
{
    original.load(":/imagenes/bloques.png"); //cargar imagen en el constructor a partir de la direccion
}

void bloques::set_imagen(int a)
{
   //Proceso de recorte
    //pixeles                     x  ,y, numero de pixeles a tomar
    if (a==8) img = original.copy(126,13,1,1); //Se captura solo ese pedazo del recorte de bloques  //parte verde del fondo

    else if(a==9) img = original.copy(0,0,1,1); //parte gris

    else img = original.copy(16*a,0,16,16);//se mueve en multiplos de 16

    //Se carga la imagen y se escala
    setPixmap(img.scaled(scalex,scaley)); //scaled retorna una imagen con una cantidad x,y de pixeles que se desea
}

//Modificar el tamaño de mi imagen
void bloques::set_scale(int a, int b)
{
    scalex=a; //cantidad de pixeles que quiero
    scaley=b;

}
