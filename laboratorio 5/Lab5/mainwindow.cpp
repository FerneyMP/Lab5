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
    puntaje->set_scale(tam*columnas,2*tam);
    puntaje->set_imagen(9); //Con el objeto bloque puedo modificar en la interfaz, gracias al paso por referencia de los punteros

    //Para el personaje principal:
    personaje_ = new personaje;

    //Puerta
    door = new Puerta;

    //timer para enemigo 1
    time_enemy1 = new QTimer;

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
    //, doorX, doorY;
    for (int i=0; i<1;i++){
        //cantidad_enemigos
        enemy1[i] = new enemigo1;
        enemyX = generar_enemyX(); // 125, 98,  ....45
        enemyY = generar_enemyY(); // 125, 103, ....70
        // 1. llamar la funcion ---> se van a mover (referencia)
        // 2. capturar las dos posiciones (contenedor) --- > llamar la función
        //generar_movimientos_enemigos(enemyX,enemyY);

        enemy1[i]->set_scale(tam,tam);
        enemy1[i]->setPos(enemyX*tam, enemyY*tam);
        enemy1[i]->set_imagen(3);
        scene->addItem(enemy1[i]);
    }

      //timer = new QTimer();
     //connect(timer,SIGNAL(timeout()),this,SLOT(change_enemies()));
     // timer-> start (1000);

    //generar_movimientos_enemigos(enemyX,enemyY);
    //generar_movimientos_enemigos();
    //connect(time_enemy1,SIGNAL(timeout()),this,SLOT(generar_movimientos_enemigos()));
    connect(time_enemy1,SIGNAL(timeout()),this,SLOT(generar_movimientos_enemigos(enemyX, enemyY)));
    time_enemy1->start(1000);


    //connect(time_enemy1,SIGNAL(timeout()),this,SLOT(movimientos_enemigos()));
    //time_enemy1->start(1000);

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
    if(aleatorioX%2==0){
        aleatorioX +=1;
    }
    //(f%2==0 && c%2==0)
    return aleatorioX;
}


int MainWindow::generar_enemyY()
{
    aleatorioY = rand()%(13-5)+5;
    if(aleatorioY%2==0){
        aleatorioY += 1;
    }
    //(f%2==0 && c%2==0)
    return aleatorioY;
}

void MainWindow::generar_movimientos_enemigos(int posX, int posY)
{
    up_down_left_right = 1+rand()%(5-1);
    //convención, si up_down... es igual a 1, va hacia arriba, si es igual a 2 va hacia abajo, si es igual a 3 derecha, si es igual a 4 izquierda
    if(up_down_left_right == 1 && m ->get_value(((posY-5)/tam)-2,posX/tam)==8 && m ->get_value(((posY-5)/tam)-2,(posX+tam-1)/tam)==8){
        enemy1[0]-> setY(enemy1[0]->y()-5); //PARA ARRIBA
    }
    if(up_down_left_right == 2 && m->get_value(((posY+tam-1+5)/tam)-2,(posX+tam-1)/tam)==8 && m ->get_value(((posY+tam-1+5)/tam)-2,posX/tam)==8){
        enemy1[0]-> setY(enemy1[0]->y()+5); //PARA ABAJO
    }
    if(up_down_left_right == 3 && m ->get_value((posY/tam)-2,(posX+tam-1+5)/tam)==8 && m ->get_value(((posY+tam-1)/tam)-2,(posX+tam-1+5)/tam)==8){
        enemy1[0]-> setX(enemy1[0]->x()+5); //PARA LA DERECHA
    }
    if(up_down_left_right == 4 && m ->get_value((posY/tam)-2,(posX-5)/tam)==8 && m ->get_value(((posY+tam-1)/tam)-2,(posX-5)/tam)==8 ){
        enemy1[0]-> setX(enemy1[0]->x()-5);//PARA LA IZQUIERDA
    }
}

void MainWindow::movimientos_enemigos(){
    //desplazamientoX = generar_enemyX();
   // desplazamientoY = generar_enemyY();
    //desplazamientoX += 5;
    //desplazamientoY -= 3;
    enemy1[0]->setPos(enemy1[0]->x()+25,enemy1[0]->y()-3);
    //timer dentro de la misma clase (modificar puntero cargado en el graphicsview)
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


