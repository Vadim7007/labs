#include "/Users/vadim/Desktop/Я/Программирование/study/Lab4/include/classes.h"
//#include "classes.h"

object::object(const struct const_param_object& c_p, 
			   const struct param_object& p, const bool affilation) noexcept
	: c_param(c_p) {
	this->param = p;
	this->activate = affilation;
	this->arms;		// ДОДЕЛАТЬ
	this->bonus = 1;
	this->currnet_coord = { 0, 0 };
	this->goal = this->currnet_coord;
	this->hp = this->param.HP;
	this->radius = 0;
	this->sum_costs = this->c_param.cost;
	calculate_radius();
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

aircraft::aircraft( const struct const_param_object& c_p, 
					const struct param_object& p, const bool a,	
					const aircrafts t, const int r, ship* const s) 
	: object(c_p, p, a), type(t), refueling(r) {
	this->affiliation_ship = s;
};

air_cruiser::air_cruiser(const struct const_param_object& c_p,
	const struct param_object& p,
	const struct param_ship& p_s, const bool a, const ships t,
	std::pair<std::string, std::string>&& c, std::string&& n, const int m)
	: ship(c_p, p, p_s, a, t,	std::move(c), std::move(n)) {
	
	this->max_aircraft = m;
	this->aircrafts_count[fighter] = 0;
	this->aircrafts_count[front_bomber] = 0;
}

air_carrier::air_carrier(const struct const_param_object& c_p,
	const struct param_object& p,
	const struct param_ship& p_s, const bool a, const ships t,
	std::pair<std::string, std::string>&& c, std::string&& n, const int m)
	: ship(c_p, p, p_s, a, t, std::move(c), std::move(n)) {

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

void deleye_this() {
	const struct const_param_object c_p;
	const struct param_object p;
	const struct param_ship p_s;
	const bool a = true;
	const ships t;
	std::pair<std::string, std::string> c;
	std::string n;

	auto s = ship(c_p, p, p_s, a, t, std::move(c), std::move(n));
}