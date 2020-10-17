#include "mylib.h"

class Alphabet
{
public:
	Alphabet();
	Alphabet(const int k);
	Alphabet(const char* str);
	friend std::ostream& operator<<(std::ostream& ostream, const Alphabet& a);
	friend std::istream& operator>>(std::istream& istream, Alphabet& a);
	friend Alphabet& operator+=( Alphabet& a, const char& c);
	friend Alphabet operator+(const Alphabet& a, const Alphabet& b);
	bool is_char(const char& c) const;
	char* coding(const char* str, int k, const char* mode) const;

private:
	int get_index(const char& c) const;
	static const int N = 26;	// максимальный размер алфавита
	int n;						// текущий размер алфавита
	char abc[N];				// алфавит
};