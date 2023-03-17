#pragma once
#include "Functional.h"
#include <Windows.h>

//	функция проверки корректности имени файла
bool сheckCorrectFilename(std::string& name);
// ввод имени файла
std::string inputFilename();
// создание файла или открытие с очисткой предыдущих записанных в нем данных
void createFile(const std::string filename);
// проверка, попадает ли введенное число в заданный диапазон
bool getCorrectNumber(int min, int max, int& number);
// меню :)
void Menu();