
#pragma once
#include "invertedIndex.h"
#include "converterJSON.h"




class SearchServer {
public:
  SearchServer(InvertedIndex& idx) : _index(idx) { };
  std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input) const;
private:
  InvertedIndex& _index;
  size_t GetResponsesLimit()const;
  std::map<size_t, size_t> GetABSRelevance(const std::string& request)const;
  std::vector<RelativeIndex> GetRelRelevance(const std::map<size_t, size_t>& abs_relevance, size_t responces_limit) const;
};