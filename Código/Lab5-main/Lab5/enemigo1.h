#ifndef ENEMIGO1_H
#define ENEMIGO1_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include <QPixmap>
class enemigo1 : QObject, public QGraphicsPixmapItem //Herencia
{
public:
    enemigo1();
private:
    QPixmap enemy1;
};

#endif // ENEMIGO1_H
