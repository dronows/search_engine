
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "nlohmann/json.hpp"




class ConverterJSON {
public:
  ConverterJSON() = default;
  /**метод добавления файлов  в файл config.json
  */
  nlohmann::json AddFile(std::vector<std::string> files);

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
  void putAnswers(std::vector<std::vector<std::pair<int, float>>> answers);
  /**
  /достать из файла answer.json результаты поисковых запросов
  */
  std::vector<std::vector<std::pair<int, float>>>getAnswer();
  /**
   положить в файл requests.json список запросов
  */
  void AddRequests(std::vector <std::string>& requests);
};

