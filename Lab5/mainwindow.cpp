#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{   //MainWindow modifica la interfaz principal  ---------------------------> IMPORTANTE

    ui->setupUi(this);
    //time = new QTimer;
    //connect(time,SIGNAL(timeout()),this,SLOT(cambio()));
    //time->start(5000);
    scene = new QGraphicsScene;
    //Se le agregan las dimensiones del graphicsView
    ui->graphicsView->setGeometry(0,0,tam*columnas+2,tam*(filas+2)+2);

    //se le definen dimensiones
    scene->setSceneRect(0,0,tam*columnas+2,tam*(filas+2));
    //se carga la escena
    ui->graphicsView->setScene(scene);
    //se escala interfaz principal
    setFixedSize(tam*columnas+2,tam*(filas+2)+2);
    setWindowTitle("Bomberman");
    //agregar icono

    generar_mapa();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    delete puntaje;
    delete mapa;
    //delete time;

    delete personaje_;
    delete enemy2;
}

void MainWindow::generar_mapa()
{
    m = new matriz(filas,columnas);
    //Agregado de bloques al graphicsView
    puntaje = new bloques;
    puntaje->set_scale(tam*columnas,2*tam);
    puntaje->set_imagen(9);//Con el objeto bloque puedo
    //modificar en la interfaz, gracias al paso por referencia de los punteros

    //Para el personaje principal:
    personaje_ = new personaje;
    //Para las condificones del personaje principal:
    puntaje_ = new bloques;
    //Para el enemigo2
    enemy2 = new enemigo2;

    puntaje->setPos(0,0); //posicionar un elemento donde se desee
    inicializar();

    m->set_diff(0.1);
    m->generar_mapa();
    mat = m->get_matriz();

    for (int f=0;f<filas ;f++ ) {
        for (int c=0;c<columnas ;c++ ) {
                mapa[f][c]->set_scale(tam,tam);
                mapa[f][c]->setPos(c*tam,(2+f)*tam);
                mapa[f][c]->set_imagen(mat[f][c]);
                //a la escena se le carga un item
                scene->addItem(mapa[f][c]);

        }
    }
    //addItem permite agregar elemento a la escena y recibe punteros
    scene->addItem(puntaje);

    personaje_->set_scale(tam,tam);
    personaje_->setPos(tam ,3*tam);
    personaje_->set_imagen(4);
    scene->addItem(personaje_);
}

void MainWindow::inicializar()
{//Inicializar un puntero a un arreglo de punteros
    mapa = new bloques** [filas]; //nuevo arreglo a un puntero de bloques de filas posiciones
    for (int f=0;f<filas ;f++ ) {
        mapa[f]=new bloques*[columnas];
        for (int c=0;c<columnas ;c++ ) {
            mapa[f][c] = new bloques;
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *tecla) //movimiento del personaje
{  // el puntero almacena el dato de que fue lo que se preciono
   //si se quiere mover en y(filas) estos permanecen ctes, toca revisar los x y al reves
   int x =personaje_->x(), y=personaje_->y();


   if (tecla-> key() == Qt:: Key_D && m ->get_value((y/tam)-2,(x+tam-1+5)/tam)==8 && m ->get_value(((y+tam-1)/tam)-2,(x+tam-1+5)/tam)==8) { //sup e inf der
    personaje_-> setX(personaje_->x()+5);
   }
   if (tecla-> key() == Qt:: Key_W && m ->get_value(((y-5)/tam)-2,x/tam)==8 && m ->get_value(((y-5)/tam)-2,(x+tam-1)/tam)==8) {  //arr
    personaje_-> setY(personaje_->y()-5);
   }
   if (tecla-> key() == Qt:: Key_A && m ->get_value((y/tam)-2,(x-5)/tam)==8 && m ->get_value(((y+tam-1)/tam)-2,(x-5)/tam)==8) {  //izq
    personaje_-> setX(personaje_->x()-5);
   }
   if (tecla-> key() == Qt:: Key_S && m ->get_value(((y+tam-1+5)/tam)-2,(x+tam-1)/tam)==8 && m ->get_value(((y+tam-1+5)/tam)-2,x/tam)==8) { //aba
   personaje_-> setY(personaje_->y()+5); //se va a mover 5 pixeles
  }

}

/*
void MainWindow::cambio()
{
    m->set_diff(0.4);
    m->generar_mapa();
    mat = m->get_matriz();
    for (int f=0;f<filas ;f++ ) {
        for (int c=0;c<columnas ;c++ ) {
            mapa[f][c]->set_imagen(mat[f][c]);
        }
    }
}*/

/*

    bloques_ = new bloques;

    bloques_->set_scale(tam);
    bloques_->set_imagen(0);


    scene->addItem(bloques_);

    bloques_->set_imagen(8);*/
