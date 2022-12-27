#include "converterJSON.h"

//--------------------------------------------------------
std::vector<std::string> ConverterJSON::GetTextDocuments() const {
  std::ifstream inFile("resources\\config.json");
  nlohmann::json j;
  if (inFile.is_open()) {
    inFile >> j;
    if (j.contains("config")) {
      std::cout << j["config"]["name"] << std::endl;
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
        } else {
          std::cerr << "file" << path << "cann not !!!" << std::endl;
        }
      }
      return doc;
    } else {
      throw "config file is invalid";
    }
  } else {
    throw "config file is missing";
  }
}
//-----------------------------------------------------------

std::vector<std::string> ConverterJSON::GetRequests() const {
  std::ifstream inFile("resources\\requests.json");
  if (inFile.is_open()) {
    nlohmann::json j;
    inFile >> j;
    if (j.contains("requests")) return  j["requests"];
    else throw "requests file is invalid";
  } else {
    throw "requests file is missing";
  }
}

//---------------------------------------------------------------------------------------
void ConverterJSON::putAnswers(const std::vector<std::vector<RelativeIndex>>& answers) const {
  nlohmann::json Js;
  int requestsCount = 0;
  for (auto& answer : answers) {
    ++requestsCount;
    std::string requestsStr = "requests" + std::to_string(requestsCount);
    if (answer.empty()) Js["answer"][requestsStr]["result"] = false;
    for (auto& doc : answer) {
      if (answer.size() > 1) {
        Js["answer"][requestsStr]["result"] = true;
        Js["answer"][requestsStr]["relevance"] += { {"docid", doc.doc_id}, { "rank", doc.rank } };
      }
      else if (answer.size() == 1) {
        Js["answer"][requestsStr] = { {"docid", doc.doc_id}, { "rank", doc.rank } };
        Js["answer"][requestsStr]["result"] = true;
      }
    }
  }
  std::ofstream outFile("resources\\answer.json");
  if (outFile.is_open()) outFile << std::setw(4) << Js;
  else throw "answer file is not created";
}
//----------------------------------------------------------------------------------------------
