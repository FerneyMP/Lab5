#include "RGB.h"

RGB::RGB()
{
}

void RGB::color_pixel(int red, int green, int blue)
{
     MapRGB['R'].push_back(red);
     MapRGB['G'].push_back(green);
     MapRGB['B'].push_back(blue);
}
