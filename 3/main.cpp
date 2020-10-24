#include "lib3.h"

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
					a = ABC_class_b::Alphabet(n);
					break;
				case 2:
					char* str = getstr(std::cin);
					a = ABC_class_b::Alphabet(str);
					delete[] str;
					break;
			}
			// работа с объектом
			ABC_class_b::Dialog(a);
		}
	}
	_CrtDumpMemoryLeaks();
}