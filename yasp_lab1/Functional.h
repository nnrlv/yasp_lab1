#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <list>
#include <string>

// ������� ���������� ���������� ����� ������� � �����
std::fstream fillFileWithCycle(const std::string filename, int n, int m);
// ������� ���������� ���������� ����� ������� � �������������� ��������� std::generate
std::fstream fillFileWithGenerator(const std::string filename, const int n, const int m);
// ������� ���������� ���������� ������� �� ���������� �����
std::list<int> createListFromFile(std::fstream& file);
// ��������������� ������� ��� ������ ������������� �������� � ����������
int findMaxNumber(std::list<int>& lst);
// �������������� ���������� (�� ������� ����� ������� ������������ �����)
std::list<int> modify(std::list<int>& lst);
// ��������������� ������� ��� ������ ������������� �������� � ���������� (� ������� ���������� ������ � �����)
int findMaxNumber(const std::list<int>::iterator begin, const std::list<int>::iterator end);
// �������������� ���������� (�� ������� ����� ������� ������������ �����) � ������� ���������� ������ � �����
std::list<int> modify(const std::list<int>::iterator begin, const std::list<int>::iterator end);
// �������������� ���������� (�� ������� ����� ������� ������������ �����) � ������� ��������� std::transform
std::list<int> modifyWithTransform(std::list<int>& lst);
// �������������� ���������� (�� ������� ����� ������� ������������ �����) � ������� ��������� std::for_each
std::list<int> modifyWithForEach(std::list<int>& lst);
// ����� ����� ����������
int getSum(std::list<int>& lst);
// ������� �������������� ����� ����������
double getAverage(std::list<int>& lst);
// ������
void print(std::ostream& out, std::list<int> lst);