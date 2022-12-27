#include "Search_server.h"
#include <iostream>

size_t SearchServer::GetResponsesLimit() const {
  std::ifstream inFile("resources\\config.json");
  nlohmann::json j;
  inFile >> j;
  if (j["config"].contains("max_responces")) {
	return j["config"]["max_responces"];
  } else {
	return 5;
  }
}

//---------------------------------------------------------------------------------

std::map<size_t, size_t> SearchServer::GetABSRelevance(const std::string& request) const {
  std::map<size_t, size_t> abs_relevance;
  for (size_t i = 0; i < request.size(); i++) {
	std::string word = _index.GetWord(request, i);
	if (!word.empty()) {
	  std::vector<Entry> entry = _index.GetWordCount(word);
	  for (const auto& el : entry) {
		abs_relevance[el.doc_id] += el.count;
	  }
	}
  }
  return abs_relevance;
}

//------------------------------------------------------------------------------

std::vector<RelativeIndex> SearchServer::GetRelRelevance(const std::map<size_t, size_t>& abs_relevance, size_t responces_limit) const {
  auto Rabs_max = std::max_element(
	abs_relevance.begin(), abs_relevance.end(),
	[](const auto& a, const auto& b) {
	  return a.second < b.second;
	}
  );
  std::vector<RelativeIndex> rel_relevance;
  for (const auto& doc_id : abs_relevance) {
	float rank = (float)doc_id.second / (float)Rabs_max->second;
	rel_relevance.push_back({ doc_id.first, rank });
  }
  std::sort(rel_relevance.begin(), rel_relevance.end(), [](const auto& a, const auto& b)
	{return a.rank > b.rank; });
  if (rel_relevance.size() > responces_limit) rel_relevance.erase(rel_relevance.begin() + responces_limit, rel_relevance.end());
  return rel_relevance;
}

//-----------------------------------------------------------------------------------------------

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& queries_input) const {
  std::vector<std::vector<RelativeIndex>>  doc_Rrel;
  for (const auto& request : queries_input) {
	std::map<size_t, size_t> doc_Rabs(GetABSRelevance(request));
	doc_Rrel.push_back(GetRelRelevance(doc_Rabs, GetResponsesLimit()));
	//std::cout << GetResponsesLimit() << std::endl;
  }
  return doc_Rrel;
}
