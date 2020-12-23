#include "/Users/vadim/Desktop/Me/Programming/study/Lab4/include/units_classes.h"
#include "/Users/vadim/Desktop/Me/Programming/study/Lab4/include/container.h"

object::object(const struct config& p, const bool a) noexcept : affiliation(a) {
	this->param = p;
	this->activate = true;
	this->currnet_coord = { 0, 0 };
	this->goal = this->currnet_coord;
	this->ammo.resize(3);
	this->ammo[light] = 0;
	this->ammo[middle] = 0;
	this->ammo[heavy] = 0;
	this->action = 3;
	this->destroyed = false;
};

void object::modificate(const modificated_parametrs& m) noexcept{
	if (m <= 5) {
		switch (m)
		{
		case 0:
			this->param.p_o[0].HP = round(this->param.p_o[0].HP * 1.1);
			this->param.p_o[1].HP = round(this->param.p_o[1].HP * 1.1);
			this->param.p_o[2].HP = round(this->param.p_o[2].HP * 1.1);
			break;
		case 1:
			this->param.p_o[0].speed = round(this->param.p_o[0].speed * 1.1);
			this->param.p_o[1].speed = round(this->param.p_o[1].speed * 1.1);
			this->param.p_o[2].speed = round(this->param.p_o[2].speed * 1.1);
			break;
		case 2:
			this->param.p_o[0].range = round(this->param.p_o[0].range * 1.1);
			this->param.p_o[1].range = round(this->param.p_o[1].range * 1.1);
			this->param.p_o[2].range = round(this->param.p_o[2].range * 1.1);
			break;
		case 3:
			this->param.p_o[0].storage = round(this->param.p_o[0].storage * 1.1);
			this->param.p_o[1].storage = round(this->param.p_o[1].storage * 1.1);
			this->param.p_o[2].storage = round(this->param.p_o[2].storage * 1.1);
			break;
		case 4:
			this->param.p_s[0].max_weapon = round(this->param.p_s[0].max_weapon * 1.1);
			this->param.p_s[1].max_weapon = round(this->param.p_s[1].max_weapon * 1.1);
			this->param.p_s[2].max_weapon = round(this->param.p_s[2].max_weapon * 1.1);
			break;
		case 5:
			this->param.p_s[0].max_aircraft = round(this->param.p_s[0].max_aircraft * 1.1);
			this->param.p_s[1].max_aircraft = round(this->param.p_s[1].max_aircraft * 1.1);
			this->param.p_s[2].max_aircraft = round(this->param.p_s[2].max_aircraft * 1.1);
			break;
		default:
			break;
		}
	}
	else if (m <= 8) {
		for (int i = 0; i < this->arms.size(); i++)
		{
			for (int j = 0; j < this->arms[i].size(); j++)
			{
				this->arms[i][j].modificate(m);
			}
		}
	}
}

void object::set_coord(const std::pair<int, int>& a) noexcept {
	this->goal = a;
}

void object::set_current_coord(const std::pair<int, int>& a) noexcept {
	this->currnet_coord = a;
}

int object::get_cost() const noexcept {
	return this->sum_costs;
}

void object::increase_cost(const int a) noexcept {
	if (a > 0) { this->sum_costs += a; }
}

std::pair<int, int> object::get_coord() const noexcept {
	return this->currnet_coord;
}

bool object::decrease_action() noexcept {
	if (0 == this->action)
	{
		return false;
	}
	(this->action)--;
	return true;
}

int object::get_hp() const noexcept {
	return hp;
}

// может вызвать исключение
void ship::set_ammo(const int a1, const int a2, const int a3) {
	if ((a1 + a2 + a3) > this->param.p_o[this->type].storage) {
		throw std::exception("incorrect arguments");
	}
	
	this->ammo[0] = a1;
	this->ammo[1] = a2;
	this->ammo[2] = a3;
}

bool ship::correct() noexcept {
	// для корабля
	if (this->hp <= 0) {
		this->hp = 0;
		this->activate = false;
		this->destroyed = true;
		return false;
	}

	// для его самолетов
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < this->own_aircrafts[i].size(); j++)
		{
			bool be = this->own_aircrafts[i][j].correct();
			if (!be) {
				this->own_aircrafts[i].erase(this->own_aircrafts[i].begin() + j);
			}
		}
	}
	return true;
}

