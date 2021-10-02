#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) //MainWindow modifica la interfaz principal
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer; //timer para el change (palpitar bomba)
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


    ui->graphicsView->setGeometry(0,0,tam*columnas+2,tam*(filas+2)+2); //Se le agregan las dimensiones del graphicsView
    scene->setSceneRect(0,0,tam*columnas,tam*(filas+2));//se le definen dimensiones
    ui->graphicsView->setScene(scene); //se carga la escena
    setFixedSize(tam*columnas+2,tam*(filas+2)+2); //se escala interfaz principal
    setWindowTitle("Bomberman");

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


void MainWindow::erase_explosion()
{
    timer_explosion-> stop();
    for (int i =0; i<5 ; i++) scene->removeItem(explosion_[i]);
}


void MainWindow::erase() //borrar la bomba  //TERMINAR
{
   bandera=false;
   scene->removeItem(bombX);
   timer->stop();
   bombX->timer->stop();

   //agregar la explosion
  // int posX= bombX->x(),  posY =bombX->y();

   /*if( ((posX>2 || posX>14) && posY==0) || (posX%2==0 && posY%2==0) || (posX==29 && (posY>1 || posY>30)) ) {



 }*/
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

   timer_explosion-> start(1000);

   //si la bomba toca al personaje-> eliminar personaje
   if ((bombX->x()+tam >= personaje_->x() -tam || bombX->x()+tam >= personaje_->x() +tam) && (bombX->x()-tam <=personaje_->x()-tam || bombX->x()-tam <=personaje_->x()+tam) && bombX-> y()== personaje_->y()){
       personaje_->activar_muerteP();
       timer_explosion-> start(1000);

      //scene->removeItem(personaje_);
      //TERMINAR JUEGO

   }   
   if ((bombX->y()+tam >= personaje_->y()-tam || bombX->y()+tam >= personaje_->y()+tam ) && (bombX->y()-tam <=personaje_->y()-tam || bombX->y()-tam <=personaje_->y()+tam ) && bombX-> x()== personaje_->x()){
       personaje_->activar_muerteP();
       timer_explosion-> start(1000);

       //scene->removeItem(personaje_);
      //TERMINAR JUEGO
   }

   //si la bomba toca al enemigo -> eliminar enemigos
   for (int i=0; i<cantidad_enemigos; i++){
       if ((bombX->x()+tam >= enemy1[i]->x()-tam || bombX->x()+tam >= enemy1[i]->x()+tam ) && ( bombX->x()-tam <=enemy1[i]->x()-tam ||bombX->x()-tam <=enemy1[i]->x() +tam ) && bombX-> y()== enemy1[i]->y()){
          enemy1[i]->activar_muerteE();
          timer_explosion-> start(1000);

         // scene->removeItem(enemy1[i]); SI SE QUITA DE LA SCENE NO SE VE EL CAMBIO DE IMAGENES PARA LA MUERTE DEL ENEMIGO
       }

       if ((bombX->y()+tam >= enemy1[i]->y()-tam || bombX->y()+tam >= enemy1[i]->y()+tam) && (bombX->y()-tam <=enemy1[i]->y() -tam || bombX->y()-tam <=enemy1[i]->y() + tam ) && bombX-> x()== enemy1[i]->x()){
           enemy1[i]->activar_muerteE();
           timer_explosion-> start(1000);

           //scene->removeItem(enemy1[i]);

       }
   }

}


void MainWindow::keyPressEvent(QKeyEvent *tecla) //movimiento del personaje
{
   int x =personaje_->x(), y=personaje_->y(); //posicion xy del personaje

   if (tecla-> key() == Qt:: Key_D && m ->get_value((y/tam)-2,(x+tam-1+5)/tam)==8 && m ->get_value(((y+tam-1)/tam)-2,(x+tam-1+5)/tam)==8) { //sup e inf der
       personaje_-> change('d'); //cambio de imagen
       personaje_-> setX(personaje_->x()+5); //mover 5 pasos de la posicion original
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
       timer->start(3000);//eliminar la bomba
       bombX->timer-> start (250);// empezar a palpitar
   }
}


