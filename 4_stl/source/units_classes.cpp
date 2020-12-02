﻿#include "/Users/vadim/Desktop/Я/Программирование/study/Lab4/include/units_classes.h"


object::object(const struct config& p, const bool a) noexcept : affiliation(a) {
	this->param = p;
	this->activate = true;
	this->currnet_coord = { 0, 0 };
	this->goal = this->currnet_coord;
	this->ammo[light] = 0;
	this->ammo[middle] = 0;
	this->ammo[heavy] = 0;
	this->action = 3;
	this->destroyed = false;
};

void object::correct() {
	if (this->hp <= 0) {
		this->hp = 0;
		this->activate = false;
		this->destroyed = true;
	}
}

void object::modificate(const modificated_parametrs m){
	if (m <= 5) {
		switch (m)
		{
		case 0:
			this->param.p_o->HP = round(this->param.p_o->HP * 1.1);
			break;
		case 1:
			this->param.p_o->speed = round(this->param.p_o->speed * 1.1);
			break;
		case 2:
			this->param.p_o->range = round(this->param.p_o->range * 1.1);
			break;
		case 3:
			this->param.p_o->storage = round(this->param.p_o->storage * 1.1);
			break;
		case 4:
			this->param.p_s->max_weapon = round(this->param.p_s->max_weapon * 1.1);
			break;
		case 5:
			this->param.p_s->max_aircraft = round(this->param.p_s->max_aircraft * 1.1);
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

void object::set_coord(const std::pair<int, int> a) {
	this->goal = a;
}

int object::get_cost() const{
	return this->sum_costs;
}

void object::increase_cost(int a){
	if (a > 0) { this->sum_costs += a; }
}

void ship::set_bonus(const float f) {
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
};

std::string ship::get_name() const {
	return this->name;
};

std::pair<std::string, std::string> ship::get_commander() const {
	return this->commander;
};

void ship::attack(ship& s) {
	if (this->activate && this->action >= 2 && 
		this->affiliation != s.affiliation) {

		bool flag = false;
		for (int i = 1; i < 3; i++)
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

void ship::attack(aircraft& a) {
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
aircraft* ship::use_air(aircrafts a) {
	if (this->own_aircrafts.size() <= a) {
		if (!this->own_aircrafts[a].empty()) {
			auto i = std::move(this->own_aircrafts[a][0]);
			this->own_aircrafts[a].pop_front();
			return &i;
		}
	}	
	return nullptr;
}

aircraft::aircraft(const struct config& p, const bool a,
				   const aircrafts t, const int r, ship* const s) 
	: object(p, a), type(t), refueling(r) {
	this->affiliation_ship = s;
	this->sum_costs = p.c_p_o[type].cost;
	this->hp = p.p_o[type].HP;
};

void aircraft::attack(aircraft& a) {
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

void aircraft::attack(ship& s) {
	if (this->activate && this->action >= 2 &&
		this->affiliation != s.affiliation) {

		int i;
		if (distance(*this, s) <= this->param.p_w[middle].radius) {
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

air_cruiser::air_cruiser(const struct config& p, const bool a, const ships t,
	const int m, std::pair<std::string, std::string>&& c, std::string&& n)
	: ship(p, a, t, std::move(c), std::move(n)) {
	
	this->download_arms(this->arms);
}

void air_cruiser::download_arms(std::vector<std::vector<weapon>>& v) {
	std::vector<weapon> l{ {this, light}, {this, light} };
	v.push_back(l);
	std::vector<weapon> m{ {this, middle}, {this, middle} };
	v.push_back(m);
}

air_carrier::air_carrier(const struct config& p, const bool a, const ships t,
	const int m, std::pair<std::string, std::string>&& c, std::string&& n)
	: ship(p, a, t, std::move(c), std::move(n)) {
	
	this->download_arms(this->arms);
}

void air_carrier::download_arms(std::vector<std::vector<weapon>>& v) {
	std::vector<weapon> l{ {this, light}, {this, light}, {this, light} };
	v.push_back(l);
}

cruiser::cruiser(const struct config& p, const bool a, const ships t,
	std::pair<std::string, std::string>&& c, std::string&& n)
	: ship(p, a, t, std::move(c), std::move(n)) {

	this->download_arms(this->arms);
}

void cruiser::download_arms(std::vector<std::vector<weapon>>& v) {
	std::vector<weapon> l{ {this, light}, {this, light} };
	v.push_back(l);
	std::vector<weapon> m{ {this, middle} };
	v.push_back(m);
	std::vector<weapon> h{ {this, heavy} };
	v.push_back(h);
}

fighter::fighter(const struct config& p, const bool a,
	const aircrafts t, const int r, ship* const s)
	: aircraft(p, a, t, r, s) {

}

front_bomber::front_bomber(const struct config& p, const bool a,
	const aircrafts t, const int r, ship* const s)
	: aircraft(p, a, t, r, s) {

}

bomber::bomber(const struct config& p, const bool a,
	const aircrafts t, const int r, ship* const s)
	: aircraft(p, a, t, r, s) {

}

weapon::weapon(object* const o, const weapons t) : type(t) {
	this->affilation_object = o;
	this->ammunation = 
		this->affilation_object->param.c_p_w[this->type].max_ammunation;
	return;
}

void weapon::attack(object& o) {

	// количество возможных зарядов для атаки
	int k = this->decrease_ammunation();
	// суммарный урон
	int d = k * (this->affilation_object->param.p_w[this->type].damage);
	// урон по обьекту
	o.hp -= d;
	return;
}

// возвращает, насколько уменьшился боезапас
int weapon::decrease_ammunation() {

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
bool weapon::recharge() {

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

void weapon::modificate(const modificated_parametrs a) {
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