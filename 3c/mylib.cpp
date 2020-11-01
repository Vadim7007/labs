#ifndef MYLIB_H
#include "mylib.h"
#endif MYLIB_H

char* getstr(std::istream& istream) {
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
	str[i - 1] = '\0';
	return str;
}
