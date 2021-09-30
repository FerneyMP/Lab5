#ifndef ENEMIGO1_H
#define ENEMIGO1_H
#include <QObject>
#include<QGraphicsPixmapItem>
#include <QPixmap>

class enemigo1 : public QObject, public QGraphicsPixmapItem //Herencia
{
public:
    enemigo1();
    void set_imagen(int a); //Para escoger una imagen del recorte
    void set_scale(int a, int b); //función que me permite modificar la escala de una imagen
private:
    QPixmap enemy1, imgn;
    int scalex = 1, scaley=1;

/*public slots:
    change_enemy();    */

};

#endif // ENEMIGO1_H




