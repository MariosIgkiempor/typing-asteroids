#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Renderer.h"
#include "Game.h"

class Game;
class Renderer;

class InputHandler 
{
  Renderer* renderer;
  
public:
  InputHandler();
  InputHandler(Renderer* r);
  void HandleEvents(Game* game);
};

#endif
