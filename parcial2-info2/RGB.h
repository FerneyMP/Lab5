#ifndef RGB_H
#define RGB_H
#include <iostream>
#include <QImage>
#include <list>

using namespace std;

class RGB
{

public:
    RGB();
    void color_pixel(int red, int green, int blue);
    void ubicacion_archivo();
    void capturaRGB();



private:
    //map<char, vector<int> > MapRGB;
    //vector<int> VectorRGB={0};
    int Red, Blue,Green;
    list<list<int>> RGB_lista[3];
    list<int> lista;
    string filename;
    //QImage imagen;

};


#endif // RGB_H
