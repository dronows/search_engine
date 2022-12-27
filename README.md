<div id="header" align="center">
  <img src="soft_log.gif" width="300"/>
</div>
<h1 align = "center"> локальный поисковой движок релевантных текстовых документов </h1>

---

Поисковый движок представляет из себя консольное приложение
(исполняемый файл, запускаемый на любом сервере или компьютере),
осуществляющее поиск и имеющее возможность настройки через файлы формата
JSON. Применённые в нём решения можно впоследствии встроить в поисковый
движок работающий на веб.
## установка
- OS  WINDOWS
- В проекте используются зависимости: 
- nlohmann::json
- googleTest
- Cmake
- компилятор MSVC
 - Приложение запускается в любой IDE С++ . После сборки и компиляции получаем два выходных файла search_engine.exe и test_search_engine.exe
## настройка
1. В конфигурационном файле config.json перед запуском приложения задаются названия
файлов, по которым движок будет осуществлять поиск.
Сами файлы для поиска помещаются в директорию docs.
 Конфигурационные файлы config.json , request.json , answer.json размещены в директории resources.
3. Пользователь задаёт запрос через JSON-файл requests.json. Запрос — это
набор слов, по которым нужно найти документы.
4. Запрос трансформируется в список слов.
5. В индексе ищутся те документы, на которых встречаются все эти слова.
6. Результаты поиска ранжируются, сортируются и отдаются пользователю,
максимальное количество возможных документов в ответе задаётся в
конфигурационном файле config.json (поле "max_responces") .
7. В конце программа формирует файл answers.json, в который записывает
результаты поиска.
#### тесты 
Для запуска тестирования приложения запустите test_search_engine.exe
## пример использования
в приложении создано три класса : <br>
>__converterJSON__ <br>
 класс для сериализации и дессиарелизации JSON (работает с конфиг. файлами) <br>
 _содержит ф-ии:_ <br>
  Метод получения содержимого файлов <br>
  @return Возвращает список с содержимым файлов перечисленных  в config.json <br>
  ___std::vector<std::string> GetTextDocuments();___ <br>
   Метод получения запросов из файла requests.json <br>
   @return возвращает список запросов из файла requests.json <br>
   ___std::vector<std::string> GetRequests();___ <br>
   Положить в файл answers.json результаты поисковых запросов <br>
  ___void putAnswers(std::vector<std::vector<std::pair<int, float>>>answers);___<br>
>>__invertedIndex__ <br>
Создание инвертированного индекса для документов <br>
_содержит ф-ии:_ <br>
 Обновить или заполнить базу документов, по которой будем совершать поиск <br>
 @param texts_input содержимое документов <br>
___void UpdateDocumentBase(std::vector<std::string> input_docs);___ <br>
Метод определяет количество вхождений слова word в загруженной базе документов <br>
 @param word слово, частоту вхождений которого необходимо определить <br>
 @return возвращает подготовленный список с частотой слов <br>
 ___std::vector<Entry> GetWordCount(const std::string& word);___<br>
>>>__Search_server__ <br>
Реализует систему определения релевантности поискового запроса.<br>
_содержит ф-ии:_ <br>
Метод обработки поисковых запросов <br>
@param queries_input поисковые запросы взятые из файлаrequests.json <br>
 @return возвращает отсортированный список релевантных ответов для заданных запросов <br>
___std::vector<std::vector<RelativeIndex>> search(const
std::vector<std::string>& queries_input);___



```
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
```
