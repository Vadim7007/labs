#include "/Users/vadim/Desktop/Me/Programming/study/Lab4/include/Download_config.h"

#define PATH1 "/Users/vadim/Desktop/Я/Программирование/study/Lab4/config/config.txt"
#define PATH2 "/Users/vadim/Desktop/Я/Программирование/study/Lab4/config/param.txt"
#define PATH3 "/Users/vadim/Desktop/Я/Программирование/study/Lab4/config/mode.txt"

void default_download(config& c0, param_mission& p0, mode_mission& m0) {
	// инициализация значений по умолчанию
	m0.game_speed = 1;
	m0.mode = false;
	m0.random = true;
	m0.side = true;

	p0.difficult = 1;
	p0.goal = 10000;
	p0.max_ship = 30;
	p0.money = 15000;
	p0.size = { 100, 100 };
	p0.visibility = 10;
	p0.list = { {"Ivan Petrov", "major"}, {"Nikita Ivanov", "captain"},
		{"Petr Nikitin", "admiral"}, {"Danil Saturday", "sergant"},
		{"Saturday Danilin", "lieutenant"},{"Ivan Ivanov", "major"},
		{"Nikita Petrov", "captain"}, {"Petr Ivanov", "admiral"},
		{"Danil Ivanov", "sergant"},	{"Saturday Ivanov", "lieutenant"},
		{"Ivan Nikitin", "major"}, {"Nikita Petrov", "captain"},
		{"Petr Petrov", "admiral"}, {"Danil Petrov", "sergant"},
		{"Saturday Petrov", "lieutenant"}, {"Ivan Nikitin", "major"},
		{"Nikita Nikitin", "captain"}, {"Petr Danilin", "admiral"},
		{"Danil Nikitin", "sergant"}, {"Saturday Nikitin", "lieutenant"},
		{"Ivan Danilin", "major"}, {"Nikita Danilin", "captain"},
		{"Petr Danilin", "admiral"}, {"Danil Danilin", "sergant"},
		{"Vadim Danilin", "lieutenant"},{"Dmitry Petrov", "major"},
		{"Dmitry Ivanov", "captain"}, {"Dmitry Nikitin", "admiral"},
		{"Dmitry Withoutsurname", "sergant"}, {"Dmitry Danilin", "lieutenant"}
	};

	c0.c_p_o[0].cost = 450;
	c0.c_p_o[1].cost = 400;
	c0.c_p_o[2].cost = 500;
	c0.c_p_w[0].cost = 100;
	c0.c_p_w[1].cost = 150;
	c0.c_p_w[2].cost = 250;
	c0.c_p_w[0].max_ammunation = 250;
	c0.c_p_w[1].max_ammunation = 150;
	c0.c_p_w[2].max_ammunation = 100;
	c0.p_o[0].HP = 550;
	c0.p_o[1].HP = 400;
	c0.p_o[2].HP = 650;
	c0.p_o[0].range = 3;
	c0.p_o[1].range = 2;
	c0.p_o[2].range = 2;
	c0.p_o[0].speed = 3;
	c0.p_o[1].speed = 3;
	c0.p_o[2].speed = 2;
	c0.p_o[0].storage = 200;
	c0.p_o[1].storage = 300;
	c0.p_o[2].storage = 400;
	c0.p_s[0].max_aircraft = 0;
	c0.p_s[1].max_aircraft = 2;
	c0.p_s[2].max_aircraft = 5;
	c0.p_s[0].max_weapon = 8;
	c0.p_s[1].max_weapon = 6;
	c0.p_s[2].max_weapon = 4;
	c0.p_w[0].damage = 2;
	c0.p_w[1].damage = 8;
	c0.p_w[2].damage = 30;
	c0.p_w[0].radius = 1;
	c0.p_w[1].radius = 1;
	c0.p_w[2].radius = 2;
	c0.p_w[0].rate = 10;
	c0.p_w[1].rate = 2;
	c0.p_w[2].rate = 1;
}

