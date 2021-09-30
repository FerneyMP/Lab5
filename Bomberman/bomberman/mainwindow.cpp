#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) //MainWindow modifica la interfaz principal
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer; //timer para el change
    timer_explosion = new QTimer; //timer para la explosion
    time_enemy1 = new QTimer; //timer para el enemigo
    bombX = new bomba;
    scene = new QGraphicsScene;

    for (int i=0; i<5 ;i++){ //crear la explosion
        explosion_[i]=new explosion;
    }

    connect(timer,SIGNAL(timeout()),this,SLOT(erase()));
    connect(timer_explosion,SIGNAL(timeout()),this,SLOT(erase_explosion()));
    connect(time_enemy1,SIGNAL(timeout()),this,SLOT(movimientos_enemigos()));

    //time_enemy1->start(2000);
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

    srand(time(NULL)); //crear la semilla para el # aleatorio
    generar_mapa();

}


MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    delete puntaje;
    delete mapa;
    delete timer;
    delete time_enemy1;
    delete personaje_;
   // delete enemy1[]; preguntar
    delete door;
    delete bombX;
}


void MainWindow::generar_mapa()
{
    m = new matriz(filas,columnas); //Agregado de bloques al graphicsView
    puntaje = new bloques;
    door = new Puerta;
    personaje_ = new personaje;

    puntaje->set_scale(tam*columnas,2*tam);
    puntaje->set_imagen(9); //Con el objeto bloque puedo modificar en la interfaz, gracias al paso por referencia de los punteros

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

    for (int i=0;i<cantidad_enemigos;i++){//generar los enemigos
        enemy1[i] = new enemigo1;
        generar_enemy( enemy1[i]);
    }
    time_enemy1->start(1000);
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


void MainWindow::change_enemies() //TERMINAR
{
    enemy1[cantidad_enemigos]->set_imagen(contador);
    if (contador==2) contador=-1;
    contador++;
}

void MainWindow::erase() //borrar la bomba  //TERMINAR
{
   bandera=false;
   scene->removeItem(bombX);
   timer->stop();
   bombX->timer->stop();

   //agregar la explosion
   explosion_[0]->set_scale(tam,tam);
   explosion_[0]->setPos( bombX->x()-tam , bombX->y());
   explosion_[0]->set_imagen(0);
   scene->addItem(explosion_[0]);

   explosion_[1]->set_scale(tam,tam);
   explosion_[1]->setPos( bombX->x() , bombX->y());
   explosion_[1]->set_imagen(1);
   scene->addItem(explosion_[1]);

   explosion_[2]->set_scale(tam,tam);
   explosion_[2]->setPos( bombX->x()+tam , bombX->y());
   explosion_[2]->set_imagen(2);
   scene->addItem(explosion_[2]);

   explosion_[3]->set_scale(tam,tam);
   explosion_[3]->setPos( bombX->x() , bombX->y()-tam);
   explosion_[3]->set_imagen(3);
   scene->addItem(explosion_[3]);

   explosion_[4]->set_scale(tam,tam);
   explosion_[4]->setPos( bombX->x() , bombX->y()+tam);
   explosion_[4]->set_imagen(5);
   scene->addItem(explosion_[4]);


   timer_explosion-> start(2000);
}


void MainWindow::keyPressEvent(QKeyEvent *tecla) //movimiento del personaje
{
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

   if (tecla-> key() == Qt::Key_R && !bandera){
       bandera=true;
       bombX->set_scale(tam,tam);
       bombX->setPos(x,y); //xy del personaje
       scene->addItem(bombX);
       timer->start(2000);//eliminar
       bombX->timer-> start (250);//palpitar

   }
}


void MainWindow::generar_enemy(enemigo1 *enemigo) //crea los puntos xy aleatorios de cada enemigo
{
 //IMPORTANTE: generar números que correspondan al rango del tamaño del mapa
    //retornar parejas de datos flotantes (agregarlos en un for <=prob)
    //esta información va dentro de SetPos

    do{
        aleatorioX = rand()%(columnas-2)+1; //(HASTA-DESDE +1)+DESDE
        aleatorioY = rand()%(filas-4)+3;

    } while(m->get_value(aleatorioY-2,aleatorioX) !=8 || (aleatorioX==1 && aleatorioY ==3) || (aleatorioX==2 && aleatorioY ==3) || (aleatorioX==1 && aleatorioY ==4) );

    enemigo->set_scale(tam,tam);
    enemigo->setPos(aleatorioX*tam, aleatorioY*tam);
    enemigo->set_imagen(3);
    scene->addItem(enemigo);
}

void MainWindow::numeros_aleatorios()
{
    up_down_left_right = 1+rand()%(5-1);
}


void MainWindow::movimientos_enemigos() //TERMINAR
{
    //decidir el aleatorio del cruce, cambio de imagenes, for, choque
    int posX= enemy1[0]->x(), posY=enemy1[0]->y();


    //f%2==0 && c%2==0 ---> sean pares , columnas 0, 27 y filas 2 y 14
    // crear un for que genere números aleatorios hasta cierta


    //RESIDUOS == 0, POSICIONES IMPARES
    //up_down_left_right = 4;

   //convención, si up_down... es igual a 1, va hacia arriba, si es igual a 2 va hacia abajo, si es igual a 3 derecha, si es igual a 4 izquierda

    //Condición Inicial
    numeros_aleatorios();
    for(int i = 0; i<cantidad_enemigos; i++){

        //deberia estar dentro de un ciclo, booleano que dependa del ciclo exterior

        //numeros_aleatorios();
        if(up_down_left_right == 1 && m ->get_value(((posY-5)/tam)-2,posX/tam)==8 && m ->get_value(((posY-5)/tam)-2,(posX+tam-1)/tam)==8){
            if( ((posX && posY)%2==0) || (((posX<1)||(posX<26) || ((posY<3)||(posY<13)) ))){
                enemy1[i]-> setY(enemy1[i]->y()-5); //PARA ARRIBA
                numeros_aleatorios();

         }
            //     "cuadros grises"        "posición de los muros"
        }
        if(up_down_left_right == 2 && m->get_value(((posY+tam-1+5)/tam)-2,(posX+tam-1)/tam)==8 && m ->get_value(((posY+tam-1+5)/tam)-2,posX/tam)==8){
            if( ((posX && posY)%2==0) || (((posX<1)||(posX<26) || ((posY<3)||(posY<13)) ))){
                enemy1[i]-> setY(enemy1[i]->y()+5); //PARA ABAJO
                numeros_aleatorios();
            }
        }
        if(up_down_left_right == 3 && m ->get_value((posY/tam)-2,(posX+tam-1+5)/tam)==8 && m ->get_value(((posY+tam-1)/tam)-2,(posX+tam-1+5)/tam)==8){
            if( ((posX && posY)%2==0) || (((posX<1)||(posX<26) || ((posY<3)||(posY<13)) ))){
                enemy1[i]-> setX(enemy1[i]->x()+5); //PARA LA DERECHA
                numeros_aleatorios();
            }
        }

        if(up_down_left_right == 4 && m ->get_value((posY/tam)-2,(posX-5)/tam)==8 && m ->get_value(((posY+tam-1)/tam)-2,(posX-5)/tam)==8 ){

            if( ((posX && posY)%2==0) || (((posX<1)||(posX<26) || ((posY<3)||(posY<13)) ))){
                enemy1[i]-> setX(enemy1[i]->x()-5);//PARA LA IZQUIERDA
                numeros_aleatorios();
            }
        }
    }
}

void MainWindow::erase_explosion()
{
    timer_explosion-> stop();
    for (int i =0; i<5 ; i++) scene->removeItem(explosion_[i]);
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


