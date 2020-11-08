#include "Source.h"
#ifndef  IOSTREAM_H
#include <stdio.h>
#include <iostream>
#endif

int menu(const HANDLE console) noexcept {
	int k = 0;	// номер выделенной строки
	const int N = 5;
	std::string m[N] = {"Start game", "Options", "Results", "About", "Exit"};
	int input;
	do
	{
		// оформление фона
		system("cls");
		SetConsoleTextAttribute(console, BACKGROUND_BLUE |
			BACKGROUND_GREEN | BACKGROUND_RED);

		// вывод меню с одной выделенной строкой
		SetConsoleTextAttribute(console, BACKGROUND_BLUE |
			BACKGROUND_GREEN | BACKGROUND_RED);
		for (int i = 0; i < k; i++)
		{
			std::cout << std::setw(30) << m[i] << std::endl;
		}
		SetConsoleTextAttribute(console,
			BACKGROUND_BLUE | BACKGROUND_INTENSITY);
		std::cout << std::setw(30) << m[k] << std::endl;
		SetConsoleTextAttribute(console, BACKGROUND_BLUE |
			BACKGROUND_GREEN | BACKGROUND_RED);
		for (int i = k+1; i < N; i++)
		{
			std::cout << std::setw(30) << m[i] << std::endl;
		}

		// захват нажатия кнопки клавиатуры
		input = _getch();
		if (input == 72) {
			k--;
		}
		if (input == 80) {
			k++;
		}
		k = (k+N) % N;
	} while (input != 13 && input != 27);
	if (input == 27) {
		k = 4;
	}
	return k;
}

int action(const int k) noexcept {
	switch (k)
	{
	case 0:
		return 1;
		break;
	case 1:
		std::cout << std::setw(30) << "No options" << std::endl;
		std::cin.ignore();
		break;
	case 2:
		std::cout << std::setw(30) << "No results" << std::endl;
		std::cin.ignore();
		break;
	case 3:
		std::cout << std::setw(30) << "No about" << std::endl;
		std::cin.ignore();
		break;
	case 4:
		return 1;
		break;
	default:
		break;
	}
	return 0;
}

struct parametrs Start_game() noexcept {
	// оформление дизайна
	system("cls");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	CONSOLE_FONT_INFOEX fontInfo;
	fontInfo.cbSize = sizeof(fontInfo);
	GetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);
	wcscpy(fontInfo.FaceName, L"Lucida Console");
	fontInfo.dwFontSize.Y = 15;
	SetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);
	std::cout << std::setw(20);

	struct parametrs p;
	// вывод меню и выбор дейсвтия
	int k;
	int st;
	do {
		k = menu(hConsole);
		st = action(k);
	} while (!st);
	if (k == 4)
	{
		p.exit = 1;
		return p;
	}

	// ввод параметров игры
	system("cls");
	std::cout << "Enter your name." << std::endl;
	std::cin >> p.name;
	int m = 0;
	std::cout << "Enter count of players (AI). No more than 16." << std::endl;
	while (m < 1 || m > 16) {
		getn(m);
	}
	p.count = m;
	m = 0;
	std::cout << "How many maps will have players. One or three." << std::endl;
	while (m != 1 && m != 3) {
		getn(m);
	}
	p.maps = m;
	m = 0;
	std::cout << "Enter count of lines. From 1 to 9." << std::endl;
	while (m < 1 || m > 9) {
		getn(m);
	}
	p.lines = m;
	return p;
}

int main() {
	struct parametrs par;
	do {
		par = Start_game();
		download_game(par);
	}
	while (par.exit != 1);
	return 0;
}
