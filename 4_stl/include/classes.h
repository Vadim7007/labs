#pragma once

#include "my_stdlib.h"

enum ships
{
	cruiser,
	aircraft_carrier,
	aircraft_carrier_cruiser
};

enum aircrafts {
	fighter,
	bomber,
	front_bomber
};

enum weapons {
	light,
	middle,
	heavy
};

enum states {
	free,
	busy,
	ground
};

enum modificated_parametrs {	// параметры, которые могут быть модифицированы
	// для объектво 0 - 5
	HP,				// живучесть
	speed,			// скорость
	range,			// дальность хода объекта
	storage,		// максимальный размер склада корабля
	max_weapon,		// максимальное количество оружия
	max_aircraft,	// максимальное количество самолетов на корабле
	// для вооружения 6 - 9
	radius,			// радиус действия определенного оружия
	max_ammunation,	// максимальный боезапас на оружии
	damage,			// урон от одного выстрела
	rate,			// скорострельность
};

struct param_mission {
	int difficult;	// уровень сложности
	int goal;		// цель для победы (в сумме уничтоженного)
	bool mode;		// рельное время или пошагово
	int max_ship;	// максимальное количество кораблей в одном флоте
	bool side;		// какая цель - нападение или защита
};

struct param_weapon {
	int max_ammunation;		// боезопас для оружия
	int cost;				// стоимость оружия
	const std::string name;	// название оружия
	const weapons type;		// тип оружия
};

// неизменняемые параметры объекта, присваиваются при инциализации
struct const_param_object {
		int cost;		// стоимость объекта
};

// параметры объекта, которые могут быть изменены
struct param_object {
	int HP;		// максимальное количество прочности
	int speed;	// скорость объекта
	int range;	// дальность хода
};

/*
класс таблицы для хранения указателей на корабли, сортируются по позывным
*/
class table
{
public:
	table();
	~table();
	ship* get_ship(const std::string s);
	int get_num();
	void add_ship(const ship& s);
	void del_ship(const ship& s);
	void del_ship(const std::string s);

private:
	std::map<std::string, ship*> array;
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
class cell: public map
{
public:
	cell();
	~cell();
	void set_state(const states s);
private:
	states state;						// состояние ячейки
	const std::pair<int, int> coord;	// координаты ячейки
};

/*
виртуальный класс для кораблей и самолетов
*/
class object
{
public:
	object(const struct const_param_object& c_p,
		   const struct param_object& p, const bool a);
	~object();
	void destroyed();
	bool move(const std::pair<int, int>);
	void attack(object& o);
	void modificate(const modificated_parametrs);
	bool recharge();
	void set_coord(const std::pair<int, int>);

	// постояные параметры, определяемые при инициализации объекта
	const struct const_param_object c_param;

protected:
	void calculate_radius();

	bool activate;						// флаг активации объекта в данный момент
	int hp;								// количество прочности
	int radius;							// максимальный радиус атаки
	container<weapon> arms;				// набор оружия объекта
	std::pair<int, int> currnet_coord;	// текущие координаты
	std::pair<int, int> goal;			// целевые координаты (куда идет объект)
	bool affiliation;					// принадлежность пользователю
	int sum_costs;						// суммарная стоимость корабля
	float bonus;						// бонус за командира или его отсутствие
	// параметры, определяемые при создании объекта, которые могут быть изменены
	struct param_object param;
};

/*
виртуальный класс кораблей
*/
class ship: public object
{
public:
	ship(const struct const_param_object& c_p, const struct param_object& p, const bool a, const ships t) : object(c_p, p, a), type(t) {};
	~ship();
	std::vector<std::pair<int, int>> get_way(const std::pair<int, int>);
	const ships type;								// тип корабля
protected:
	std::pair<std::string, std::string> commander;	// звание и имя капитана судна
	std::string name;								// имя судна
	int ammunation;									// ёмкость склада с боеприпасами
	int max_weapon;									// максимальное количество оружия
	std::vector<int> ammo;							// боезапас по видам оружия
};

/*
виртуальный класс самолетов
*/
class aircraft : public object
{
public:
	aircraft(const struct const_param_object& c_p, const struct param_object& p, const bool a, const aircrafts t, const int r) : object(c_p, p, a), type(t), refueling(r) {};
	~aircraft();
	const aircrafts type;	// тип самолета
	const int refueling;	// время на заправку самолета
	void return_back();
	void transfer(ship& s);
protected:
	ship* affiliation_ship;	// корабль, которому принадлежит самолет
};

/*
класс авианесущего крейсера
*/
class air_cruiser: public ship
{
public:
	air_cruiser();
	~air_cruiser();

private:
	int max_aircraft;					// максимальное количество самолетов
	container<aircraft> aircrafts;		// все самолеты
	std::vector<int> aircrafts_count;	// количество самолетов по типам
};

/*
класс авианосца
*/
class air_carrier : public ship
{
public:
	air_carrier();
	~air_carrier();

private:
	int max_aircraft;					// максимальное количество самолетов
	container<aircraft> aircrafts;		// все самолеты
	std::vector<int> aircrafts_count;	// количество самолетов по типам
};

/*
класс крейсера
*/
class cruiser : public ship
{
public:
	cruiser();
	~cruiser();

private:

};

/*
класс истребителя
*/
class fighter: public aircraft
{
public:
	fighter();
	~fighter();

private:

};

/*
класс бомбардировщика
*/
class bomber : public aircraft
{
public:
	bomber();
	~bomber();

private:

};

/*
класс штурмовика
*/
class front_bomber : public aircraft
{
public:
	front_bomber();
	~front_bomber();

private:

};

/*
класс оружия объектов
*/
class weapon
{
public:
	weapon(const struct param_weapon p);
	~weapon();
	const struct param_weapon param;	// параметры, загружаемые изначально
private:
	int radius;				// радиус действия
	int ammination;			// боезапас
	bool activate;			// флаг активации
	int damage;				// наносимый урон
	int rate;				// скорострельность
};