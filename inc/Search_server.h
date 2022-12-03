#pragma once
#include "invertedIndex.h"
#include "converterJSON.h"




class SearchServer {
public:
  /**
  * @param idx � ����������� ������ ��������� ������ �� �����
  InvertedIndex,
  * ����� SearchServer ��� ������ ������� ���� ����������� �
  �������
  */
  SearchServer(InvertedIndex& idx) : _index(idx) { };
  /**
  * ����� ��������� ��������� ��������
  * @param queries_input ��������� ������� ������ �� �����
  requests.json
  * @return ���������� ��������������� ������ ����������� ������� ���
  �������� ��������
  */
  std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input);
private:
  InvertedIndex  _index;
};


