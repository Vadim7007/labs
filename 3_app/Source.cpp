#include "Source.h"

int mini_menu(player& person, const int digital, 
	const struct parametrs& p, bool* balls) {
	int action;
	do {
		system("cls");
		std::cout << std::endl;
		std::cout << "\t1 - View my cards." << std::endl;
		std::cout << "\t2 - View all balls." << std::endl;
		std::cout << "\t3 - Put barrell." << std::endl;
		std::cout << "\t4 - Continue." << std::endl;
		std::cout << "\t0 - Exit." << std::endl;
		action = -1;
		while (action < 0 || action > 4) {
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
					std::cout << '\t' << i;
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
		case 0:
			return 1;
		default:
			break;
		}
	} while (action!= 4 );

	//  действия, не связанные с выбором игрока (проверки)
	for (int j = 0; j < p.maps; j++)	// для каждой карты
	{
		if (!person.card[j].fil) {	// если карта ещё не заполнена
			// если вся линия заполнена
			if (person.card[j].MapState() == Prog3::BUSY) {
				person.shout();
				person.card[j]--;
			}
			// если пустых ячеек не осталось
			auto mtx = person.card[j].FreeCells();
			int comm = -1;
			if (mtx[comm + 1].type == Prog3::EMPTY) {
				person.card[j].fil = 1;
				person.fil++;
			}
		}
	}

	// если у игрока не осталось пустых карт
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
		//  выпадание мяча
		int digital;
		do {
			digital = random(45) + 46;
		} while (balls[digital - 1]);
		SetConsoleTextAttribute(console, BACKGROUND_RED 
									   | BACKGROUND_INTENSITY);
		std::cout << std::setw(20) << "Ball number " << digital 
			<< " dropped." << std::endl;
		balls[digital-1] = 1;

		// просмотр всех карт у ботов
		for (int i = 0; i < p.count; i++)	// для каждого игрока
		{
			SetConsoleTextAttribute(console, BACKGROUND_RED 
						| BACKGROUND_GREEN | BACKGROUND_BLUE);
			std::cout << std::setw(20) << ai[i].name << " plays...\n";
			Sleep(250);
			for (int j = 0; j < p.maps; j++)	// для каждой карты
			{
				if (!ai[i].card[j].fil) {	// если карта ещё не заполнена
					ai[i].card[j](digital);	// установить состоянение ячейки с этим номером
					// если вся линия заполнена
					if (ai[i].card[j].MapState() == Prog3::BUSY) {
						ai[i].shout();
						ai[i].card[j]--;
					}
					// если пустых ячеек не осталось
					auto mtx = ai[i].card[j].FreeCells();
					int comm = -1;
					if (mtx[comm + 1].type == Prog3::EMPTY) {
						ai[i].card[j].fil = 1;
						ai[i].fil++;
					}
				}
			}

			// если у бота не осталось пустых карт
			if (ai[i].fil == p.maps)
			{
				win = 1;
				SetConsoleTextAttribute(console, BACKGROUND_RED | BACKGROUND_INTENSITY);
				std::cout << std::setw(20) << ai[i].name << " win!" << std::endl;
				break;
			}
		}

		// меню для игрока
		if (!win) {
			win = mini_menu(person, digital, p, balls);
		}

	} while (!win);
	std::cin.ignore();
}

void download_game(const struct parametrs& p){
	// выход, если была соответсвующая команда
	if (p.exit == 1) {
		return;
	}

	// начало
	std::cout << std::setw(30) << "Download..." << std::endl;

	// создание игроков
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

	// создание игрока
	player person(p.maps, p.lines, 0);
	person.name = p.name;

	// массив шаров, которые выпали
	bool balls[Prog3::MaxNumber];
	for (int i = 0; i < Prog3::MaxNumber; i++)
	{
		balls[i] = FALSE;
	}

	// игра
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
