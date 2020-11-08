#include "Source.h"

int mini_menu(player& person, const int digital, 
	const struct parametrs& p, bool* balls) {
	int action;
	do {
		system("cls");
		std::cout << std::setw(20) << "1 - View my cards." << std::endl;
		std::cout << std::setw(20) << "2 - View all balls." << std::endl;
		std::cout << std::setw(20) << "3 - Put barrell." << std::endl;
		std::cout << std::setw(20) << "4 - Continue" << std::endl;
		action = 0;
		while (action < 1 || action > 4) {
			getn(action);
		}
		switch (action)
		{
		case 1:
			for (int i = 0; i < p.maps; i++)
			{
				std::cout << person.card[i] << std::endl << std::endl;
			}
			std::cin.ignore();
			break;
		case 2:
			for (int i = 0; i < Prog3::MaxNumber; i++)
			{
				if (balls[i])
				{
					std::cout << std::setw(20) << i << " ";
				}
			}
			std::cout << std::endl;
			std::cin.ignore();
			break;
		case 3:
			for (int i = 0; i < p.maps; i++)
			{
				person.card[i](digital);
			}
			break;
		default:
			break;
		}
	} while (action!= 4);

	//  ��������, �� ��������� � ������� ������ (��������)
	for (int j = 0; j < p.maps; j++)	// ��� ������ �����
	{
		if (!person.card[j].fil) {	// ���� ����� ��� �� ���������
			// ���� ��� ����� ���������
			if (person.card[j].MapState() == Prog3::BUSY) {
				person.shout();
				person.card[j]--;
			}
			// ���� ������ ����� �� ��������
			auto mtx = person.card[j].FreeCells();
			int comm = -1;
			if (mtx[comm + 1].type == Prog3::EMPTY) {
				person.card[j].fil = 1;
			}
			person.fil++;
		}
	}

	// ���� � ������ �� �������� ������ ����
	if (person.fil == p.maps)
	{
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(console, BACKGROUND_RED | BACKGROUND_INTENSITY);
		std::cout << std::setw(20) << "You win!" << std::endl;
		return 1;
	}
	return 0;
}

void game(player* ai, const struct parametrs& p, player& person, bool* balls){
	int win = 0;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	do
	{
		system("cls");
		//  ��������� ����
		int digital;
		do {
			digital = random(45) + 46;
		} while (balls[digital - 1]);
		SetConsoleTextAttribute(console, BACKGROUND_RED 
									   | BACKGROUND_INTENSITY);
		std::cout << std::setw(20) << "Ball number " << digital 
			<< " dropped." << std::endl;
		balls[digital] = 1;

		// �������� ���� ���� � �����
		for (int i = 0; i < p.count; i++)	// ��� ������� ������
		{
			SetConsoleTextAttribute(console, BACKGROUND_RED 
						| BACKGROUND_GREEN | BACKGROUND_BLUE);
			std::cout << std::setw(20) << ai[i].name << " plays...\n";
			Sleep(300);
			for (int j = 0; j < p.maps; j++)	// ��� ������ �����
			{
				if (!ai[i].card[j].fil) {	// ���� ����� ��� �� ���������
					ai[i].card[j](digital);	// ���������� ����������� ������ � ���� �������
					// ���� ��� ����� ���������
					if (ai[i].card[j].MapState() == Prog3::BUSY) {
						ai[i].shout();
						ai[i].card[j]--;
					}
					// ���� ������ ����� �� ��������
					auto mtx = ai[i].card[j].FreeCells();
					int comm = -1;
					if (mtx[comm + 1].type == Prog3::EMPTY) {
						ai[i].card[j].fil = 1;
					}
					ai[i].fil++;
				}
			}

			// ���� � ���� �� �������� ������ ����
			if (ai[i].fil == p.maps)
			{
				win = 1;
				SetConsoleTextAttribute(console, BACKGROUND_RED | BACKGROUND_INTENSITY);
				std::cout << std::setw(20) << ai[i].name << "win!" << std::endl;
				break;
			}
		}

		// ���� ��� ������
		if (!win) {
			win = mini_menu(person, digital, p, balls);
		}

	} while (!win);
}

void download_game(const struct parametrs& p){
	// �����, ���� ���� �������������� �������
	if (p.exit == 1) {
		return;
	}

	// ������
	std::cout << std::setw(30) << "Download..." << std::endl;

	// �������� �������
	player* ai;
	try {
		ai = new player[p.count];
	}
	catch (std::bad_alloc &exception) {
		std::cout << exception.what() << std::endl;
		return;
	}
	for (int i = 0; i < p.count; i++)
	{
		ai[i] = player(p.maps, p.lines, i);
	}

	// �������� ������
	player person(p.maps, p.lines, 0);
	person.name = p.name;

	// ������ �����, ������� ������
	bool balls[Prog3::MaxNumber];
	for (int i = 0; i < Prog3::MaxNumber; i++)
	{
		balls[i] = FALSE;
	}

	// ����
	system("cls");
	game(ai, p, person, balls);

	return;
}

player::player() {
	card = nullptr;
}

player::player(int maps_count, int lines_count, int index)
{
	maps = maps_count;
	lines = lines_count;
	char num[3];
	_itoa(index, num, 10);
	name = "Player_";
	name+=num;
	card = new Prog3::Map[maps];
	for (int i = 0; i < maps; i++)
	{
		card[i] = Prog3::Map(lines);
	}
}

player::~player()
{
	delete[]card;
}

void player::shout() {

	std::cout << std::setw(20) << name << ": Kvartira!" << std::endl;
	return;
}