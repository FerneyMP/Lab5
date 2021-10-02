#include "enemigo1.h"

enemigo1::enemigo1()
{
    enemy1.load(":/imagenes/enemigo1.png");
    enemy1_muerte.load(":/imagenes/muerte_enemigo1.png");

    timer_muerteE= new QTimer;
    connect(timer_muerteE,SIGNAL(timeout()),this,SLOT(change_muerteE()));
}

void enemigo1::set_imagen(int a, int b)
{
    //16 es el ancho para mi recorte, al estar en una sola fila puedo moverme en x, ya que y siempre toma el valor de 0
    if (b==1) {
        imgn = enemy1.copy(16*a,0,16,16);

    }
    if (b==2){
        imgn = enemy1_muerte.copy(14*a,0,14,16);

    }
    setPixmap(imgn.scaled(scalex,scaley));  //se carga la imagen
}

void enemigo1::set_scale(int a, int b) //cantidad de pixeles
{
    scalex=a;
    scaley=b;
}

void enemigo1::activar_muerteE()
{
     timer_muerteE->start(350);
}

enemigo1::~enemigo1()
{

}

void enemigo1::change_muerteE()
{
    set_imagen(contadorME,2 );
    if (contadorME==3)  timer_muerteE->stop();
    contadorME++;
}


