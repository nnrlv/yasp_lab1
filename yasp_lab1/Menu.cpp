#include "Menu.h"

//	функция проверки корректности имени файла
bool сheckCorrectFilename(std::string& name)
{
	// проверяем, нет ли в переданном имени запрещенных символов
	for (char c : name)
		if (c == '\\' || c == '/' || c == ':' || c == '*' || c == '?' || c == '\"' || c == '>' || c == '<' || c == '|' || c == '.')
			return false;
	// дописываем расширение
	name += ".txt";
	return true;
}

// ввод имени файла
std::string inputFilename()
{
	std::cout << "Введите имя файла (без расширения): ";
	std::string name;
	// забираем из потока введенное имя файла
	std::cin >> name;
	// проверяем на корректность введенное имя, если некорректно - повторяем запрос на ввод
	while (!сheckCorrectFilename(name))
	{
		std::cout << "Некорректное имя файла, введите другое\n\n";
		std::cout << "Введите имя файла (без расширения): ";
		std::cin >> name;
		std::cout << std::endl;
	}
	return name;
}

// создание файла или открытие с очисткой предыдущих записанных в нем данных
void createFile(const std::string filename)
{
	std::ofstream f(filename);
	f.close();
}

// проверка, попадает ли введенное число в заданный диапазон
bool getCorrectNumber(int min, int max, int& number)
{
	bool correct = true;
	std::cin >> number;
	// ввели что-то не то
	if (std::cin.fail() || number < min || number > max)
	{
		correct = false;
		std::cout << "Некорректный ввод. Повторите попытку\n\n";
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
		std::cout << "[0]. Выйти из программы\n";
		std::cout << "[1]. Открыть файл и заполнить его случайными числами\n";
		std::cout << "[2]. Заполнить список числами из файла\n";
		std::cout << "[3]. Преобразовать список (из каждого элемента вычесть максимальное значение)\n";
		std::cout << "[4]. Вычислить сумму чисел, содержащихся в списке\n";
		std::cout << "[5]. Вычислить среднее арифметическое чисел, содержащихся в списке\n";
		std::cout << "[6]. Печать списка\n\n";
		// запрашиваем на ввод число до тех пор, пока не введут корректное в диапазоне [0;6]
		do
			std::cout << "Выберите действие: ";
		while (!getCorrectNumber(0, 6, choice));
		std::cout << '\n';
		switch (choice)
		{
		case 0:
		{
			std::cout << "Выход . . .\n";
			exit_flag = true;
			if (file.is_open())	
				file.close();
			break;
		}
		case 1:
		{
			// вводим имя файла, потом открываем или создаем его
			filename = inputFilename();
			createFile(filename);
			file.open(filename);
			int n, m, choice2;
			do 
				std::cout << "Введите N (количество генерируемых чисел): "; 
			while (!getCorrectNumber(0, MAXINT, n));
			do
				std::cout << "Введите M (диапазон генерируемых чисел): ";
			while (!getCorrectNumber(0, MAXINT, m));
			std::cout << '\n';
			// выбираем способ генерации чисел
			do
			{
				std::cout << "Заполнить файл числами с помощью: \n";
				std::cout << "[0]. Цикла\n";
				std::cout << "[1]. Алгоритма std::generate\n";
				std::cout << "Выберите действие: ";
			} while (!getCorrectNumber(0, 1, choice2));
			// генерируем числа с помощью std::generate
			if (choice2)
				file = fillFileWithGenerator(filename, n, m);
			// генерируем числа по очереди в цикле
			else
				file = fillFileWithCycle(filename, n, m);
			std::cout << '\n';
			std::cout << "Числа были сгенерированы в файл " << filename << '\n';
			std::cout << "Нажмите любую клавишу, чтобы продолжить\n";
			std::cin.clear();
			std::cin.ignore(255, '\n');
			std::cin.get();
			break;
		}
		case 2:
		{
			if (file.is_open())
			{
				// записываем в контейнер числа из сгенерированного ранее файла
				lst = createListFromFile(file);
				std::cout << "Список был заполнен числами из файла " << filename << '\n';
			}
			else
				std::cout << "Сначала выберите пункт меню [1] и заполните файл\n";
			std::cout << "Нажмите любую клавишу, чтобы продолжить\n";
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
					std::cout << "[ Список пуст ]\n\n";
				// выводим на экран исходный список и 4 преобразованных разными способами
				else
				{
					std::cout << "Исходный список: [ ";
					print(std::cout, lst);
					std::cout << "]\n\n";
					std::cout << "Преобразование функцией modify, получающей на вход контейнер:\n[ ";
					print(std::cout, modify(lst));
					std::cout << "]\n\n";
					std::cout << "Преобразование функцией modify, получающей на вход итераторы начала и конца контейнера:\n[ ";
					print(std::cout, modify(lst.begin(), lst.end()));
					std::cout << "]\n\n";
					std::cout << "Преобразование c помощью алгоритма std::generate:\n[ ";
					print(std::cout, modifyWithTransform(lst));
					std::cout << "]\n\n";
					std::cout << "Преобразование c помощью алгоритма std::for_each:\n[ ";
					// запоминаем преобразованный список вместо исходного
					lst = modifyWithForEach(lst);
					print(std::cout, lst);
					std::cout << "]\n\n";
				}
			}
			else
				std::cout << "Список еще не был заполнен, сначала выберите пункт меню [2]\n\n";
			std::cout << "Нажмите любую клавишу, чтобы продолжить\n";
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
					std::cout << "[ Список пуст ]\n\n";
				else
				{
					std::cout << "[ ";
					print(std::cout, lst);
					std::cout << "]\n\n";
					std::cout << "Cумма чисел, находящихся в контейнере = " << getSum(lst) << "\n\n";
				}
			}
			else
				std::cout << "Список еще не был заполнен, сначала выберите пункт меню [2]\n\n";
			std::cout << "Нажмите любую клавишу, чтобы продолжить\n";
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
					std::cout << "[ Список пуст ]\n\n";
				else
				{
					std::cout << "[ ";
					print(std::cout, lst);
					std::cout << "]\n\n";
					std::cout << "Среднее арифметическое чисел, находящихся в контейнере = " << getAverage(lst) << "\n\n";
				}
			}
			else
				std::cout << "Список еще не был заполнен, сначала выберите пункт меню [2]\n\n";
			std::cout << "Нажмите любую клавишу, чтобы продолжить\n";
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
					std::cout << "[ Список пуст ]\n\n";
				else
				{
					int choice3;
					// выбираем способ печати
					do
					{
						std::cout << "[0]. Напечатать список на экран\n";
						std::cout << "[1]. Напечатать список в файл\n";
						std::cout << "Выберите действие: ";
					} while (!getCorrectNumber(0, 1, choice3));
					// печать в файл
					if (choice3)
					{
						std::cout << '\n';
						// запрашиваем на ввод новое имя файла, куда запишем данные контейнера
						std::string output_filename = inputFilename();
						// открываем/создаем файл
						createFile(output_filename);
						std::ofstream output_file(output_filename);
						// печатаем в файл
						print(output_file, lst);
						output_file.close();
						std::cout << "\nСписок напечатан в файл " << output_filename << "\n\n";
					}
					// печать в консоль
					else
					{
						std::cout << "[ ";
						print(std::cout, lst);
						std::cout << "]\n\n";
					}
				}
			}
			else
				std::cout << "Список еще не был заполнен, сначала выберите пункт меню [2]\n\n";
			std::cout << "Нажмите любую клавишу, чтобы продолжить\n";
			std::cin.clear();
			std::cin.ignore(255, '\n');
			std::cin.get();
			break;
		}
		}
	} while (!exit_flag);
}