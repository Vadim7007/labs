#pragma once

// �����������
#include <math.h>
#include <corecrt_math_defines.h>
#include <stdlib.h>
#include <utility>
// ������ ������
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
// ����
#include <iostream>
#include <limits>
#include <sstream>
#include <conio.h>
#include <iomanip>
// ������ �� ��������
#include <time.h>
#include <dos.h>
// ����������
#include <string>
#include <vector>
#include <map>

#define _CRT_SECURE_NO_WARNINGS

// ������� ����� �����
template <class T>
int getn(T& a) {
	using std::cin;
	cin >> a;
	while (!cin.good())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cin.ignore();
		cin.clear();
		cin >> a;
	}
	cin.ignore(1);
	return 1;
}

// ������� ��������� ������ ���������� ������
template <class T>
T* r_alloc(const T* array, const int new_size, int length) {
	T* n_array;
	try
	{
		n_array = new T[new_size];
	}
	catch (const std::exception&)
	{
		return nullptr;
	}
	if (new_size < length)
	{
		length = new_size;
	}
	try
	{
		memcpy(n_array, array, length);
	}
	catch (const std::exception&)
	{
		delete[] n_array;
		n_array = nullptr;
	}

	delete[] array;
	return n_array;
}

// ������� ����� ������ ������������ �����
char* getstr(std::istream& istream);

// ���������� ��������� ����� � ��������� �� - N �� N - 1 ������������
int random(const int N) noexcept;

// �������, ������������ ��������� ������ ����� n
char* random_str(const int n) noexcept;

// ����� ���������
template<class T>
class ptr
{
	T* m_ptr;
public:
	ptr(T* ptr = nullptr)
		:m_ptr(ptr)
	{
	}

	~ptr()
	{
		delete m_ptr;
	}

	ptr(ptr& a)
	{
		m_ptr = a.m_ptr;
		a.m_ptr = nullptr;
	}

	ptr& operator=(ptr& a)
	{
		if (&a == this)
			return *this;

		delete m_ptr;
		m_ptr = a.m_ptr;
		a.m_ptr = nullptr;
		return *this;
	}

	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
	bool isNull() const { return m_ptr == nullptr; }
};

// ������ � ��������
#include <Windows.h>