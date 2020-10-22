#include "mylib.h"

char* getstr(std::istream& istream) {
	/*
	char* str = nullptr;
	char* buf = nullptr;
	int i = 5;
	int k = 0;
	int sum = 0;
	buf = new char[i + 1];
	do {
		i++;
		//istream.getline(buf, i);
		k = istream.readsome(buf, i);
		//k = istream.gcount();
		str = r_alloc(str, sum + k, sum);
		for (int j = 0; j < k; j++)
		{
			str[sum + j] = buf[j];
		}
		sum = sum + k;
		buf = r_alloc(buf, i+1, i);
	} while (i == k);
	delete[] buf;
	*/
	char* str = nullptr;
	char c;
	int i = 0;
	do
	{
		i++;
		str = r_alloc(str, i, i - 1);
		istream.get(c);
		str[i - 1] = c;
	} while (c !=  '\n');
	return str;
}