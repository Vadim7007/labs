#ifndef Loto_h
#define Loto_h
namespace Prog3 {
	const int SZline = 9; //максимальная длина строки
	const int NumNum = 5; //количество непустых ячеек в строке
	const int MaxNumber = 90; //максимально возможное значение ячейки
	enum Fullness {
		EMPTY,
		BUSY,
		FREE,
	};
	typedef struct Cell {
		int number;
		Fullness type;
	}Cell;
	typedef struct Line {
		struct Cell columns[Prog3::SZline];
		int BusyCells;
	}Line;
	class Map {
	private:
		int UL; //used lines
		struct Line* lines;
		void EmptySetter();
		int FindBusyCells(int all) const;
		int HelpfulFunction(int barrel, int occupy);
	public:
		Map();
		Map(int NL);
		Map(const Map& ob);
		~Map() { delete[] lines; }
		Map& operator = (const Map& ob);
		int AppropriateCells(int barrel);
		Fullness MapState() const;
		struct Cell* FreeCells() const;
		friend std::ostream& operator << (std::ostream& c, const Map& a);
		friend int operator >> (std::istream& c, Map& a);
		Fullness operator () (int Lnumber, int Cnumber) const;
		void operator () (int barrel);
		const Map operator -- (int);
		int fil = 0;
	};
}
#endif