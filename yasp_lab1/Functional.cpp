#include "Functional.h"

// функция заполнения текстового файла числами в цикле
std::fstream fillFileWithCycle(const std::string filename, const int n, const int m)
{
	srand((unsigned)time(nullptr));
	std::fstream file(filename);
	// записываем рандомно сгенерированные числа в диапазоне [-m, m]  в файл
	for (int i = 0; i < n; ++i)
		file << -m + rand() % ((2 * m) + 1) << ' ';
	return file;
}

// функция заполнения текстового файла цифрами с использованием алгоритма std::generate
std::fstream fillFileWithGenerator(const std::string filename, const int n, const int m)
{
	srand((unsigned)time(nullptr));
	// функция, генерирующая рандомные числа в диапазоне [-m, m]
	auto gen = [m]() -> int { return -m + rand() % ((2 * m) + 1); };
	// вспомогательный список, в который сгенерируются числа
	std::list<int> tmp(n);
	std::generate(tmp.begin(), tmp.end(), gen);
	std::fstream file(filename);
	// записываем числа из списка в файл
	for (std::list<int>::iterator it = tmp.begin(); it != tmp.end(); ++it)
		file << *it << ' ';
	return file;
}

// функция заполнения контейнера числами из текстового файла
std::list<int> createListFromFile(std::fstream& file)
{
	// ставим курсор на начало файла
	file.seekp(0);
	int number;
	std::list<int> lst;
	// считываем из файла по одному целому числу и записываем в список
	while (file >> number)
		lst.push_back(number);
	return lst;
}

// вспомогательная функция для поиска максимального значения в контейнере
int findMaxNumber(std::list<int>& lst)
{
	int max = *lst.begin();
	for (int& i : lst)
		if (i > max)
			max = i;
	return max;
}

// преобразование контейнера (из каждого числа вычесть максимальное число)
std::list<int> modify(std::list<int>& lst)
{
	// ищем максимальный элемент в списке
	int max = findMaxNumber(lst);
	// из каждого элемента вычитаем максимальное значение
	for (int& i : lst)
		i -= max;
	return lst;
}

// вспомогательная функция для поиска максимального значения в контейнере (с помощью итераторов начала и конца)
int findMaxNumber(const std::list<int>::iterator begin, const std::list<int>::iterator end)
{
	int max = *begin;
	for (std::list<int>::iterator it = begin; it != end; ++it)
		if (*it > max)
			max = *it;
	return max;
}

// преобразование контейнера (из каждого числа вычесть максимальное число) с помощью итераторов начала и конца
std::list<int> modify(const std::list<int>::iterator begin, const std::list<int>::iterator end)
{
	// ищем максимальный элемент в списке
	int max = findMaxNumber(begin, end);
	std::list<int> lst;
	// двигаемся по итераторам, из каждого элемента вычитаем максимальное значение и записываем "новый" элемент в новый список
	for (std::list<int>::iterator it = begin; it != end; ++it)
	{
		*it -= max;
		lst.push_back(*it);
	}
	return lst;
}

// преобразование контейнера (из каждого числа вычесть максимальное число) с помощью алгоритма std::transform
std::list<int> modifyWithTransform(std::list<int>& lst)
{
	int max = findMaxNumber(lst);
	auto transformation = [max](int num) -> int { return num - max; };
	// из каждого элемента списка вычитаем максимальное значение
	std::transform(lst.begin(), lst.end(), lst.begin(), transformation);
	return lst;
}

// преобразование контейнера (из каждого числа вычесть максимальное число) с помощью алгоритма std::for_each
std::list<int> modifyWithForEach(std::list<int>& lst)
{
	int max = findMaxNumber(lst);
	auto transformation = [max](int num) -> int { return num - max; };
	// из каждого элемента списка вычитаем максимальное значение
	std::for_each(lst.begin(), lst.end(), transformation);
	return lst;
}

// сумма чисел контейнера
int getSum(std::list<int>& lst)
{
	int sum = 0;
	for (int& i : lst)
		sum += i;
	return sum;
}

// среднее арифметическое чисел контейнера
double getAverage(std::list<int>& lst)
{
	int sum = getSum(lst);
	return static_cast<double>(sum) / lst.size() ;
}

// печать
void print(std::ostream& out, std::list<int> lst)
{
	for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it)
		out << *it << ' ';
}
