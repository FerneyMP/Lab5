#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <bloques.h>
#include <QTimer>
#include <QKeyEvent>

#include "matriz.h"
#include "personaje.h"
#include "bomba.h"
#include "enemigo1.h"
#include "enemigo2.h"
#include "explosion.h"
#include "puerta.h"

//macro, constantes todo el tiempo, no ocupa tiempo ni espacio en ejecucion

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
    void set_window(); //ventana principal
    void generar_mapa(); //todos los elementos tipo bloques se carga en la interfaz
    void inicializar(); //inicializar matriz
    void keyPressEvent(QKeyEvent *tecla);//funcion ya establecida
    int generar_enemyX();
    int generar_enemyY();

/*private slots:
    void cambio();*/

private:
    Ui::MainWindow *ui;
    //se crean 31 bloques de flias y 13 de columnas
    //representan todos los elementos dentro del mapa
    bloques *puntaje,***mapa;
    QGraphicsScene *scene;
    QTimer *time;
    matriz *m;
    int **mat;
    personaje *personaje_;
    enemigo2 *enemy2, *enemy3;
    Puerta *door;

    int **matrixEnemy;
    int aleatorioX, aleatorioY;

};
#endif // MAINWINDOW_H
