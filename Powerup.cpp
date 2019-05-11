#include <iostream>
#include "Powerup.h"

Powerup::Powerup(Vec2D p)
{
  vecPosition = p;
  vecVelocity = { 0, 50 };
  color = {255.0,0.0,100.0}; // Powerups are purple
  bIsPowerup = true;
}

Powerup::Powerup() {}

Powerup::~Powerup() {}

PowerupSlowDown::PowerupSlowDown(Vec2D p):Powerup(p)
{
  sWord = "slowdown";
}

void Powerup::UsePower(std::vector<std::shared_ptr<Asteroid>>& vObjects) {}

// Slows down an asteroid, down to a minimum of MIN_VEL
void PowerupSlowDown::UsePower(std::shared_ptr<Asteroid>& a)
{
  Vec2D vecCurrentVel = a->GetVelocity();
  vecCurrentVel.y -= 5;
  if (vecCurrentVel.y < MIN_VEL) vecCurrentVel.y = MIN_VEL;
  a->SetVelocity(vecCurrentVel);
}

PowerupReset::PowerupReset(Vec2D p):Powerup(p)
{
  sWord = "reset";
}

// Resets the Y coordinate of an asteroid to 0
void PowerupReset::UsePower(std::shared_ptr<Asteroid>& a)
{
    Vec2D vecCurrentPos = a->GetPosition();
    vecCurrentPos.y = 0;
    a->SetPosition(vecCurrentPos);
}
