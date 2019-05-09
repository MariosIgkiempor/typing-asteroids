// Typing Asteroids by Marios Igkiempor 10335752
#include <iostream>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <stdlib.h>

#include "Asteroid.h"
#include "FuzzySearcher.h"
#include "Vec2D.h"
#include "Renderer.h"
#include "InputHandler.h"
#include "Game.h"

// CLASSES --------------------------------------------------------------------
// Forward Declarations

int main(int argc, char* argv[])
{
  Game game;
  game.Start();
  game.Run();
}
