#ifndef __BOOM_2D_H__
#define __BOOM_2D_H__
#include <iostream>
#include "punt2.h" 
using namespace std;
typedef unsigned int uint;
template<class D>
class Boom2D;

template<class D>
class Knoop2D {
public:
	Knoop2D(punt2 punt);
	punt2 punt;
	Boom2D<D> *links, *rechts;
};

template<class D>
Knoop2D<D>::Knoop2D(punt2 punt) {
	this->punt = punt;
	links = new Boom2D<D>();
	rechts = new Boom2D<D>();
}
template<class D>
class Boom2D {
public:
	Boom2D();
	Knoop2D<D> * wortel;
	void voeg_toe(punt2 punt);
	bool bevat(punt2 & punt);
	void zoek(Boom2D<D> * & plaats, punt2 & punt, bool & gelijk);
	void zoek_buur(const punt2 & punt, punt2 & buur, int & doorzochte_knopen);
};
template<class D>
Boom2D<D>::Boom2D() {
	this->wortel = 0;
}
template<class D>
void Boom2D<D>::voeg_toe(punt2 punt) {
	Boom2D<D> *plaats = this;
	bool gelijk = false;
	//cout << "vooraf   plaats "<< plaats << " met wortel=" << plaats->wortel <<endl;
	zoek(plaats, punt, gelijk);
	//cout << "gevonden plaats "<< plaats << " met wortel=" << plaats->wortel <<endl;
	if (plaats->wortel == 0) {
		plaats->wortel = new Knoop2D<D>(punt);
		//cout << "toegevoegd" << endl;
	} else {
		cout << "tzit er al in " << plaats->wortel->punt << endl;
	}
	//cout << "------------------" << endl;
}
template<class D>
void Boom2D<D>::zoek(Boom2D<D> * & plaats, punt2 & punt, bool & gelijk) {
	bool controleer_x = true;
	while (plaats->wortel != 0) { //zolang wortel van huidige plaats niet nullpointer is
		//cout << plaats->wortel->punt<< endl;
		//cout << (controleer_x ? "x": "y")<<endl;
		if((punt == plaats->wortel->punt)){
			gelijk = true;
		}
		int nieuwpunt = controleer_x ? punt.x : punt.y;
		int huidigpunt = !controleer_x ? plaats->wortel->punt.x : plaats->wortel->punt.y;
		// volgende plaats is linkerdeelboom of rechterdeelboom
		plaats = (nieuwpunt < huidigpunt) ? plaats->wortel->links : plaats->wortel->rechts;
		//cout << (nieuwpunt<huidigpunt?"links":"rechts") << endl;
		controleer_x = !controleer_x;
	}
	//cout << "Gevonden plaats "<< plaats << " met wortel=" << plaats->wortel <<endl;
	//return plaats;
}

template<class D>
bool Boom2D<D>::bevat(punt2 & punt) {
	Boom2D<D> *plaats = this;
	bool gelijk = false;
	zoek(plaats, punt, gelijk);
	return gelijk;
}

template<class D>
void Boom2D<D>::zoek_buur(const punt2 & punt, punt2 & buur, int & doorzochte_knopen){
	if(this->wortel != 0){
		bool controleer_x = true;
		doorzochte_knopen = 0;
		Boom2D<D> * plaats = this;
		buur = plaats->wortel->punt;
		uint kortste_afstand = punt.kwadafstand(buur);

		while (plaats->wortel != 0 ){//&& !(punt == plaats->wortel->punt) ){
			bool controleer_links = false;
			int afstand_links = 0;
			int afstand_rechts = 0;
			if(plaats->wortel->links != 0 ){
				int afstand_links = punt.kwadafstand(plaats->wortel->links->wortel->punt);
			}
			if(plaats->wortel->rechts != 0 ){
				int afstand_rechts = punt.kwadafstand(plaats->wortel->rechts->wortel->punt);
			}
			if (afstand_links !=0 && afstand_rechts !=0 && afstand_links < afstand_rechts && kortste_afstand > afstand_links) {
				plaats = plaats->wortel->links;
				//buur = plaats->wortel->punt;
				//kortste_afstand = punt.kwadafstand(buur);
			}
			if (afstand_links !=0 && afstand_rechts !=0 && afstand_rechts < afstand_links && kortste_afstand > afstand_rechts) {
				plaats = plaats->wortel->rechts;
			}
			buur = plaats->wortel->punt;
			kortste_afstand = punt.kwadafstand(buur);
			doorzochte_knopen++;
		}
	}
}
#endif
