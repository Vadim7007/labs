#include "mylib.h"

class Tr	// трактрисса
{
public:
	Tr() {
		set(1);
	};				// конструктор
	Tr(double p);					// конструктор
	Tr& set(double new_p);			// изменение параметра кривой
	
	double get(void) const {		// получение параметра кривой
		return a;
	};
	void coord(double& x, 
			   double& y, 
			   double n) const;		// получение координат по углу
	double len(double n) const;		// возвращает длину дуги
	double rad(double n) const;		// радиус кривизны
	double area(void) const;			// площадь полосы
	double surface(void) const;			// поверхность вращения
	double volume(void) const;			// объем тела вращения
private:
	double a;
	const double pi = M_PI;
	double engle_num(double n) const;
};