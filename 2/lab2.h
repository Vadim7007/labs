#include "mylib.h"

class Tr	// трактрисса
{
public:
	Tr() {
		a = 1;
	};				// конструктор
	Tr(double p);					// конструктор
	~Tr() {};						// деструктор
	void set(double new_p);			// изменение параметра кривой
	
	double get(void) const {		// получение параметра кривой
		return a;
	};
	void coord(double& x, 
	double& y, double n_pi) const;	// получение координат по углу
	double len(double n_pi) const;		// возвращает длину дуги
	double rad(double n_pi) const;		// радиус кривизны
	double area(void) const;			// площадь полосы
	double surface(void) const;			// поверхность вращения
	double volume(void) const;			// объем тела вращения
private:
	double a;
};