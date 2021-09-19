#ifndef GREEN_H
#define GREEN_H
#include <vector>
#include <map>
using namespace std;


class RGB
{
public:
    RGB();
private:
    vector <int> RGB;
    map<int, vector<int> > mapRGB;
};

#endif // GREEN_H