void ship::recovery() noexcept {
	// для корабля
	this->action = 3;
	this->hp += this->param.p_o[this->type].HP / 20;

	// для его самолетов
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < this->own_aircrafts[i].size(); j++)
		{
			this->own_aircrafts[i][j].recovery();
		}
	}
}

void ship::set_bonus(const float f) noexcept {
	this->bonus = f;
	this->param.p_o[this->type].HP *= f;
	this->param.p_o[this->type].range *= f;
	this->param.p_o[this->type].speed *= f;
	this->param.p_w[this->type].damage *= f;
	this->param.p_w[this->type].rate *= f;
	this->param.p_w[this->type].radius *= f;
}

int distance(const object& a, const object& b) {
	int x = a.currnet_coord.first - b.currnet_coord.first;
	int y = a.currnet_coord.second - b.currnet_coord.second;
	return round(sqrt(x * x + y * y));
}

ship::ship(const struct config& p, const bool a, const ships t,
			std::pair<std::string, std::string>&& c, std::string&& n) noexcept
	: object(p, a), type(t) {
	this->commander = c;
	this->name = n;
	this->sum_costs = p.c_p_o[type].cost;
	this->hp = p.p_o[type].HP;
	this->own_aircrafts.resize(3);
};

std::string ship::get_name() const noexcept {
	return this->name;
};

std::pair<std::string, std::string> ship::get_commander() const noexcept {
	return this->commander;
};

void ship::attack(ship& s) noexcept {
	if (this->activate && this->action >= 2 && 
		this->affiliation != s.affiliation) {

		bool flag = false;
		for (int i = 1; i < this->arms.size(); i++)
		{
			if (distance(*this, s) <= this->param.p_w[i].radius) {
				for (int j = 0; j < this->arms[i].size(); j++)
				{
					this->arms[i][j].attack(s);
					flag = true;
				}
			}
		}
		if (flag) {
			this->action -= 2;
			s.correct();
		}
	}
	return;
}

void ship::attack(aircraft& a) noexcept {
	if (this->activate && this->action >= 2 &&
		this->affiliation != a.affiliation) {

		bool flag = false;
		if (distance(*this, a) <= this->param.p_w[light].radius) {
			for (int j = 0; j < this->arms[light].size(); j++)
			{
				this->arms[light][j].attack(a);
				flag = true;
			}
		}
		if (flag) {
			this->action -= 1;
			a.correct();
		}
	}
	return;
}

// в случае ошибки возвращает nullptr
aircraft* ship::use_air(aircrafts a)noexcept {
	if (!this->own_aircrafts[a].empty()) {
		aircraft* i = new aircraft(this->own_aircrafts[a][0]);
		this->own_aircrafts[a].pop_front();
		this->decrease_action();
		i->decrease_action();
		return i;
	}
return nullptr;
}

// убирает из списка самолетов этого корабля самолет с указателем "a"
void ship::remove(aircrafts a) {
	int size = this->own_aircrafts[a].size();
	if (0 == size) {
		throw std::exception("Such element is upsent");
	}
	auto i = this->own_aircrafts[a].end();
	i--;
	try {
		this->own_aircrafts[a].erase(i);
	}
	catch (std::exception& e) {
		throw std::exception("Such element is upsent");
	};
}

// возвращает true, если есть свободое место для корабля
bool ship::get_max_a() const noexcept {
	int a = this->param.p_s[this->type].max_aircraft;
	int b = 0;
	for (int i = 0; i < this->own_aircrafts.size(); i++)
	{
		for (int j = 0; j < this->own_aircrafts[i].size(); j++)
		{
			b++;
		}
	}
	return a > b;
}

void ship::add_aircraft(aircraft* a) noexcept {
	int size = 0;
	for (int i = 0; i < this->own_aircrafts.size(); i++)
	{
		size += this->own_aircrafts[i].size();
	}
	if (this->param.p_s[this->type].max_aircraft > size) {
		this->own_aircrafts[a->type].push_back(*a);
		a->set_coord(this->get_coord());
	}
}

void ship::add_weapon(weapon* w) noexcept {
	int size = 0;
	for (int i = 0; i < this->arms.size(); i++)
	{
		size += this->arms[i].size();
	}
	if (this->param.p_s[this->type].max_weapon > size) {
		this->arms[w->type].push_back(*w);
	}
}

