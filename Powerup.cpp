#include "Powerup.h"

Powerup::Powerup(Vec2D p)
{
  vecPosition = p;
  //SetFont(TTF_OpenFont("UbuntuMono-R.ttf", 16));
  //SetColor({ 0, 255.0, 100.0 });
  vecVelocity = { 0, 50 };
}

Powerup::Powerup() {}

Powerup::~Powerup() {}

PowerupSlowDown::PowerupSlowDown(Vec2D p):Powerup(p)
{
  sWord = "slowdown";
}

void Powerup::Show(SDL_Surface* surface) 
{
  TTF_Font* font = TTF_OpenFont("UbuntuMono-R.ttf", 16);
  SDL_Color color = { 0, 255.0, 100.0 };
  SDL_Surface* textSurface = TTF_RenderText_Solid(font, sWord.c_str(), color);
  if (textSurface != NULL)
  {
    SDL_Rect destPos;
    destPos.x = GetPosition().x;
    destPos.y = GetPosition().y;
    SDL_BlitSurface(textSurface, NULL, surface, &destPos);
    SDL_FreeSurface(textSurface);
  }
  TTF_CloseFont(font);
}

void PowerupSlowDown::UsePower(std::vector<Asteroid*>& vObjects)
{
  for (std::size_t i = 0; i < vObjects.size(); ++i)
  {
    Vec2D vecCurrentVel = vObjects[i]->GetVelocity();
    vecCurrentVel.y -= 5;
    vObjects[i]->SetVelocity(vecCurrentVel);
  }
}

PowerupReset::PowerupReset(Vec2D p):Powerup(p)
{
  sWord = "reset";
}

void PowerupReset::UsePower(std::vector<Asteroid*>& vObjects)
{
  for (std::size_t i = 0; i < vObjects.size(); ++i)
  {
    Vec2D vecCurrentPos = vObjects[i]->GetPosition();
    vecCurrentPos.y = 0;
    vObjects[i]->SetPosition(vecCurrentPos);
  }
}
