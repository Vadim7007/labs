//#include "my_stdlib.h"
#include "/Users/vadim/Desktop/Я/Программирование/study/Lab4/include/my_stdlib.h"

char* getstr(std::istream& istream) {
	char* str = nullptr;
	char c;
	int i = 0;
	do
	{
		i++;
		str = r_alloc(str, i, i - 1);
		if (!str) {
			istream.setstate(std::ios_base::failbit);
			return nullptr;
		}
		istream.get(c);
		str[i - 1] = c;
	} while (c != '\n');
	str[i - 1] = '\0';
	return str;
}

int random(const int N) noexcept {
	int n = ((rand() + clock()) % (2 * N)) - N;
	return n;
}

char* random_str(const int n) noexcept {
	char* str;
	try
	{
		str = new char[n + 1];
	}
	catch (const std::exception&)
	{
		return nullptr;
	}
	for (int i = 0; i < n; i++)
	{
		int k = (rand() % 2 + 1) * 32 + 33 + rand() % 26;
		str[i] = k;
	}
	str[n] = '\0';
	return str;
}