#include "Asteroid.h"

Asteroid::Asteroid(Vec2D p, std::string w)
{
  vecPosition = p;
  sWord = w;
}

Asteroid Asteroid::destroy() 
{
}

bool Asteroid::OffScreen()
{
  return vecPosition.y >= WINDOW_HEIGHT;
}

void Asteroid::Update()
{
  vecPosition.y += 5;
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
