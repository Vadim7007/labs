#include "mylib.h"

namespace ABC_class {
	class Alphabet
	{
	public:
		Alphabet();
		Alphabet(const int k);
		Alphabet(const char& c); //
		Alphabet(const char* str);
		friend std::ostream& operator<<(std::ostream& ostream, const Alphabet& a);
		friend std::istream& operator>>(std::istream& istream, Alphabet& a);
		Alphabet& operator+=(const char& c); // Зачем, работает и так
		friend Alphabet operator+(const Alphabet& a, const Alphabet& b);
		bool is_char(const char& c) const;
		int coding(const char* plain_text, int size, 
					 int offset, const bool mode, char* cipher_text) const;

	private:
		int get_index(const char& c) const;
		static const int N = 26;	// максимальный размер алфавита
		int n;						// текущий размер алфавита
		char abc[N];				// алфавит
	};
};

void Dialog(ABC_class::Alphabet& a);