#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QGraphicsScene>
#include <bloques.h>
#include <QTimer>
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
#define columnas 31 //tamaño del mapa fil y col 31
#define tam 50 //50 pixeles
#define cantidad_enemigos 10


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void change(); //cambio de imagen para el movimiento de la bomba
    void change_enemies(); //cambio de imagen para el movimiento de los enemigos
    void erase(); //borrar bomba
    void movimientos_enemigos();
    void erase_explosion(); //borrar explosion

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void set_window(); //ventana principal
    void generar_mapa(); //todos los elementos tipo bloques se carga en la interfaz
    void inicializar(); //inicializar matriz
    void keyPressEvent(QKeyEvent *tecla);//funcion ya establecida
    void generar_enemy(enemigo1 *enemigo);
    void generar_movimientos_enemigos();


private:
    Ui::MainWindow *ui;

    bloques *puntaje,***mapa;
    QGraphicsScene *scene;
    matriz *m;

    personaje *personaje_;
    enemigo1 *enemy1[cantidad_enemigos];
    enemigo2 *enemy2[cantidad_enemigos];
    Puerta *door;
    bomba *bombX;
    explosion  *explosion_[5];

    QTimer *timer;
    QTimer *time_enemy1;
    QTimer *timer_explosion;

    int **mat;
    int **matrixEnemy;
    int aleatorioX, aleatorioY;
    int contador=0;
    int desplazamientoX=0, desplazamientoY=0;
    int enemyX, enemyY;
    int up_down_left_right;

    bool bandera=false; //saber si hay o no una bomba en la escena


};
#endif // MAINWINDOW_H
