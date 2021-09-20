#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{//MainWindow modifica la interfaz principal
    ui->setupUi(this);
    scene = new QGraphicsScene;
    //Se le agregan las dimensiones del graphicsView
    ui->graphicsView->setGeometry(0,0,tam*columnas+2,tam*(filas+2)+2);

    //se le definen dimensiones
    scene->setSceneRect(0,0,tam*columnas,tam*(filas+2));
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
}

void MainWindow::generar_mapa()
{
    matriz m(filas,columnas);
    //Agregado de bloques al graphicsView
    puntaje = new bloques;
    puntaje->set_scale(tam*columnas,2*tam);
    puntaje->set_imagen(9);//Con el objeto bloque puedo
    //modificar en la interfaz, gracias al paso por referencia de los punteros

    puntaje->setPos(0,0);
    inicializar();

    m.generar_mapa();
    mat = m.get_matriz();

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
}

void MainWindow::inicializar()
{//Inicializar un puntero a un arreglo de punteros
    mapa = new bloques** [filas];
    for (int f=0;f<filas ;f++ ) {
        mapa[f]=new bloques*[columnas];
        for (int c=0;c<columnas ;c++ ) {
            mapa[f][c] = new bloques;
        }
    }
}

/*

    bloques_ = new bloques;

    bloques_->set_scale(tam);
    bloques_->set_imagen(0);


    scene->addItem(bloques_);

    bloques_->set_imagen(8);*/
