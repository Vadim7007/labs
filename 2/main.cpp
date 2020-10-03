#include "lab2.h"

int main(void) {
	double p = 1;
	Tr X(p);
	while (p != -1) {
		std::cout << "Enter parametr. -1 for the end.\n";
		getn(p);
		try {
			X.set(p);
		}
		catch (const std::exception&) {
			std::cout << "Failed to set such parameter." << std::endl;
			continue;
		}
		std::cout << "Enter angle.\n";
		double an;
		getn(an);
		double x, y;
		X.coord(x, y, an);
		std::cout << x << " " << y << "\t" << X.len(an) << "\t" << X.rad(an) <<
			"\t" <<	X.area() << "\t" << X.surface() << "\t" << X.volume() << "\n";
	}
	_CrtDumpMemoryLeaks();
	return 0;
}
