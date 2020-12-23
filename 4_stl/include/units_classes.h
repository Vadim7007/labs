#pragma once

#include "my_stdlib.h"

enum ships
{	// виды кораблей
	cruiser_t,
	aircraft_carrier_cruiser,
	aircraft_carrier
};

enum aircrafts {
	// виды самолетов
	fighter_t,
	front_bomber_t,
	bomber_t
};

enum weapons {
	// виды вооружения
	light,
	middle,
	heavy
};

enum modificated_parametrs {	
	// параметры, которые могут быть модифицированы
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

struct config {	
	// информация, загружаемая из конфигурационных файлов
	
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

	/*
	параметры объектов присваиваются кораблям
	самолетам они присваиваются с коэффицентом (через функции)
	*/

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
class aircraft;
class ship;

/*
виртуальный класс для кораблей и самолетов
*/
class object
{
public:
	object(const struct config& p, const bool a) noexcept;
	~object() noexcept {};
	virtual void attack(aircraft& a) noexcept = 0;
	virtual void attack(ship& s) noexcept = 0;
	void modificate(const modificated_parametrs& m) noexcept;
	void set_coord(const std::pair<int, int>& p) noexcept;
	void set_current_coord(const std::pair<int, int>& a) noexcept;
	friend int distance(const object& a, const object& b);
	int get_cost() const noexcept;
	int get_hp() const noexcept;
	void increase_cost(const int a) noexcept;
	std::pair<int, int> get_coord() const noexcept;
	virtual void recovery() noexcept = 0;
	virtual bool correct() noexcept = 0;
	virtual int get_range() const noexcept = 0;
	bool decrease_action() noexcept;

	bool destroyed;			// флаг, означающий уничтожение корабля
	bool activate;			// флаг активации объекта в данный момент
	const bool affiliation;	// принадлежность пользователю
	friend class weapon;

protected:
	virtual void download_arms(std::vector<std::vector<weapon>>& v) noexcept = 0;

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
		 std::pair<std::string, std::string>&& c, std::string&& n) noexcept;
	~ship() noexcept {};
	std::string get_name() const noexcept;
	std::pair<std::string, std::string> get_commander() const noexcept;
	void set_bonus(const float f) noexcept;
	void attack(aircraft& a) noexcept;
	void attack(ship& s) noexcept;
	aircraft* use_air(aircrafts a) noexcept;
	void recovery() noexcept;
	bool correct() noexcept;
	void remove(aircrafts a);
	bool get_max_a() const noexcept;
	void add_aircraft(aircraft* a) noexcept;
	void add_weapon(weapon* w) noexcept;
	void set_ammo(const int a1, const int a2, const int a3);
	int get_storage() const noexcept { return param.p_o[type].storage; }
	int get_range() const noexcept { return param.p_o[type].range; }

	const ships type;	// тип корабля	

protected:
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
		const aircrafts t, const int r, ship* const s) noexcept;
	aircraft(aircraft&& a) noexcept;
	aircraft(const aircraft& a) noexcept;
	~aircraft() noexcept {};
	void return_back() noexcept;
	void transfer(ship& s);
	void attack(aircraft& a) noexcept;
	void attack(ship& s) noexcept;
	void recovery() noexcept;
	bool correct() noexcept;
	int get_range() const noexcept { return param.p_o[type].range; }
	aircraft& operator=(aircraft&& a) noexcept;

	const aircrafts type;	// тип самолета
	const int refueling;	// время на заправку самолета

protected:
	virtual void download_arms(std::vector<std::vector<weapon>>& v) noexcept {};

	ship* affiliation_ship;	// корабль, которому принадлежит самолет
};

/*
класс авианесущего крейсера
*/
class air_cruiser: public ship
{
public:
	air_cruiser(const struct config& p, const bool a,
		std::pair<std::string, std::string>&& c, std::string&& n) noexcept;
	~air_cruiser() noexcept {};

private:
	void download_arms(std::vector<std::vector<weapon>>& v) noexcept;
};

/*
класс авианосца
*/
class air_carrier : public ship
{
public:
	air_carrier(const struct config& p, const bool a,
		std::pair<std::string, std::string>&& c, std::string&& n) noexcept;
	~air_carrier() noexcept {};

private:
	void download_arms(std::vector<std::vector<weapon>>& v) noexcept;
};

/*
класс крейсера
*/
class cruiser : public ship
{
public:
	cruiser(const struct config& p, const bool a,
		std::pair<std::string, std::string>&& c, std::string&& n) noexcept;
	~cruiser() noexcept {};
private:
	void download_arms(std::vector<std::vector<weapon>>& v) noexcept;
};

/*
класс истребителя
*/
class fighter: public aircraft
{
public:
	fighter(const struct config& p, const bool a,
		const int r, ship* const s) noexcept;
	~fighter() noexcept {};
};

/*
класс бомбардировщика
*/
class bomber : public aircraft
{
public:
	bomber(const struct config& p, const bool a,
		const int r, ship* const s) noexcept;
	~bomber() noexcept {};
};

/*
класс штурмовика
*/
class front_bomber : public aircraft
{
public:
	front_bomber(const struct config& p, const bool a,
		const int r, ship* const s) noexcept;
	~front_bomber() noexcept {};
};

/*
класс оружия объектов
*/
class weapon
{
public:
	weapon(object* const o, const weapons t) noexcept;
	~weapon() noexcept { this->affilation_object = nullptr; };
	weapon& operator=(const weapon& w) noexcept;
	void attack(object& o) noexcept;
	void modificate(const modificated_parametrs a) noexcept;
	bool recharge() noexcept;

	const weapons type;

private:
	int decrease_ammunation() noexcept;

	object* affilation_object;	// объект, которому оружие принадлежит
	int ammunation;				// боезапас
};