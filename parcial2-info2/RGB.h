#ifndef RGB_H
#define RGB_H
#include <vector>
#include <map>
#include <iostream>
#include <QImage>

using namespace std;

class RGB
{

public:
    RGB();
    void color_pixel(int red, int green, int blue);

private:
    map<char, vector<int> > MapRGB;
    vector<int> VectorRGB={0};
};


#endif // RGB_H
