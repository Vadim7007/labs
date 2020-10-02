// ������ ������
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
// ����
#include <iostream>
#include <limits>

namespace lab1 {
	struct item {
		int j, a;
		struct item* ptr;
	};
}
using namespace lab1;

// ������� ����� ����������� �������
int input_matrix(struct item**& column);

// �������� ������� �� �������� ��������
void create(struct item** matrix, int*& line, int n);

// ����� �������
void output_matrix(struct item** matrix, int n);

// ����� �������
void output_line(int* line, int n);

// ������� ������ �������
void free_m(struct item** matrix, int n);

// ������� ������ �������
void free_l(int* line);