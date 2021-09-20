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

    void set_diff(float b);

    ~matriz();
private:
    bool aleatorio();
    int **matrix, fil, col;
    float diff=0.4;

};

#endif // MATRIZ_H
