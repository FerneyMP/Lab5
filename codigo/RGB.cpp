#include "RGB.h"

RGB::RGB()
{
}

void RGB::capturaRGB(QImage imagen)
{

    for (int indx=0;indx<imagen.width(); ++indx){
       for (int indy=0;indy<imagen.height(); ++indy){
           Red= imagen.pixelColor(indx, indy).red();
           Green= imagen.pixelColor(indx, indy).green();
           Blue= imagen.pixelColor(indx, indy).blue();
           lista.push_back(Red);
           RGB_lista[0].push_back(lista);
           lista.clear();
           lista.push_back(Green);
           RGB_lista[1].push_back(lista);
           lista.clear();
           lista.push_back(Blue);
           RGB_lista[2].push_back(lista);
           lista.clear();
       }
    }
}

void RGB::escribir_Archivo(int *datos)
{
    fstream matriz;
    string nombre = "Archivo.txt";
    matriz.open(nombre, fstream::out);
    matriz<<datos;
    //matriz.write(datos, tamanio);
    matriz.close();
}
