﻿#include "converterJSON.h"

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
//----------------------------------------------------------------------------------------------
