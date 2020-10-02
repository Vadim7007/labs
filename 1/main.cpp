#include "C:\Users\vadim\Desktop\Я\Программирование\study\Lab1+\lib1.h"

int main(void) {
	using std::cin;
	using std::cout;
	using std::endl;
	struct item** matrix;
	if (int n = input_matrix(matrix)) {
		int* line;
		create(matrix, line, n);
		output_matrix(matrix, n);
		output_line(line, n);
		free_m(matrix, n);
		free_l(line);
	}
	_CrtDumpMemoryLeaks();
	return 0;
}