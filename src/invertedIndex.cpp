#include "invertedIndex.h"

std::mutex mtx;

std::string InvertedIndex::GetWord(const std::string& doc, int& index) const {
  std::string str;
  while (isalnum(doc[index]))
  {
	str += doc[index++];
  }
  return str;
}
//----------------------------------------------------------------------------

void InvertedIndex::ThreadUpdateDoc(const std::string doc, size_t doc_id) {
  std::map<std::string, size_t> word_freq;
  for (int i = 0; i < doc.size(); i++) {
	std::string word = GetWord(doc, i);
	if (!word.empty()) word_freq[word] += 1;
  }
  mtx.lock();
  for (auto el : word_freq) {
	Entry entry = { doc_id, el.second };
	freq_dictionary[el.first].push_back(entry);
  }
  mtx.unlock();
}

//---------------------------------------------------------------------------------

void InvertedIndex::UpdateDocumentBase(const std::vector<std::string>& input_docs) {
  size_t doc_id = 0;
  std::vector<std::thread> th;
  for (auto doc : input_docs) {
	std::thread t(&InvertedIndex::ThreadUpdateDoc, this, doc, doc_id);
	th.push_back(std::move(t));
	++doc_id;
  }

  for (auto& t : th) t.join();
  for (auto it = freq_dictionary.begin(); it != freq_dictionary.end(); ++it) {
	std::sort(it->second.begin(), it->second.end(), [](const auto& a, const auto& b) {return a.doc_id < b.doc_id; });
  }
}

//---------------------------------------------------------------------------------------

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word) const {
  std::map<std::string, std::vector<Entry>>::const_iterator it = freq_dictionary.find(word);
  if (it != freq_dictionary.end()) return it->second;
  return {};
}