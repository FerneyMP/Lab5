#ifndef MATRIZ_H
#define MATRIZ_H
#include <cstdlib>
#include <time.h>

#define diff 0.2
class matriz
{
public:
    matriz(int a, int b);
    void generar_mapa();
    int ** get_matriz();
    int **matrix;
private:
    bool aleatorio();
    int fil, col;

};

#endif // MATRIZ_H