bool download_config(config& c) {
	std::ifstream fin(PATH1, std::ios_base::in);
	if (!fin.is_open()) {
		std::cout << "File is not open" << std::endl;
		return false;
	}

	fin >> c.c_p_o[0].cost;
	fin >> c.c_p_o[1].cost;
	fin >> c.c_p_o[2].cost;
	fin >> c.c_p_w[0].cost;
	fin >> c.c_p_w[1].cost;
	fin >> c.c_p_w[2].cost;
	fin >> c.c_p_w[0].max_ammunation;
	fin >> c.c_p_w[1].max_ammunation;
	fin >> c.c_p_w[2].max_ammunation;
	fin >> c.p_o[0].HP;
	fin >> c.p_o[1].HP;
	fin >> c.p_o[2].HP;
	fin >> c.p_o[0].range;
	fin >> c.p_o[1].range;
	fin >> c.p_o[2].range;
	fin >> c.p_o[0].speed;
	fin >> c.p_o[1].speed;
	fin >> c.p_o[2].speed;
	fin >> c.p_o[0].storage;
	fin >> c.p_o[1].storage;
	fin >> c.p_o[2].storage;
	fin >> c.p_s[0].max_aircraft;
	fin >> c.p_s[1].max_aircraft;
	fin >> c.p_s[2].max_aircraft;
	fin >> c.p_s[0].max_weapon;
	fin >> c.p_s[1].max_weapon;
	fin >> c.p_s[2].max_weapon;
	fin >> c.p_w[0].damage;
	fin >> c.p_w[1].damage;
	fin >> c.p_w[2].damage;
	fin >> c.p_w[0].radius;
	fin >> c.p_w[1].radius;
	fin >> c.p_w[2].radius;
	fin >> c.p_w[0].rate;
	fin >> c.p_w[1].rate;
	fin >> c.p_w[2].rate;

	if (!fin.good()) {
		std::cout << "File was damaged" << std::endl;
		return false;
	}
	return true;
}

bool download_param(param_mission& p) {
	std::ifstream fin(PATH2, std::ios_base::in);
	if (!fin.is_open()) {
		std::cout << "File is not open" << std::endl;
		return false;
	}

	fin >> p.difficult;
	fin >> p.goal;
	fin >> p.money;
	fin >> p.max_ship;
	fin >> p.size.first;
	fin >> p.size.second;
	fin >> p.visibility;
	for (int i = 0; i < 2*p.max_ship; i++)
	{
		std::pair<std::string, std::string> tmp;
		std::string name;
		std::string surname;
		fin >> name;
		fin >> surname;
		tmp.first = name + " " + surname;
		fin >> tmp.second;
		fin.ignore(1);
		p.list.push_back(tmp);
	}

	if (!fin.good()) {
		std::cout << "File was damaged" << std::endl;
		return false;
	}
	return true;
}

bool download_mode(mode_mission& m) {
	std::ifstream fin(PATH3, std::ios_base::in);
	if (!fin.is_open()) {
		std::cout << "File is not open" << std::endl;
		return false;
	}

	fin >> m.game_speed;
	fin >> m.mode;
	fin >> m.random;
	fin >> m.side;

	if (!fin.good()) {
		std::cout << "File was damaged" << std::endl;
		return false;
	}
	return true;
}


/*
возвращает false, если загружены значения по умолчанию
возвращает true, если загружены значения из конфигурационных файлов
*/
bool download_info(config& c, param_mission& p, mode_mission& m) {
	config c0;
	param_mission p0;
	mode_mission m0;

	default_download(c0, p0, m0);

	bool flag = download_config(c);
	flag &= download_param(p);
	flag &= download_mode(m);

	if (!flag)
	{
		c = c0;
		p = p0;
		m = m0;
		return false;
	}
	return true;
}