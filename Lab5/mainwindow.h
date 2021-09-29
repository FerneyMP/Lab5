#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QGraphicsScene>
#include <bloques.h>
//#include <QTimer>
#include <QKeyEvent>
#include <QList>

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
#define cantidad_enemigos 10


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void change (); //cambio de imagen para el movimiento de la bomba
    void change_enemies (); //cambio de imagen para el movimiento de los enemigos
    void erase (int x, int y);

    void movimientos_enemigos();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void set_window(); //ventana principal
    void generar_mapa(); //todos los elementos tipo bloques se carga en la interfaz
    void inicializar(); //inicializar matriz
    void keyPressEvent(QKeyEvent *tecla);//funcion ya establecida
    int generar_enemyX();
    int generar_enemyY();


private:
    Ui::MainWindow *ui;
    //se crean 31 bloques de flias y 13 de columnas
    //representan todos los elementos dentro del mapa

    bloques *puntaje,***mapa;
    QGraphicsScene *scene;
    matriz *m;
    int **mat;
    personaje *personaje_;
    enemigo1 *enemy1[cantidad_enemigos];
    enemigo2 *enemy2[cantidad_enemigos];
    Puerta *door;

    int **matrixEnemy;
    int aleatorioX, aleatorioY;
    bomba *bombX;

    int contador=0; // mov

    QTimer *timer;
    //
    int desplazamientoX=0, desplazamientoY=0;
    QTimer *time;

};
#endif // MAINWINDOW_H
