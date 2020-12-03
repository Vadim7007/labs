#pragma once


#include "units_classes.h"


enum states {
	free_st,
	busy,
	ground
};


struct mode_mission { // парамеры миссии, загружаемые изначально, отвечают за режим игры
	bool mode;			// режим рельного времени (иначе пошагово)
	int game_speed;		// темп игры
	bool side;			// цель для пользователя - нападение (иначе - защита)
	bool random;		// радномная карта (иначе - чистая)
};

struct param_mission { // парамеры миссии, загружаемые изначально
	int money;					// количесвто денег, выдаваемое игрокам
	int visibility;				// радиус видимости объектов
	float difficult;			// уровень сложности
	int goal;					// цель для победы (в сумме уничтоженного)
	int max_ship;				// максимальное количество кораблей в одном флоте
	std::pair<int, int> size;	// размер карты

	// список всех возможных коммандиров
	std::vector <std::pair<std::string, std::string>> list;
};


/*
класс таблицы для хранения указателей на корабли, сортируются по позывным
*/
class table
{
public:
	table() {};
	~table() {};
	std::shared_ptr<ship> get_ship(const std::string& s) noexcept;
	int get_num(const std::string& s) const noexcept;
	void add_ship(const struct const_param_object& c_p,
		const struct param_object& p,
		const struct param_ship& p_s, const bool a, const ships t,
		std::pair<std::string, std::string>&& c, std::string&& n) noexcept;
	bool find_ship(const std::string& s) const noexcept;
	void del_ship(const ship& s) noexcept;
	void del_ship(const std::string& s) noexcept;
	std::shared_ptr<ship> operator[](const std::string& s) noexcept;
	std::shared_ptr<ship> operator[](const int n) noexcept;
	int size() const { return conformity.size(); }

private:
	std::vector<std::string> conformity;
	std::map<std::string, std::shared_ptr<ship>> array;
};

/*
класс миссии
*/
class mission
{
public:
	mission(const struct mode_mission &m, const struct param_mission &p);
	~mission();
	const struct param_mission param;	// параметры игры
	const struct mode_mission mode;		// параметры для настройки режима игры

	bool buy_or_sell(player& p);
	bool transfer(aircraft& a, ship& s);
	void finish();
	void destroy(object& o);
	bool modificate(object& o);
	bool reached(ship& s);
	void general_death(player& p);
	// возвращает true, если игра завершена
	bool end_turn();

protected:
	int lenhtg_list;	// количесвто незанятых командиров
	map	arena;			// игровая карта
	table ships1;		// таблица кораблей пользователя
	table ships2;		// таблица кораблей бота
	player p1;			// пользователь
	player p2;			// бот
};

/*
класс одного игрока (пользователь и AI)
*/
class player
{
public:
	player() {};
	player(std::pair<std::string, std::string> g, int m);
	~player() {};
	void set_general(std::pair<std::string, std::string>);
	std::pair<std::string, std::string> get_general() const;
	void increase_damage(const int a);

protected:
	int money;										// текущее количество денег
	int costs;										// суммарно потрачено денег
	int damage;										// суммарный урон игрока
	std::pair<std::string, std::string> general;	// командующий флотом
};

/*
класс одной клетки карты
*/
class cell
{
public:
	cell(const int x, const int y);
	~cell() {};
	void set_state(const states s);

private:
	states state;						// состояние ячейки
	const std::pair<int, int> coord;	// координаты ячейки
};

/*
класс игровой карты
*/
class map
{
public:
	map() {};
	map(const std::pair<int, int>, bool);
	~map() {};
	map& operator=(map&& m);

protected:
	std::vector<std::vector<cell>> array;	// массив ячеек карты
	const std::pair<int, int> size;			// размер карты
};