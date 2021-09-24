#include "RGB.h"

RGB::RGB()
{
}

void RGB::color_pixel(int red, int green, int blue)
{
    /*
     MapRGB['R'].push_back(red);
     MapRGB['G'].push_back(green);
     MapRGB['B'].push_back(blue);*/


}

void RGB::ubicacion_archivo()
{
    filename = "../parcial2-info2/imagen/bandera.jpg"; //ubicacion del archivo

    //filename.c_str();
}

void RGB::capturaRGB()
{
    QImage imagen (filename.c_str());
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
           //matrix.color_pixel(Red, Green, Blue);
       }
    }
}
