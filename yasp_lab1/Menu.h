#pragma once
#include "Functional.h"
#include <Windows.h>

//	������� �������� ������������ ����� �����
bool �heckCorrectFilename(std::string& name);
// ���� ����� �����
std::string inputFilename();
// �������� ����� ��� �������� � �������� ���������� ���������� � ��� ������
void createFile(const std::string filename);
// ��������, �������� �� ��������� ����� � �������� ��������
bool getCorrectNumber(int min, int max, int& number);
// ���� :)
void Menu();