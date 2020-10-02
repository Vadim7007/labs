#include <C:\Users\vadim\Desktop\Я\Программирование\study\Lab1+\lib1.h>

using namespace lab1;

// функция ввода числа
template <class T>
int getn(T& a) {
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

// функция ввода разряженной матрицы
int input_matrix(struct item**& column)
{
	// матрица хранится в виде вектора списков
	using std::cin;
	using std::cout;

	// ввод количества строк
	cout << "Enter the count of rows.\n";
	int n = 0;
	getn(n);

	// создание вектора
	try {
		column = new struct item* [n];
	}
	catch (std::bad_alloc& er) {
		cout << "Error: " << er.what() << std::endl;
		return 0;
	}

	// обнуление вектора
	for (int i = 0; i < n; i++)
	{
		column[i] = nullptr;
	}

	// ввод чисел матрицы
	int i = -1;
	int j = 0;
	cout << "Enter the number of row (i). -1 for the end.\n";
	getn(i);
	// инициализация
	int* j_old = new int[n]; //here
	for (int i = 0; i < n; i++)
	{
		j_old[i] = -1;
	}

	while (i < n && i >-1)
	{
		cout << "Enter the number of column (j).\n";
		getn(j);
		// проверка на j в допустимах пределах и по порядку
		if (j >= 0 && j < n && j > j_old[i]) {
			// проверка первого элемента в списке
			if (column[i] == nullptr) {
				try {
					column[i] = new struct item;
				}
				catch (std::bad_alloc& er) {
					cout << "Error: " << er.what() << std::endl;
					return 0;
				}
				column[i]->ptr = nullptr;
				column[i]->j = j;
				cout << "Enter the number.\n";
				getn(column[i]->a);
				j_old[i] = j;
			}
			// проход по списку
			else {
				struct item* pt = column[i];
				int flag_search = 0;
				while (pt->ptr != nullptr)
				{
					if (pt->j == j) {
						cout << "Such item already exist.\n";
						flag_search = 1;
						break;
					}
					pt = pt->ptr;
				}
				if (!flag_search) {
					try {
						pt->ptr = new struct item;
					}
					catch (std::bad_alloc& er) {
						cout << "Error: " << er.what() << std::endl;
						return 0;
					}
					pt->ptr->ptr = nullptr;
					pt->ptr->j = j;
					cout << "Enter the number.\n";
					getn(pt->ptr->a);
					j_old[i] = j;
				}
			}
		}
		else {
			cout << "the j went out of bounds.\n";
		}
		// ввод нового элемента
		cout << "Enter the number of row (i). -1 for the end.\n";
		getn(i);
	}
	// очистка памяти для вектора j_old
	delete(j_old);
	// количество элементов
	return n;
}

// поиск максимального элемента в i-той строке матрицы
// возврашает значение элемента
int search_max(struct item** matrix, int i) {
	int max = 0;
	struct item* ptr = matrix[i];
	while (ptr != nullptr)
	{
		if (ptr->a > max)
		{
			max = ptr->a;
		}
		ptr = ptr->ptr;
	}
	return max;
}

// создание вектора по заданным правилам
void create(struct item** matrix, int*& line, int n) {

	// создание вектора
	try
	{
		line = new int[n];
	}
	catch (std::bad_alloc& er) {
		std::cout << "Error: " << er.what() << std::endl;
		line = nullptr;
		return;
	}

	// ввод элементов в вектор
	for (int i = 0; i < n; i++)
	{
		line[i] = 0;
		struct item* p = matrix[i];
		while (p != nullptr) {
			line[i] += (p->a) * search_max(matrix, p->j);
			p = p->ptr;
		}
	}
	return;
}

// вывод матрицы
void output_matrix(struct item** matrix, int n) {
	for (int i = 0; i < n; i++)
	{
		struct item* p = matrix[i];
		// если строка непустая
		if (p) {
			int k1 = 0;
			int k2;
			while (p) {
				k2 = p->j;
				for (int k = k1; k < k2; k++)
				{
					std::cout << "0\t";
				}
				std::cout << p->a << "\t";
				k1 = k2 + 1;
				p = p->ptr;
			}
			// вывод остальной части
			for (int k = k1; k < n; k++)
			{
				std::cout << "0\t";
			}
			std::cout << "\n";
		}
		// если строка пустая
		else {
			for (int k = 0; k < n; k++)
			{
				std::cout << "0\t";
			}
			std::cout << "\n";
		}
	}
	std::cout << std::endl;
}

// вывод вектора
void output_line(int* line, int n) {
	std::cout << "Vector:\t";
	for (int i = 0; i < n; i++)
	{
		std::cout << line[i] << "\t";
	}
	std::cout << std::endl;
	return;
}

// очистка памяти матрицы
void free_m(struct item** matrix, int n) {
	for (int i = 0; i < n; i++)
	{
		struct item* p = matrix[i];
		struct item* prev;
		while (p != nullptr) {
			prev = p;
			p = p->ptr;
			delete prev;
		}

	}
	delete[]matrix;
}

// очистка памяти вектора
void free_l(int* line) {
	delete[]line;
	return;
}