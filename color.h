#ifndef COLOR_H_
#define COLOR_H_

#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

class Color
{
  private:
    unsigned char red = 0;
    unsigned char green = 0;
    unsigned char blue = 0;
    unsigned char alpha = 1; //note: alpha is belongs to [0 , 1]
    unsigned int color = 0;  //new Uint32;

  public:
    void setColor(unsigned char r, unsigned char g, unsigned char b , unsigned char alpha)
    {
        red = r;
        green = g;
        blue = b;

        color = red;
        color = color << 8;
        color = green;
        color = color << 8;
        color = blue;
        color = color << 8;
        color = alpha;
        color = color << 8;
    }
    static unsigned int RGBA(unsigned char red, unsigned char green, unsigned char blue,unsigned char alpha)
    {   
        unsigned int color;

        color = red;
        color = color << 8;
        color = green;
        color = color << 8;
        color = blue;
        color = color << 8;
        color = alpha;
        color = color << 8;

        return color;
    }

    void showColor()
    {
        cout << "Red:" << (int)red << " Green: " << (int)green << " Blue: "
             << (int)blue << " Whole color is " << color << endl;
    }
    Uint32 returnColor()
    {
        return color;
    }
};

#endif