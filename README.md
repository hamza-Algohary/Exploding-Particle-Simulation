# Exploding Particle Simulation
Simple program to display an explosion
# Building
make sure that g++ and SDL2 are installed on your system , then run:
```
g++ main.cpp screen.cpp swarm.cpp particle.cpp -o explosion `sdl2-config --cflags --libs` -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf
```
![explosion-gif](explosion.gif)
