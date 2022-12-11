#include "converterJSON.h"
#include "invertedIndex.h"
#include "Search_Server.h"
#include <exception>



int main()
{
  std::ifstream inFile("../../../../resources/config.json");
  nlohmann::json configJs;
  try {
	if (inFile.is_open()) {
	  inFile >> configJs;
	  if (configJs.contains("config")) { std::cout << configJs["config"]["name"] << std::endl; }
	  else { throw "config file is empty"; }
	}
	else {
	  throw "config file is missing";
	}
  }
  catch (const char* exception) {
	std::cerr << exception << std::endl;
	inFile.close();
	return 0;
  }
  inFile.close();
  std::cout << " a set of words for which you need to find documents. (or accept) :	" << std::endl;
  std::vector<std::string> to_files;
  std::string inStr;
  std::getline(std::cin, inStr);
  while (inStr != "accept") {
	to_files.push_back(inStr);
	std::getline(std::cin, inStr);
  }
  ConverterJSON converter;
  converter.AddRequests(to_files);
  const std::vector<std::string> from_files = converter.GetTextDocuments();
  InvertedIndex idx;
  idx.UpdateDocumentBase(from_files);
  SearchServer server(idx);
  converter.putAnswers(server.search(converter.GetRequests()));
  return 0;
}


