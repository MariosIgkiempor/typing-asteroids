#ifndef POWERUP_H
#define POWERUP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include <memory>
#include "Vec2D.h"
#include "Constants.h"
#include "Asteroid.h"

// Virtual class representing a powerup. Subclasses will inherit and modify the UsePower function to 
// implement their respective power
class Powerup : public Asteroid
{
public:
  Powerup();
  ~Powerup();
  Powerup(Vec2D p);
  virtual void UsePower(std::vector<std::shared_ptr<Asteroid>>& vObjects);
};

class PowerupSlowDown : public Powerup
{
public:
  PowerupSlowDown(Vec2D p);
  void UsePower(std::shared_ptr<Asteroid>& a);
};

class PowerupReset : public Powerup
{
public:
  PowerupReset(Vec2D p);
  void UsePower(std::shared_ptr<Asteroid>& a);
};
#endif
