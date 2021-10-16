#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include <ctime>
#include "screen.h"
#include "swarm.h"
#include "particle.h"

using namespace std;
using namespace SDL_Graphics;

int main()
{
    srand(time(NULL));
    screen screen1;

    if (!screen1.init())
    {
        cout << "Error initializing SDL , ERR_CODE: " << SDL_GetError();
    }

        SDL_Surface* surface; 
  


    swarm swarm1;
    const particle *particles = swarm1.getParticles();

    while (screen1.exitEvent())
    {
        int elapsed = SDL_GetTicks();

        swarm1.update(elapsed);

        unsigned char red = (1 + sin(elapsed * 0.0002)) * 128;
        unsigned char green = (1 + sin(elapsed * 0.0001)) * 128;
        unsigned char blue = (1 + sin(elapsed * 0.0003)) * 128;

        for (int i = 0; i < swarm::NPARTICLES; i++)
        {
            int x = (particles[i].x + 1) * screen::WIDTH / 2;
            int y = particles[i].y * screen::WIDTH / 2 + screen::HEIGHT / 2;
            //#f76912
            screen1.setPixel(x, y, red, green, blue);
        }
        screen1.blur();
        screen1.update();

    }

    screen1.close();

    return 0;
}