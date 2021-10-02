#ifndef BLOQUES_H
#define BLOQUES_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include <QPixmap>

class bloques : public QObject, public QGraphicsPixmapItem //Herencia
{

public:

    bloques();
    void set_imagen(int a); //Para escoger una imagen del recorte
    void set_scale(int a, int b); //función que me permite modificar la escala de una imagen

private:

    QPixmap original, img; //  crear objetos QPixmap (imagen original, imagen a cargar en la intefaz)
    int scalex = 1, scaley=1;
};

#endif // BLOQUES_H
