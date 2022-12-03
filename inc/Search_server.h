#pragma once
#include "invertedIndex.h"
#include "converterJSON.h"




class SearchServer {
public:
  SearchServer(InvertedIndex& idx) : _index(idx) { };
  std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input);
private:
  InvertedIndex  _index;
};


