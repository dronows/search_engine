
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "nlohmann/json.hpp"


struct RelativeIndex {
  size_t doc_id;
  float rank;
  RelativeIndex(size_t _doc_id, float _rank) : doc_id(_doc_id), rank(_rank) {}
  bool operator ==(const RelativeIndex& other) const {
	return (doc_id == other.doc_id && rank == other.rank);
  }
};

class ConverterJSON {
public:
  ConverterJSON() = default;
  
  /**
  * Метод получения содержимого файлов
  * @return Возвращает список с содержимым файлов перечисленных
  * в config.json
  */
  std::vector<std::string> GetTextDocuments();
  /**
  * Метод считывает поле max_responses для определения предельного
  * количества ответов на один запрос
  * @return
  */
  int GetResponsesLimit();
  /**
  * Метод получения запросов из файла requests.json
  * @return возвращает список запросов из файла requests.json
  */
  std::vector<std::string> GetRequests();
  /**
  * Положить в файл answers.json результаты поисковых запросов
  */
  void putAnswers(std::vector<std::vector<RelativeIndex>>answers );
  /**
   положить в файл requests.json список запросов
  */
  void AddRequests(std::vector <std::string>& requests);
};

