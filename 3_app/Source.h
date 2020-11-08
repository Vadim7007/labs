#include "mylib.h"
#include "Map.h"
#include <string> // �� �����

struct parametrs {
	int exit = 0;		// ������ ����, ����������, ����� �� ����� �� ����
	int count;			// ���������� �������
	int lines;			// ���������� ����� � �����
	int maps;			// ���������� ���� � ������� ������
	std::string name;	// ��� �������� ���������
};

void download_game(const struct parametrs& p);

class player
{
public:
	player();
	player(int maps_count, int lines_count, int index);
	~player();
	void shout();		// �����, ������� ������� "��������"
	Prog3::Map* card;	// ������ ����
	int fil = 0;		// ���������� ����������� ����
	std::string name;	// ��� ������
private:
	int maps;	// ���������� ���� � ������
	int lines;	// ���������� ����� � �����
};