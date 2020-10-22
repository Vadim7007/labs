#include "mylib.h"

namespace ABC_class {
	class Alphabet
	{
	public:
		// конструктор по умолчанию, создает пустой алфавит
		Alphabet();
		// создает алфавит заданной длины из символов ASCII
		Alphabet(const int k);	
		// для +=, уточнить, алфавит из одного символа
		Alphabet(const char& c);
		// создает алфавит из элементов строки
		Alphabet(const char* str);
		// перегруженный оператор вывода
		friend std::ostream& operator<<(std::ostream& ostream, const Alphabet& a);
		// перегруженный оператор ввода
		friend std::istream& operator>>(std::istream& istream, Alphabet& a);
		// перегруженный оператор посимвольного прибавления к алфавиту
		Alphabet& operator+=(const char& c);							// Зачем, работает и так
		// перегруженный оператор сложения двух алфавитов, возвращает новый
		friend Alphabet operator+(const Alphabet& a, const Alphabet& b);
		// метод для определения, имеется ли смивол в алфавите
		bool is_char(const char& c) const;
		// кодирование и декодирование строки на основе шифра цезаря
		// 0 в mode - декодирование, иначе кодирование
		// для cipher_text память должна быть выделена заранее
		int coding(const char* plain_text, int size, 
					 int offset, const bool mode, char* cipher_text) const;

	private:
		int get_index(const char& c) const;	// возвращает номер символа в алфавите
		static const int N = 26;			// максимальный размер алфавита
		int n;								// текущий размер алфавита
		char abc[N];						// алфавит
	};
};

// диалоговая функция для работы с объектом
void Dialog(ABC_class::Alphabet& a);