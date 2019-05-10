#ifndef POWERUP_H
#define POWERUP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include "Vec2D.h"
#include "Constants.h"
#include "Asteroid.h"

// Virtual class representing a powerup. Subclasses will inherit and modify the UsePower function to 
// implement their respective power
class Powerup : public Asteroid
{
public:
  Powerup();
  Powerup(Vec2D p);
  ~Powerup();
  void Show(SDL_Surface* surface);
  virtual void UsePower(std::vector<Asteroid*>& vAsteroids) = 0;
};

class PowerupSlowDown : public Powerup
{
  PowerupSlowDown(Vec2D p);
  void UsePower(std::vector<Asteroid*>& vObjectes);
};

class PowerupReset : public Powerup
{
  PowerupReset(Vec2D p);
  void UsePower(std::vector<Asteroid*>& vObjects);
};
#endif
