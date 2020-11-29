#include "/Users/vadim/Desktop/Я/Программирование/study/Lab4/include/units_classes.h"


object::object(const struct config& p, const bool affilation) noexcept {
	this->param = p;
	this->activate = affilation;
	this->currnet_coord = { 0, 0 };
	this->goal = this->currnet_coord;
	this->ammo[light] = 0;
	this->ammo[middle] = 0;
	this->ammo[heavy] = 0;
};

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

bool ship::attack(object& a) {
	if (this->radius < distance(*this, a)) {
		return false;
	}

}



aircraft::aircraft(const struct config& p, const bool a,
				   const aircrafts t, const int r, ship* const s) 
	: object(p, a), type(t), refueling(r) {
	this->affiliation_ship = s;
	this->sum_costs = p.c_p_o[type].cost;
	this->hp = p.p_o[type].HP;
};

bool aircraft::attack(aircraft& a) {
	for (int i = 0; i < this->arms[light].size(); i++)
	{
		if activate
		this->arms[light][i].attack(a);
	}
}

air_cruiser::air_cruiser(const struct config& p, const bool a, const ships t,
	const int m, std::pair<std::string, std::string>&& c, std::string&& n)
	: ship(p, a, t, std::move(c), std::move(n)) {
	
	this->download_arms(this->arms);
	calculate_radius();
	this->max_aircraft = m;
	this->aircrafts_count[fighter] = 0;
	this->aircrafts_count[front_bomber] = 0;
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
	calculate_radius();
	this->max_aircraft = m;
	this->aircrafts_count[fighter] = 0;
	this->aircrafts_count[front_bomber] = 0;
	this->aircrafts_count[bomber] = 0;
}

void air_carrier::download_arms(std::vector<std::vector<weapon>>& v) {
	std::vector<weapon> l{ {this, light}, {this, light}, {this, light} };
	v.push_back(l);
}

cruiser::cruiser(const struct config& p, const bool a, const ships t,
	std::pair<std::string, std::string>&& c, std::string&& n)
	: ship(p, a, t, std::move(c), std::move(n)) {

	this->download_arms(this->arms);
	calculate_radius();
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
	this->activate = true;
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
	o.correct();
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
			this->activate = false;
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