#include "/Users/vadim/Desktop/Я/Программирование/study/Lab4/include/units_classes.h"


object::object(const struct const_param_object& c_p, 
			   const struct param_object& p, const bool affilation) noexcept
	: c_param(c_p) {
	this->param = p;
	this->activate = affilation;
	this->bonus = 1;
	this->currnet_coord = { 0, 0 };
	this->goal = this->currnet_coord;
	this->hp = this->param.HP;
	this->sum_costs = this->c_param.cost;
};

ship::ship (const struct const_param_object& c_p,
			const struct param_object& p,
			const struct param_ship& p_s, const bool a, const ships t,
			std::pair<std::string, std::string>&& c, std::string&& n) noexcept
	: object(c_p, p, a), type(t) {
	this->commander = c;
	this->name = n;
	this->p_s = p_s;
	this->ammo[light] = 0;
	this->ammo[middle] = 0;
	this->ammo[heavy] = 0;
};

aircraft::aircraft(const struct const_param_object& c_p, 
				   const struct param_object& p, const bool a,	
				   const aircrafts t, const int r, ship* const s) 
	: object(c_p, p, a), type(t), refueling(r) {
	this->affiliation_ship = s;
};

air_cruiser::air_cruiser(const struct const_param_object& c_p,
						 const struct param_object& p,
						 const struct param_ship& p_s, const bool a, 
						 const ships t, std::pair<std::string, std::string>&& c,
						 std::string&& n, const int m)
	: ship(c_p, p, p_s, a, t,	std::move(c), std::move(n)) {
	download_arms(this->arms);
	calculate_radius();
	this->max_aircraft = m;
	this->aircrafts_count[fighter] = 0;
	this->aircrafts_count[front_bomber] = 0;
}

void air_cruiser::download_arms(std::vector<std::vector<weapon>>& v) {
	v[light]
	v[middle]
}

air_carrier::air_carrier(const struct const_param_object& c_p,
						 const struct param_object& p,
						 const struct param_ship& p_s, const bool a, 
						 const ships t,	std::pair<std::string, std::string>&& c,
						 std::string&& n, const int m)
	: ship(c_p, p, p_s, a, t, std::move(c), std::move(n)) {
	download_arms(this->arms);
	calculate_radius();
	this->max_aircraft = m;
	this->aircrafts_count[fighter] = 0;
	this->aircrafts_count[front_bomber] = 0;
	this->aircrafts_count[bomber] = 0;
}

cruiser::cruiser(const struct const_param_object& c_p,
				 const struct param_object& p,
				 const struct param_ship& p_s, const bool a, const ships t,
				 std::pair<std::string, std::string>&& c, std::string&& n)
	: ship(c_p, p, p_s, a, t, std::move(c), std::move(n)) {
	download_arms(this->arms);
	calculate_radius();
}

fighter::fighter(const struct const_param_object& c_p,
				 const struct param_object& p, const bool a,
				 const aircrafts t, const int r, ship* const s)
	: aircraft(c_p, p, a, t, r, s) {

}

front_bomber::front_bomber(const struct const_param_object& c_p,
						   const struct param_object& p, const bool a,
						   const aircrafts t, const int r, ship* const s)
	: aircraft(c_p, p, a, t, r, s) {

}

bomber::bomber(const struct const_param_object& c_p,
			   const struct param_object& p, const bool a,
			   const aircrafts t, const int r, ship* const s)
	: aircraft(c_p, p, a, t, r, s) {

}

weapon::weapon(const struct param_weapon& p, const int r, 
	const int d, const int rate, object* const o) 
	: param(p) {

	this->o = o;
	this->radius = r;
	this->ammunation = this->param.max_ammunation;
	this->activate = true;
	this->damage = d;
	this->rate = rate;
}

void weapon::attack(object& o) {
	// количество возможных зарядов для атаки
	int k = this->decrease_ammunation();
	// суммарный урон
	int d = k * this->damage;

	// урон по обьекту
	o.hp -= d;
	o.correct();
}

// возвращает, насколько уменьшилс боезапас
int weapon::decrease_ammunation() {
	if (this->rate >= this->ammunation)
	{
		if (this->recharge()) {
			this->ammunation -= this->rate;
			return this->rate;
		}
		else {
			int k = this->ammunation;
			this->ammunation = 0;
			this->activate = false;
			return k;
		}
	}
	this->ammunation -= this->rate;
	return this->rate;
}

// возвращает, удалось ли полностью перезарядить оружие
bool weapon::recharge() {
	int nessesary = this->param.max_ammunation - this->ammunation;
	if (this->o->param.storage < nessesary)
	{
		this->ammunation += this->o->param.storage;
		this->o->param.storage = 0;
		return false;
	}
	else {
		this->o->param.storage -= nessesary;
		this->ammunation += nessesary;
		return true;
	}
}

void weapon::modificate(const modificated_parametrs a) {
	switch (a)
	{
	case Radius:
		this->radius *= 1.1;
		break;
	case Damage:
		this->damage *= 1.1;
		break;
	case Rate:
		this->rate *= 1.1;
		break;
	}
	return;
}