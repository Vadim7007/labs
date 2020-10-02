// ошибки памяти
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
// ввод
#include <iostream>
#include <limits>

namespace lab1 {
	struct item {
		int j, a;
		struct item* ptr;
	};
}
using namespace lab1;

// функция ввода разряженной матрицы
int input_matrix(struct item**& column);

// создание вектора по заданным правилам
void create(struct item** matrix, int*& line, int n);

// вывод матрицы
void output_matrix(struct item** matrix, int n);

// вывод вектора
void output_line(int* line, int n);

// очистка памяти матрицы
void free_m(struct item** matrix, int n);

// очистка памяти вектора
void free_l(int* line);