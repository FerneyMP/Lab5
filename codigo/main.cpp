#include "RGB.h"

void lectura_matrix(list<list<int> > matrix);

int main()

//ImageRead e ImageWrite desarrollado en Qt para que pueda entender como es el proceso de cargar una imagen desde su directorio de trabajo y cómo generarla.

{
    string filename = "../parcial2:info2/1/imagen/bandera.jpg"; //ubicacion del archivo
    //Tenga en cuenta que el usuario indicará la ubicación del archivo de imagen

    //con Qimage se carga la imagen al programa
    RGB matrix; //clase
    QImage imagen (filename.c_str());
    matrix.capturaRGB(imagen);

    // *************************************** Código para TinkerCad **********************************************
    /*
    IDEAS:  1. Diseñar la matriz
            2. Diseñar función para escribir en un archivo .txt

    */
    list<list<int>> pruebA = {{{1,2,3}},
                              {{4,5,6}},
                              {{7,8,9}}};
    /*int prueba[3][3][3]={{{1,2,3}},
                         {{4,5,6}},
                         {{7,8,9}}};*/

    lectura_matrix(pruebA);


    return 0;
}

void lectura_matrix(list<list<int>> matrix){
    int pixeles = 12*12;
    int captura = 0;
    for(int indx=0; indx<pixeles; indx++){
        //captura = matrix[1][0][0];
    }
    //cout << matrix[1][0][0] << endl;
}



/*unsigned int pixel_x =200;//ubicacion en x y
unsigned int pixel_y =200;//retorna el color del pixel
cout<<imagen.pixelColor(pixel_x, pixel_y).red()<<endl;
cout<<imagen.pixelColor(pixel_x, pixel_y).green()<<endl;
cout<<imagen.pixelColor(pixel_x, pixel_y).blue()<<endl;*/
