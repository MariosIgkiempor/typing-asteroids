#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include "Renderer.h"
#include "InputHandler.h"
#include "Asteroid.h"
#include "Constants.h"

class Renderer;
class InputHandler;
class Game
{
  Renderer* renderer;
  InputHandler* inputHandler;
  SDL_Window* window;
  std::vector<Asteroid> vAsteroids;
  bool bRunning;
  bool bWordEntered;
  std::string sInputWord;
  std::string sTempInputWord;
  int nRecentDistance;
  Asteroid CreateAsteroid(std::vector<std::string> possibleWords);

public:
  Game();
  int FindClosestAsteroidIndex();
  void Start();
  void Run();
  void Update();
  void SetInputWord(std::string w);
  void SetTempInputWord(std::string w);
  std::string GetTempInputWord();
  std::vector<Asteroid> GetAsteroids();
};

#endif
