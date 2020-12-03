#include "/Users/vadim/Desktop/Я/Программирование/study/Lab4/include/Download_config.h"

bool download_info(config& c, param_mission& p, mode_mission& m) {
	config c0;
	param_mission p0;
	mode_mission m0;

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

	// ошибка в данных
	c0.c_p_o[0].cost = 300;
	c0.c_p_o[1].cost = 400;
	c0.c_p_o[2].cost = 500;
	c0.c_p_w[0].cost = 100;
	c0.c_p_w[1].cost = 150;
	c0.c_p_w[2].cost = 250;
	c0.p_o[0].HP = 300;
	c0.p_o[1].HP = 400;
	c0.p_o[2].HP = 550;
	c0.p_o[0].range = 3;
	c0.p_o[1].range = 2;
	c0.p_o[2].range = 2;
	c0.p_o[0].speed = 4;
	c0.p_o[1].speed = 3;
	c0.p_o[2].speed = 2;
	c0.p_o[0].storage = 150;
	c0.p_o[1].storage = 300;
	c0.p_o[2].storage = 400;
}