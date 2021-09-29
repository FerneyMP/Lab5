#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) //MainWindow modifica la interfaz principal
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
    delete timer;
    delete time;


    delete personaje_;
   // delete enemy1[]; preguntar
    delete door;
    delete bombX;
}


void MainWindow::generar_mapa()
{
    m = new matriz(filas,columnas); //Agregado de bloques al graphicsView
    puntaje = new bloques;
    puntaje->set_scale(tam*columnas,2*tam);
    puntaje->set_imagen(9); //Con el objeto bloque puedo modificar en la interfaz, gracias al paso por referencia de los punteros

    //Para el personaje principal:
    personaje_ = new personaje;

    //
    door = new Puerta;  //Puerta

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
                scene->addItem(mapa[f][c]); //a la escena se le carga un item

        }
    }
    scene->addItem(puntaje);  //addItem permite agregar elemento a la escena y recibe punteros

    personaje_->set_scale(tam,tam);
    personaje_->setPos(tam ,3*tam);
    personaje_->set_imagen(4,1);
    scene->addItem(personaje_);

    timer = new QTimer(); //

    int enemyX, enemyY, doorX, doorY;
    for (int i=0; i<cantidad_enemigos;i++){
        enemy1[i] = new enemigo1;
        enemyX = generar_enemyX();
        enemyY = generar_enemyY();

        enemy1[i]->set_scale(tam,tam);
        enemy1[i]->setPos(enemyX*tam, enemyY*tam);
        enemy1[i]->set_imagen(3);
        scene->addItem(enemy1[i]);

      /*  timer = new QTimer();
        connect(timer,SIGNAL(timeout()),this,SLOT(change_enemies()));
        timer-> start (1000);*/

    }

    connect(time,SIGNAL(timeout()),this,SLOT(movimientos_enemigos()));
    time->start(1000);

}

void MainWindow::movimientos_enemigos(){
    //desplazamientoX = generar_enemyX();
   // desplazamientoY = generar_enemyY();
    //desplazamientoX += 5;
    //desplazamientoY -= 3;
    enemy2[0]->setPos(enemy2[0]->x()+25,enemy2[0]->y()-3);
    //timer dentro de la misma clase (modificar puntero cargado en el graphicsview)
}


void MainWindow::inicializar() //Inicializar un puntero a un arreglo de punteros
{
    mapa = new bloques** [filas]; //nuevo arreglo a un puntero de bloques de filas posiciones
    for (int f=0;f<filas ;f++ ) {
        mapa[f]=new bloques*[columnas];
        for (int c=0;c<columnas ;c++ ) {
            mapa[f][c] = new bloques;
        }
    }
}


void MainWindow::change() //movimiento de la bomba
{
    bombX->set_imagen(contador);
    if (contador==2) contador=-1;
    contador++;
}


void MainWindow::change_enemies()
{
    enemy1[cantidad_enemigos]->set_imagen(contador);
    if (contador==2) contador=-1;
    contador++;
}

void MainWindow::erase(int x, int y) //borrar la bomba
{
    timer -> stop ();
    m ->get_value(x,y);
    mapa[x][y]->set_imagen(8);
}


void MainWindow::keyPressEvent(QKeyEvent *tecla) //movimiento del personaje
{  // el puntero almacena el dato de que fue lo que se preciono
   //si se quiere mover en y(filas) estos permanecen ctes, toca revisar los x y al reves

    int x =personaje_->x(), y=personaje_->y();

   if (tecla-> key() == Qt:: Key_D && m ->get_value((y/tam)-2,(x+tam-1+5)/tam)==8 && m ->get_value(((y+tam-1)/tam)-2,(x+tam-1+5)/tam)==8) { //sup e inf der
       personaje_-> change('d');
       personaje_-> setX(personaje_->x()+5);
   }
   if (tecla-> key() == Qt:: Key_W && m ->get_value(((y-5)/tam)-2,x/tam)==8 && m ->get_value(((y-5)/tam)-2,(x+tam-1)/tam)==8) {  //arr
    personaje_-> change('w');
    personaje_-> setY(personaje_->y()-5);
   }
   if (tecla-> key() == Qt:: Key_A && m ->get_value((y/tam)-2,(x-5)/tam)==8 && m ->get_value(((y+tam-1)/tam)-2,(x-5)/tam)==8) {  //izq
       personaje_-> change('a');
       personaje_-> setX(personaje_->x()-5);
   }
   if (tecla-> key() == Qt:: Key_S && m ->get_value(((y+tam-1+5)/tam)-2,(x+tam-1)/tam)==8 && m ->get_value(((y+tam-1+5)/tam)-2,x/tam)==8) { //aba
       personaje_-> change('s');
       personaje_-> setY(personaje_->y()+5); //se va a mover 5 pixeles
  }

   if (tecla-> key() == Qt::Key_R){
       bombX = new bomba;
       timer = new QTimer();

       bombX->set_scale(tam,tam);
       bombX->setPos(x,y);
       scene->addItem(bombX);

       connect(timer,SIGNAL(timeout()),this,SLOT(change()));
       //change, funcion para cambiar de imagen y generar el mov
       timer-> start (250);

      //erase(x,y);


   }
}


int MainWindow::generar_enemyX()
{
 //IMPORTANTE: generar números que correspondan al rango del tamaño del mapa
    //retornar parejas de datos flotantes (agregarlos en un for <=prob)
    //esta información va dentro de SetPos
    //srand(time(NULL));

    aleatorioX = rand()%(30-3)+3; //(HASTA-DESDE +1)+DESDE
    return aleatorioX;
}


int MainWindow::generar_enemyY()
{
     aleatorioY = rand()%(13-5)+5;
    return aleatorioY;
}


/*PARA EL SEGUNDO MUNDO en generar mapa
for (int i=0; i<cantidad_enemigos;i++){
    enemy2[i] = new enemigo2;
    enemyX = generar_enemyX();
    enemyY = generar_enemyY();

    enemy2[i]->set_scale(tam,tam);
    enemy2[i]->setPos(enemyX*tam, enemyY*tam);
    enemy2[i]->set_imagen(4);
    scene->addItem(enemy2[i]);

}

//PARA GENERAR LA PUERTA
doorX = generar_enemyX();
doorY = generar_enemyY();
door->set_scale(tam,tam);
door->setPos(doorX*tam, doorY*tam);
door->set_imagen(0);
scene->addItem(door);*/


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

    bloques_->set_imagen(8);








    int x =personaje_->x(), y=personaje_->y();
    bool ban=false;
    while(ban){
        if  (( m ->get_value((y/tam)-2,(x+tam-1+5)/tam)==8 && m ->get_value(((y+tam-1)/tam)-2,(x+tam-1+5)/tam)==8)|| ( m ->get_value((y/tam)-2,(x-5)/tam)==8 && m ->get_value(((y+tam-1)/tam)-2,(x-5)/tam)==8) ){
        aleatorioX = rand()%(30-3)+3; //(HASTA-DESDE +1)+DESDE
        ban=true;
        }
        else ban= false;
    }
    return aleatorioX;



*/


