#ifndef PARTICLE_H_
#define PARTICLE_H_
#include <cstdlib>

namespace SDL_Graphics
{
class particle
{
public:
  double x, y;
  double direction;
  double speed;

private:
  void init();
  //int initialDirection;
public:
  particle();
  void initOut();
  void fall(int interval);
  void move(int interval);
};

} // namespace SDL_Graphics

#endif