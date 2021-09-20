#include "matriz.h"

matriz::matriz(int a, int b)
{
    fil = a;
    col = b;
    matrix =new int* [fil];
    for (int f=0;f<fil ;f++ ) {
        matrix[f]=new int[col];
    }
    srand(time(NULL));
}

void matriz::generar_mapa()
{
    for(int f=0; f<fil;f++){
        for(int c=0;c<col;c++){
            if(f*c==0 || f==fil-1 || c==col-1 || (f%2==0 && c%2==0)){
                matrix[f][c]=0;
            }
            else if(aleatorio()){
                matrix[f][c]=1;
            }
            else matrix[f][c]=8;
        }
    }
}

bool matriz::aleatorio()
{
    int n;
    float x;
    n = rand();
    x = diff*(RAND_MAX+1)-1;
    return n<=x;

}

int **matriz::get_matriz()
{
    return matrix;
}
