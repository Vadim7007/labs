﻿#ifndef LIB3_H
#include "lib3.h"
#endif LIB3_H

int main(void) {
	int k = 0;
	while (k != -1) {
		// вывод меню и выбор действия
		system("cls");
		std::cout << "Enter action" << std::endl;
		std::cout << "-1 - Exit" << std::endl;
		std::cout << " 0 - Create empty abc" << std::endl;
		std::cout << " 1 - Create abc of length n" << std::endl;
		std::cout << " 2 - Create abc from string" << std::endl;
		getn(k);
		if (k > -1 && k < 3)
		{
			// создание объекта
			ABC_class_b::Alphabet a;
			switch (k)
			{
				case 0:
					a = ABC_class_b::Alphabet();
					break;
				case 1:
					int n;
					getn(n);
					try
					{
						a = ABC_class_b::Alphabet(n);
					}
					catch (const std::exception& exception)
					{
						std::cout << exception.what() << std::endl;
						std::cin.ignore();
						continue;
					}
					break;
				case 2:
					char* str = getstr(std::cin);
					try {
						a = ABC_class_b::Alphabet(str);
					}
					catch (const std::exception& exception)
					{
						std::cout << exception.what() << std::endl;
						std::cin.ignore();
						continue;
					}
					delete[] str;
					break;
			}
			// работа с объектом
			ABC_class_b::Dialog(a);
		}
	}
	_CrtDumpMemoryLeaks();
}