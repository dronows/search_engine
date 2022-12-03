#include"invertedIndex.h"

std::mutex mtx;

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs) {
  size_t doc_id = 0;
  std::vector<std::thread> th;
  for (auto doc : input_docs) {
	auto f = ([this](auto doc, size_t doc_id) {
	  std::map<std::string, size_t> word_count;
	  for (int i = 0; i < doc.size(); i++) {
		std::string str;
		while (isalnum(doc[i]))
		{
		  str += doc[i++];
		}
		if (!str.empty()) word_count[str] += 1;
	  }
	  mtx.lock();
	  for (auto el : word_count) {
		Entry entry = { doc_id, el.second };
		freq_dictionary[el.first].push_back(entry);
	  }
	  mtx.unlock();
	  });
	std::thread t(f, doc, doc_id);
	th.push_back(std::move(t));
	++doc_id;
  }
  for (auto& t : th) t.join();
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word) {

  std::map<std::string, std::vector<Entry>>::iterator it = freq_dictionary.find(word);
  if (it != freq_dictionary.end()) return it->second;
  return {};
}