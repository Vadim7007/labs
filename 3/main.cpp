#include "lib3.h"

int main(void) {
	int k = 0;
	while (k != -1) {
		system("cls");
		std::cout << "Enter action" << std::endl;
		std::cout << "-1 - Exit" << std::endl;
		std::cout << " 0 - Create empty abc" << std::endl;
		std::cout << " 1 - Create abc of length n" << std::endl;
		std::cout << " 2 - Create abc from string" << std::endl;
		getn(k);
		std::cin.get();
		if (k > -1 && k < 3)
		{
			ABC_class::Alphabet a;
			switch (k)
			{
				case 0:
					a = ABC_class::Alphabet();
					break;
				case 1:
					int n;
					getn(n);
					a = ABC_class::Alphabet(n);
					break;
				case 2:
					a = ABC_class::Alphabet(getstr(std::cin));
					break;
			}
			Dialog(a);
		}
		std::cin.get();
	}
	_CrtDumpMemoryLeaks();
}