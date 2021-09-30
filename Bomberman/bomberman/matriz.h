#ifndef MATRIZ_H
#define MATRIZ_H
#include <cstdlib>
#include <time.h>

//#define diff 0.3
class matriz
{

public:

    matriz(int a, int b);

    int ** get_matriz();
    int get_value(int fila, int colu);
    int generar_enemy();

    void set_diff(float b);
    void generar_mapa();

    ~matriz();

private:
    bool aleatorio();    

    float diff = 0.4;

    int **matrix, fil, col;
    int **matrixEnemy;
    int aleatorioX, aleatorioY;
};

#endif // MATRIZ_H
