#include "lab2.h"

Tr::Tr(double p) {
	if (p > 0) {
		a = p;
	}
	else {
		throw std::exception("Invalid parametr.");
	}
}

Tr& Tr::set(double new_p) {
	if (new_p > 0) {
		a = new_p;
	}
	else {
		throw std::exception("Invalid parametr.");
	}
	return *this;
}

void Tr::coord(double& x, double& y, double n) const {
	double z = 0;
	z = engle_num(n);
	y = a * sin(z);
	x = a * cos(z) + a * log(tan(z / 2));
	return;
}

double Tr::len(double n) const {
	double z = 0;
	z = engle_num(n);
	return a * log(1 / sin(z));
}

double Tr::rad(double n) const {
	double z = 0;
	z = engle_num(n);
	return (a / tan(z));
}

double Tr::area(void) const {
	return (pi * a * a / 2);
}

double Tr::surface(void) const {
	return (pi * a * a * 4);
}

double Tr::volume(void) const {
	return (pi * a * a * a * 2 / 3);
}

double Tr::engle_num(double n) const {
	int k = trunc(n / 360);
	n = n - k * 360;
	if (n < 0) {
		n += 360;
	}
	if (n > 180) {
		throw std::exception("Incorrect engle");
	}
	return (n / 180 * pi);
}
