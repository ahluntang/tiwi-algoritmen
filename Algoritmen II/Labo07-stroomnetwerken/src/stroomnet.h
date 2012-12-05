#ifndef __STROOMNET_H
#define __STROOMNET_H
#include "graaf.h"
#include "pad.h"
#include "vergrotendpadzoeker.h"
#include "kortstepadzoeker.h"
#include <cassert>
#include <iostream>
using std::vector;
using std::ostream;

/**********************************************************************

 Class: Stroomnetwerk

 beschrijving: Een stroomnetwerk gaat uit van een gewogen gerichte graaf
 die in de constructor wordt opgegeven

 ***************************************************************************/

template<class T> //T = takdata
class Stroomnetwerk: public GraafMetTakdata<GERICHT, T> {
public:
//Copyconstructor. Let op: Graaf<GERICHT>(gr) moet toegevoegd,
//anders roept de copyconstructor van GraafMetTakdata de defaultconstructor
//van Graaf op en krijgen we een lege graaf.
	Stroomnetwerk(const GraafMetTakdata<GERICHT, T>& gr) :
			Graaf<GERICHT>(gr), GraafMetTakdata<GERICHT, T>(gr) {
	}
	;

	Stroomnetwerk(const GraafMetTakdata<GERICHT, T>& gr, int _van, int _naar) :
			Graaf<GERICHT>(gr.aantalKnopen()), van(_van), naar(_naar) {
		capaciteit = 0;
		Stroomnetwerk<T> restnetwerk(gr);
		Pad<T> vergrotendpad;
		Vergrotendpadzoeker<T> vg(restnetwerk, van, naar, vergrotendpad);
		//Kortstepadzoeker<T> vg(restnetwerk, van, naar, vergrotendpad);
		while(vergrotendpad.size() !=0 ){
			restnetwerk -= vergrotendpad;
			*this += vergrotendpad;
			capaciteit += vergrotendpad.geefCapaciteit();
			Vergrotendpadzoeker<T> vg(restnetwerk, van, naar, vergrotendpad);
			//Kortstepadzoeker<T> vg(restnetwerk, van, naar, vergrotendpad);
		}
	}

	int geefCapaciteit() {
		return capaciteit;
	}

	void operator-=(const Pad<T>& pad);
	void operator+=(const Pad<T>& pad);

protected:
	int van, naar, capaciteit;

};

template<class T>
void Stroomnetwerk<T>::operator-=(const Pad<T>& pad) {
	int cap = pad.geefCapaciteit();
	T van = pad[0];
	T naar = pad[1];
	for (int i = 1; i < pad.size() - 1; i++) {
		T *huidige_capaciteit = geefTakdata(van, naar);
		(*huidige_capaciteit) -= cap;

		T *teruggeduwde_capaciteit = geefTakdata(naar, van);
		if (teruggeduwde_capaciteit == 0) {
			voegVerbindingToe(naar, van, cap);
		} else {
			(*teruggeduwde_capaciteit) += cap;
		}

		van = pad[i];
		naar = pad[i + 1];
	}
}

template<class T>
void Stroomnetwerk<T>::operator+=(const Pad<T>& pad) {
	int cap = pad.geefCapaciteit();
	T van = pad[0];
	T naar = pad[1];
	for (int i = 1; i < pad.size() - 1; i++) {
		T *huidige_capaciteit = geefTakdata(van, naar);
		if (huidige_capaciteit == 0) {
			voegVerbindingToe(van, naar, cap);
		} else {
			(*huidige_capaciteit) += cap;
		}
		van = pad[i];
		naar = pad[i + 1];
	}
}

#endif
