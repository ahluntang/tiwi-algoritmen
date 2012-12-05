#ifndef __SCHIJF
#define __SCHIJF
#include <map>
using std::map;
#include <iostream>
typedef unsigned int blokindex;

//naamgeving gaat uit van de gebruiker: schrijf is een schrijfoperatie naar
//de schijf, enzovoorts
template<class T>
class Schijf: private map<blokindex, T> {
public:
//schrijf: voegt een T toe aan de schijf. Geeft de index terug
	blokindex schrijf(const T & b) {
		++indexteller;
//this-> is nodig (bij sommige compilers) omdat de parametrisatie
//niet afgeleid kan worden uit de argumenten.
		this->operator[](indexteller) = b;
		return indexteller;
	}
	void verwijder(blokindex bi) {
		this->erase(bi);
	}
	void herschrijf(const T& b, const blokindex bi) {
		this->operator[](bi) = b;
	}
	void lees(T& b, const blokindex bi) {
		b = this->operator[](bi);
	}
//
//  einde interface
//
	Schijf() :
			map<blokindex, T>(), indexteller(10) {
	}
	;
private:
	blokindex indexteller;

};

#endif
