#include "Asteroid.h"

Asteroid::Asteroid(){}
Asteroid::Asteroid(Vec2D p, std::string w)
{
  vecPosition = p;
  vecVelocity = { rand() % 6 - 3, rand() % 10 };
  sWord = w;
}

bool Asteroid::OffScreen()
{
  return vecPosition.y >= WINDOW_HEIGHT;
}

void Asteroid::Update()
{
  // Move the asteroids by the velocity
  vecPosition.x += vecVelocity.x;
  vecPosition.y += vecVelocity.y;

  // Slightly adjust the x component of the velocity
  vecVelocity.x = rand() % 6 - 3;
}

void Asteroid::Show(SDL_Surface* surface) 
{
  TTF_Font* font = TTF_OpenFont("UbuntuMono-R.ttf", 16);
  SDL_Color color = { 255.0, 255.0, 255.0 };
  SDL_Surface* textSurface = TTF_RenderText_Solid(font, sWord.c_str(), color);
  if (textSurface != NULL)
  {
    SDL_Rect destPos;
    destPos.x = vecPosition.x;
    destPos.y = vecPosition.y;
    SDL_BlitSurface(textSurface, NULL, surface, &destPos);
    SDL_FreeSurface(textSurface);
  }
  TTF_CloseFont(font);
}

std::string Asteroid::GetWord() { return sWord; }

Vec2D Asteroid::GetPosition() { return vecPosition; }
Vec2D Asteroid::GetVelocity() { return vecVelocity; }

void Asteroid::SetVelocity(Vec2D v) { vecVelocity = v; }
void Asteroid::SetPosition(Vec2D v) { vecPosition = v; }
