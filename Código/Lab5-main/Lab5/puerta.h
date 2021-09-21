#ifndef PUERTA_H
#define PUERTA_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include <QPixmap>
class Puerta : QObject, public QGraphicsPixmapItem //Herencia
{
public:
    Puerta();
private:
    QPixmap door;
};

#endif // PUERTA_H
