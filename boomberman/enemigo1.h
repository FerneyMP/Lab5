#ifndef ENEMIGO1_H
#define ENEMIGO1_H
#include <QObject>
#include<QGraphicsPixmapItem>
#include <QPixmap>
#include <QTimer>

class enemigo1 : public QObject, public QGraphicsPixmapItem //Herencia
{
     Q_OBJECT

public:

    enemigo1();
    void set_imagen(int a, int b); //Para escoger una imagen del recorte
    void set_scale(int a, int b); //función que me permite modificar la escala de una imagen
    void activar_muerteE();
    QTimer *timer_muerteE;
    ~enemigo1();

private:

    QPixmap enemy1, imgn, enemy1_muerte;
    int scalex = 1, scaley=1;
    int contadorME=0;//muerte

public slots:
    void change_muerteE();

};

#endif // ENEMIGO1_H




