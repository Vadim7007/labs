﻿#ifndef LIB3_H
#include "lib3.h"
#endif LIB3_H

namespace ABC_class_a {
	Alphabet::Alphabet()
	{
		n = 0;
	}

	// может вызвать исключение
	Alphabet::Alphabet(const int k)
	{
		if (k > N)
		{
			throw std::invalid_argument("Exceeded maximum alphabet size.\n");
		}
		else
		{
			n = k;
			if (k<0)
			{
				n = 0;
			}
			for (int i = 0; i < k; i++)
			{
				abc[i] = i + 48;
			}
		}
	}

	Alphabet::Alphabet(const char& c) {
		abc[0] = c;
		n = 1;
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
				if (m >= N) {	// если превышен максимальный размер алфавита
					throw std::length_error("Exceeded maximum alphabet size.\n");
				}
				abc[m] = str[i];
				m++;
				n = m;
			}
		}
	}

	std::ostream& Alphabet:: output(std::ostream& ostream) {
		for (int i = 0; i < this->n; i++)
		{
			ostream << this->abc[i];
		}
		return ostream;
	}

	// при ошибке содержимое обьекта не теряется
	std::istream& input(std::istream& istream, Alphabet& a) {
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
	Alphabet Alphabet::add(const char& c) {
		if (this->n == this->N)
		{
			throw std::length_error("Exceeded maximum alphabet size.\n");
		}
		if (this->is_char(c)) {
			return *this;
		}
		else {
			this->abc[this->n] = c;
			this->n++;
			return *this;
		}
	}

	// сложение двух алфавитов
	// может вызвать исключение
	Alphabet Alphabet::sum(const Alphabet& a) {
		Alphabet c = a;
		for (int i = 0; i < this->n; i++)
		{
			c.add(this->abc[i]);
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

	// кодирование и декодирование строки
	// может вернуть -1 в случае ошибки
	int Alphabet::coding(const char* plain_text, int size,
		int offset, const bool mode, char* cipher_text) const {

		// проверка на правильность данных
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
				cipher_text[i] = this->abc[(j - offset + offset * this->n) % this->n];
			}
		}
		cipher_text[size] = '\0';
		return 0;
	}

	void Dialog(ABC_class_a::Alphabet& a) {
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
					ABC_class_a::Alphabet b;
					input(std::cin, b);
					try {
						a = a.sum(b);
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
						a.add(c);
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
					a.output(std::cout);
					std::cin.ignore();
					break;
				}
				}
			}
		}
		return;
	}
}

namespace ABC_class_b {
	Alphabet::Alphabet()
	{
		n = 0;
	}

	// может вызвать исключение
	Alphabet::Alphabet(const int k)
	{
		if (k > N)
		{
			throw std::invalid_argument("Exceeded maximum alphabet size.\n");
		}
		else
		{
			n = k;
			if (k < 0)
			{
				n = 0;
			}
			for (int i = 0; i < k; i++)
			{
				abc[i] = i + 48;
			}
		}
	}

	Alphabet::Alphabet(const char& c) {
		abc[0] = c;
		n = 1;
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
				if (m >= N) {	// если превышен максимальный размер алфавита
					throw std::length_error("Exceeded maximum alphabet size.\n");
				}
				abc[m] = str[i];
				m++;
				n = m;
			}
		}
	}

	std::ostream& operator<<(std::ostream& ostream, const Alphabet& a) {
		for (int i = 0; i < a.n; i++)
		{
			ostream << a.abc[i];
		}
		return ostream;
	}

	// при ошибке содержимое обьекта "a" не теряется
	std::istream& operator>>(std::istream& istream, Alphabet& a) {
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
	Alphabet& Alphabet::operator+=(const char& c) {
		if (this->n == this->N)
		{
			throw std::length_error("Exceeded maximum alphabet size.\n");
		}
		if (this->is_char(c)) {
			return *this;
		}
		else {
			this->abc[this->n] = c;
			this->n++;
			return *this;
		}
	}

	// сложение двух алфавитов
	// может вызвать исключение
	Alphabet Alphabet::operator+(const Alphabet& b) {
		Alphabet c = *this;
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

	// кодирование и декодирование строки
	// может вернуть -1 в случае ошибки
	int Alphabet::coding(const char* plain_text, int size,
		int offset, const bool mode, char* cipher_text) const {

		// проверка на правильность данных
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
				cipher_text[i] = this->abc[(j - offset + offset * this->n) % this->n];
			}
		}
		cipher_text[size] = '\0';
		return 0;
	}

	void Dialog(ABC_class_b::Alphabet& a) {
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
					ABC_class_b::Alphabet b;
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