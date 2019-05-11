#include "Asteroid.h"

Asteroid::Asteroid(){}
Asteroid::Asteroid(Vec2D p, std::string w)
{
  vecPosition = p;
  // Set an initial velocity, as a function of the MIN_VEL field specified in Constants.h
  vecVelocity = { rand() % MIN_VEL - (MIN_VEL/2), (rand() % (MIN_VEL*5)) + MIN_VEL };
  sWord = w;
  color = {255.0,255.0,255.0}; // Normal asteroids are white
  bIsPowerup = false;
}

// Check if an asteroid has gone off the bottom of the screen
bool Asteroid::OffScreen()
{
  return vecPosition.y >= WINDOW_HEIGHT;
}

void Asteroid::Update()
{
  // Move the asteroids by the velocity
  vecPosition.y += vecVelocity.y;
  vecPosition.x += vecVelocity.x;
  // Clamp the x position to between MARGIN and SCREEN_WIDTH - MARGIN
  if (vecPosition.x <= MARGIN) vecPosition.x = MARGIN;
  else if (vecPosition.x >= WINDOW_WIDTH - MARGIN) vecPosition.x = WINDOW_WIDTH - MARGIN;

  // Slightly adjust the x component of the velocity
  vecVelocity.x = rand() % 12 - 6;
}

// Display the word of the asteroid at its position with its color on the Surface provided
void Asteroid::Show(SDL_Surface* surface) 
{
  TTF_Font* font = TTF_OpenFont("UbuntuMono-R.ttf", 16);
  SDL_Surface* textSurface = TTF_RenderText_Solid(font, sWord.c_str(), color);
  if (textSurface != NULL)
  {
    // The position the asteroid will be drawn to
    SDL_Rect destPos;
    destPos.x = vecPosition.x;
    destPos.y = vecPosition.y;

    // Combine the surface the text is on with the given surface at the position
    SDL_BlitSurface(textSurface, NULL, surface, &destPos);
    SDL_FreeSurface(textSurface);
  }
  TTF_CloseFont(font);
}

std::string Asteroid::GetWord() { return sWord; }

Vec2D Asteroid::GetPosition() { return vecPosition; }
Vec2D Asteroid::GetVelocity() { return vecVelocity; }
SDL_Color Asteroid::GetColor() { return color; }
bool Asteroid::IsPowerup() { return bIsPowerup; }

void Asteroid::SetVelocity(Vec2D v) { vecVelocity = v; }
void Asteroid::SetPosition(Vec2D v) { vecPosition = v; }
