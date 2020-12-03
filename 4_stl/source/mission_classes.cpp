#include "/Users/vadim/Desktop/Я/Программирование/study/Lab4/include/mission_classes.h"

mission::mission(const struct mode_mission& m, const struct param_mission& p)
	: param(p), mode(m), arena(p.size, m.random) {
	this->lenhtg_list = this->param.list.size() - 2;
	this->p1 = player(p.list[this->lenhtg_list + 1], round(p.money / p.difficult));
	this->p2 = player(p.list[this->lenhtg_list ], round(p.money * p.difficult));
}

bool mission::buy_or_sell(player& p) {
	bool buy_ship(player & p);
	void sell_ship(player & p);
	bool buy_aircraft(player & p);
	void sell_aircraft(player & p);
	bool buy_weapons(ship & s);
	bool sell_weapons(ship & s);
	bool buy_ammunations(ship & s);
	bool sell_ammunations(ship & s);
}

bool mission::end_turn() {
	// проверка всех кораблей
	int k = ships1.size();
	for (int i = 0; i < k; i++)
	{
		// откорректировать данные
		ships1[i]->correct();

		// проверить на уничтожение
		if (ships1[i]->destroyed) {
			if(ships1[i]->get_commander() == this->p1.get_general()){
				this->general_death(p1);
			}
			this->p2.increase_damage(ships1[i]->get_cost());
			ships1.del_ship(ships1[i]->get_name());
			continue;
		}
	}
	k = ships2.size();
	for (int i = 0; i < k; i++)
	{
		ships2[i]->correct();
		if (ships2[i]->destroyed) {
			if (ships2[i]->get_commander() == this->p2.get_general()) {
				this->general_death(p2);
			}
			this->p1.increase_damage(ships2[i]->get_cost());
			ships2.del_ship(ships2[i]->get_name());
			continue;
		}
	}

	// если кораблей где-то не осталось
	if (!ships1.size() || !ships2.size()) {
		return true;
	}

	// восстановление всех кораблей
	k = ships1.size();
	for (int i = 0; i < k; i++)
	{
		// восстановить активность
		ships1[i]->recovery();
	}
	k = ships2.size();
	for (int i = 0; i < k; i++)
	{
		ships2[i]->recovery();
	}

	return false;
}

/*
метод извлечения ссылки на обьект по позывному. Если ссылки по этому ключу
не существует, добавляет nullptr с таким ключом и его возвращает
*/
std::shared_ptr<ship> table::get_ship(const std::string& s) {
	return this->array[s];
}

/*
возвращает номер корабля по его названию, либо -1, если такого нет
*/
int table::get_num(const std::string& s) const {
	for (int i = 0; i < this->conformity.size(); i++)
	{
		if (s == this->conformity[i])
		{
			return i;
		}
	}
	return -1;
}

void table::add_ship(const struct const_param_object& c_p,
	const struct param_object& p,
	const struct param_ship& p_s, const bool a, const ships t,
	std::pair<std::string, std::string>&& c, std::string&& n) {
	const std::string a = n;
	n = a;
	this->array[n] = std::make_shared<ship>(c_p, p, p_s, a, t, std::move(c), std::move(n));
	n = a;
	this->conformity.push_back(n);
}

bool table::find_ship(const std::string& s) const {
	if (this->get_num(s) == -1) return false;
	return true;
}

void table::del_ship(const ship& s) noexcept {
	this->del_ship(s.get_name());
}

void table::del_ship(const std::string& s) noexcept {
	int k = this->get_num(s);
	if (k == -1) return;
	this->conformity.erase(this->conformity.begin() + k);
	this->array.erase(s);
}

std::shared_ptr<ship> table::operator[](const std::string& s) {
	return this->get_ship(s);
}

std::shared_ptr<ship> table::operator[](const int n) {
	auto s = this->conformity[n];
	if (!this->find_ship(s))
	{
		return nullptr;
	}
	return this->get_ship(s);
}

player::player(std::pair<std::string, std::string> g, int m) {
	this->costs = 0;
	this->damage = 0;
	this->general = g;
	this->money = m;
}

void player::set_general(std::pair<std::string, std::string> g) {
	this->general = g;
}

std::pair<std::string, std::string> player::get_general() const {
	return this->general;
}

void player::increase_damage(const int a) {
	if (a>=0) this->damage += a;
	return;
}

map::map(const std::pair<int, int> s, bool random = false){
	if (random)
	{
		for (int i = 0; i < s.first; i++)
		{
			std::vector<cell> v;
			for (int j = 0; i < s.second; i++)
			{
				cell c = { i, j };
				if (mine::random(10) > 6) c.set_state(ground);
				v.push_back(c);
			}
			this->array.push_back(v);
		}
	}
	else {
		for (int i = 0; i < s.first; i++)
		{
			std::vector<cell> v;
			for (int j = 0; i < s.second; i++)
			{
				v.push_back({i, j});
			}
			this->array.push_back(v);
		}
	}
}

cell::cell(const int x, const int y) : coord({x, y}) {
	this->state = free_st;
}

void cell::set_state(const states s) {
	this->state = s;
}