#ifndef LIB3_2_H
#include "lib3_2.h"
#endif LIB3_2_H

namespace ABC_class_c {
	Alphabet::Alphabet() noexcept
	{
		n = 0;
		abc = nullptr;
	}

	// может вызвать исключение
	Alphabet::Alphabet(const int k)
	{
		n = k;
		if (k < 0)
		{
			std::cout << "Warning. n will be zero." << std::endl;
			n = 0;
			this->abc = nullptr;
			return;
		}
		abc = new char[k];
		for (int i = 0; i < k; i++)
		{
			abc[i] = i%95 + 32;
		}
	}

	// может вызвать исключение
	Alphabet::Alphabet(const char& c) {
		abc = new char[1];
		abc[0] = c;
		n = 1;
	}

	// может вызвать исключение
	Alphabet::Alphabet(const char* str) {
		int k = 0;
		if (!str)
		{
			this->n = 0;
			this->abc = nullptr;
			return;
		}
		else {
			k = strlen(str);		// размер строки
		}
		/*
		есть 2 варианта 
		1) создавать массив сразу по длине строки
		- не эффективен по памяти, так как возможно, 
		что не вся строка будет записана в алфавит (массив abc),
		тогда выделяется лишняя память
		2) перевыделять память каждый раз, когда добавляется элемент
		- не эффективен по времени выполнения (зависит от k^2)
		*/
		abc = new char[k];
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
				n = m;
			}
		}
		abc = r_alloc(abc, m, k);
	}

	Alphabet::Alphabet(Alphabet&& c) noexcept {
		n = c.n;
		abc = c.abc;
		c.n = 0;
		c.abc = nullptr;
	}

	// может вызвать исключение
	Alphabet::Alphabet(const Alphabet& c){
		n = c.n;
		try {
			abc = new char[n];
		}
		catch (std::exception& exception) {
			throw std::bad_alloc();
		}
		memcpy(abc, c.abc, n);
	}

	Alphabet::~Alphabet() noexcept {
		delete[] abc;
	}

	std::ostream& operator<<(std::ostream& ostream, const Alphabet& a) noexcept {
		for (int i = 0; i < a.n; i++)
		{
			ostream << a.abc[i];
		}
		return ostream;
	}

	// при ошибке содержимое обьекта "a" не теряется
	std::istream& operator>>(std::istream& istream, Alphabet& a) noexcept {
		char* str = getstr(istream);
		Alphabet b;
		try
		{
			b = Alphabet(str);
		}
		catch (const std::exception&)
		{
			istream.setstate(std::ios_base::failbit);
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
		if (!a.is_char(c)) {
			a.abc = r_alloc(a.abc, (a.n+1), a.n);
			if (!a.abc) {
				throw std::bad_alloc();
			}
			a.abc[a.n] = c;
			a.n++;
		}
		return a;
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

	// может вызвать исключение
	Alphabet& Alphabet::operator=(const Alphabet& c){
		this->n = c.n;
		try
		{
			delete[](this->abc);
			this->abc = new char[n];
		}
		catch (const std::exception&)
		{
			throw std::bad_alloc();
		}
		memcpy(this->abc, c.abc, c.n);
		return *this;
	}

	Alphabet& Alphabet::operator=(Alphabet&& c) noexcept {
		this->n = c.n;
		delete[](this->abc);
		this->abc = c.abc;
		c.n = 0;
		c.abc = nullptr;
		return *this;
	}

	// проверка на существованрие символа в алфавите
	bool Alphabet::is_char(const char& c) const noexcept {
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
	int Alphabet::get_index(const char& c) const noexcept {
		for (int i = 0; i < this->n; i++)
		{
			if (this->abc[i] == c)
			{
				return i;
			}
		}
		return -1;
	}

	// кодирование и декодирование строки
	// может вернуть -1 в случае ошибки
	int Alphabet::coding(const char* plain_text, int size,
		int offset, const bool mode, char* cipher_text) const noexcept {

		// проверка на правильность
		if (strlen(plain_text) != size)
		{
			std::cout << "Invalid size of text" << std::endl;
			return -1;
		}
		try
		{
			cipher_text[size];
		}
		catch (const std::exception& exception)
		{
			std::cout << exception.what() << std::endl;
			return -1;
		}

		// замена
		for (int i = 0; i < size; i++)
		{
			int j = this->get_index(plain_text[i]);
			if (j == -1) {
				std::cout << "Incomplete alphabet" << std::endl;
				cipher_text[0] = '\0';
				return -1;
			}
			if (mode) {
				cipher_text[i] = this->abc[(j + offset) % this->n];
			}
			else {
				cipher_text[i] = this->abc[(j - offset + abs(offset) * this->n) % this->n];
			}
		}
		cipher_text[size] = '\0';
		return 0;
	}

	int Alphabet::get_len() const noexcept {
		return this->n;
	}

	void Dialog(ABC_class_c::Alphabet& a) noexcept {
		int k = 0;
		while (k != -1) {
			system("cls");
			std::cout << "Enter action" << std::endl;
			std::cout << "-1 - Exit" << std::endl;
			std::cout << " 0 - Add 2 alphabets" << std::endl;
			std::cout << " 1 - Add symbol" << std::endl;
			std::cout << " 2 - Encoding string" << std::endl;
			std::cout << " 3 - Decoding string" << std::endl;
			std::cout << " 4 - Determining if a symbol is" << std::endl;
			std::cout << " 5 - Output alphabet" << std::endl;
			getn(k);
			if (k > -1 && k < 6)
			{
				switch (k)
				{
				case 0: {
					std::cout << "Enter new alphabet" << std::endl;
					ABC_class_c::Alphabet b;
					std::cin >> b;
					try {
						a = a + b;
					}
					catch (const std::exception& exception)
					{
						std::cout << exception.what() << std::endl;
						std::cin.ignore();
					}
					break;
				}
				case 1: {
					char c;
					std::cin.get(c);
					try
					{
						a += c;
					}
					catch (const std::exception& exception)
					{
						std::cout << exception.what() << std::endl;
						std::cin.ignore();
					}
					break;
				}
				case 2: {
					std::cout << "Enter string and key" << std::endl;
					char* str = getstr(std::cin);
					int k;
					getn(k);
					char* cipher;
					try
					{
						cipher = new char[strlen(str) + 1]; // +1 для '\0'
					}
					catch (const std::exception& exception)
					{
						std::cout << exception.what() << std::endl;
						delete[]str;
						std::cin.ignore();
						break;
					}
					a.coding(str, strlen(str), k, 1, cipher);
					std::cout << cipher << std::endl;
					delete[]str;
					delete[]cipher;
					std::cin.ignore();
					break;
				}
				case 3: {
					std::cout << "Enter string and key" << std::endl;
					char* str = getstr(std::cin);
					int k;
					getn(k);
					char* cipher;
					try
					{
						cipher = new char[strlen(str) + 1]; // +1 для '\0'
					}
					catch (const std::exception& exception)
					{
						std::cout << exception.what() << std::endl;
						delete[]str;
						std::cin.ignore();
						break;
					}
					a.coding(str, strlen(str), k, 0, cipher);
					std::cout << cipher << std::endl;
					delete[]str;
					delete[]cipher;
					std::cin.ignore();
					break;
				}
				case 4: {
					char c;
					std::cin.get(c);
					std::cin.ignore();
					std::cout << a.is_char(c) << std::endl;
					std::cin.ignore();
					break;
				}
				case 5: {
					std::cout << a << std::endl;
					std::cin.ignore();
					break;
				}
				}
			}
		}
		return;
	}
}