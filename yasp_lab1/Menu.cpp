#include "Menu.h"

//	������� �������� ������������ ����� �����
bool �heckCorrectFilename(std::string& name)
{
	// ���������, ��� �� � ���������� ����� ����������� ��������
	for (char c : name)
		if (c == '\\' || c == '/' || c == ':' || c == '*' || c == '?' || c == '\"' || c == '>' || c == '<' || c == '|' || c == '.')
			return false;
	// ���������� ����������
	name += ".txt";
	return true;
}

// ���� ����� �����
std::string inputFilename()
{
	std::cout << "������� ��� ����� (��� ����������): ";
	std::string name;
	// �������� �� ������ ��������� ��� �����
	std::cin >> name;
	// ��������� �� ������������ ��������� ���, ���� ����������� - ��������� ������ �� ����
	while (!�heckCorrectFilename(name))
	{
		std::cout << "������������ ��� �����, ������� ������\n\n";
		std::cout << "������� ��� ����� (��� ����������): ";
		std::cin >> name;
		std::cout << std::endl;
	}
	return name;
}

// �������� ����� ��� �������� � �������� ���������� ���������� � ��� ������
void createFile(const std::string filename)
{
	std::ofstream f(filename);
	f.close();
}

// ��������, �������� �� ��������� ����� � �������� ��������
bool getCorrectNumber(int min, int max, int& number)
{
	bool correct = true;
	std::cin >> number;
	// ����� ���-�� �� ��
	if (std::cin.fail() || number < min || number > max)
	{
		correct = false;
		std::cout << "������������ ����. ��������� �������\n\n";
		std::cin.clear();
		std::cin.ignore(255, '\n');
	}
	return correct;
}

