#include "converterJSON.h"


/*
void ConverterJSON::AddFile(std::vector<std::string> files) {
  std::ofstream outFile("config.json");
  nlohmann::json jF = files;
  std::map<std::string, nlohmann::json> confMap{ {"config",JSconfig},{"files",jF} };
  nlohmann::json confJson(confMap);
  outFile << std::setw(4) << confJson;
  outFile.close();
}

*/



//--------------------------------------------------------
std::vector<std::string> ConverterJSON::GetTextDocuments() const {
  std::ifstream inFile("config.json");
  nlohmann::json j;
  inFile >> j;
  inFile.close();
  std::vector<std::string> docTitle = j["files"];
  std::vector<std::string> doc;
  for (auto& path : docTitle) {
    std::ifstream inTempFile(path);
    if (inTempFile.is_open()) {
      std::string str, tempStr;
      while (!inTempFile.eof()) {
        std::getline(inTempFile, tempStr);
        str += " " + tempStr;
      }
      doc.push_back(str);
    }
    else {
      std::cerr << "file" << path << "cann not !!!" << std::endl;
    }
  }
  return doc;
}
//-----------------------------------------------------------

std::vector<std::string> ConverterJSON::GetRequests() const {
  std::ifstream inFile("requests.json");
  nlohmann::json j;
  inFile >> j;
  inFile.close();
  return  j["requests"];
}
//---------------------------------------------------------------------------------
void ConverterJSON::AddRequests(std::vector <std::string>& requests) const {
  std::ofstream outFile("requests.json");
  nlohmann::json js;
  js["requests"] = requests;
  outFile << std::setw(4) << js;
  outFile.close();
}
//---------------------------------------------------------------------------------------
void ConverterJSON::putAnswers(const std::vector<std::vector<RelativeIndex>>& answers) const {
  nlohmann::json Js;
  int requestsCount = 0;
  for (auto& answer : answers) {
    ++requestsCount;
    std::string requestsStr = "requests" + std::to_string(requestsCount);
    if (answer.empty()) Js["answer"][requestsStr]["rezult"] = false;
    for (auto& doc : answer) {
      if (answer.size() > 1) {
        Js["answer"][requestsStr]["rezult"] = true;
        Js["answer"][requestsStr]["relevance"] += { {"docid", doc.doc_id}, { "rank", doc.rank } };
      }
      else if (answer.size() == 1) {
        Js["answer"][requestsStr] = { {"docid", doc.doc_id}, { "rank", doc.rank } };
        Js["answer"][requestsStr]["rezult"] = true;
      }
    }
  }
  std::ofstream outFile("answer.json");
  outFile << std::setw(4) << Js;
  outFile.close();
}
//-----------------------------------------------------------------------------------------------
/*
std::vector<std::vector<RelativeIndex>> ConverterJSON::getAnswer() {
  std::ifstream inFile("answer.json");
  nlohmann::json j;
  inFile >> j;
  std::vector<std::vector<RelativeIndex>> fromAnswer;
  nlohmann::json temp;
  int requestsCount = 1;
  while (j["answer"].contains("requests" + std::to_string(requestsCount))) {
    for (nlohmann::json::iterator it1 = j.begin(); it1 != j.end(); ++it1) {
      temp = it1.value()["requests" + std::to_string(requestsCount)];
      std::vector<RelativeIndex> pairs;
      if (temp.contains("responce")) {
        nlohmann::json js = temp["responce"];
        for (nlohmann::json::iterator it = js.begin(); it != js.end(); ++it) {
          pairs.push_back({ it.value()["docid"], it.value()["rank"] });
        }
        fromAnswer.push_back(pairs);
      }
      else {
        pairs.push_back({ temp["docid"], temp["rank"] });
        fromAnswer.push_back(pairs);
      }
    }
    requestsCount++;
  }
  return fromAnswer;
}
*/


//-----------------------------------------------------------------------------------------------
