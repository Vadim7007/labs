#include "/Users/vadim/Desktop/Me/Programming/study/Lab4/include/mission_classes.h"

mission::mission(const struct mode_mission& m, 
	const struct param_mission& p, const struct config& c)
	: param(p), mode(m), conf(c), arena(p.size, m.random) {
	this->lenhtg_list = this->param.list.size();
	this->p1 = player(std::move(get_commander()), round(p.money / p.difficult), true);
	this->p2 = player(std::move(get_commander()), round(p.money * p.difficult), false);
}

std::pair<std::string, std::string> mission::get_commander() {
	this->lenhtg_list--;
	std::pair<std::string, std::string> s = std::move(param.list[this->lenhtg_list]);
	return s;
}

bool mission::buy_ship(player& pl, ships t){
	if (pl.set_money(this->conf.c_p_o[t].cost))
	{
		std::string name = "Ship" + std::to_string(this->lenhtg_list);
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
		if (this->param.max_ship == ships1.size()) return false;
		auto s = this->ships1.GetById(index);
		aircraft* a;
		switch (t)
		{
		case fighter_t:
			a = new fighter(conf, true, 2, &(*s));
			break;
		case front_bomber_t:
			a = new front_bomber(conf, true, 2, &(*s));
			break;
		case bomber_t:
			a = new bomber(conf, true, 2, &(*s));
			break;
		default:
			throw std::exception("Incorrect argument: type of aircraft");
		}

		int mon = a->get_cost();
		if (p.set_money(mon))
		{
			s->add_aircraft(a);
			s->increase_cost(mon);
			return true;
		}
	}
	else {
		if (this->param.max_ship == ships2.size()) return false;
		auto s = this->ships2.GetById(index);
		aircraft* a;
		switch (t)
		{
		case fighter_t:
			a = new fighter(conf, true, 2, &(*s));
			break;
		case front_bomber_t:
			a = new front_bomber(conf, true, 2, &(*s));
			break;
		case bomber_t:
			a = new bomber(conf, true, 2, &(*s));
			break;
		default:
			throw std::exception("Incorrect argument: type of aircraft");
		}

		int mon = a->get_cost();
		if (p.set_money(mon))
		{
			s->add_aircraft(a);
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
		if ((t == heavy &&
			(s->type == aircraft_carrier || s->type == aircraft_carrier_cruiser))
			|| (t == middle && s->type == aircraft_carrier)) return false;
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
		if ((t == heavy &&
			(s->type == aircraft_carrier || s->type == aircraft_carrier_cruiser))
			|| (t == middle && s->type == aircraft_carrier)) return false;
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

void mission::buy_ammunations(player& p, const int index) {
	std::shared_ptr<ship> s;
	if (p.affilation)
	{
		s = this->ships1.GetById(index);
	}
	else {
		s = this->ships2.GetById(index);
	}

	int mon = s->get_storage();
	if (!p.set_money(mon))
	{
		mon = p.get_money();
		p.set_money(mon);
	}
	s->set_ammo(mon / 3, mon / 3, mon / 3);
	s->increase_cost(mon);
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

	bool win = false;
	// если корабли достигли контрольной точки
	for (size_t i = 0; i < ships2.size(); i++)
	{
		win = true;
		if (!((ships2[i]->get_coord().first > param.size.first - 7) &&
			(ships2[i]->get_coord().second > param.size.second - 7))) {
			win = false;
			break;
		}
	}
	// если кораблей где-то не осталось
	win |= (!ships1.size() || !ships2.size());
	// если достигнута сумма уничтоженного
	win |= (p1.get_damage() > param.goal || p2.get_damage() > param.goal);
	if (win) {
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

void mission::player_turn() {
	int min = ships2[0]->get_range();
	for (size_t i = 0; i < ships2.size(); i++)
	{
		min = std::min(min, ships2[i]->get_range());
	}
	if (mine::random(2) > -2) {
		for (size_t i = 0; i < ships2.size(); i++)
		{
			// атака
			for (size_t j = 0; j < ships1.size(); j++)
			{
				ships2[i]->attack(*ships1[j]);
			}

			// перемещение
			int x = ships2[i]->get_coord().first;
			int y = ships2[i]->get_coord().second;
			this->arena.move_ob(*ships2[i], arena[x + min / 2][y + min / 2]);
		}
	}
	else {
		for (size_t i = 0; i < ships2.size(); i++)
		{
			// перемещение
			int x = ships2[i]->get_coord().first;
			int y = ships2[i]->get_coord().second;
			this->arena.move_ob(*ships2[i], arena[x + min / 2][y + min / 2]);
			
			// атака
			for (size_t j = 0; j < ships1.size(); j++)
			{
				ships2[i]->attack(*ships1[j]);
			}
		}
	}
}

void mission::player_ready() {
	bool flag = true;
	p2.set_general(param.list[lenhtg_list]);
	while (flag)
	{
		buy_ship(p2, cruiser_t);
		ships2[ships2.size() - 1]->set_coord({ (ships2.size() - 1)%3, (ships2.size() - 1) / 3});
		buy_ammunations(p2, ships2.size()-1);
		buy_ship(p2, aircraft_carrier_cruiser);
		ships2[ships2.size() - 1]->set_coord({ ships2.size()%3, ships2.size() / 3 });
		buy_ammunations(p2, ships2.size() - 1);
		buy_aircraft(p2, fighter_t, ships2.size() - 1);
		buy_aircraft(p2, front_bomber_t, ships2.size() - 1);
		flag &= buy_ship(p2, aircraft_carrier);
		ships2[ships2.size() - 1]->set_coord({ (ships2.size()+1)%3, (ships2.size() + 1)/ 3});
		buy_ammunations(p2, ships2.size() - 1);
		buy_aircraft(p2, fighter_t, ships2.size() - 1);
		buy_aircraft(p2, front_bomber_t, ships2.size() - 1);
		buy_aircraft(p2, bomber_t, ships2.size() - 1);
		flag &= buy_aircraft(p2, bomber_t, ships2.size() - 1);
	}
}

std::shared_ptr<ship> mission::GetById(const player& p, const int id) noexcept {
	if (p.affilation) {
		return this->ships1.GetById(id);
	}
	else {
		return this->ships2.GetById(id);
	}
}

bool mission::transfer(aircraft& a, ship& s) {
	if (s.type != cruiser_t)
	{
		a.transfer(s);
		return true;
	}
	return false;
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

bool mission::modificate(player& p, object& o, const modificated_parametrs mp) {
	int mon = o.get_cost()/20;
	if (p.set_money(mon)) {
		o.modificate(mp);
		o.increase_cost(mon);
		return true;
	}
	return false;
}

/*
метод извлечения ссылки на обьект по позывному. Если ссылки по этому ключу
не существует, добавляет nullptr с таким ключом и его возвращает
*/
std::shared_ptr<ship> table::get_ship(const std::string& s) noexcept {
	return this->array[s];
}

/*
возвращает номер корабля по его названию, либо -1, если такого нет
*/
int table::get_num(const std::string& s) const noexcept {
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
	switch (t)
	{
	case 0: {
		this->array[n] = std::make_shared<cruiser>(
			p, a, std::move(c), std::move(n));
		break;
	}
	case 1:{
		this->array[n] = std::make_shared<air_cruiser>(
			p, a, std::move(c), std::move(n));
		break;
	}
	case 2: {
		this->array[n] = std::make_shared<air_carrier>(
			p, a, std::move(c), std::move(n));
		break;
	}
	default:
		throw std::exception ("Incorrect type");
	}
	n = s;
	this->conformity.push_back({ n, ids });
	ids++;
}

bool table::find_ship(const std::string& s) const noexcept {
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

std::shared_ptr<ship> table::operator[](const std::string& s) noexcept {
	return this->get_ship(s);
}

std::shared_ptr<ship> table::operator[](const int n) noexcept {
	auto s = this->conformity[n];
	if (!this->find_ship(s.first))
	{
		return nullptr;
	}
	return this->get_ship(s.first);
}

std::shared_ptr<ship> table::GetById(const int id) noexcept {
	for (int i = 0; i < this->conformity.size(); i++)
	{
		if (id == this->conformity[i].second)
		{
			return get_ship(this->conformity[i].first);
		}
	}
	return nullptr;
}

player::player(std::pair<std::string, std::string>&& g, const int m, const bool a) noexcept {
	this->costs = 0;
	this->damage = 0;
	this->general = g;
	this->money = m;
	this->affilation = a;
}

void player::set_general(std::pair<std::string, std::string> g) noexcept {
	this->general = g;
}

std::pair<std::string, std::string> player::get_general() const noexcept {
	return this->general;
}

void player::increase_damage(const int a) noexcept {
	if (a>=0) this->damage += a;
	return;
}

bool player::set_money(int increase) noexcept {
	if (increase > this->money)
	{
		return false;
	}
	this->money -= increase;
	this->costs += increase;
	return true;
}

int player::get_money() const noexcept {
	return this->money;
}

Map::Map(const std::pair<int, int> s, bool random = false) noexcept
: size(s) {
	if (random)
	{
		for (int i = 0; i < s.first; i++)
		{
			std::vector<cell> v;
			for (int j = 0; j < s.second; j++)
			{
				cell c = { i, j };
				if (mine::random(10) > 6 &&
					(i > 6 && i < (size.first-6) && j > 6 && j < (size.second - 6)))
					c.set_state(ground);
				v.push_back(c);
			}
			this->array.push_back(v);
		}
	}
	else {
		for (int i = 0; i < s.first; i++)
		{
			std::vector<cell> v;
			for (int j = 0; j < s.second; j++)
			{
				v.push_back({i, j});
			}
			this->array.push_back(v);
		}
	}
}

std::vector <cell>& Map::operator[](const int i) {
	if (i > size.first) throw std::exception("incorrect argument");
	return array[i];
}

std::vector<cell*> Map::get_way(const cell& from, const cell& to) noexcept {
	std::vector<cell*> way;
	auto current_cell = &from;

	int vec_x = to.coord.first - from.coord.first;
	int vec_y = to.coord.second - from.coord.second;
	
	bool flag = true;

	while (flag) {
		flag = false;
		// перемещение клетки
		if (vec_x != 0) {
			int offset = vec_x / abs(vec_x);
			auto cc = &(*this)
				[current_cell->coord.first + offset][current_cell->coord.second];
			if (cc->state == free_st) {
				current_cell = cc;
				way.push_back(cc);
				flag = true;
			}
		}
		if (vec_y != 0) {
			int offset = vec_y / abs(vec_y);
			auto cc = &(*this)[current_cell->coord.first]
				[current_cell->coord.second + offset];
			if (cc->state == free_st) {
				current_cell = cc;
				way.push_back(cc);
				flag = true;
			}
		}

		int vec_x = to.coord.first - current_cell->coord.first;
		int vec_y = to.coord.first - current_cell->coord.second;
	}	
	return way;
}

void Map::move_ob(object& o, cell& to) noexcept {
	if (!o.activate) return;
	auto coord = o.get_coord();
	auto from = (*this)[coord.first][coord.second];
	o.set_coord(to.coord);
	auto way = this->get_way(from, to);

	if (o.decrease_action()) {
		for (int j = 0; j < std::min(o.get_range(), (int)way.size()); j++)
		{
			way[j]->set_state(busy);
			(*this)[o.get_coord().first][o.get_coord().second].set_state(free_st);
			o.set_current_coord(way[j]->coord);
		}
	}
}

cell::cell(const int x, const int y) noexcept : coord({x, y}) {
	this->state = free_st;
}

void cell::set_state(const states s) noexcept {
	this->state = s;
}