#ifndef ASTEROID_H
#define ASTEROID_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "Vec2D.h"
#include "Constants.h"

class Asteroid
{
protected:
  Vec2D vecPosition;
  Vec2D vecVelocity;
  std::string sWord;

public:
  Asteroid();
  Asteroid(Vec2D p, std::string w);
  bool OffScreen();
  std::string GetWord();
  Vec2D GetPosition();
  Vec2D GetVelocity();
  void SetVelocity(Vec2D v);
  void SetPosition(Vec2D v);
  void Update();
  void Show(SDL_Surface* surface);
};

#endif
