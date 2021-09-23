#ifndef BOMBA_H
#define BOMBA_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include <QPixmap>
class bomba : QObject, public QGraphicsPixmapItem //Herencia
{
public:
    bomba();
    void set_imagen(int a); //Para escoger una imagen del recorte
    void set_scale(int a, int b); //función que me permite modificar la escala de una imagen
private:
    QPixmap bomb, imgBom;
    int scalex = 1, scaley=1;
};

#endif // BOMBA_H
