#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <list>
#include <string>

// функция заполнения текстового файла числами в цикле
std::fstream fillFileWithCycle(const std::string filename, int n, int m);
// функция заполнения текстового файла цифрами с использованием алгоритма std::generate
std::fstream fillFileWithGenerator(const std::string filename, const int n, const int m);
// функция заполнения контейнера числами из текстового файла
std::list<int> createListFromFile(std::fstream& file);
// вспомогательная функция для поиска максимального значения в контейнере
int findMaxNumber(std::list<int>& lst);
// преобразование контейнера (из каждого числа вычесть максимальное число)
std::list<int> modify(std::list<int>& lst);
// вспомогательная функция для поиска максимального значения в контейнере (с помощью итераторов начала и конца)
int findMaxNumber(const std::list<int>::iterator begin, const std::list<int>::iterator end);
// преобразование контейнера (из каждого числа вычесть максимальное число) с помощью итераторов начала и конца
std::list<int> modify(const std::list<int>::iterator begin, const std::list<int>::iterator end);
// преобразование контейнера (из каждого числа вычесть максимальное число) с помощью алгоритма std::transform
std::list<int> modifyWithTransform(std::list<int>& lst);
// преобразование контейнера (из каждого числа вычесть максимальное число) с помощью алгоритма std::for_each
std::list<int> modifyWithForEach(std::list<int>& lst);
// сумма чисел контейнера
int getSum(std::list<int>& lst);
// среднее арифметическое чисел контейнера
double getAverage(std::list<int>& lst);
// печать
void print(std::ostream& out, std::list<int> lst);