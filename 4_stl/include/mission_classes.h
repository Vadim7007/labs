#pragma once


#include "units_classes.h"


enum states {
	free_st,
	busy,
	ground
};


/*
шаблон контейнерного класса
*/
template <typename T>
class container
{
public:
	container();
	~container();
	T& operator[](int index);
	int length() { return this->length; };
private:
	T* array;
	int length = 0;
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
	void del_ship(const ship& s);
	void del_ship(const std::string& s);
	std::shared_ptr<ship> operator[](const std::string& s) noexcept;
	std::shared_ptr<ship> operator[](const int n) noexcept;

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
	mission();
	~mission();
	const struct param_mission param;	// параметры миссии, загружаемы изначально

	bool buy_ship(player& p);
	void sell_ship(player& p);
	bool buy_aircraft(player& p);
	void sell_aircraft(player& p);
	bool buy_weapons(ship& s);
	bool sell_weapons(ship& s);
	bool buy_ammunations(ship& s);
	bool sell_ammunations(ship& s);
	bool transfer(aircraft& a, ship& s);
	void finish();
	void destroy(ship& s);
	void destroy(aircraft& a);
	bool modificate(object& o);
	bool reached(ship& s);
	void general_death(player& p);

protected:
	int game_speed;		// темп игры
	int visibility;		// радиус видимости объектов
	map	arena;			// игровая карта
	// список всех возможных коммандиров
	std::vector <std::pair<std::string, std::string>> list;
	table ships1;		// таблица кораблей пользователя
	table ships2;		// таблица кораблей бота
};

/*
класс одного игрока (пользователь и AI)
*/
class player
{
public:
	player();
	~player();
	friend class mission;
	void set_general(std::pair<std::string, std::string>);
protected:
	int money;										// текущее количество денег
	int costs;										// суммарно потрачено денег
	int damage;										// суммарный урон игрока
	std::pair<std::string, std::string> general;	// командующий флотом
};

/*
класс игровой карты
*/
class map
{
public:
	map();
	~map();

protected:
	ptr<ptr<cell>> array;			// массив ячеек карты
	const std::pair<int, int> size;	// размер карты
};

/*
класс одной клетки карты
*/
class cell : public map
{
public:
	cell();
	~cell();
	void set_state(const states s);
private:
	states state;						// состояние ячейки
	const std::pair<int, int> coord;	// координаты ячейки
};