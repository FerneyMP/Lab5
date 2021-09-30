#ifndef PUERTA_H
#define PUERTA_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include <QPixmap>

class Puerta : public QObject, public QGraphicsPixmapItem //Herencia
{

public:
    Puerta();
    void set_imagen(int a); //Para escoger una imagen del recorte
    void set_scale(int a, int b); //función que me permite modificar la escala de una imagen

private:
    QPixmap door, imgn;
    int scalex = 1, scaley=1;
};

#endif // PUERTA_H
