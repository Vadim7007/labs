#include "/Users/vadim/Desktop/Я/Программирование/study/Lab4/include/mission_classes.h"

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