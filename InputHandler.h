#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Renderer.h"
#include "Game.h"

// Forward declaration of needed classes
class Renderer;
class Game;

class InputHandler 
{
  Renderer* renderer; // Instance of the renderer in case we need to quit it
  
public:
  InputHandler();
  InputHandler(Renderer* r);
  void HandleEvents(Game* game);
};

#endif
