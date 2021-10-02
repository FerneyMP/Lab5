#ifndef ENEMIGO2_H
#define ENEMIGO2_H
#include <QObject>
#include<QGraphicsPixmapItem>
#include <QPixmap>

class enemigo2 : public QObject, public QGraphicsPixmapItem //Herencia
{
public:

    enemigo2();
    void set_imagen(int a); //Para escoger una imagen del recorte
    void set_scale(int a, int b); //función que me permite modificar la escala de una imagen

private:

    QPixmap enemy2, imgn;
    int scalex = 1, scaley=1;
};

#endif // ENEMIGO2_H
