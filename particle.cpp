#include "particle.h"
#include "screen.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

/* IMPORTANT NOTE:
    Some notes to remind you of how to convert -vector-(theta-degree,length unit) to -cartesian-(X,Y)
    Put every thing inside a right-angled triangle where hypotonese is the length-unit in the vector  
    and the angle down is theta-degree , the other two sides are the X-coordinate & Y-coordinate.

    Formulae are:

    X = hyp.*cos(angle)
    Y = hyp.*sin(angle)
*/

using namespace SDL_Graphics;


particle::particle() : x(0), y(0)
{
    init();

}

void particle::initOut()
{
    x = ((2.0 * rand()) / RAND_MAX) - 1 + 2; //Out of the screen at the
    y = ((2.0 * rand()) / RAND_MAX) - 1 - 2; //top-right of the window
}

void particle::init()
{
    x = 0;
    y = 0;
    direction = (2.0 * M_PI * rand()) / RAND_MAX;
    speed = (0.04 * rand()) / RAND_MAX;
    speed *= speed;
}

void particle::move(int interval)
{

    direction += interval * 0.0004;

    double xspeed = speed * cos(direction);
    double yspeed = speed * sin(direction);

    x += xspeed * interval;
    y += yspeed * interval;

    if (x < -1 || x > 1 || y < -1 || y > 1)
    {
        init();
    }

    if (rand() < RAND_MAX / 100)
    {
        init();
    }
}

void particle::fall(int interval)
{

    //if (rand() < RAND_MAX/10)
    //{
        x -=  interval * speed;
        y +=  interval * speed;
    //}
}