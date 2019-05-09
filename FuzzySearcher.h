#ifndef FUZZYSEARCHER_H
#define FUZZYSEARCHER_H

#include <string>
#include <vector>

class FuzzySearcher {
private:
  std::string file;
  std::string pattern;
public:
  void FuzzySearch();
  int Search();
  int EditDistance(std::string a, std::string b);
};

#endif
