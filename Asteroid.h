#ifndef ASTEROID_H
#define ASTEROID_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "Vec2D.h"
#include "Constants.h"

class Asteroid
{
  Vec2D vecPosition;
  std::string sWord;

public:
  Asteroid(Vec2D p, std::string w);
  Asteroid destroy();
  bool OffScreen();
  std::string GetWord();
  Vec2D GetPosition();
  void Update();
  void Show(SDL_Surface* surface);
};

#endif
