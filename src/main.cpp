#include "search_engine.h"
#include <exception>



int main()
{
  
  std::fstream configFile;
  configFile.open("config.json");
  nlohmann::json configJs;
  try {
	if (configFile.is_open()) {
	  configFile >> configJs;
	  if (configJs.contains("config")) { std::cout << configJs["config"]["name"] << std::endl; }
	  else { throw "config file is empty"; }
	} else {
	  throw "config file is missing";
	}
  } catch (const char* exception) {
	std::cerr << exception << std::endl;
	configFile.close();
	return 0;
  }
  std::cout << "names of files to search for (or accept) :	" << std::endl;
  std::vector<std::string> to_files;
  std::string inStr;
  std::cin >> inStr;
  /*
   while (inStr != "accept") {
	to_files.push_back(inStr);
	std::cin >> inStr;
  }
  
   ConverterJSON converter;
  configJs = converter.AddFile(to_files);
  configFile << configJs;
  
  */
  
 
  configFile.close();
return 0;

}


