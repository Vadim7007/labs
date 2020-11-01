#ifndef MYLIB_H
#include "mylib.h"
#endif MYLIB_H

namespace ABC_class_c {
	class Alphabet
	{
	public:
		// конструктор по умолчанию, создает пустой алфавит
		Alphabet() noexcept;
		// создает алфавит заданной длины из символов ASCII
		Alphabet(const int k);
		// для +=, уточнить, алфавит из одного символа
		Alphabet(const char& c);
		// создает алфавит из элементов строки
		Alphabet(const char* str);
		// перемещающий конструктор
		Alphabet(Alphabet&& c) noexcept;
		// копирующий конструктор
		Alphabet(const Alphabet& c);
		// деструктор
		~Alphabet() noexcept;
		// перегруженный оператор вывода
		friend std::ostream& operator<<(std::ostream& ostream, 
			const Alphabet& c) noexcept;
		// перегруженный оператор ввода
		friend std::istream& operator>>(std::istream& istream, 
			Alphabet& c) noexcept;
		// перегруженный оператор посимвольного прибавления к алфавиту
		Alphabet& operator+=(const char& c);	
		// перегруженный оператор сложения двух алфавитов, возвращает новый
		Alphabet operator+(const Alphabet& c);
		// перемещающее присваивание
		Alphabet& operator=(const Alphabet& c);
		// копирующее присваивание
		Alphabet& operator=(Alphabet&& c) noexcept;
		// метод для определения, имеется ли смивол в алфавите
		bool is_char(const char& c) const noexcept;
		// кодирование и декодирование строки на основе шифра цезаря
		// 0 в mode - декодирование, иначе кодирование
		// для cipher_text память должна быть выделена заранее
		int coding(const char* plain_text, int size,
			int offset, const bool mode, char* cipher_text) const noexcept;

	private:
		int get_index(const char& c) const noexcept;	// возвращает номер символа в алфавите
		int n;								// текущий размер алфавита
		char* abc;							// алфавит
	};

	// диалоговая функция для работы с объектом
	void Dialog(ABC_class_c::Alphabet& c) noexcept;
};