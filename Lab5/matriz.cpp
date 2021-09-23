#include "matriz.h"

matriz::matriz(int a, int b)
{
    fil = a;
    col = b;
    matrix =new int* [fil]; //puntero doble, su primera dimension apunta a un arreglo de punteros de tam fijo y cada puntero (segunda dim) apuntan a un arreglo de tam col
    for (int f=0;f<fil ;f++ ) {
        matrix[f]=new int[col];
    }
    srand(time(NULL)); //semilla
}

void matriz::generar_mapa()
{
    for(int f=0; f<fil;f++){ //ciclo para recorrer la matriz por fil y col
        for(int c=0;c<col;c++){
            if(f*c==0 || f==fil-1 || c==col-1 || (f%2==0 && c%2==0)){ //primera, ultima fila y columana y par
                matrix[f][c]=0; //bloque solido gris
            }
            else if(! aleatorio()|| (f==1 && c==2) || (f==2  && c==1) || (f==1  && c==1)){ //si es verdadero genera el fondo
                matrix[f][c]=8;

            }
            else matrix[f][c]=1; //ladrillo

        }
    }
}

bool matriz::aleatorio()//dificultad del juego
{
    int n;
    float x;
    n = rand(); //generar numero aleatorio
    x = diff*(RAND_MAX+1.0)-1; //numero dependiendo de la probabilidad
    return n<=x;
}

int **matriz::get_matriz()
{
    return matrix;
}

int matriz::get_value(int fila, int colu) //obtener inodmracion de la matriz
{
    return matrix[fila][colu]; //valor de la matriz en el punto que le pase
}

void matriz::set_diff(float b)
{
    diff = b;
}

matriz::~matriz()
{
    delete matrix;

}
