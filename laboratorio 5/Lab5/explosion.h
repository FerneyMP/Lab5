#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include <QPixmap>
class explosion : QObject, public QGraphicsPixmapItem //Herencia
{
public:
    explosion();
private:
    QPixmap explosionVer, explosionHor;
};

#endif // EXPLOSION_H
