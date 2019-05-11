#include "Game.h"
#include "FuzzySearcher.h"

// HELPERS --------------------------------------------------------------------
// Read all the words in the word file and return them in a vector of strings
std::vector<std::string> ReadWords()
{
  std::ifstream file("words");
  std::vector<std::string> words;
  std::string word;
  while (std::getline(file, word))
    words.push_back(word);

  return words;
}

// Prepare the list of words for the game by reading all the words and removing those that are longer than the given max length
std::vector<std::string> InitialiseWordsForGame(int nMaxLength)
{
  // Get all the words from the words file
  std::vector<std::string> words = ReadWords();
  // Remove all the words that are less than the size of the difficulty
  words.erase(std::remove_if(std::begin(words), std::end(words), [&](std::string a) { return a.length() > nMaxLength; }), std::end(words));
  return words;
}

// Create an asteroid at a random position with a random with from a list of possible words
Asteroid Game::CreateAsteroid(std::vector<std::string> possibleWords)
{
  int x = rand() % (WINDOW_WIDTH - MARGIN);
  int y = rand() % (WINDOW_HEIGHT / 2);
  int wordIndex = rand() % possibleWords.size();
  return Asteroid({x, y}, possibleWords[wordIndex]);
}

Game::Game()
{
}

// Find the asteroid whose word has the smallest edit distance to the input word
// If the distance between an asteroid and the input word is 0, return that asteroid immediately
int Game::FindClosestAsteroidIndex() 
{
  if (vAsteroids.empty()) return -1;

  FuzzySearcher searcher;
  int nSmallestDistance = searcher.EditDistance(sInputWord, vAsteroids[0]->GetWord());
  int closestAsteroidIndex = 0;
  for (std::size_t i = 0; i < vAsteroids.size(); ++i)
  {
    int nEditDist = searcher.EditDistance(sInputWord, vAsteroids[i]->GetWord());
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
  for (std::size_t i = 0; i < DIFFICULTY * 2; ++i)
  {
    Asteroid a = CreateAsteroid(possibleWords);
    vAsteroids.push_back(std::make_shared<Asteroid>(a));
  }

  // Start the rendering engine
  renderer = new Renderer(this);
  SDL_Window* windowPtr = renderer->Start();
  if (windowPtr != NULL) 
    window = windowPtr;

  // Create an input handler with an instance of the renderer so that, on quit, the renderer can clean up
  inputHandler = new InputHandler(renderer);

  bRunning = true;
  bWordEntered = false;
}

void Game::Run()
{
  // Main game loop. Will run while the game is playing
  while (bRunning)
  {
    // Handle events
    inputHandler->HandleEvents(this);

    // Update logic and game state
    if (bWordEntered)
    {
      // Find asteroid
      int closestAsteroidIndex = FindClosestAsteroidIndex();
      if (closestAsteroidIndex >= 0)
      {
        // If the input word was an exact match with one of the asteroids
        if (vAsteroids[closestAsteroidIndex]->GetWord() == sInputWord)
        {
          // Handle the case that the asteroid destroyed was a powerup
          if (vAsteroids[closestAsteroidIndex]->IsPowerup())
          {
            // Reset powerup
            if (vAsteroids[closestAsteroidIndex]->GetWord() == "reset")
            {
              // Cast the asteroid to a PowerupReset so we can use the right UsePower method
              auto r = std::dynamic_pointer_cast<PowerupReset>(vAsteroids[closestAsteroidIndex]);
              for (auto& a : vAsteroids)
                r->UsePower(a);
            }
            // Slow down powerup
            else if (vAsteroids[closestAsteroidIndex]->GetWord() == "slowdown")
            {
              // Cast the asteroid to a PowerupSlowDown so we can use the right UsePower method
              auto r = std::dynamic_pointer_cast<PowerupSlowDown>(vAsteroids[closestAsteroidIndex]);
              for (auto& a : vAsteroids)
                r->UsePower(a);
            }
          }
        }
        // The input word din't match exactly
        else
        {
          // If the asteroid's word length - the edit distance between that word and the asteroid is greater than 3
          // spawn a new rocket of size the difference and push it to the vector
          int nNewAsteroidSize = vAsteroids[closestAsteroidIndex]->GetWord().length() - nRecentDistance;
          if (nNewAsteroidSize > 3)
          {
            auto possibleWords = InitialiseWordsForGame(nNewAsteroidSize);
            Asteroid a = CreateAsteroid(possibleWords);
            vAsteroids.push_back(std::make_shared<Asteroid>(a));
          }
        }
        // Delete the destroyed asteroid
        vAsteroids.erase(vAsteroids.begin() + closestAsteroidIndex);
      }

      // Reset input parameters once we have handled an input
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
      return;
    }

    // Lose condition - any word's y location is at the bottom of the screen
    // unless it is a powerup
    for (std::size_t i = 0; i < vAsteroids.size(); ++i)
    {
      if (!vAsteroids[i]->IsPowerup() && vAsteroids[i]->GetPosition().y >= WINDOW_HEIGHT - 20 )
      {
        bRunning = false;
        renderer->RenderLostScreen();
        SDL_Delay(5000);
        return;
      }
    }

    // Spawn powerups given some probability in Constants.h
    if ((float) rand() / RAND_MAX < POWERUP_PROBABILITY)
    {
      if ((float) rand() / RAND_MAX < 0.5)
      {
        // Spawn a slow down powerup with 50% probability
        PowerupSlowDown p({ rand() % WINDOW_WIDTH, 0 });
        vAsteroids.push_back(std::make_shared<Asteroid>(p));
      }
      else
      {
        // Spawn a reset powerup with 50% probability
        PowerupReset p({ rand() % WINDOW_WIDTH, 0 });
        vAsteroids.push_back(std::make_shared<Asteroid>(p));
      }
    }

    // Make all asteroids update their own locations
    for (std::size_t i = 0; i < vAsteroids.size(); ++i)
      vAsteroids[i]->Update();

    // Render everything
    renderer->Render(sTempInputWord);
    SDL_Delay(1000);
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

std::vector<std::shared_ptr<Asteroid>> Game::GetAsteroids() { return this->vAsteroids; }
