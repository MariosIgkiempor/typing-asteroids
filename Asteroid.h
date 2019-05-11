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
  Vec2D vecPosition;  // Position of the asteroid on the window
  Vec2D vecVelocity;  // Velocity of the asteroid in both axises
  std::string sWord;  // The word of the asteroid
  SDL_Color color;    // Color of the astroid on the screen
  bool bIsPowerup;    // Flag indicating if the asteroid is a powerup

public:
  Asteroid();
  Asteroid(Vec2D p, std::string w);
  bool OffScreen();
  std::string GetWord();
  Vec2D GetPosition();
  Vec2D GetVelocity();
  void SetVelocity(Vec2D v);
  void SetPosition(Vec2D v);
  SDL_Color GetColor();
  bool IsPowerup();
  void Update();
  virtual void Show(SDL_Surface* surface);
};

#endif
