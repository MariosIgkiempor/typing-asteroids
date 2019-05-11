#include "InputHandler.h"

InputHandler::InputHandler() {}
InputHandler::InputHandler(Renderer* r)
{
  renderer = r;
}

void InputHandler::HandleEvents(Game* game)
{
  // SDL queues all events, therefore we must keep polling all the events that have happened between frames
  SDL_Event event;
  while(SDL_PollEvent(&event))
  {
    switch(event.type)
    {
      case SDL_QUIT: renderer->Stop(); break;
      case SDL_KEYDOWN: 
                         {
                           // Append characters entered between frames to the temporary input string
                           std::string inputString = game->GetTempInputWord();
                           if      (event.key.keysym.sym == SDLK_a) inputString += 'a';
                           else if (event.key.keysym.sym == SDLK_b) inputString += 'b';
                           else if (event.key.keysym.sym == SDLK_c) inputString += 'c';
                           else if (event.key.keysym.sym == SDLK_d) inputString += 'd';
                           else if (event.key.keysym.sym == SDLK_e) inputString += 'e';
                           else if (event.key.keysym.sym == SDLK_f) inputString += 'f';
                           else if (event.key.keysym.sym == SDLK_g) inputString += 'g';
                           else if (event.key.keysym.sym == SDLK_h) inputString += 'h';
                           else if (event.key.keysym.sym == SDLK_i) inputString += 'i';
                           else if (event.key.keysym.sym == SDLK_j) inputString += 'j';
                           else if (event.key.keysym.sym == SDLK_k) inputString += 'k';
                           else if (event.key.keysym.sym == SDLK_l) inputString += 'l';
                           else if (event.key.keysym.sym == SDLK_m) inputString += 'm';
                           else if (event.key.keysym.sym == SDLK_n) inputString += 'n';
                           else if (event.key.keysym.sym == SDLK_o) inputString += 'o';
                           else if (event.key.keysym.sym == SDLK_p) inputString += 'p';
                           else if (event.key.keysym.sym == SDLK_q) inputString += 'q';
                           else if (event.key.keysym.sym == SDLK_r) inputString += 'r';
                           else if (event.key.keysym.sym == SDLK_s) inputString += 's';
                           else if (event.key.keysym.sym == SDLK_t) inputString += 't';
                           else if (event.key.keysym.sym == SDLK_u) inputString += 'u';
                           else if (event.key.keysym.sym == SDLK_v) inputString += 'v';
                           else if (event.key.keysym.sym == SDLK_w) inputString += 'w';
                           else if (event.key.keysym.sym == SDLK_x) inputString += 'x';
                           else if (event.key.keysym.sym == SDLK_y) inputString += 'y';
                           else if (event.key.keysym.sym == SDLK_z) inputString += 'z';
                           // If the user preses enter, set the game's input string to the current whole input string
                           else if (event.key.keysym.sym == SDLK_RETURN) game->SetInputWord(inputString);
                           game->SetTempInputWord(inputString);
                           renderer->RenderInputWord(inputString);
                         }
                         break;
    }
  }
}

