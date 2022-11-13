
#include "search_engine.h"
#include "json_config.h"



nlohmann::json ConverterJSON::AddFile(std::vector<std::string> files) {
  nlohmann::json jF = files;
  std::map<std::string, nlohmann::json> confMap{ {"config",jConf},{"files",jF} };
  nlohmann::json confJson(confMap);
  return confJson;
}



//--------------------------------------------------------
std::vector<std::string> ConverterJSON::GetTextDocuments() {
  std::ifstream inFile("config.json");
  nlohmann::json j;
  inFile >> j;
  std::vector<std::string> v = j["files"];
  inFile.close();
  return v;
}
//-----------------------------------------------------------

int ConverterJSON::GetResponsesLimit() {
  std::ifstream inFile("config.json");
  nlohmann::json j;
  inFile >> j;
  int temp = j["config"]["max_responces"];
  inFile.close();
  return temp;
}
//-------------------------------------------------------------

std::vector<std::string> ConverterJSON::GetRequests() {
  std::ifstream inFile("requests.json");
  nlohmann::json j;
  inFile >> j;
  std::vector<std::string > v = j["requests"];
  inFile.close();
  return v;
}
//---------------------------------------------------------------------------------
void ConverterJSON::AddRequests(std::vector <std::string>& requests) {
  std::ofstream outFile("requests.json");
  nlohmann::json js;
  js["requests"] = requests;
  outFile << std::setw(4) << js;
  outFile.close();
}
//---------------------------------------------------------------------------------------
void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>>answers) {
  nlohmann::json Js;
  int requestsCount = 0;
  for (auto& el : answers) {
	++requestsCount;
	std::string requestsStr = "requests" + std::to_string(requestsCount);
	for (auto& et : el) {
	  if (el.size() > 1) {
		Js["answer"][requestsStr]["responce"] += { {"docid", et.first}, { "rank", et.second }};
	  
	  } else {
	  Js["answer"][requestsStr] = { {"docid", et.first}, { "rank",et.second } };
	  }
	}
  }
  std::ofstream outFile("resources\\answer.json");
  outFile << std::setw(4) << Js;
  outFile.close();
}
//-----------------------------------------------------------------------------------------------
std::vector<std::vector<std::pair<int, float>>> ConverterJSON::getAnswer() {
  std::ifstream inFile("answer.json");
  nlohmann::json j;
  inFile >> j;
  std::vector<std::vector<std::pair<int, float>>> fromAnswer;
  nlohmann::json temp;
  int requestsCount = 1;
  while (j["answer"].contains("requests" + std::to_string(requestsCount))) {
    for (nlohmann::json::iterator it1 = j.begin(); it1 != j.end(); ++it1) {
      temp = it1.value()["requests" + std::to_string(requestsCount)];
      std::vector<std::pair<int, float>> pairs;
      if (temp.contains("responce")) {
        nlohmann::json js = temp["responce"];
        for (nlohmann::json::iterator it = js.begin(); it != js.end(); ++it) {
          pairs.push_back(std::make_pair(it.value()["docid"], it.value()["rank"]));
        }
        fromAnswer.push_back(pairs);
      }
      else {
        pairs.push_back(std::make_pair(temp["docid"], temp["rank"]));
        fromAnswer.push_back(pairs);
      }
    }
    requestsCount++;
  }
  return fromAnswer;
}
