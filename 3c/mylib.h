// стандартное
#include <math.h>
#include <corecrt_math_defines.h>
#include <stdlib.h>
#include <utility>
// ошибки памяти
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
// ввод
#include <iostream>
#include <limits>
#include <sstream>
// работа со временем
#include <time.h>

// функция ввода числа
template <class T>
int getn(T& a) {
	using std::cin;
	cin >> a;
	while (!cin.good())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cin.ignore();
		cin.clear();
		cin >> a;
	}
	cin.ignore(1);
	return 1;
}

// функция изменения объема выделенной памяти
template <class T>
T* r_alloc(const T* array, const int new_size, int length) {
	T* n_array;
	try
	{
		n_array = new T[new_size];
	}
	catch (const std::exception&)
	{
		return nullptr;
	}
	if (new_size < length)
	{
		length = new_size;
	}
	try
	{
		memcpy(n_array, array, length);
	}
	catch (const std::exception&)
	{
		delete[] n_array;
		n_array = nullptr;
	}

	delete[] array;
	return n_array;
}

// функция ввода строки произвольной длины
char* getstr(std::istream& istream);

// возвращает случайное число в диапозоне от - N до N - 1 включительно
int random(const int N) noexcept;

// функция, генерирующая случайную строку длины n
char* random_str(const int n) noexcept;