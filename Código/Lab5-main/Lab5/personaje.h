#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include <QPixmap>

class personaje : QObject, public QGraphicsPixmapItem
{
public:
    personaje();
    void set_imagen(int a); //Para escoger una imagen del recorte
    void set_scale(int a, int b); //función que me permite modificar la escala de una imagen
private:
    QPixmap Pprincipal, Principal_right_back, Principal_death,imgn;
    int scalex = 1, scaley=1;
};

#endif // PERSONAJE_H
