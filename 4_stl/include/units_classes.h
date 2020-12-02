#pragma once


#include "my_stdlib.h"


enum ships
{
	cruiser,
	aircraft_carrier_cruiser,
	aircraft_carrier
};

enum aircrafts {
	fighter,
	front_bomber,
	bomber
};

enum weapons {
	light,
	middle,
	heavy
};

enum modificated_parametrs {	// параметры, которые могут быть модифицированы
	// для объектво 0 - 5
	HP,				// живучесть
	speed,			// скорость
	range,			// дальность хода объекта
	storage,		// максимальный размер склада корабля
	max_weapon,		// максимальное количество оружия
	max_aircraft,	// максимальное количество самолетов на корабле
	// для вооружения 6 - 8
	Radius,			// радиус действия определенного оружия
	Damage,			// урон от одного выстрела
	Rate,			// скорострельность
};

struct config {	// информация, загружаемая из конфигурационных файлов
	// неизменяемые параметры оружия
	struct const_param_weapon {
		int max_ammunation;		// боезопас для оружия
		int cost;				// стоимость оружия
	};

	const_param_weapon c_p_w[3];

	// параметры оружия, которые могут быть изменены
	struct param_weapon {
		int radius;				// радиус действия
		int damage;				// наносимый урон
		int rate;				// скорострельность
	};

	param_weapon p_w[3];

	// неизменняемые параметры объекта, присваиваются при инциализации
	struct const_param_object {
		int cost;		// стоимость объекта
	};

	const_param_object c_p_o[3];


	// параметры объекта, которые могут быть изменены
	struct param_object {
		int HP;		// максимальное количество прочности
		int speed;	// скорость объекта
		int range;	// дальность хода
		int storage;// ёмкость склада с боеприпасами
	};

	struct param_object p_o[3];

	// параметры корабля, могут быть изменены
	struct param_ship {
		int max_weapon;		// максимальное количество оружия
		int max_aircraft;	// максимальное количество самолетов

	};

	struct param_ship p_s[3];
};

class weapon;

/*
виртуальный класс для кораблей и самолетов
*/
class object
{
public:
	object(const struct config& p, const bool a);
	~object() {};
	virtual void attack(aircraft& a) = 0;
	virtual void attack(ship& s) = 0;
	void modificate(const modificated_parametrs);
	void set_coord(const std::pair<int, int>);
	void correct();
	friend int distance(const object& a, const object& b);
	int get_cost() const;
	void increase_cost(int a);

	bool destroyed;			// флаг, означающий уничтожение корабля
	bool activate;			// флаг активации объекта в данный момент
	const bool affiliation;	// принадлежность пользователю
	friend class weapon;

protected:
	virtual void download_arms(std::vector<std::vector<weapon>>& v) = 0;

	int action;								// количесвто возможных действий
	int hp;									// количество прочности
	std::vector<std::vector<weapon>> arms;	// набор оружия объекта
	std::pair<int, int> currnet_coord;		// текущие координаты
	std::pair<int, int> goal;				// целевые координаты (куда идет объект)
	int sum_costs;							// суммарная стоимость корабля
	std::vector<int> ammo;					// боезапас по видам оружия
	// параметры, определяемые при создании объекта
	struct config param;
};

/*
виртуальный класс кораблей
*/
class ship: public object
{
public:
	ship(const struct config& p, const bool a, const ships t,
		 std::pair<std::string, std::string>&& c, std::string&& n);
	~ship() {};
	std::string get_name() const;
	std::pair<std::string, std::string> get_commander() const;
	void set_bonus(const float f);
	void attack(aircraft& a);
	void attack(ship& s);
	aircraft* use_air(aircrafts a);

	const ships type;	// тип корабля	

protected:
	int max_aircraft;								// максимальное количество самолетов
	std::vector<std::deque<aircraft>> own_aircrafts;// все самолеты
	float bonus = 1;								// бонус за командира или его отсутствие
	std::pair<std::string, std::string> commander;	// звание и имя капитана судна
	std::string name;								// имя судна
	int radius;										// максимальный радиус атаки
};

/*
виртуальный класс самолетов
*/
class aircraft : public object
{
public:
	aircraft(const struct config& p, const bool a, 
		const aircrafts t, const int r, ship* const s);
	~aircraft();
	void return_back();
	void transfer(ship& s);
	void attack(aircraft& a);
	void attack(ship& s);

	const aircrafts type;	// тип самолета
	const int refueling;	// время на заправку самолета

protected:
	virtual void download_arms(std::vector<std::vector<weapon>>& v);

	ship* affiliation_ship;	// корабль, которому принадлежит самолет
};

/*
класс авианесущего крейсера
*/
class air_cruiser: public ship
{
public:
	air_cruiser(const struct config& p, const bool a, const ships t,
		const int m, std::pair<std::string, std::string>&& c, std::string&& n);
	~air_cruiser() {};

private:
	void download_arms(std::vector<std::vector<weapon>>& v);
};

/*
класс авианосца
*/
class air_carrier : public ship
{
public:
	air_carrier(const struct config& p, const bool a, const ships t,
		const int m, std::pair<std::string, std::string>&& c, std::string&& n);
	~air_carrier() {};

private:
	void download_arms(std::vector<std::vector<weapon>>& v);
};

/*
класс крейсера
*/
class cruiser : public ship
{
public:
	cruiser(const struct config& p, const bool a, const ships t,
		std::pair<std::string, std::string>&& c, std::string&& n);
	~cruiser() {};
private:
	void download_arms(std::vector<std::vector<weapon>>& v);
};

/*
класс истребителя
*/
class fighter: public aircraft
{
public:
	fighter(const struct config& p, const bool a,
		const aircrafts t, const int r, ship* const s);
	~fighter() {};

private:

};

/*
класс бомбардировщика
*/
class bomber : public aircraft
{
public:
	bomber(const struct config& p, const bool a,
		const aircrafts t, const int r, ship* const s);
	~bomber() {};

private:

};

/*
класс штурмовика
*/
class front_bomber : public aircraft
{
public:
	front_bomber(const struct config& p, const bool a,
		const aircrafts t, const int r, ship* const s);
	~front_bomber() {};

private:

};

/*
класс оружия объектов
*/
class weapon
{
public:
	weapon(object* const o, const weapons t);
	~weapon() { this->affilation_object = nullptr; };
	void attack(object& o) noexcept;
	void modificate(const modificated_parametrs a) noexcept;
	bool recharge() noexcept;

	const weapons type;

private:
	int decrease_ammunation() noexcept;

	object* affilation_object;	// объект, которому оружие принадлежит
	int ammunation;				// боезапас
};