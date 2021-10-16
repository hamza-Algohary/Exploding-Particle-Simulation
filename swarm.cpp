#include "particle.h"
#include "swarm.h"

using namespace SDL_Graphics;

swarm::swarm() : lastTime(0)
{
    particles = new particle[NPARTICLES];
    for(int i=0 ; i<NPARTICLES ;i++){
        particles[i].initOut();
    }
}
swarm::~swarm()
{
    delete[] particles;
}

void swarm::update(int elapsed)
{

    int interval = elapsed - lastTime;
    for (int i = 0; i < NPARTICLES; i++)
    {
        particles[i].move(interval);
    }
    lastTime = elapsed;
}