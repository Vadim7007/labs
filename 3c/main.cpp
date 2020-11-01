/*
сложение с nullptr
*/
#ifndef LIB3_H
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
			ABC_class_c::Alphabet c;
			switch (k)
			{
				case 0:
					c = ABC_class_c::Alphabet();
					break;
				case 1:
					int n;
					std::cout << "Enter n" << std::endl;
					getn(n);
					try
					{
						c = ABC_class_c::Alphabet(n);
					}
					catch (const std::exception& exception)
					{
						std::cout << exception.what() << std::endl;
						std::cin.ignore();
						continue;
					}
					break;
				case 2:
					std::cout << "Enter string" << std::endl;
					char* str = getstr(std::cin);
					try {
						c = ABC_class_c::Alphabet(str);
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
			ABC_class_c::Dialog(c);
		}
	}
	_CrtDumpMemoryLeaks();
}