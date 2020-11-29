#include "/Users/vadim/Desktop/Я/Программирование/study/Lab4/include/units_classes.h"


object::object(const struct config& p, const bool affilation) noexcept {
	this->param = p;
	this->activate = affilation;
	this->bonus = 1;
	this->currnet_coord = { 0, 0 };
	this->goal = this->currnet_coord;
	this->hp = this->param.p_o.HP;
	this->sum_costs = this->param.c_p_o.cost;
};

ship::ship(const struct config& p, const bool a, const ships t,
			std::pair<std::string, std::string>&& c, std::string&& n) noexcept
	: object(p, a), type(t) {
	this->commander = c;
	this->name = n;
	this->ammo[light] = 0;
	this->ammo[middle] = 0;
	this->ammo[heavy] = 0;
};

aircraft::aircraft(const struct config& p, const bool a,
				   const aircrafts t, const int r, ship* const s) 
	: object(p, a), type(t), refueling(r) {
	this->affiliation_ship = s;
};

air_cruiser::air_cruiser(const struct config& p, const bool a, const ships t,
	const int m, std::pair<std::string, std::string>&& c, std::string&& n)
	: ship(p, a, t, std::move(c), std::move(n)) {
	
	download_arms(this->arms);
	calculate_radius();
	this->max_aircraft = m;
	this->aircrafts_count[fighter] = 0;
	this->aircrafts_count[front_bomber] = 0;
}

void air_cruiser::download_arms(std::vector<std::vector<weapon>>& v) {
	v[light];
	v[middle];
}

air_carrier::air_carrier(const struct config& p, const bool a, const ships t,
	const int m, std::pair<std::string, std::string>&& c, std::string&& n)
	: ship(p, a, t, std::move(c), std::move(n)) {
	
	download_arms(this->arms);
	calculate_radius();
	this->max_aircraft = m;
	this->aircrafts_count[fighter] = 0;
	this->aircrafts_count[front_bomber] = 0;
	this->aircrafts_count[bomber] = 0;
}

cruiser::cruiser(const struct config& p, const bool a, const ships t,
				 std::pair<std::string, std::string>&& c, std::string&& n)
	: ship(p, a, t, std::move(c), std::move(n)) {
	
	download_arms(this->arms);
	calculate_radius();
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

weapon::weapon(object* const o, const weapons type) {

	this->o = o;
	this->ammunation = this->o->param.c_p_w.max_ammunation;
	this->activate = true;
}

void weapon::attack(object& o) {
	// количество возможных зарядов для атаки
	int k = this->decrease_ammunation();
	// суммарный урон
	int d = k * this->o->param.p_w.damage;

	// урон по обьекту
	o.hp -= d;
	o.correct();
}

// возвращает, насколько уменьшилс боезапас
int weapon::decrease_ammunation() {
	int rate = this->o->param.p_w.rate;
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
	int nessesary = this->o->param.c_p_w.max_ammunation - this->ammunation;
	if (this->o->param.p_o.storage < nessesary)
	{
		this->ammunation += this->o->param.p_o.storage;
		this->o->param.p_o.storage = 0;
		return false;
	}
	else {
		this->o->param.p_o.storage -= nessesary;
		this->ammunation += nessesary;
		return true;
	}
}

void weapon::modificate(const modificated_parametrs a) {
	switch (a)
	{
	case Radius:
		this->o->param.p_w.radius *= 1.1;
		break;
	case Damage:
		this->o->param.p_w.damage *= 1.1;
		break;
	case Rate:
		this->o->param.p_w.rate *= 1.1;
		break;
	}
	return;
}