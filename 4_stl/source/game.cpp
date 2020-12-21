#pragma once

#include "/Users/vadim/Desktop/Me/Programming/study/Lab4/include/Download_config.h"

/*
#ifndef MISSION_CLASSES_H
#include "/Users/vadim/Desktop/Me/Programming/study/Lab4/include/mission_classes.h"
#endif
*/
int main() {
	param_mission p;
	mode_mission m;
	config c;
	download_info(c, p, m);
	mission M(m, p, c);
	M.buy_ship(M.p1, aircraft_carrier);
	M.buy_aircraft(M.p1, bomber_t, 0);
	M.sell_ship(M.p1, 0);
	M.p1.get_money();

	ship* array[6];
	aircraft* array2[6];
		cruiser s1(c, true, { "Name_com1", "Rang" }, "Ship_test1");
		air_cruiser s2(c, true, { "Name_com2", "Rang" }, "Ship_test2");
		air_carrier s3(c, true, { "Name_com3", "Rang" }, "Ship_test3");
		cruiser s4(c, false, { "Name_com4", "Rang" }, "Ship_test4");
		air_cruiser s5(c, false, { "Name_com5", "Rang" }, "Ship_test5");
		air_carrier s6(c, false, { "Name_com6", "Rang" }, "Ship_test6");
		array[0] = &s1;
		array[1] = &s2;
		array[2] = &s3;
		array[3] = &s4;
		array[4] = &s5;
		array[5] = &s6;
		fighter a1(c, true, 2, &s3);
		bomber a2(c, true, 2, &s3);
		front_bomber a3(c, true, 2, &s3);
		s3.add_aircraft(&a1);
		s3.add_aircraft(&a2);
		s3.add_aircraft(&a3);
		fighter a4(c, false, 2, &s6);
		bomber a5(c, false, 2, &s6);
		front_bomber a6(c, false, 2, &s6);
		s6.add_aircraft(&a4);
		s6.add_aircraft(&a5);
		s6.add_aircraft(&a6);
		array2[0] = &a1;
		array2[1] = &a2;
		array2[2] = &a3;
		array2[3] = &a4;
		array2[4] = &a5;
		array2[5] = &a6;
		for (int i = 0; i < 6; i++)
		{
			array2[i]->correct();
			array2[i]->recovery();
			array2[i]->decrease_action();
			array2[i]->get_coord();
			array2[i]->get_cost();
			array2[i]->get_range();
			array2[i]->increase_cost(10);
			array2[i]->modificate(range);
			array2[i]->modificate(Rate);
			array2[i]->set_current_coord({ 50, 50 });
			array2[i]->set_coord({ 1, 1 });
			array2[i]->return_back();
		}
}