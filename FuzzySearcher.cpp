#include "FuzzySearcher.h"

void FuzzySearcher::FuzzySearch() 
{
  // Find all substrings of length(pattern) in str
  std::vector<std::string> substrings;
  long int len = this->file.length(), substrCount = 0;
  for (std::size_t i = 0; i < len - this->pattern.length() - 1; ++i)
  {
      substrings.push_back(this->file.substr(i, this->pattern.length()));
  }

  // Compute Levenshtein distance from pattern to all substrings
  std::vector<int> distances;
  for (std::size_t i = 0; i < substrings.size(); ++i)
  {
      int ed = this->EditDistance(pattern, substrings[i]);
      distances.push_back(ed);
  }

  // Return index of most similar substring
  int minDistance = distances[0];
  int minIndex = 0;
  for (std::size_t i = 1; i < distances.size(); ++i)
  {
      if (distances[i] < minDistance)
      {
          minDistance = distances[i];
          minIndex = i;
      }
  }
}

int FuzzySearcher::Search() 
{
    int count = 0;                                  // Number of occurances of the pattern in the string str
    size_t index = this->file.find(this->pattern, 0); // Index of the first occurance of the pattern
    while (index != std::string::npos)                   // Keep looking through the rest of the string while an occurance of pattern has been found
    {
      count++;                                    // A match of pattern has been found, increase count
      index = this->file.find(this->pattern, index + 1);  // Look at the rest of the string after the last occurance
    }
    return count;
}

// Implementation of the Levenshtein distance between two strings
int FuzzySearcher::EditDistance(std::string a, std::string b)
{
  // Initialise the matrix of edit distances
  unsigned long rows = b.length() + 1;
  unsigned long cols = a.length() + 1;
  std::vector<std::vector<int>> matrix(rows);
  for (std::size_t i = 0; i < rows; ++i)
    matrix[i] = std::vector<int>(cols);

  // Populate the first row and first column with numbers 0 - a.length() and 0 - b.length()
  for (std::size_t i = 0; i < matrix[0].size(); ++i)
    matrix[0][i] = i;
  for (std::size_t i = 0; i < rows; ++i)
    matrix[i][0] = i;

  for (std::size_t i = 1; i < rows; ++i)
    for (std::size_t j = 1; j < cols; ++j)
      // If the two characters currently being compared are not the same
      if (b[i - 1] != a[j - 1]) 
      { 
        // Find the minimum of the three cells to the left, above and top left of the current cell
        int replaceCost = matrix[i - 1][j - 1];
        int deleteCost = matrix[i][j - 1];
        int insertCost = matrix[i - 1][j];
        int min = replaceCost < deleteCost ? replaceCost : deleteCost;
        min = min < insertCost ? min : insertCost;
        matrix[i][j] = min + 1;
      }
      // Else the two characters being compared are the same, set the cost to the cost of replacing the letter
      // We dont need to add one because the characters are the same, there is nothing to add
      else 
        matrix[i][j] = matrix[i - 1][j - 1];

  // Print the matrix
  // cout << "    ";
  // for (int i = 0; i < a.length(); ++i)
  //     cout << a[i] << " ";
  // cout << endl;
  // for (int i = 0; i < rows; i++)
  // {
  //     if (i != 0)
  //         cout << b[i - 1] << " ";
  //     else
  //         cout << "  ";
  //     for (int j = 0; j < matrix[i].size(); j++)
  //     {
  //         cout << matrix[i][j] << " ";
  //     }
  //     cout << endl;
  // }

  return matrix[rows - 1][cols - 1];
}
