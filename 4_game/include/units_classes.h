/**
\file
\brief Классы юнитов
Файл с классами всех юнитов в игре и оружия, базовый файл для игры
*/

#pragma once

#include "my_stdlib.h"
#include "container.h"

/// возможные виды кораблей
enum ships
{	
	cruiser_t,					///< крейсер
	aircraft_carrier_cruiser,	///< авианесущий крейсер
	aircraft_carrier			///< авианосец
};

/// возможные виды самолетов
enum aircrafts {
	fighter_t,		///< тип истребителя
	front_bomber_t,	///< тип штурмовика
	bomber_t		///< тип бомбардировщика
};

/// возможные виды вооружения
enum weapons {
	light,	///< легкое оружие, только для стрельбы по самолетам
	middle,	///< среднее оружие, только для стрельбы по кораблям
	heavy	///< тяжелое оружие, для стрельбы по кораблям, увеличеная дальность
};

/// все параметры юнитов, которые могут быть модифицированы
enum modificated_parametrs {	
	// для объектво 0 - 5
	HP,				///< живучесть
	speed,			///< скорость
	range,			///< дальность хода объекта
	storage,		///< максимальный размер склада корабля
	max_weapon,		///< максимальное количество оружия
	max_aircraft,	///< максимальное количество самолетов на корабле
	// для вооружения 6 - 8
	Radius,			///< радиус действия определенного оружия
	Damage,			///< урон от одного выстрела
	Rate,			///< скорострельность
};

/// информация о юнитах, загружаемая из конфигурационных файлов
struct config {	
	/// неизменяемые параметры оружия
	struct const_param_weapon {
		int max_ammunation;		///< боезопас для оружия
		int cost;				///< стоимость оружия
	};

	const_param_weapon c_p_w[3];

	/// параметры оружия, которые могут быть изменены
	struct param_weapon {
		int radius;				///< радиус действия
		int damage;				///< наносимый урон
		int rate;				///< скорострельность
	};

	param_weapon p_w[3];

	/// неизменняемые параметры объекта, присваиваются при инциализации
	/**
	параметры объектов присваиваются кораблям
	самолетам они присваиваются с коэффицентом (через функции)
	*/
	struct const_param_object {
		int cost;		///< стоимость объекта
	};

	const_param_object c_p_o[3];

	/// параметры объекта, которые могут быть изменены
	struct param_object {
		int HP;		///< максимальное количество прочности
		int speed;	///< скорость объекта
		int range;	///< дальность хода
		int storage;///< ёмкость склада с боеприпасами
	};

	struct param_object p_o[3];

	/// параметры корабля, могут быть изменены
	struct param_ship {
		int max_weapon;		///< максимальное количество оружия
		int max_aircraft;	///< максимальное количество самолетов

	};

	struct param_ship p_s[3];
};

class weapon;
class aircraft;
class ship;

/// абстрактный класс юнита для кораблей и самолетов
class object
{
public:
	/**
	Конструктор	
	\param[in] p Характеристики (конфигурация)
	\param[in] a принадлежнсть игроку
	*/
	object(const struct config& p, const bool a) noexcept;
	~object() noexcept {};
	/// виртуальный метод атаки на самолет
	virtual void attack(aircraft& a) noexcept = 0;
	/// виртуальный метод атаки на корабль
	virtual void attack(ship& s) noexcept = 0;
	/// метод модификации характеристики
	void modificate(const modificated_parametrs& m) noexcept;
	/// метод изменения целевых координат
	void set_coord(const std::pair<int, int>& p) noexcept;
	/// метод изменения текущего положения
	void set_current_coord(const std::pair<int, int>& a) noexcept;
	/// функция расчета расстояния между обьектами
	friend int distance(const object& a, const object& b);
	/// получить суммарную стоимость обьекта
	int get_cost() const noexcept;
	/// получить текущую прочность
	int get_hp() const noexcept;
	/// увеличить стоимость
	void increase_cost(const int a) noexcept;
	/// получить текущие координаты
	std::pair<int, int> get_coord() const noexcept;
	/// метод воостановления обьекта в конце хода
	virtual void recovery() noexcept = 0;
	/// метод корректировки обьекта
	virtual bool correct() noexcept = 0;
	/// получить дальность хода
	virtual int get_range() const noexcept = 0;
	/// уменьшить действия
	bool decrease_action() noexcept;

	bool destroyed;			///< флаг, означающий уничтожение корабля
	bool activate;			///< флаг активации объекта в данный момент
	const bool affiliation;	///< принадлежность пользователю
	friend class weapon;

protected:
	/// виртуальный метод загрузки оружия по умолчанию
	virtual void download_arms(std::vector<std::vector<weapon>>& v) noexcept = 0;

