#include "screen.h"
#include <iostream>
#include <SDL2/SDL_timer.h> 
#include <SDL2/SDL_image.h> 
#include <iomanip>

using namespace std;
using namespace SDL_Graphics;

screen::screen() : window(NULL), renderer(NULL), texture(NULL), buffer(NULL), buffer2(NULL)
{
}
bool screen::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        return false;
    }
    else
    {
        cout << "No problem with sdl init" << endl;
    }
    window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    cout << "Window created." << endl;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    cout << "renderer created" << endl;

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT);
    cout << "Texture created" << endl;

    if (window == NULL)
    {
        SDL_Quit();
        return false;
        cout << "No problem with the window" << endl;
    }
    if (renderer == NULL)
    {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        return false;
        cout << "No problem with the renderer" << endl;
    }
    if (texture == NULL)
    {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        return false;
        cout << "No problem with the texture" << endl;
    }
    buffer = new Uint32[WIDTH * HEIGHT];
    buffer2 = new Uint32[WIDTH * HEIGHT];

    /*for (int i = 0; i < PIXELS; i++)
    {
        buffer[i] = 0x00ff0000;
    }*/
    cout << "No problem with the buffer" << endl;
    memset(buffer, 0, WIDTH * HEIGHT * sizeof(Uint32));
    memset(buffer2, 0, WIDTH * HEIGHT * sizeof(Uint32));

    SDL_Surface* surface;

        // please provide a path for your image 
    surface = IMG_Load("/home/hamza/Pictures/planet.png"); 
  
    // loads image to our graphics hardware memory. 
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface); 
  
    // clears main-memory 
    SDL_FreeSurface(surface); 

    return true;
}

void screen::setPixel(int x, int y, unsigned char red, unsigned char green, unsigned char blue)
{
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
    {
        //cout << "out of screen:" << "x: " << x << " y: " << y <<endl;
        return;
    }
    int color = 0;
    color += red;
    color <<= 8;

    color += green;
    color <<= 8;

    color += blue;
    color <<= 8;

    color += 0xff;

    buffer[x + (y * WIDTH)] = color;
}

void screen::blur()
{
    Uint32 *temp = buffer;
    buffer = buffer2;
    buffer2 = temp;

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            int redTotal = 0;
            int greenTotal = 0;
            int blueTotal = 0;

            for (int row = -1; row <= 1; row++)
            {
                for (int col = -1; col <= 1; col++)
                {
                    int currentX = x + col;
                    int currentY = y + row;

                    if (currentX >= 0 && currentX < WIDTH && currentY >= 0 && currentY < HEIGHT)
                    {
                        Uint32 color = buffer2[(currentY * WIDTH) + currentX];

                        Uint8 red = color >> 24;
                        Uint8 green = color >> 16;
                        Uint8 blue = color >> 8;

                        redTotal += red;
                        greenTotal += green;
                        blueTotal += blue;
                    }
                }
            }

            Uint8 red = redTotal / 9;
            Uint8 green = greenTotal / 9;
            Uint8 blue = blueTotal / 9;

            setPixel(x, y, red, green, blue);
        }
    }
}

void screen::boxBlur()
{
    // Swap the buffers, so pixel is in m_buffer2 and we are drawing to m_buffer1.
    Uint32 *temp = buffer;
    buffer = buffer2;
    buffer2 = temp;

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {

            /*
			 * 0 0 0
			 * 0 1 0
			 * 0 0 0
			 */

            int redTotal = 0;
            int greenTotal = 0;
            int blueTotal = 0;

            for (int row = -1; row <= 1; row++)
            {
                for (int col = -1; col <= 1; col++)
                {
                    int currentX = x + col;
                    int currentY = y + row;

                    if (currentX >= 0 && currentX < WIDTH && currentY >= 0 && currentY < HEIGHT)
                    {
                        Uint32 color = buffer2[currentY * WIDTH + currentX];

                        Uint8 red = color >> 24;
                        Uint8 green = color >> 16;
                        Uint8 blue = color >> 8;

                        redTotal += red;
                        greenTotal += green;
                        blueTotal += blue;
                    }
                }
            }

            Uint8 red = redTotal / 9;
            Uint8 green = greenTotal / 9;
            Uint8 blue = blueTotal / 9;

            setPixel(x, y, red, green, blue);
        }
    }
}

void screen::update()
{
    SDL_UpdateTexture(texture, NULL, buffer, WIDTH * sizeof(Uint32));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}
bool screen::exitEvent()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            return false;
        }
    }

    return true;
}
void screen::close()
{
    delete[] buffer;
    delete[] buffer2;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);
    SDL_Quit();
}