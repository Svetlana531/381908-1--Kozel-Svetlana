#include <iostream>
#include <locale>
#include "Three.h"

#define PATH "C:\\out.txt"

void menu(Tree& _tree);
void chooseMenu(int _choose, Tree _tree);
void errorMessage(Tree _tree);

bool answer = false;

int main()
{
	setlocale(LC_ALL, "RUS");

	Tree tree;
	menu(tree);

	return 0;
}

void menu(Tree& _tree)
{
	cout << "\tМеню: " << endl;
	cout << "1) Ввести арифмитическое выражение" << endl;
	cout << "2) Посчитать результат" << endl;
	cout << "3) Прочитать с файла" << endl;
	cout << "4) Вывести в файл" << endl;
	cout << "0) Выход" << endl;
	if (_tree.checkInit())
	{
		cout << "Текущее:\t"; _tree.print();
		if(answer)
			cout << "\nОтвет: \t\t" << _tree.calculate();
		cout << endl;
	}
	cout << "> ";

	string in;
	cin >> in;

	if (in.size() == 1)
		chooseMenu(atoi(in.c_str()), _tree);
	else errorMessage(_tree);
}

void chooseMenu(int _choose, Tree _tree)
{
	string exp;
	switch (_choose)
	{
	case 1:
		system("cls");
		cout << "Выражение: ";
		cin >> exp;
		if (_tree.checkInput(exp))
		{
			if (_tree.checkInit()) { answer = false; }
			_tree.input(exp);
		}
		else { errorMessage(_tree); break; }
		menu(_tree);
		break;
	case 2:
		system("cls");
		if (_tree.checkInit())
		{
			_tree.calculate();
			answer = true;
		}
		menu(_tree);
		break;
	case 3:
		system("cls");
		if (_tree.ReadFile(PATH))
			cout << endl << "Выражение прочитано с файла!\n";
		else cout << endl << "Не удалось открыть файл!\n";
		system("pause");
		system("cls");
		menu(_tree);
		break;
	case 4:
		system("cls");
		if (_tree.WriteFile(PATH))
			cout << endl << "Выражение записано в файл!\n";
		else cout << endl << "Не удалось открыть файл!\n";
		system("pause");
		system("cls");
		menu(_tree);
		break;
	case 0:
		system("cls");
		cout << "Завершение работы...." << endl;
		exit(0);
		break;
	default:
		errorMessage(_tree);
		break;
	}
}

void errorMessage(Tree _tree)
{
	system("cls");
	cout << "Ошибка ввода!" << endl;
	system("pause");
	system("cls");
	menu(_tree);
}