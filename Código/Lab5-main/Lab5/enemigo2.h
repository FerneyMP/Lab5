#ifndef ENEMIGO2_H
#define ENEMIGO2_H
#include <QObject>
#include<QGraphicsPixmapItem>
#include <QPixmap>

class enemigo2 : QObject, public QGraphicsPixmapItem //Herencia
{
public:
    enemigo2();
private:
    QPixmap enemy2;
};

#endif // ENEMIGO2_H
