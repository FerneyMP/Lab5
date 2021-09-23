#ifndef MATRIZ_H
#define MATRIZ_H
#include <cstdlib>
#include <time.h>

//#define diff 0.3
class matriz
{
public:
    matriz(int a, int b);
    void generar_mapa();    
    int ** get_matriz();
    int get_value(int fila, int colu);


    void set_diff(float b);

    int generar_enemy();
    ~matriz();
private:
    bool aleatorio();
    int **matrix, fil, col;
    float diff = 0.4;


    int **matrixEnemy;
    int aleatorioX, aleatorioY;
};

#endif // MATRIZ_H