aircraft::aircraft(const struct config& p, const bool a,
				   const aircrafts t, const int r, ship* const s) noexcept
	: object(p, a), type(t), refueling(r) {
	this->affiliation_ship = s;
	this->sum_costs = round( 10 * sqrt(p.c_p_o[type].cost));
	this->param.p_o[type].HP = round(7 * sqrt(this->param.p_o[type].HP));
	this->param.p_o[type].range = 3*this->param.p_o[0].range;
	this->param.p_o[type].speed = 3*this->param.p_o[type].speed;
	this->param.p_o[type].storage = 0;

	this->hp = this->param.p_o[type].HP;
};

aircraft::aircraft(aircraft&& a) noexcept : object(a.param, a.affiliation), 
	type(a.type), refueling(a.refueling) {
	this->action = a.action;
	this->activate = a.activate;
	this->affiliation_ship = a.affiliation_ship;
	this->ammo = a.ammo;
	this->arms = a.arms;
	this->currnet_coord = a.currnet_coord;
	this->destroyed = a.destroyed;
	this->goal = a.goal;
	this->hp = a.hp;
	this->param = a.param;
	this->sum_costs = a.sum_costs;
}

aircraft::aircraft(const aircraft& a) noexcept : object(a.param, a.affiliation),
type(a.type), refueling(a.refueling) {
	this->action = a.action;
	this->activate = a.activate;
	this->affiliation_ship = a.affiliation_ship;
	this->ammo = a.ammo;
	this->arms = a.arms;
	this->currnet_coord = a.currnet_coord;
	this->destroyed = a.destroyed;
	this->goal = a.goal;
	this->hp = a.hp;
	this->param = a.param;
	this->sum_costs = a.sum_costs;
}

bool aircraft::correct() noexcept {
	if (this->hp <= 0) {
		this->hp = 0;
		this->activate = false;
		this->destroyed = true;
		return false;
	}
}

void aircraft::recovery() noexcept {
	this->action = 3;
	this->hp += this->param.p_o[this->type].HP / 20;
}

void aircraft::attack(aircraft& a) noexcept {
	if (this->activate && this->action >= 2 &&
		this->affiliation != a.affiliation) {

		int i;
		if (distance(*this, a) <= this->param.p_w[light].radius) {
			for (i = 0; i < this->arms[light].size(); i++)
			{
				this->arms[light][i].attack(a);
			}
			if (!i) {
				return;
			}
			this->action -= 2;
			a.correct();
		}
	}
	return;
}

void aircraft::attack(ship& s) noexcept {
	if (this->activate && this->action >= 2 &&
		this->affiliation != s.affiliation) {

		int i;
		if (distance(*this, s) <= this->param.p_w[middle].radius
			&& this->arms.size() > 1) {
			for (i = 0; i < this->arms[middle].size(); i++)
			{
				this->arms[middle][i].attack(s);
			}
			if (!i) {
				return;
			}
			s.correct();
			this->action -= 2;
		}
	}
	return;
}

void aircraft::transfer(ship& s) {
	/*if (s.get_max_a())
	{
		this->affiliation_ship->remove(this->type);
		s.add_aircraft(this);
		this->affiliation_ship = &s;
	}*/
}

void aircraft::return_back() noexcept {
	auto s = this->affiliation_ship;
	this->goal = s->get_coord();

	if (distance(*this, *s) < 2) {
		s->add_aircraft(this);
		this->decrease_action();
	}
}

aircraft& aircraft::operator=(aircraft&& a) noexcept {
	this->action = a.action;
	this->activate = a.activate;
	this->affiliation_ship = a.affiliation_ship;
	this->ammo = a.ammo;
	this->arms = a.arms;
	this->currnet_coord = a.currnet_coord;
	this->destroyed = a.destroyed;
	this->goal = a.goal;
	this->hp = a.hp;
	this->param = a.param;
	this->sum_costs = a.sum_costs;
	return *this;
}

air_cruiser::air_cruiser(const struct config& p, const bool a,
	std::pair<std::string, std::string>&& c, std::string&& n) noexcept
	: ship(p, a, aircraft_carrier_cruiser, std::move(c), std::move(n)) {
	
	this->download_arms(this->arms);
}

