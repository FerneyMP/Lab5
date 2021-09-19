#include<RGB.h>

int main()

//ImageRead e ImageWrite desarrollado en Qt para que pueda entender como es el proceso de cargar una imagen desde su directorio de trabajo y cómo generarla.

{
    string filename = "../parcial2-info2/imagen/bandera.jpg"; //ubicacion del archivo
    //Tenga en cuenta que el usuario indicará la ubicación del archivo de imagen
    QImage imagen (filename.c_str());
    int Red, Blue,Green;

    RGB matrix; //clase

    for (int indx=0;indx<imagen.width(); ++indx){
       for (int indy=0;indy<imagen.height(); ++indy){
           Red= imagen.pixelColor(indx, indy).red();
           Green= imagen.pixelColor(indx, indy).green();
           Blue= imagen.pixelColor(indx, indy).blue();
           matrix.color_pixel(Red, Green, Blue);

       }
    }

    return 0;
}

//con qimage se carga la imagen al programa

/*unsigned int pixel_x =200;//ubicacion en x y
unsigned int pixel_y =200;//retorna el color del pixel
cout<<imagen.pixelColor(pixel_x, pixel_y).red()<<endl;
cout<<imagen.pixelColor(pixel_x, pixel_y).green()<<endl;
cout<<imagen.pixelColor(pixel_x, pixel_y).blue()<<endl;*/
