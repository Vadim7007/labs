#include "lib3.h"

Alphabet::Alphabet()
{
	n = 0;
}

// может вызвать исключение
Alphabet::Alphabet(const int k)
{
	if (k > N)
	{
		throw std::exception("Exceeded maximum alphabet size.\n");
	}
	else
	{
		n = k;
		for (int i = 0; i < k; i++)
		{
			abc[i] = i + 48;
		}
	}
}

// может вызвать исключение
Alphabet::Alphabet(const char* str) {
	int k = strlen(str);			// размер строки
	int m = 0;						// текущий размер алфавита
	for (int i = 0; i < k; i++) {	// для каждого символа из строки

		// проверка на существование этого символа в алфавите
		if (this->is_char(str[i]))	// если такой элемент был найден
		{
			continue;
		}
		else {	// если элемент новый
			abc[m] = str[i];
			m++;
		}
		if (m > N) {	// если превышен максимальный размер алфавита
			throw std::exception("Exceeded maximum alphabet size.\n");
		}
	}
	n = m;
}

std::ostream& operator<<(std::ostream& ostream, const Alphabet& a) {
	for (int i = 0; i < a.n; i++)
	{
		ostream << a.abc[i];
	}
	return ostream;
}

std::istream& operator>>(std::istream& istream, Alphabet& a) {
	char* str = new char[a.N];
	istream.getline(str, a.N);
	Alphabet b;
	try
	{
		b = Alphabet(str);
	}
	catch (const std::exception&)
	{
		istream.setstate(std::ios_base::failbit);
		istream.setstate(std::ios_base::goodbit);
		delete[] str;
		return istream;
	}
	a = b;
	delete[] str;
	return istream;
}

// добавление символа в алфавит
// может вызвать исключение
Alphabet& operator+=(Alphabet& a, const char& c) {
	if (a.n == a.N)
	{
		throw std::exception("Exceeded maximum alphabet size.\n");
	}
	if (a.is_char(c)) {
		return a;
	}
	else {
		a.abc[a.n] = c;
		a.n++;
		return a;
	}
}

// сложение двух алфавитов
// может вызвать исключение
Alphabet operator+(const Alphabet& a, const Alphabet& b) {
	Alphabet c = a;
	for (int i = 0; i < b.n; i++)
	{
		c += b.abc[i];
	}
	return c;
}

// проверка на существованрие символа в алфавите
bool Alphabet::is_char(const char& c) const {
	for (int i = 0; i < this->n; i++)
	{
		if (this->abc[i] == c)
		{
			return true;
		}
	}
	return false;
}

// возвращает индекс символа в алфавите или -1, если его нет
int Alphabet::get_index(const char& c) const {
	for (int i = 0; i < this->n; i++)
	{
		if (this->abc[i] == c)
		{
			return i;
		}
	}
	return -1;
}

// создание новой закодированной строки
char* Alphabet::coding(const char* str, int k, const char* mode) const {
	if (k < 0) {
		std::cout << "Invalid offset" << std::endl;
		return NULL;
	}
	int size = strlen(str);
	char* cipher = new char[size];
	for (int i = 0; i < k; i++)
	{
		int j = this->get_index(str[i]);
		if (j == -1) {
			std::cout << "Incomplete alphabet" << std::endl;
			delete[] cipher;
			return NULL;
		}
		if (mode == "encoding") {
			cipher[i] = this->abc[(j + k) % this->n];
		}
		else if (mode == "decoding") {
			cipher[i] = this->abc[(k - j + this->n) % this->n];
		}
		else {
			std::cout << "Invalid mode" << std::endl;
			delete[] cipher;
			return NULL;
		}
	}
	return cipher;
}