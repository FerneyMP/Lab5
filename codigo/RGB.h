#ifndef RGB_H
#define RGB_H
#include <iostream>
#include <QImage>
#include <list>
#include <fstream>

using namespace std;

class RGB
{

public:
    RGB();
    void capturaRGB(QImage imagen);
    void escribir_Archivo(int *datos);

private:
    int Red, Blue,Green;
    list<list<int>> RGB_lista[3];
    list<int> lista;
    string filename;
};


#endif // RGB_H
