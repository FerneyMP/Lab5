#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include <QPixmap>
#include <QTimer>

class personaje : public QObject, public QGraphicsPixmapItem
{
     Q_OBJECT

public:

    personaje();
    void set_imagen(int a, int b); //Para escoger una imagen del recorte
    void set_scale(int a, int b); //función que me permite modificar la escala de una imagen
    void change (char Tecla);
    void activar_muerteP();
    QTimer *timer_muerteP;
    ~personaje();

private:

    QPixmap Pprincipal, Principal_right_back, Principal_death,imgn,imgn2;
    int scalex = 1, scaley=1;
    int contador=0;//mov

public slots:
    void change_muerteP();

};

#endif // PERSONAJE_H