	int action;								///< количесвто возможных действий
	int hp;									///< количество прочности
	std::vector<std::vector<weapon>> arms;	///< набор оружия объекта
	std::pair<int, int> currnet_coord;		///< текущие координаты
	std::pair<int, int> goal;				///< целевые координаты (куда идет объект)
	int sum_costs;							///< суммарная стоимость корабля
	std::vector<int> ammo;					///< боезапас по видам оружия
	/// параметры, определяемые при создании объекта
	struct config param;
};

/// абстрактный класс кораблей
/**
Наследуется от класса обьект
Перемещаются только по воде, не могут занять занятую кораблем клетку
*/
class ship: public object
{
public:
	/**
	Конструктор
	\param[in] p Характеристики (конфигурация)
	\param[in] a принадлежнсть игроку
	\param[in] t тип корабля
	\param[in] c коммандир корабля
	\param[in] n название корабля
	*/
	ship(const struct config& p, const bool a, const ships t,
		 std::pair<std::string, std::string>&& c, std::string&& n) noexcept;
	~ship() noexcept {};
	/// получить имя корабля
	std::string get_name() const noexcept;
	/// получить коммандира
	std::pair<std::string, std::string> get_commander() const noexcept;
	/// изменить бонус для корабля
	void set_bonus(const float f) noexcept;
	/// метод атаки на самолет
	void attack(aircraft& a) noexcept;
	/// метод атаки на корабль
	void attack(ship& s) noexcept;
	/// запускает самолет типа a на поле с корабля
	aircraft* use_air(aircrafts a) noexcept;
	/// метод воостановления обьекта в конце хода
	void recovery() noexcept;
	/// метод корректировки обьекта
	bool correct() noexcept;
	/// метод удаления самолета типа a с данного корабля
	void remove(aircrafts a);
	/// получить максимальное количесвто самолетов
	bool get_max_a() const noexcept;
	/// метод добавления самолета
	void add_aircraft(aircraft* a) noexcept;
	/// метод добавления оружия
	void add_weapon(weapon* w) noexcept;
	/// метод изменения боезапаса
	void set_ammo(const int a1, const int a2, const int a3);
	/// получить объем склада
	int get_storage() const noexcept { return param.p_o[type].storage; }
	/// получить дальность хода
	int get_range() const noexcept { return param.p_o[type].range; }
	/// получить текущее количество самолетов
	int get_a() const noexcept;
	/// получить текущее количество оружия
	int ship::get_w() const noexcept;
	/// получить максимальное количество оружия
	int get_max_w() const noexcept { return param.p_s[type].max_weapon; }

	const ships type;	///< тип корабля	

protected:
	std::vector<std::deque<aircraft>> own_aircrafts;///< все самолеты
	float bonus = 1;								///< бонус за командира или его отсутствие
	std::pair<std::string, std::string> commander;	///< звание и имя капитана судна
	std::string name;								///< имя судна
	int radius;										///< максимальный радиус атаки
};

/// виртуальный класс самолетов
/**
Наследуется от класса обьект
На игровом поле отдельный юнит, может передвинаться по любой территории
*/
class aircraft : public object
{
public:
	/**
	Конструктор
	\param[in] p Характеристики (конфигурация)
	\param[in] a принадлежнсть игроку
	\param[in] t тип самолета
	\param[in] r время, необходимое для заправки
	\param[in] s корабль, которуму принадлежит самолет
	*/
	aircraft(const struct config& p, const bool a, 
		const aircrafts t, const int r, ship* const s) noexcept;
	/// перемещающий конструктор
	aircraft(aircraft&& a) noexcept;
	/// копирующий конструктор
	aircraft(const aircraft& a) noexcept;
	~aircraft() noexcept {};
	/// метод посадки на корабль
	void return_back() noexcept;
	/// метод перехода самолета с одного корабля на другой
	void transfer(ship& s);
	/// метод атаки на самолет
	void attack(aircraft& a) noexcept;
	/// метод атаки на корабль
	void attack(ship& s) noexcept;
	/// метод воостановления обьекта в конце хода
	void recovery() noexcept;
	/// метод корректировки обьекта
	bool correct() noexcept;
	/// получить дальность вылета
	int get_range() const noexcept { return param.p_o[type].range; }
	/// перемещающее присваивание
	aircraft& operator=(aircraft&& a) noexcept;

	const aircrafts type;	///< тип самолета
	const int refueling;	///< время на заправку самолета

protected:
	/// виртуальный метод, ничего не делает
	virtual void download_arms(std::vector<std::vector<weapon>>& v) noexcept {};

	ship* affiliation_ship;	///< корабль, которому принадлежит самолет
};