void air_cruiser::download_arms(std::vector<std::vector<weapon>>& v) noexcept {
	std::vector<weapon> l{ {this, light}, {this, light} };
	v.push_back(l);
	std::vector<weapon> m{ {this, middle}, {this, middle} };
	v.push_back(m);
}

air_carrier::air_carrier(const struct config& p, const bool a,
	std::pair<std::string, std::string>&& c, std::string&& n) noexcept
	: ship(p, a, aircraft_carrier, std::move(c), std::move(n)) {
	
	this->download_arms(this->arms);
}

void air_carrier::download_arms(std::vector<std::vector<weapon>>& v) noexcept {
	std::vector<weapon> l{ {this, light}, {this, light}, {this, light} };
	v.push_back(l);
}

cruiser::cruiser(const struct config& p, const bool a,
	std::pair<std::string, std::string>&& c, std::string&& n) noexcept
	: ship(p, a, cruiser_t, std::move(c), std::move(n)) {

	this->download_arms(this->arms);
}

void cruiser::download_arms(std::vector<std::vector<weapon>>& v) noexcept {
	std::vector<weapon> l{ {this, light}, {this, light} };
	v.push_back(l);
	std::vector<weapon> m{ {this, middle} };
	v.push_back(m);
	std::vector<weapon> h{ {this, heavy} };
	v.push_back(h);
}

fighter::fighter(const struct config& p, const bool a,
	const int r, ship* const s) noexcept
	: aircraft(p, a, fighter_t, r, s) {
	auto l = new std::vector<weapon>{ {this, light}, {this, light} };
	this->arms.push_back(*l);
}

front_bomber::front_bomber(const struct config& p, const bool a,
	const int r, ship* const s) noexcept
	: aircraft(p, a, front_bomber_t, r, s) {
	auto l = new std::vector<weapon>{ {this, light}};
	auto m = new std::vector<weapon>{ {this, middle}};
	this->arms.push_back(*l);
	this->arms.push_back(*m);
}

bomber::bomber(const struct config& p, const bool a,
	const int r, ship* const s) noexcept
	: aircraft(p, a, bomber_t, r, s) {
	auto m = new std::vector<weapon>{ {this, middle}, {this, middle} };
	this->arms.push_back(*m);
}

weapon::weapon(object* const o, const weapons t) noexcept : type(t) {
	this->affilation_object = o;
	this->ammunation = 
		this->affilation_object->param.c_p_w[this->type].max_ammunation;
	return;
}

weapon& weapon::operator=(const weapon& w) noexcept {
	this->affilation_object = w.affilation_object;
	this->ammunation = w.ammunation;
	return *this;
}

void weapon::attack(object& o) noexcept {

	// количество возможных зарядов для атаки
	int k = this->decrease_ammunation();
	// суммарный урон
	int d = k * (this->affilation_object->param.p_w[this->type].damage);
	// урон по обьекту
	o.hp -= d;
	return;
}

// возвращает, насколько уменьшился боезапас
int weapon::decrease_ammunation() noexcept {

	int rate = this->affilation_object->param.p_w[this->type].rate;
	if (rate >= this->ammunation)
	{
		if (this->recharge()) {
			this->ammunation -= rate;
			return rate;
		}
		else {
			int k = this->ammunation;
			this->ammunation = 0;
			return k;
		}
	}
	this->ammunation -= rate;
	return rate;
}

// возвращает, удалось ли полностью перезарядить оружие
bool weapon::recharge() noexcept {

	int nessesary = 
		this->affilation_object->param.c_p_w[this->type].max_ammunation -
		this->ammunation;

	if (this->affilation_object->ammo[type] < nessesary)
	{
		this->ammunation += this->affilation_object->ammo[type];
		this->affilation_object->ammo[type] = 0;
		return false;
	}
	else {
		this->affilation_object->ammo[type] -= nessesary;
		this->ammunation += nessesary;
		return true;
	}
}

void weapon::modificate(const modificated_parametrs a) noexcept {
	switch (a)
	{
	case Radius:
		this->affilation_object->param.p_w[this->type].radius *= 1.1;
		break;
	case Damage:
		this->affilation_object->param.p_w[this->type].damage *= 1.1;
		break;
	case Rate:
		this->affilation_object->param.p_w[this->type].rate *= 1.1;
		break;
	}
	return;
}