void MainWindow::generar_enemy(enemigo1 *enemigo) //crea los puntos xy aleatorios de cada enemigo
{
 //IMPORTANTE: generar números que correspondan al rango del tamaño del mapa
    //retornar parejas de datos flotantes (agregarlos en un for <=prob)
    //esta información va dentro de SetPos

    do{
        //(HASTA-DESDE +1)+DESDE
        aleatorioX = rand()%(columnas-2)+1; //# 1 a 25
        aleatorioY = rand()%(filas-4)+3; //# 3 a 11

    } while(m->get_value(aleatorioY-2,aleatorioX) !=8 || (aleatorioX==1 && aleatorioY ==3) || (aleatorioX==2 && aleatorioY ==3) || (aleatorioX==1 && aleatorioY ==4) );
    //posicionarse en espacios diferentes a el fondo, el espacio del jugador y sus alrededores

    enemigo->set_scale(tam,tam);
    enemigo->setPos(aleatorioX*tam, aleatorioY*tam);
    enemigo->set_imagen(3,1);
    scene->addItem(enemigo);
}


void MainWindow::movimientos_enemigos() //TERMINAR
{
    //decidir el aleatorio del cruce, cambio de imagenes, for, choque
    int posX= enemy1[0]->x(), posY=enemy1[0]->y();

    up_down_left_right = 4;
   // up_down_left_right = 1+rand()%(5-1);
   //convención, si up_down... es igual a 1, va hacia arriba, si es igual a 2 va hacia abajo, si es igual a 3 derecha, si es igual a 4 izquierda

    if(up_down_left_right == 1 && m ->get_value(((posY-5)/tam)-2,posX/tam)==8 && m ->get_value(((posY-5)/tam)-2,(posX+tam-1)/tam)==8){
        enemy1[0]-> setY(enemy1[0]->y()-25); //PARA ARRIBA
    }
    if(up_down_left_right == 2 && m->get_value(((posY+tam-1+5)/tam)-2,(posX+tam-1)/tam)==8 && m ->get_value(((posY+tam-1+5)/tam)-2,posX/tam)==8){
        enemy1[0]-> setY(enemy1[0]->y()+25); //PARA ABAJO
    }
    if(up_down_left_right == 3 && m ->get_value((posY/tam)-2,(posX+tam-1+5)/tam)==8 && m ->get_value(((posY+tam-1)/tam)-2,(posX+tam-1+5)/tam)==8){
        enemy1[0]-> setX(enemy1[0]->x()+25); //PARA LA DERECHA
    }
    if(up_down_left_right == 4 && m ->get_value((posY/tam)-2,(posX-5)/tam)==8 && m ->get_value(((posY+tam-1)/tam)-2,(posX-5)/tam)==8 ){

        enemy1[0]-> setX(enemy1[0]->x()-25);//PARA LA IZQUIERDA
    }

    //si el personaje toca al enemigo -> eliminar personaje
    for (int i=0; i<cantidad_enemigos; i++){

        //((bombX->x()+tam >= personaje_->x() -tam || bombX->x()+tam >= personaje_->x() +tam) && (bombX->x()-tam <=personaje_->x()-tam || bombX->x()-tam <=personaje_->x()+tam) && bombX-> y()== personaje_->y()){


        if (enemy1[i]->x()+tam >= personaje_->x() && enemy1[i]->x()-tam <=personaje_->x() && enemy1[i]->y()== personaje_->y()){
            personaje_->activar_muerteP();
           // scene->removeItem(personaje_);  SI SE QUITA DE LA SCENE NO SE VE EL CAMBIO DE IMAGENES PARA LA MUERTE DEL PERSONAJE
           //TERMINAR JUEGO
        }
        if (enemy1[i]->y()+tam >= personaje_->y() && enemy1[i]->y()-tam <=personaje_->y() && enemy1[i]->x()== personaje_->x()){
            personaje_->activar_muerteP();
           // scene->removeItem(personaje_);
           //TERMINAR JUEGO

        }
    }
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


