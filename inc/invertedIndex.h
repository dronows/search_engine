#pragma once

#include <sstream>
#include <vector>
#include <map>
#include <thread>
#include <mutex>

struct Entry {
  size_t doc_id, count = 0;
  Entry(size_t in_doc_id, size_t in_count) : doc_id(in_doc_id), count(in_count) {}
  // ������ �������� ��������� ��� ���������� �������� ���������
  bool operator ==(const Entry& other) const {
	return (doc_id == other.doc_id &&
	  count == other.count);
  }
};
class InvertedIndex {
public:
  InvertedIndex() = default;
  /**
  * �������� ��� ��������� ���� ����������, �� ������� ����� ���������
  �����
  * @param texts_input ���������� ����������
  */
  void UpdateDocumentBase(std::vector<std::string> input_docs);
  /*
  *����� ���������� ���������� ��������� ����� word � ����������� ����
	����������
	* @param word �����, ������� ��������� �������� ���������� ����������
	* @return ���������� �������������� ������ � �������� ����
	*/
  std::vector<Entry> GetWordCount(const std::string& word);
private:
  std::vector<std::string> docs; // ������ ����������� ����������
  std::map<std::string, std::vector<Entry>> freq_dictionary; // �������� �������

};