/// класс авианесущего крейсера
/**
Наследуется от класса ship
Корабль типа авианесущей крейсер, обладает небольшим авиапарком,
средним и легким оружием, есть оружие по умолчанию, 
самолеты и боезапас покупаются отдельно
*/
class air_cruiser: public ship
{
public:
/**
Конструктор
\param[in] p Характеристики (конфигурация)
\param[in] a принадлежнсть игроку
\param[in] c коммандир корабля
\param[in] n название корабля
*/
	air_cruiser(const struct config& p, const bool a,
		std::pair<std::string, std::string>&& c, std::string&& n) noexcept;
	~air_cruiser() noexcept {};

private:
	/// метод загрузки оружия по умолчанию
	void download_arms(std::vector<std::vector<weapon>>& v) noexcept;
};

/// класс авианосца
/**
Наследуется от класса ship
Корабль типа авианосец, обладает большим авиапарком и легким вооружением, 
есть оружие по умолчанию, самолеты и боезапас покупаются отдельно
*/
class air_carrier : public ship
{
public:
/**
Конструктор
\param[in] p Характеристики (конфигурация)
\param[in] a принадлежнсть игроку
\param[in] c коммандир корабля
\param[in] n название корабля
*/
	air_carrier(const struct config& p, const bool a,
		std::pair<std::string, std::string>&& c, std::string&& n) noexcept;
	~air_carrier() noexcept {};

private:
	/// метод загрузки оружия по умолчанию
	void download_arms(std::vector<std::vector<weapon>>& v) noexcept;
};

/// класс крейсера
/**
Наследуется от класса ship
Корабль типа крейсер, обладает тяжелым, средним и легким вооружением
боезапас покупаеться отдельно
*/
class cruiser : public ship
{
public:
	/**
Конструктор
\param[in] p Характеристики (конфигурация)
\param[in] a принадлежнсть игроку
\param[in] c коммандир корабля
\param[in] n название корабля
*/
	cruiser(const struct config& p, const bool a,
		std::pair<std::string, std::string>&& c, std::string&& n) noexcept;
	~cruiser() noexcept {};
private:
	/// метод загрузки оружия по умолчанию
	void download_arms(std::vector<std::vector<weapon>>& v) noexcept;
};

/// класс истребителя
/**
Наследуется от класса aircraft
Класс самолетов истребитель, обладают легким вооружением
боезапас по умолчанию, перезаряжается со склада на корабле
Могут атаковать только воздушные цели
*/
class fighter: public aircraft
{
public:
	/**
Конструктор
\param[in] p Характеристики (конфигурация)
\param[in] a принадлежнсть игроку
\param[in] r время, необходимое для заправки
\param[in] s корабль, которуму принадлежит самолет
*/
	fighter(const struct config& p, const bool a,
		const int r, ship* const s) noexcept;
	~fighter() noexcept {};
};

/// класс бомбардировщика
/**
Наследуется от класса aircraft
Класс самолетов бомбардировщик, обладают легкиим и средним вооружением
боезапас по умолчанию, перезаряжается со склада на корабле
Могут атаковать только наземные цели
*/
class bomber : public aircraft
{
public:
	/**
Конструктор
\param[in] p Характеристики (конфигурация)
\param[in] a принадлежнсть игроку
\param[in] r время, необходимое для заправки
\param[in] s корабль, которуму принадлежит самолет
*/
	bomber(const struct config& p, const bool a,
		const int r, ship* const s) noexcept;
	~bomber() noexcept {};
};

/// класс штурмовика
/**
Наследуется от класса aircraft
Класс самолетов истребитель, обладают легким вооружением средним
боезапас по умолчанию, перезаряжается со склада на корабле
Могут атаковать только воздушные и наземные цели
*/
class front_bomber : public aircraft
{
public:
	/**
Конструктор
\param[in] p Характеристики (конфигурация)
\param[in] a принадлежнсть игроку
\param[in] r время, необходимое для заправки
\param[in] s корабль, которуму принадлежит самолет
*/
	front_bomber(const struct config& p, const bool a,
		const int r, ship* const s) noexcept;
	~front_bomber() noexcept {};
};

/// класс оружия
/**
Является дружеским для класса object
Класс самолетов истребитель, обладают легким вооружением
боезапас по умолчанию, перезаряжается со склада на корабле
Могут атаковать только воздушные цели
*/
/**
Конструктор
\param[in] p Характеристики (конфигурация)
\param[in] a принадлежнсть игроку
\param[in] r время, необходимое для заправки
\param[in] s корабль, которуму принадлежит самолет
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

	object* affilation_object;	///< объект, которому оружие принадлежит
	int ammunation;				///< боезапас
};