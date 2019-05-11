#include "Renderer.h"

// Default constructor
Renderer::Renderer() {}

// Construct a renderer with a pointer to a Game instance
Renderer::Renderer(Game* g)
{
  game = g;
}

SDL_Window* Renderer::Start()
{
  // Initialise SDL and ensure it didn't fail
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    std::cout << "ERROR: could not initialise SDL\n" << SDL_GetError() << std::endl;
  else
  {
    // Initialise TTF SDL library and ensure it didn't fail
    if (TTF_Init() < 0)
      std::cout << "ERROR: could not initialise TTF\n" << std::endl;
    else
    {
      // Create the window and ensure creation didn't fail
      window = SDL_CreateWindow("TypeRoids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
      if (window == NULL)
        std::cout << "ERROR: could not create window\n" << SDL_GetError() << std::endl;
      else
      {
        // Store a pointer to the surface
        surface = SDL_GetWindowSurface(window);
        return window;
      }
    }
  }
  return NULL;
}

void Renderer::Render(std::string inputWord = "")
{
  SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0x00, 0x00, 0x00));
  auto vAsteroids = game->GetAsteroids();
  for (std::size_t i = 0; i < vAsteroids.size(); ++i) vAsteroids[i]->Show(surface);
  RenderInputWord(inputWord);
  SDL_UpdateWindowSurface(window);
}

void Renderer::RenderInputWord(std::string word)
{
  TTF_Font* font = TTF_OpenFont("UbuntuMono-R.ttf", 16);
  SDL_Color color = { 0.0, 255.0, 0.0 };
  SDL_Surface* textSurface = TTF_RenderText_Solid(font, word.c_str(), color);
  if (textSurface != NULL)
  {
    SDL_Rect destPos;
    destPos.x = WINDOW_WIDTH * 0.75;
    destPos.y = WINDOW_HEIGHT * 0.9;
    SDL_BlitSurface(textSurface, NULL, surface, &destPos);
    SDL_FreeSurface(textSurface);
  }
  TTF_CloseFont(font);
}

void Renderer::RenderWonScreen()
{
  SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0x00, 0xF0, 0x00));

  TTF_Font* font = TTF_OpenFont("UbuntuMono-R.ttf", 72);
  SDL_Color color = { 255.0, 255.0, 255.0 };
  SDL_Surface* textSurface = TTF_RenderText_Solid(font, "YOU WON!", color);
  if (textSurface != NULL)
  {
    SDL_Rect destPos;
    destPos.x = WINDOW_WIDTH / 2;
    destPos.y = WINDOW_HEIGHT / 2;
    SDL_BlitSurface(textSurface, NULL, surface, &destPos);
    SDL_FreeSurface(textSurface);
  }
  TTF_CloseFont(font);
  SDL_UpdateWindowSurface(window);
}

void Renderer::RenderLostScreen()
{
  SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xF0, 0x00, 0x00));

  TTF_Font* font = TTF_OpenFont("UbuntuMono-R.ttf", 72);
  SDL_Color color = { 255.0, 255.0, 255.0 };
  SDL_Surface* textSurface = TTF_RenderText_Solid(font, "YOU LOST!", color);
  if (textSurface != NULL)
  {
    SDL_Rect destPos;
    destPos.x = WINDOW_WIDTH / 2;
    destPos.y = WINDOW_HEIGHT / 2;
    SDL_BlitSurface(textSurface, NULL, surface, &destPos);
    SDL_FreeSurface(textSurface);
  }
  TTF_CloseFont(font);
  SDL_UpdateWindowSurface(window);
}

void Renderer::Stop()
{
  if (window != NULL) SDL_DestroyWindow(window);
  SDL_Quit();
}
