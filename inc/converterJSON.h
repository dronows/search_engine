
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "nlohmann/json.hpp"


struct RelativeIndex {
  size_t doc_id;
  float rank;
  RelativeIndex(size_t _doc_id, float _rank) : doc_id(_doc_id), rank(_rank) {}
  bool operator ==(const RelativeIndex& other) const {
	return (doc_id == other.doc_id && rank == other.rank);
  }
};

class ConverterJSON {
public:
  ConverterJSON() = default;
  std::vector<std::string> GetTextDocuments() const;
  std::vector<std::string> GetRequests() const;
  void putAnswers(const std::vector<std::vector<RelativeIndex>>& answers) const;
};

