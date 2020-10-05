#include "lab2.h"

Tr::Tr(double p) {
	if (p > 0) {
		a = p;
	}
	else {
		throw std::exception("Negative parametr.");
	}
}

Tr Tr::set(double new_p) {
	if (new_p > 0) {
		a = new_p;
	}
	else {
		throw std::exception("Negative parametr.");
	}
	return *this;
}

void Tr::coord(double& x, double& y, double n_pi) const {
	n_pi = abs(n_pi) - trunc(abs(n_pi));
	y = a * sin(n_pi * pi);
	x = a * cos(n_pi * pi) + a * log(tan(n_pi * pi / 2));
}

double Tr::len(double n_pi) const {
	n_pi = abs(n_pi) - trunc(abs(n_pi));
	return a * log(1 / sin(n_pi * pi));
}

double Tr::rad(double n_pi) const {
	n_pi = abs(n_pi) - trunc(abs(n_pi));
	return (a / tan(n_pi * pi));
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