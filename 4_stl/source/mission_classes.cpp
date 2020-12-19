#include "/Users/vadim/Desktop/Me/Programming/study/Lab4/include/mission_classes.h"

mission::mission(const struct mode_mission& m, 
	const struct param_mission& p, const struct config& c)
	: param(p), mode(m), conf(c), arena(p.size, m.random) {
	this->lenhtg_list = this->param.list.size();
	this->p1 = player(p.list[this->lenhtg_list + 1], round(p.money / p.difficult), true);
	this->p2 = player(p.list[this->lenhtg_list ], round(p.money * p.difficult), false);
}

std::pair<std::string, std::string>& mission::get_commander() {
	this->lenhtg_list--;
	std::pair<std::string, std::string> s = std::move(param.list[this->lenhtg_list]);
	return s;
}

bool mission::buy_ship(player& pl, ships t){
	if (pl.set_money(this->conf.c_p_o[t].cost))
	{
		std::string name = "Ship" + this->lenhtg_list;
		if (pl.affilation)
		{
			this->ships1.add_ship(conf, true, t,
				std::move(this->get_commander()), std::move(name));
		}
		else {
			this->ships2.add_ship(conf, false, t,
				std::move(this->get_commander()), std::move(name));
		}
		return true;
	}
	else return false;
}

void mission::sell_ship(player& pl, const int index){
	if (pl.affilation)
	{
		auto s = this->ships1.GetById(index);
		pl.set_money(-s->get_cost());
		this->ships1.del_ship(*s);		
	}
	else {
		auto s = this->ships2.GetById(index);
		pl.set_money(-s->get_cost());
		this->ships2.del_ship(*s);
	}
}
	
bool mission::buy_aircraft(player& p, aircrafts t, const int index) {
	if (p.affilation)
	{
		auto s = this->ships1.GetById(index);
		aircraft a(conf, p.affilation, t, 2, &(*s));
		int mon = a.get_cost();
		if (p.set_money(mon))
		{
			s->add_aircraft(&a);
			s->increase_cost(mon);
			return true;
		}
	}
	else {
		auto s = this->ships2.GetById(index);
		aircraft a(conf, p.affilation, t, 2, &(*s));
		int mon = a.get_cost();
		if (p.set_money(mon))
		{
			s->add_aircraft(&a);
			s->increase_cost(mon);
			return true;
		}
	}
	return false;
}

bool mission::buy_weapons(player& p, weapons t, const int index){
	if (p.affilation)
	{
		auto s = this->ships1.GetById(index);
		weapon w(&*s, t);
		int mon = conf.c_p_w[t].cost;
		if (p.set_money(mon))
		{
			s->add_weapon(&w);
			s->increase_cost(mon);
			return true;
		}
	}
	else {
		auto s = this->ships2.GetById(index);
		weapon w(&*s, t);
		int mon = conf.c_p_w[t].cost;
		if (p.set_money(mon))
		{
			s->add_weapon(&w);
			s->increase_cost(mon);
			return true;
		}
	}
	return false;
}

void mission::buy_ammunations(player& p, ship& s) {
	int mon = s.get_storage();
	if (!p.set_money(mon))
	{
		mon = p.get_money();
		p.set_money(mon);
	}
	s.set_ammo(mon / 3, mon / 3, mon / 3);
	s.increase_cost(mon);
}

bool mission::end_turn() {
	// ходит другой игрок
	player_turn();

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

bool mission::transfer(aircraft& a, ship& s) {
	if (s.type != cruiser_t)
	{
		a.transfer(s);
	}
}

void mission::general_death(player& p) {
	if (p.affilation)
	{
		for (int i = 0; i < this->ships1.size(); i++)
		{
			ships1[i]->set_bonus(0.9* sqrt(1 / this->param.difficult));
		}
	}
	else {
		for (int i = 0; i < this->ships2.size(); i++)
		{
			ships2[i]->set_bonus(0.9 * sqrt(1 / this->param.difficult));
		}
	}
	p.set_general({ "Admiral died", p.get_general().second });
}

bool mission::modificate(object& o, const modificated_parametrs p) {

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
		if (s == this->conformity[i].first)
		{
			return i;
		}
	}
	return -1;
}

void table::add_ship(const struct config& p, const bool a, const ships t,
	std::pair<std::string, std::string>&& c, std::string&& n) {
	const std::string s = n;
	this->array[n] = std::make_shared<ship>(p, a, t, std::move(c), std::move(n));
	n = s;
	this->conformity.push_back({ n, ids });
	ids++;
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
	if (!this->find_ship(s.first))
	{
		return nullptr;
	}
	return this->get_ship(s.first);
}

std::shared_ptr<ship> table::GetById(int id) {
	for (int i = 0; i < this->conformity.size(); i++)
	{
		if (id == this->conformity[i].second)
		{
			return get_ship(this->conformity[i].first);
		}
	}
	return nullptr;
}

player::player(std::pair<std::string, std::string> g, int m, bool a) {
	this->costs = 0;
	this->damage = 0;
	this->general = g;
	this->money = m;
	this->affilation = a;
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

bool player::set_money(int increase) {
	if (increase > this->money)
	{
		return false;
	}
	this->money -= increase;
	this->costs += increase;
	return true;
}

int player::get_money() {
	return this->money;
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