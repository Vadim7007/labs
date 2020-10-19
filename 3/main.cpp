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
		if (k > -1 && k < 3)
		{
			switch (k)
			{
				case 0:
					ABC_class::Alphabet a;
					break;
				case 1:
					int n;
					getn(n);
					ABC_class::Alphabet a(n);
					break;
				case 2:

					break;

			}
		}
	}
	_CrtDumpMemoryLeaks();
	return 0;
}