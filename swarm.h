#ifndef SWARM_H_
#define SWARM_H_
#include "particle.h"

namespace SDL_Graphics
{
    class swarm
    {
    public:
        const static int NPARTICLES = 5000;
    private:
        particle *particles;
        int lastTime;
    public:
        swarm();
        ~swarm();

        const particle * const getParticles(){
            return particles;
        }
        void update(int elapsed);
    };
};


#endif