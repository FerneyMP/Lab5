#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include <QPixmap>
class explosion : public QObject, public QGraphicsPixmapItem //Herencia
{
public:
    explosion();
    void set_imagen(int a);
    void set_scale(int a, int b);

private:
    QPixmap img, explosionVer, explosionHor;

    int scalex = 1, scaley=1;
};

#endif // EXPLOSION_H