void Menu()
{
	bool exit_flag = false;
	std::fstream file;
	std::string filename;
	std::list<int> lst;
	do
	{
		system("cls");
		int choice;
		std::cout << "[0]. ����� �� ���������\n";
		std::cout << "[1]. ������� ���� � ��������� ��� ���������� �������\n";
		std::cout << "[2]. ��������� ������ ������� �� �����\n";
		std::cout << "[3]. ������������� ������ (�� ������� �������� ������� ������������ ��������)\n";
		std::cout << "[4]. ��������� ����� �����, ������������ � ������\n";
		std::cout << "[5]. ��������� ������� �������������� �����, ������������ � ������\n";
		std::cout << "[6]. ������ ������\n\n";
		// ����������� �� ���� ����� �� ��� ���, ���� �� ������ ���������� � ��������� [0;6]
		do
			std::cout << "�������� ��������: ";
		while (!getCorrectNumber(0, 6, choice));
		std::cout << '\n';
		switch (choice)
		{
		case 0:
		{
			std::cout << "����� . . .\n";
			exit_flag = true;
			if (file.is_open())	
				file.close();
			break;
		}
		case 1:
		{
			// ������ ��� �����, ����� ��������� ��� ������� ���
			filename = inputFilename();
			createFile(filename);
			file.open(filename);
			int n, m, choice2;
			do 
				std::cout << "������� N (���������� ������������ �����): "; 
			while (!getCorrectNumber(0, MAXINT, n));
			do
				std::cout << "������� M (�������� ������������ �����): ";
			while (!getCorrectNumber(0, MAXINT, m));
			std::cout << '\n';
			// �������� ������ ��������� �����
			do
			{
				std::cout << "��������� ���� ������� � �������: \n";
				std::cout << "[0]. �����\n";
				std::cout << "[1]. ��������� std::generate\n";
				std::cout << "�������� ��������: ";
			} while (!getCorrectNumber(0, 1, choice2));
			// ���������� ����� � ������� std::generate
			if (choice2)
				file = fillFileWithGenerator(filename, n, m);
			// ���������� ����� �� ������� � �����
			else
				file = fillFileWithCycle(filename, n, m);
			std::cout << '\n';
			std::cout << "����� ���� ������������� � ���� " << filename << '\n';
			std::cout << "������� ����� �������, ����� ����������\n";
			std::cin.clear();
			std::cin.ignore(255, '\n');
			std::cin.get();
			break;
		}
		case 2:
		{
			if (file.is_open())
			{
				// ���������� � ��������� ����� �� ���������������� ����� �����
				lst = createListFromFile(file);
				std::cout << "������ ��� �������� ������� �� ����� " << filename << '\n';
			}
			else
				std::cout << "������� �������� ����� ���� [1] � ��������� ����\n";
			std::cout << "������� ����� �������, ����� ����������\n";
			std::cin.clear();
			std::cin.ignore(255, '\n');
			std::cin.get();
			break;
		}
		case 3:
		{
			if (file.is_open())
			{
				if (lst.empty())
					std::cout << "[ ������ ���� ]\n\n";
				// ������� �� ����� �������� ������ � 4 ��������������� ������� ���������
				else
				{
					std::cout << "�������� ������: [ ";
					print(std::cout, lst);
					std::cout << "]\n\n";
					std::cout << "�������������� �������� modify, ���������� �� ���� ���������:\n[ ";
					print(std::cout, modify(lst));
					std::cout << "]\n\n";
					std::cout << "�������������� �������� modify, ���������� �� ���� ��������� ������ � ����� ����������:\n[ ";
					print(std::cout, modify(lst.begin(), lst.end()));
					std::cout << "]\n\n";
					std::cout << "�������������� c ������� ��������� std::generate:\n[ ";
					print(std::cout, modifyWithTransform(lst));
					std::cout << "]\n\n";
					std::cout << "�������������� c ������� ��������� std::for_each:\n[ ";
					// ���������� ��������������� ������ ������ ���������
					lst = modifyWithForEach(lst);
					print(std::cout, lst);
					std::cout << "]\n\n";
				}
			}
			else
				std::cout << "������ ��� �� ��� ��������, ������� �������� ����� ���� [2]\n\n";
			std::cout << "������� ����� �������, ����� ����������\n";
			std::cin.clear();
			std::cin.ignore(255, '\n');
			std::cin.get();
			break;
		}
		case 4:
		{
			if (file.is_open())
			{
				if (lst.empty())
					std::cout << "[ ������ ���� ]\n\n";
				else
				{
					std::cout << "[ ";
					print(std::cout, lst);
					std::cout << "]\n\n";
					std::cout << "C���� �����, ����������� � ���������� = " << getSum(lst) << "\n\n";
				}
			}
			else
				std::cout << "������ ��� �� ��� ��������, ������� �������� ����� ���� [2]\n\n";
			std::cout << "������� ����� �������, ����� ����������\n";
			std::cin.clear();
			std::cin.ignore(255, '\n');
			std::cin.get();
			break;
		}
		case 5:
		{
			if (file.is_open())
			{
				if (lst.empty())
					std::cout << "[ ������ ���� ]\n\n";
				else
				{
					std::cout << "[ ";
					print(std::cout, lst);
					std::cout << "]\n\n";
					std::cout << "������� �������������� �����, ����������� � ���������� = " << getAverage(lst) << "\n\n";
				}
			}
			else
				std::cout << "������ ��� �� ��� ��������, ������� �������� ����� ���� [2]\n\n";
			std::cout << "������� ����� �������, ����� ����������\n";
			std::cin.clear();
			std::cin.ignore(255, '\n');
			std::cin.get();
			break;
		}
		case 6:
		{
			if (file.is_open())
			{
				if (lst.empty())
					std::cout << "[ ������ ���� ]\n\n";
				else
				{
					int choice3;
					// �������� ������ ������
					do
					{
						std::cout << "[0]. ���������� ������ �� �����\n";
						std::cout << "[1]. ���������� ������ � ����\n";
						std::cout << "�������� ��������: ";
					} while (!getCorrectNumber(0, 1, choice3));
					// ������ � ����
					if (choice3)
					{
						std::cout << '\n';
						// ����������� �� ���� ����� ��� �����, ���� ������� ������ ����������
						std::string output_filename = inputFilename();
						// ���������/������� ����
						createFile(output_filename);
						std::ofstream output_file(output_filename);
						// �������� � ����
						print(output_file, lst);
						output_file.close();
						std::cout << "\n������ ��������� � ���� " << output_filename << "\n\n";
					}
					// ������ � �������
					else
					{
						std::cout << "[ ";
						print(std::cout, lst);
						std::cout << "]\n\n";
					}
				}
			}
			else
				std::cout << "������ ��� �� ��� ��������, ������� �������� ����� ���� [2]\n\n";
			std::cout << "������� ����� �������, ����� ����������\n";
			std::cin.clear();
			std::cin.ignore(255, '\n');
			std::cin.get();
			break;
		}
		}
	} while (!exit_flag);
}