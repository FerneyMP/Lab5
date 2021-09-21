#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <bloques.h>
#include <QTimer>

#include "matriz.h"
#include "personaje.h"
#include "bomba.h"
#include "enemigo1.h"
#include "enemigo2.h"
#include "explosion.h"
#include "puerta.h"

//macro, constantes todo el tiempo
//DIMENSIONES DE MI MAPA:
#define filas 13 //para el mapa
#define columnas 31 //tamaño del mapa fil y col
#define tam 50 //50 pixeles

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void set_window();
    void generar_mapa();
    void inicializar();
/*private slots:
    void cambio();*/

private:
    Ui::MainWindow *ui;
    //se crean 31 bloques de flias y 13 de columnas
    //representan todos los elementos dentro del mapa
    bloques *puntaje, *puntaje_,***mapa;
    QGraphicsScene *scene;
    QTimer *time;
    matriz *m;
    int **mat;
    personaje *personaje_;
    enemigo2 *enemy2;
};
#endif // MAINWINDOW_H
