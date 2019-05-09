#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "Game.h"
#include "Constants.h"

class Game;
class Renderer
{
  SDL_Window* window;
  SDL_Surface* surface;
  Game* game; 
  
public:
  Renderer();
  Renderer(Game* g);
  SDL_Window* Start();
  void Render(std::string inputWord);
  void RenderLostScreen();
  void RenderWonScreen();
  void RenderInputWord(std::string word);
  void Stop();
};

#endif
