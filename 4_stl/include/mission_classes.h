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
класс одного игрока (пользователь и AI)
*/
class player
{
public:
	player() noexcept {};
	player(std::pair<std::string, std::string>&& g, const int m, const bool a) noexcept;
	~player() noexcept {};
	void set_general(std::pair<std::string, std::string> g) noexcept;
	std::pair<std::string, std::string> get_general() const noexcept;
	void increase_damage(const int a) noexcept;
	bool set_money(const int increase) noexcept;
	int get_money() const noexcept;
	int get_damage() const noexcept { return damage; }

	bool affilation;

protected:
	int money;										// текущее количество денег
	int costs;										// суммарно потрачено денег
	int damage;										// суммарный урон игрока
	std::pair<std::string, std::string> general;	// командующий флотом
};

/*
класс таблицы для хранения указателей на корабли, сортируются по позывным
*/
class table
{
public:
	table() { ids = 0; };
	~table() {};
	std::shared_ptr<ship> get_ship(const std::string& s) noexcept;
	int get_num(const std::string& s) const noexcept;
	void add_ship(const struct config& p, const bool a, const ships t,
		std::pair<std::string, std::string>&& c, std::string&& n);
	bool find_ship(const std::string& s) const noexcept;
	void del_ship(const ship& s) noexcept;
	void del_ship(const std::string& s) noexcept;
	std::shared_ptr<ship> operator[](const std::string& s) noexcept;
	std::shared_ptr<ship> operator[](const int n) noexcept;
	int size() const noexcept { return conformity.size(); }
	std::shared_ptr<ship> GetById(const int id) noexcept;

private:
	int ids;
	std::vector<std::pair<std::string, int>> conformity;
	std::map<std::string, std::shared_ptr<ship>> array;
};

/*
класс одной клетки карты
*/
class cell
{
public:
	cell(const int x, const int y) noexcept;
	~cell() noexcept {};
	void set_state(const states s) noexcept;

	states state;						// состояние ячейки
	const std::pair<int, int> coord;	// координаты ячейки
};

/*
класс игровой карты
*/
class Map
{
public:
	Map() noexcept {};
	Map(const std::pair<int, int>, const bool) noexcept;
	~Map() noexcept {};
	std::vector <cell>& operator[](const int i);
	std::vector<cell*> get_way(const cell& from, const cell& to) noexcept;
	void move_ob(object& o, cell& to) noexcept;

protected:
	std::vector<std::vector<cell>> array;	// массив ячеек карты
	const std::pair<int, int> size;			// размер карты
};

/*
класс миссии
*/
class mission
{
public:
	mission(const struct mode_mission &m,
		const struct param_mission &p, const struct config& c);
	~mission() {};
	const struct param_mission param;	// параметры игры
	const struct mode_mission mode;		// параметры для настройки режима игры
	const struct config conf;			// параметры юнитов

	std::shared_ptr<ship> GetById(const player& p, const int id) noexcept;
	bool buy_ship(player& p, ships t);
	void sell_ship(player& pl, const int index);
	bool buy_aircraft(player& p, aircrafts t, const int index);
	bool buy_weapons(player& p, weapons t, const int index);
	void buy_ammunations(player& p, const int index);
	void player_turn();
	bool modificate(player& p, object& o, const modificated_parametrs mp);
	bool transfer(aircraft& a, ship& s);
	void general_death(player& p);
	void player_ready();
	// возвращает true, если игра завершена
	bool end_turn();
	std::pair<std::string, std::string> get_commander();

	player p1;			// пользователь
	player p2;			// бот
	Map	arena;			// игровая карта

protected:
	int lenhtg_list;	// количесвто незанятых командиров
	table ships1;		// таблица кораблей пользователя
	table ships2;		// таблица кораблей бота
};