#include "mylib.h"

class Alphabet
{
public:
	Alphabet();
	Alphabet(const int k);
	Alphabet(const char str[]);
	friend std::ostream& operator<<(std::ostream& ostream, const Alphabet& a);
	friend std::istream& operator>>(std::istream& istream, Alphabet& a);
	friend Alphabet& operator+=( Alphabet& a, const char& c);
	friend Alphabet operator+(const Alphabet& a, const Alphabet& b);
	bool is_char(const char& c);
	~Alphabet();

private:
	static const int N = 26;	// ������������ ������ ��������
	int n;						// ������� ������ ��������
	char abc[N];				// �������
};

Alphabet::Alphabet()
{
	n = 0;
}

Alphabet::Alphabet(const int k)
{
	if (k > N)
	{
		throw std::exception ("Exceeded maximum alphabet size.\n");
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

Alphabet::Alphabet(const char str[]) {
	int k = sizeof(str) / sizeof(char);	// ������ ������
	int m = 0;							// ������� ������ ��������
	for (int i = 0; i < k; i++) {		// ��� ������� ������� �� ������

		// �������� �� ������������� ����� ������� � ��������
		int j;
		for (j = 0; j < m; j++)
		{
			if (abc[j] == str[i]) {	// ���� ����� ������� ������
				break;
			}
		}
		if (j != m)	// ���� ����� ������� ��� ������
		{
			continue;
		}
		else {	// ���� ������� �����
			abc[m] = str[i];
			m++;
		}
		if (m > N) {	// ���� �������� ������������ ������ ��������
			throw std::exception("Exceeded maximum alphabet size.\n");
		}
	}
	n = m;
}

std::ostream& operator<<(std::ostream& ostream, const Alphabet& a){
	for (int i = 0; i < a.n; i++)
	{
		ostream << a.abc[i];
	}
	return ostream;
}

std::istream& operator>>(std::istream& istream, Alphabet& a) {
	char* str;
	istream.getline(str, a.N);
	Alphabet b;
	try
	{
		b  = Alphabet(str);
	}
	catch (const std::exception&)
	{
		istream.setstate(std::ios_base::failbit);
		istream.setstate(std::ios_base::goodbit);
		return istream;
	}
	a = b;
	return istream;
}

Alphabet& operator+=(Alphabet& a, const char& c) {
	if (a.n = a.N)
	{
		throw std::exception("Exceeded maximum alphabet size.\n");
	}
	int i;
	for (i = 0; i < a.n; i++)
	{
		if (a.abc[i] == c) {
			break;
		}
	}
	if (a.n != i) {
		return a;
	}
	else {
		a.abc[a.n] = c;
		a.n++;
		return a;
	}
}

Alphabet operator+(const Alphabet& a, const Alphabet& b) {
	Alphabet c = a;
	for (int i = 0; i < b.n; i++)
	{
		c += b.abc[i];
	}
	return c;
}

bool Alphabet::is_char(const char& c) {
	for (int i = 0; i < this->n; i++)
	{
		if (this->abc[i] == c)
		{
			return true;
		}
	}
	return false;
}

Alphabet::~Alphabet()
{
}