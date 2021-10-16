#ifndef SCREEN_H_
#define SCREEN_H_
#include <SDL2/SDL.h>

namespace SDL_Graphics
{
class screen
{
public:
  const static int WIDTH = 800;
  const static int HEIGHT = 600;
  const static int PIXELS = WIDTH * HEIGHT;
private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  Uint32 *buffer;
  Uint32 *buffer2;

public:
  screen();
  bool init();
  void setPixel(int x, int y, unsigned char red, unsigned char green, unsigned char blue);
  unsigned int color(unsigned char red, unsigned char green, unsigned char blue);
  void blur();
  void boxBlur();
  void update();
  void clear();
  bool exitEvent();
  void close();
};
} // namespace SDL_Graphics

#endif