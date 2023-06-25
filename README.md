<div id="header" align="center">
  <img src="soft_log.gif" width="300"/>
</div>
<h1 align = "center">lokale Suchmaschine für relevante Textdokumente </h1>

---

Die Suchmaschine ist eine Konsolenanwendung
(eine ausführbare Datei, die auf einem beliebigen Server oder Computer ausgeführt wird),
durchsuchbar und anpassbar über Formatdateien
JSON. Sie können die darin verwendeten Lösungen später in die Suche einbetten
die Engine läuft im Web.
## Einstellung
- OS  WINDOWS
- nlohmann::json
- googleTest release-1.12.1
- Cmake 3.19
- Compiller MSVC
 - Die Anwendung wird in jeder C ++ - IDE ausgeführt. Nach dem Erstellen und Kompilieren werden zwei Ausgabedateien search_engine .exe und test_search_engine.exe
## Konfiguration
1. In der Konfigurationsdatei config.json-Namen werden vor dem Ausführen der Anwendung angegeben
  dateien, nach denen die Engine suchen wird.
  Die zu durchsuchenden Dateien werden im Verzeichnis docs abgelegt.
  Config-Konfigurationsdateien.json , requests.json , answer.der json befindet sich im resources-Verzeichnis.

3. Der Benutzer legt die Anforderung über die JSON-Datei request.json. Die Anfrage ist
eine Reihe von Wörtern, nach denen Sie Dokumente finden müssen.
4. Die Abfrage wird in eine Wortliste umgewandelt.
5. Im Index werden die Dokumente gesucht, auf denen all diese Wörter vorkommen.
6. Die Suchergebnisse werden geordnet, sortiert und an den Benutzer weitergegeben,
die maximale Anzahl möglicher Dokumente in einer Antwort wird in angegeben
der Konfigurationsdatei config.json (Feld "max_responses") .
7. Am Ende erstellt das Programm eine Datei answers.json, in den er schreibt
suchergebnisse.
#### Tests
Führen Sie test_search_engine.exe aus, um die Anwendung zu testen
## beschreibung des Codes
die Anwendung erstellt drei Klassen : <br>
>__converterJSON__ <br>
 klasse zum Serialisieren und Deserialisieren von JSON (funktioniert mit config. Dateien) <br>
 _enthält Funktionen:_ <br>
  - funktion zum Abrufen von Dateiinhalten<br>
  @return   Gibt eine Liste mit dem Inhalt der in config.json aufgeführten Dateien zurück  <br>
  ___std::vector<std::string> GetTextDocuments();___ <br>
  - Methode zum Abrufen von Anforderungen aus der request.json Datei <br>
   @return    gibt eine Liste von Anforderungen aus der request.json Datei zurück. <br>
   ___std::vector<std::string> GetRequests();___ <br>
  - suchergebnisse  einfügen in die Datei answer.json <br>
  ___void putAnswers(std::vector<std::vector<std::pair<int, float>>>answers);___<br>
>>__invertedIndex__ <br>
Erstellen eines invertierten Index für Dokumente <br>
_enthält Funktionen:_ <br>
- Aktualisieren oder füllen Sie die Dokumentdatenbank aus, nach der wir suchen werden <br>
  die Funktion funktioniert im Multithreading
  
 @param texts_input inhalt der Dokumente <br>
___void UpdateDocumentBase(std::vector<std::string> input_docs);___ <br>
- die Funktion bestimmt die Anzahl der Vorkommen von Word in der geladenen Dokumentdatenbank <br>
 @param word das Wort, dessen Häufigkeit bestimmt werden muss<br>
 @return gibt eine vorbereitete Liste mit der Häufigkeit von Wörtern zurück <br>
 ___std::vector<Entry> GetWordCount(const std::string& word);___<br>
>>>__Search_server__ <br>
Implementiert ein System zur Bestimmung der Relevanz einer Suchanfrage.<br>
_enthält Funktionen:__ <br>
- funktion zur Bearbeitung von Suchanfragen <br>
@param queries_input die Suchanfragen stammen aus der request.json -Datei<br>
 @return gibt eine sortierte Liste relevanter Antworten für die angegebenen Abfragen zurück <br>
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
