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
	
}