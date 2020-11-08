#include "mylib.h"
#include "Map.h"
#include <string> // не бейте

struct parametrs {
	int exit = 0;		// особый флаг, показывает, нужен ли выход из игры
	int count;			// количество игроков
	int lines;			// количесвто строк в карте
	int maps;			// количество карт у каждого игрока
	std::string name;	// имя главного персонажа
};

void download_game(const struct parametrs& p);

class player
{
public:
	player();
	player(int maps_count, int lines_count, int index);
	~player();
	void shout();		// метод, который говорит "квартира"
	Prog3::Map* card;	// массив карт
	int fil = 0;		// количесвто заполненный карт
	std::string name;	// имя игрока
private:
	int maps;	// количесвто карт у игрока
	int lines;	// количесвто линий в карте
};
