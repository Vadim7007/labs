// ошибки памяти
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
// ввод
#include <iostream>
#include <limits>

// функция ввода числа
template <class T>
int getn(T& a){
	using std::cin;
	cin >> a;
	while (!cin.good())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cin.clear();
		cin >> a;
	}
	return 1;
}