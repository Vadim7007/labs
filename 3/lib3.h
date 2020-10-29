#ifndef MYLIB_H
#include "mylib.h"
#endif MYLIB_H

namespace ABC_class_a {
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
		std::ostream& output(std::ostream& ostream);
		// перегруженный оператор ввода
		friend std::istream& input(std::istream& istream, Alphabet& a);
		// перегруженный оператор посимвольного прибавления к алфавиту
		Alphabet add(const char& c);							
		// перегруженный оператор сложения двух алфавитов, возвращает новый
		Alphabet sum(const Alphabet& a);
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

	// диалоговая функция для работы с объектом
	void Dialog(ABC_class_a::Alphabet& a);
};

namespace ABC_class_b {
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
		Alphabet& operator+=(const char& c);	
		// перегруженный оператор сложения двух алфавитов, возвращает новый
		Alphabet operator+(const Alphabet& b);
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

	// диалоговая функция для работы с объектом
	void Dialog(ABC_class_b::Alphabet& a);
};