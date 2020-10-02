#include "mylib.h"

class Tr	// ����������
{
public:
	Tr();						// �����������
	Tr(double p);				// �����������
	~Tr();						// ����������
	void set(double new_p);		// ��������� ��������� ������
	
	double get(void) const;				// ��������� ��������� ������
	void coord(double& x, 
		double& y, double n_pi) const;	// ��������� ��������� �� ����
	double len(double n_pi) const;		// ���������� ����� ����
	double rad(double n_pi) const;		// ������ ��������
	double area(void) const;			// ������� ������
	double surface(void) const;			// ����������� ��������
	double volume(void) const;			// ����� ���� ��������
private:
	double a;
};