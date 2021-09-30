#ifndef BOMBA_H
#define BOMBA_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include <QPixmap>
#include <QTimer>

class bomba : public QObject, public QGraphicsPixmapItem //Herencia
{

  Q_OBJECT

public:
    bomba();
    void set_imagen(int a); //Para escoger una imagen del recorte
    void set_scale(int a, int b); //función que me permite modificar la escala de una imagen
    void activar(); //funcion para activar el timer de la bomba para el cambio de imagen
    QTimer *timer;
    ~bomba();

private:
    QPixmap bomb, imgBom;
    int scalex = 1, scaley=1;
    int contador=0; // contador para el movimiento

public slots:
    void change(); //cambio de imagen
};

#endif // BOMBA_H
