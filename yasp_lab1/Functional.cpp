#include "Functional.h"

// ������� ���������� ���������� ����� ������� � �����
std::fstream fillFileWithCycle(const std::string filename, const int n, const int m)
{
	srand((unsigned)time(nullptr));
	std::fstream file(filename);
	// ���������� �������� ��������������� ����� � ��������� [-m, m]  � ����
	for (int i = 0; i < n; ++i)
		file << -m + rand() % ((2 * m) + 1) << ' ';
	return file;
}

// ������� ���������� ���������� ����� ������� � �������������� ��������� std::generate
std::fstream fillFileWithGenerator(const std::string filename, const int n, const int m)
{
	srand((unsigned)time(nullptr));
	// �������, ������������ ��������� ����� � ��������� [-m, m]
	auto gen = [m]() -> int { return -m + rand() % ((2 * m) + 1); };
	// ��������������� ������, � ������� ������������� �����
	std::list<int> tmp(n);
	std::generate(tmp.begin(), tmp.end(), gen);
	std::fstream file(filename);
	// ���������� ����� �� ������ � ����
	for (std::list<int>::iterator it = tmp.begin(); it != tmp.end(); ++it)
		file << *it << ' ';
	return file;
}

// ������� ���������� ���������� ������� �� ���������� �����
std::list<int> createListFromFile(std::fstream& file)
{
	// ������ ������ �� ������ �����
	file.seekp(0);
	int number;
	std::list<int> lst;
	// ��������� �� ����� �� ������ ������ ����� � ���������� � ������
	while (file >> number)
		lst.push_back(number);
	return lst;
}

// ��������������� ������� ��� ������ ������������� �������� � ����������
int findMaxNumber(std::list<int>& lst)
{
	int max = *lst.begin();
	for (int& i : lst)
		if (i > max)
			max = i;
	return max;
}

// �������������� ���������� (�� ������� ����� ������� ������������ �����)
std::list<int> modify(std::list<int>& lst)
{
	// ���� ������������ ������� � ������
	int max = findMaxNumber(lst);
	// �� ������� �������� �������� ������������ ��������
	for (int& i : lst)
		i -= max;
	return lst;
}

// ��������������� ������� ��� ������ ������������� �������� � ���������� (� ������� ���������� ������ � �����)
int findMaxNumber(const std::list<int>::iterator begin, const std::list<int>::iterator end)
{
	int max = *begin;
	for (std::list<int>::iterator it = begin; it != end; ++it)
		if (*it > max)
			max = *it;
	return max;
}

// �������������� ���������� (�� ������� ����� ������� ������������ �����) � ������� ���������� ������ � �����
std::list<int> modify(const std::list<int>::iterator begin, const std::list<int>::iterator end)
{
	// ���� ������������ ������� � ������
	int max = findMaxNumber(begin, end);
	std::list<int> lst;
	// ��������� �� ����������, �� ������� �������� �������� ������������ �������� � ���������� "�����" ������� � ����� ������
	for (std::list<int>::iterator it = begin; it != end; ++it)
	{
		*it -= max;
		lst.push_back(*it);
	}
	return lst;
}

// �������������� ���������� (�� ������� ����� ������� ������������ �����) � ������� ��������� std::transform
std::list<int> modifyWithTransform(std::list<int>& lst)
{
	int max = findMaxNumber(lst);
	auto transformation = [max](int num) -> int { return num - max; };
	// �� ������� �������� ������ �������� ������������ ��������
	std::transform(lst.begin(), lst.end(), lst.begin(), transformation);
	return lst;
}

// �������������� ���������� (�� ������� ����� ������� ������������ �����) � ������� ��������� std::for_each
std::list<int> modifyWithForEach(std::list<int>& lst)
{
	int max = findMaxNumber(lst);
	auto transformation = [max](int num) -> int { return num - max; };
	// �� ������� �������� ������ �������� ������������ ��������
	std::for_each(lst.begin(), lst.end(), transformation);
	return lst;
}

// ����� ����� ����������
int getSum(std::list<int>& lst)
{
	int sum = 0;
	for (int& i : lst)
		sum += i;
	return sum;
}

// ������� �������������� ����� ����������
double getAverage(std::list<int>& lst)
{
	int sum = getSum(lst);
	return static_cast<double>(sum) / lst.size() ;
}

// ������
void print(std::ostream& out, std::list<int> lst)
{
	for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it)
		out << *it << ' ';
}
