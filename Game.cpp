#include "Game.h"
#include "FuzzySearcher.h"

// HELPERS --------------------------------------------------------------------
std::vector<std::string> ReadWords()
{
  std::ifstream file("words");
  std::vector<std::string> words;
  std::string word;
  while (std::getline(file, word))
    words.push_back(word);

  return words;
}

std::vector<std::string> InitialiseWordsForGame(int nMaxLength)
{
  // Get all the words from the words file
  std::vector<std::string> words = ReadWords();
  // Remove all the words that are less than the size of the difficulty
  words.erase(std::remove_if(std::begin(words), std::end(words), [&](std::string a) { return a.length() > nMaxLength; }), std::end(words));
  // Sort them in ascending order of size
  std::sort(std::begin(words), std::end(words), [](std::string a, std::string b) { return a.length() > b.length(); });
  return words;
}

Asteroid Game::CreateAsteroid(std::vector<std::string> possibleWords)
{
  int x = rand() % (WINDOW_WIDTH - MARGIN);
  int y = rand() % (WINDOW_HEIGHT / 2);
  int wordIndex = rand() % possibleWords.size();
  Asteroid a({x, y}, possibleWords[wordIndex]);
  return a;
}

Game::Game()
{
  bRunning = false;
}

int Game::FindClosestAsteroidIndex() 
{
  // Find the asteroid whose word has the smallest string distance
  // If the distance between an asteroid and the input word is 0, return that asteroid immediately
  if (vAsteroids.empty()) return -1;

  FuzzySearcher searcher;
  int nSmallestDistance = searcher.EditDistance(sInputWord, vAsteroids[0].GetWord());
  int closestAsteroidIndex = 0;
  for (std::size_t i = 0; i < vAsteroids.size(); ++i)
  {
    int nEditDist = searcher.EditDistance(sInputWord, vAsteroids[i].GetWord());
    if (nEditDist == 0) return i;
    if (nEditDist < nSmallestDistance)
    {
      nSmallestDistance = nEditDist;
      closestAsteroidIndex = i;
    }
  }
  nRecentDistance = nSmallestDistance;
  return closestAsteroidIndex;
}

void Game::Start()
{
  // Initialise the asteroids
  auto possibleWords = InitialiseWordsForGame(DIFFICULTY);
  for (std::size_t i = 0; i < DIFFICULTY * 1; ++i)
  {
    Asteroid a = CreateAsteroid(possibleWords);
    vAsteroids.push_back(a);
  }

  // Start the rendering engine
  renderer = new Renderer(this);
  SDL_Window* windowPtr = renderer->Start();
  if (windowPtr != NULL) 
    window = windowPtr;
  inputHandler = new InputHandler(renderer);

  bRunning = true;
  bWordEntered = false;
}

void Game::Run()
{
  while (bRunning)
  {
    // Handle events
    inputHandler->HandleEvents(this);
    // Update logic
    if (bWordEntered)
    {
      std::cout << sInputWord << std::endl;
      // Find asteroid
      int closestAsteroidIndex = FindClosestAsteroidIndex();
      if (closestAsteroidIndex >= 0)
      {
        vAsteroids.erase(vAsteroids.begin() + closestAsteroidIndex);
        if (vAsteroids[closestAsteroidIndex].GetWord() == sInputWord) 
        {
          std::cout << "success" << std::endl;
        }
        else
        {
          // If the asteroid's word length - the edit distance between that word and the asteroid is greater than 3
          // spawn a new rocket and push it to the vector
          int nNewAsteroidSize = vAsteroids[closestAsteroidIndex].GetWord().length() - nRecentDistance;
          if (nNewAsteroidSize > 3)
          {
            auto possibleWords = InitialiseWordsForGame(nNewAsteroidSize);
            Asteroid a = CreateAsteroid(possibleWords);
            vAsteroids.push_back(a);
          }
        }
      }


      SetInputWord("");
      SetTempInputWord("");
      bWordEntered = false;
    }

    // Win condition - all words have been destroyed
    if (vAsteroids.empty())
    {
      renderer->RenderWonScreen();
      SDL_Delay(5000);
      bRunning = false;
      break;
    }

    // Lose condition - any word's y location is at the bottom of the screen
    for (auto a : vAsteroids)
    {
      if (a.GetPosition().y > WINDOW_HEIGHT - 20)
      {
        bRunning = false;
        renderer->RenderLostScreen();
        SDL_Delay(5000);
        break;
      }
    }
    // Skip the rest of the logic updates and rendering - the game has been lost
    if (!bRunning) break;

    for (auto &a : vAsteroids)
      a.Update();

    // Render 
    renderer->Render(sTempInputWord);
    SDL_Delay(1000);
  }
}

void Game::Update() 
{
  for (auto a : vAsteroids)
  {
    a.Update();
  }
}

void Game::SetInputWord(std::string w)
{
  if (sInputWord != w)
  {
    sInputWord = w;
    bWordEntered = true;
  }
}

void Game::SetTempInputWord(std::string w) { sTempInputWord = w; }
std::string Game::GetTempInputWord() { return sTempInputWord; }

std::vector<Asteroid> Game::GetAsteroids() { return this->vAsteroids; }
