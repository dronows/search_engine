#include"Search_server.h"
#include <algorithm>
#include <iostream>

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& queries_input) {
  std::vector<std::vector<RelativeIndex>>  doc_Rrel;
  std::map<size_t, size_t> doc_Rabs;
  for (auto& request : queries_input) {
	std::map<size_t, size_t> doc_Rabs;
	for (int i = 0; i < request.size(); i++) {
	  std::string str;
	  while (isalnum(request[i]))
	  {
		str += request[i++];
	  }
	  if (!str.empty()) {
		std::vector<Entry> entry = _index.GetWordCount(str);
		for (auto& el : entry) {
		  doc_Rabs[el.doc_id] += el.count;
		}
	  }
	}
	auto Rabs_max = std::max_element(
	  doc_Rabs.begin(), doc_Rabs.end(),
	  [](const auto& a, const auto& b) {
		return a.second < b.second;
	  }
	);
	std::vector<RelativeIndex> temp;
	for (auto& doc : doc_Rabs) {
	  float rank = (float)doc.second / (float)Rabs_max->second;
	  temp.push_back({ doc.first, rank });
	}
	std::sort(temp.begin(), temp.end(), [](const auto& a, const auto& b)
	  {return a.rank > b.rank; });
	if (temp.size() > 5) temp.erase(temp.begin() + 5, temp.end());
	doc_Rrel.push_back(temp);
  }
  return doc_Rrel;
}