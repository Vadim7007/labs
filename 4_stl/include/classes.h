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

enum modificated_parametrs {	// ���������, ������� ����� ���� ��������������
	// ��� �������� 0 - 5
	HP,				// ���������
	speed,			// ��������
	range,			// ��������� ���� �������
	storage,		// ������������ ������ ������ �������
	max_weapon,		// ������������ ���������� ������
	max_aircraft,	// ������������ ���������� ��������� �� �������
	// ��� ���������� 6 - 9
	radius,			// ������ �������� ������������� ������
	max_ammunation,	// ������������ �������� �� ������
	damage,			// ���� �� ������ ��������
	rate,			// ����������������
};

struct param_mission {
	int difficult;	// ������� ���������
	int goal;		// ���� ��� ������ (� ����� �������������)
	bool mode;		// ������� ����� ��� ��������
	int max_ship;	// ������������ ���������� �������� � ����� �����
	bool side;		// ����� ���� - ��������� ��� ������
};

struct param_weapon {
	int max_ammunation;		// �������� ��� ������
	int cost;				// ��������� ������
	const std::string name;	// �������� ������
	const weapons type;		// ��� ������
};

// ������������� ��������� �������, ������������� ��� ������������
struct const_param_object {
		int cost;		// ��������� �������
};

// ��������� �������, ������� ����� ���� ��������
struct param_object {
	int HP;		// ������������ ���������� ���������
	int speed;	// �������� �������
	int range;	// ��������� ����
};

/*
����� ������� ��� �������� ���������� �� �������, ����������� �� ��������
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
������ ������������� ������
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
����� ������
*/
class mission
{
public:
	mission();
	~mission();
	const struct param_mission param;	// ��������� ������, ���������� ����������

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
	int game_speed;		// ���� ����
	int visibility;		// ������ ��������� ��������
	map	arena;			// ������� �����
	// ������ ���� ��������� �����������
	std::vector <std::pair<std::string, std::string>> list;
	table ships1;		// ������� �������� ������������
	table ships2;		// ������� �������� ����
};

/*
����� ������ ������ (������������ � AI)
*/
class player
{
public:
	player();
	~player();
	friend class mission;
	void set_general(std::pair<std::string, std::string>);
protected:
	int money;										// ������� ���������� �����
	int costs;										// �������� ��������� �����
	int damage;										// ��������� ���� ������
	std::pair<std::string, std::string> general;	// ����������� ������
};

/*
����� ������� �����
*/
class map
{
public:
	map();
	~map();

protected:
	ptr<ptr<cell>> array;			// ������ ����� �����
	const std::pair<int, int> size;	// ������ �����
};

/*
����� ����� ������ �����
*/
class cell: public map
{
public:
	cell();
	~cell();
	void set_state(const states s);
private:
	states state;						// ��������� ������
	const std::pair<int, int> coord;	// ���������� ������
};

/*
����������� ����� ��� �������� � ���������
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

	// ��������� ���������, ������������ ��� ������������� �������
	const struct const_param_object c_param;

protected:
	void calculate_radius();

	bool activate;						// ���� ��������� ������� � ������ ������
	int hp;								// ���������� ���������
	int radius;							// ������������ ������ �����
	container<weapon> arms;				// ����� ������ �������
	std::pair<int, int> currnet_coord;	// ������� ����������
	std::pair<int, int> goal;			// ������� ���������� (���� ���� ������)
	bool affiliation;					// �������������� ������������
	int sum_costs;						// ��������� ��������� �������
	float bonus;						// ����� �� ��������� ��� ��� ����������
	// ���������, ������������ ��� �������� �������, ������� ����� ���� ��������
	struct param_object param;
};

/*
����������� ����� ��������
*/
class ship: public object
{
public:
	ship(const struct const_param_object& c_p, const struct param_object& p, const bool a, const ships t) : object(c_p, p, a), type(t) {};
	~ship();
	std::vector<std::pair<int, int>> get_way(const std::pair<int, int>);
	const ships type;								// ��� �������
protected:
	std::pair<std::string, std::string> commander;	// ������ � ��� �������� �����
	std::string name;								// ��� �����
	int ammunation;									// ������� ������ � ������������
	int max_weapon;									// ������������ ���������� ������
	std::vector<int> ammo;							// �������� �� ����� ������
};

/*
����������� ����� ���������
*/
class aircraft : public object
{
public:
	aircraft(const struct const_param_object& c_p, const struct param_object& p, const bool a, const aircrafts t, const int r) : object(c_p, p, a), type(t), refueling(r) {};
	~aircraft();
	const aircrafts type;	// ��� ��������
	const int refueling;	// ����� �� �������� ��������
	void return_back();
	void transfer(ship& s);
protected:
	ship* affiliation_ship;	// �������, �������� ����������� �������
};

/*
����� ������������ ��������
*/
class air_cruiser: public ship
{
public:
	air_cruiser();
	~air_cruiser();

private:
	int max_aircraft;					// ������������ ���������� ���������
	container<aircraft> aircrafts;		// ��� ��������
	std::vector<int> aircrafts_count;	// ���������� ��������� �� �����
};

/*
����� ���������
*/
class air_carrier : public ship
{
public:
	air_carrier();
	~air_carrier();

private:
	int max_aircraft;					// ������������ ���������� ���������
	container<aircraft> aircrafts;		// ��� ��������
	std::vector<int> aircrafts_count;	// ���������� ��������� �� �����
};

/*
����� ��������
*/
class cruiser : public ship
{
public:
	cruiser();
	~cruiser();

private:

};

/*
����� �����������
*/
class fighter: public aircraft
{
public:
	fighter();
	~fighter();

private:

};

/*
����� ���������������
*/
class bomber : public aircraft
{
public:
	bomber();
	~bomber();

private:

};

/*
����� ����������
*/
class front_bomber : public aircraft
{
public:
	front_bomber();
	~front_bomber();

private:

};

/*
����� ������ ��������
*/
class weapon
{
public:
	weapon(const struct param_weapon p);
	~weapon();
	const struct param_weapon param;	// ���������, ����������� ����������
private:
	int radius;				// ������ ��������
	int ammination;			// ��������
	bool activate;			// ���� ���������
	int damage;				// ��������� ����
	int rate;				// ����������������
};