#include "/Users/vadim/Desktop/Я/Программирование/study/Lab4/include/classes.h"
//#include "classes.h"

object::object(const struct const_param_object& c_p, 
			   const struct param_object& p, const bool affilation)
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


