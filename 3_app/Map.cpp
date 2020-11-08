#include <exception>
#include <ostream>
#include <istream>
#include "Map.h"
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <iomanip>
namespace Prog3 {
	void Map::EmptySetter() {
		for (int Lnumber = 0; Lnumber < UL; Lnumber++) {
			for (int Cnumber = 0; Cnumber < SZline; Cnumber++) {
				lines[Lnumber].columns[Cnumber].type = EMPTY;
				lines[Lnumber].columns[Cnumber].number = -1;
			}
			lines[Lnumber].BusyCells = 0;
		}
	}
	Map::Map() {
		UL = 10;
		lines = new struct Line[UL];
		EmptySetter();
		int count = 0;
		for (int Lnumber = 0; Lnumber < UL; Lnumber++) {
			for (int j = 0; j < NumNum; j++) {
				count = (j + Lnumber + UL) % SZline;
				lines[Lnumber].columns[count].number = ((count + 1) * NumNum + Lnumber + j) % MaxNumber;
				lines[Lnumber].columns[count].type = FREE;
			}
		}
	}
	Map::Map(int NL) {
		if (NL < 0)
			throw std::invalid_argument("Invalid quantity of lines");
		else {
			int count1, count2, again;
			srand(time(NULL));
			UL = NL;
			lines = new struct Line[UL];
			EmptySetter();
			for (int Lnumber = 0; Lnumber < UL; Lnumber++) {
				for (int j = 0; j < NumNum; j++) {
					do {
						again = -1;
						count1 = rand() % (SZline); //выбор ячейки в строке
						if (lines[Lnumber].columns[count1].type == Prog3::EMPTY) {
							lines[Lnumber].columns[count1].type = Prog3::FREE;
							count2 = 1 + rand() % (MaxNumber);//выбор значения ячейки
							lines[Lnumber].columns[count1].number = count2;
							again = 0;
						}
					} while (again == -1); //пока count1 не выдаст пустую ячейку 
				}
			}
		}
	}
	Map::Map(const Map& ob) : UL(ob.UL), lines(nullptr) {
		if (UL) {
			lines = new Line[UL];
			for (int i = 0; i < UL; i++) {
				for (int j = 0; j < SZline; j++) {
					lines[i].columns[j].number = ob.lines[i].columns[j].number;
					lines[i].columns[j].type = ob.lines[i].columns[j].type;
				}
				lines[i].BusyCells = ob.lines[i].BusyCells;
			}
		}
	}
	Map& Map::operator = (const Map& ob) {
		if (this != &ob) {
			delete[] lines;
			lines = nullptr;
			UL = ob.UL;
			if (UL != 0) {
				lines = new Line[UL];
				for (int i = 0; i < UL; i++) {
					for (int j = 0; j < SZline; j++) {
						lines[i].columns[j].number = ob.lines[i].columns[j].number;
						lines[i].columns[j].type = ob.lines[i].columns[j].type;
					}
					lines[i].BusyCells = ob.lines[i].BusyCells;
				}
			}
		}
		return *this;
	}
	int Map::HelpfulFunction(int barrel, int occupy) {
		int Cnumber, FBcount, count = 0; //count считает, сколько ячеек соответствует
		for (int Lnumber = 0; Lnumber < UL; Lnumber++) {
			FBcount = 0; //счётчик непустых ячеек в строке (free/busy)
			Cnumber = 0;
			while (Cnumber < SZline && FBcount < NumNum) {
				if (lines[Lnumber].columns[Cnumber].type != EMPTY && lines[Lnumber].columns[Cnumber].number == barrel) {
					count += 1;
					if (occupy == 1) {
						lines[Lnumber].columns[Cnumber].type = BUSY;
						lines[Lnumber].BusyCells += 1;
					}

				}
				if (lines[Lnumber].columns[Cnumber].type != EMPTY)
					FBcount += 1;
				Cnumber += 1;
			}
		}
		return count;
	}
	int Map::AppropriateCells(int barrel) {
		return HelpfulFunction(barrel, 0);
	}
	int Map::FindBusyCells(int all) const {
		int Lnumber = 0, number = 0;
		while ((number == 0 || all == 1) && Lnumber < UL) {
			if (lines[Lnumber].BusyCells == NumNum)
				number += 1;
			Lnumber += 1;
		}
		return number;
	}
	Fullness Map::MapState() const {
		Fullness exist = FREE; //отвечает за состояние карты
		int number = FindBusyCells(0);
		if (number != 0)
			exist = BUSY;
		return exist;
	}
	struct Cell* Map::FreeCells() const {
		struct Cell* mtx = new struct Cell[NumNum * UL];
		int i, count = 0, Cnumber, FBcount; //count - текущий размер массива свободных ячеек
		for (int Lnumber = 0; Lnumber < UL; Lnumber++) {
			FBcount = 0;
			Cnumber = 0;
			while (FBcount < NumNum && Cnumber < SZline) {
				if (lines[Lnumber].columns[Cnumber].type == FREE) {
					i = 0;
					mtx[count].type = EMPTY;
					while (i < count && mtx[count].type == EMPTY) {
						if (mtx[i].number == lines[Lnumber].columns[Cnumber].number)
							mtx[count].type = BUSY;
						i += 1;
					}
					if (mtx[count].type == EMPTY) {
						mtx[count].type = FREE;
						mtx[count].number = lines[Lnumber].columns[Cnumber].number;
						count += 1;
					}
				}
				if (lines[Lnumber].columns[Cnumber].type != EMPTY)
					FBcount += 1;
				Cnumber += 1;
			}
		}
		if (count == 0)
			mtx[count].type = EMPTY; //для случая, когда массив пуст
		else
			mtx[count - 1].type = BUSY;
		return mtx;
	}
	std::ostream& operator << (std::ostream& c, const Map& a) {
		if (a.UL <= 0)
			c << "Map is empty";
		else
			for (int Lnumber = 0; Lnumber < a.UL; Lnumber++) {
				for (int Cnumber = 0; Cnumber < SZline; Cnumber++) {
					switch (a.lines[Lnumber].columns[Cnumber].type) {
					case EMPTY:
						c << " - " << "   ";
						break;
					case FREE:
						c << std::setw(3) << a.lines[Lnumber].columns[Cnumber].number << "   ";
						break;
					case BUSY:
						c << std::setw(3) << a.lines[Lnumber].columns[Cnumber].number << "!  ";
						break;
					}
				}
				c << std::endl;
			}
		return c;
	}
	/*	std::istream& operator >> (std::istream &c, Map &a) {
			c >> a.barrel;
			if (!std::cin.good() || a.barrel < 1 || a.barrel > MaxNumber)
					c.setstate(std::ios::failbit);
			return c;
		}*/
	int operator >> (std::istream& c, Map& a) {
		int barrel;
		c >> barrel;
		if (!c.good() || barrel < 1 || barrel > MaxNumber) {
			throw std::invalid_argument("Invalid value");
		}
		return barrel;
	}
	Fullness Map::operator () (int Lnumber, int Cnumber) const {
		if (Lnumber < 0 || Lnumber >= UL || Cnumber < 0 || Cnumber >= SZline) {
			throw std::invalid_argument("Invalid value");
		}
		else
			return lines[Lnumber].columns[Cnumber].type;
	}
	void Map::operator () (int barrel) {
		HelpfulFunction(barrel, 1);
	}
	const Map Map::operator -- (int) {
		Map b(*this);
		int number = FindBusyCells(1);
		if (number != 0) {
			int Cnumber, Ncur = 0, Ncopy = 0;
			struct Line* newlines = new struct Line[UL - number];
			while (Ncopy < UL) {
				if (lines[Ncopy].BusyCells != 5) {
					for (Cnumber = 0; Cnumber < MaxNumber; Cnumber++) {
						newlines[Ncur].columns[Cnumber].number = lines[Ncopy].columns[Cnumber].number;
						newlines[Ncur].columns[Cnumber].type = lines[Ncopy].columns[Cnumber].type;
					}
					newlines[Ncur].BusyCells = lines[Ncopy].BusyCells;
					Ncur += 1;
				}
				Ncopy += 1;
			}
			struct Line* deline = lines;
			lines = newlines;
			delete[] deline;
			UL = UL - number;
		}
		return b;
	}
}
