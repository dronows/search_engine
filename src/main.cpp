#include "converterJSON.h"
#include "invertedIndex.h"
#include "Search_Server.h"
#include <exception>



int main()
{
  try {
	ConverterJSON converter;
	const std::vector<std::string> from_files = converter.GetTextDocuments();
	InvertedIndex idx;
	idx.UpdateDocumentBase(from_files);
	SearchServer server(idx);
	converter.putAnswers(server.search(converter.GetRequests()));
	std::cout << "File verification is finished !!" << std::endl;
	return 0;
  }
  catch (const char* exception) {
	std::cerr << exception << std::endl;
	return 0;
  }
}


