#pragma once

#include <sstream>
#include <vector>
#include <map>
#include <thread>
#include <mutex>
#include <algorithm>

struct Entry {
  size_t doc_id, count = 0;
  Entry(size_t in_doc_id, size_t in_count) : doc_id(in_doc_id), count(in_count) {}
  // Данный оператор необходим для проведения тестовых сценариев
  bool operator ==(const Entry& other) const {
	return (doc_id == other.doc_id &&
	  count == other.count);
  }

};
class InvertedIndex {
public:
  InvertedIndex() = default;
  std::string GetWord(const std::string& doc, size_t& index) const;
  void UpdateDocumentBase(const std::vector<std::string>& input_docs);
  std::vector<Entry> GetWordCount(const std::string& word) const;
private:
  std::map<std::string, std::vector<Entry>> freq_dictionary;
  void ThreadUpdateDoc(const std::string doc, size_t doc_id);
};


