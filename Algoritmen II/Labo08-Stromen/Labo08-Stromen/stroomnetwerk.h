//
//  stroomnetwerk.h
//  Labo08-Stromen
//
//

#ifndef Labo08_Stromen_stroomnetwerk_h
#define Labo08_Stromen_stroomnetwerk_h

#include "pad.h"
#include "vergrotendpadzoeker.h"
#include "graaf.h"


// STROOMNETWERKEN

template < class Takdata >
class StroomNetwerk: public GraafMetTakdata< GERICHT,Takdata > {
public:
    StroomNetwerk();
    StroomNetwerk(const GraafMetTakdata<GERICHT, Takdata>& gr);
    
    void operator+=( const Pad<Takdata>& pad );
    void operator-=( const Pad<Takdata>& pad );
    
    Takdata wordMaxStroomVan(GraafMetTakdata<GERICHT, Takdata>& netwerk, int producent, int verbruiker);
    
protected:
};

// IMPLEMENTATIE

/** Default constructor
 */
template < class Takdata >
StroomNetwerk<Takdata>::StroomNetwerk(){
}

/** Copy/Conversion constructor
 * @param gr GraafMetTakdata
 */
template < class Takdata >
StroomNetwerk<Takdata>::StroomNetwerk(const GraafMetTakdata<GERICHT, Takdata>& gr):
    Graaf<GERICHT>(gr), GraafMetTakdata<GERICHT, Takdata>(gr){
}

/** Maximale stroom berekenen
 * @param producent (int)
 * @param verbruiker (int)
 * @return capaciteit (int)
 */
template < class Takdata >
Takdata StroomNetwerk<Takdata>::wordMaxStroomVan(GraafMetTakdata<GERICHT, Takdata>& netwerk, int producent, int verbruiker) {
    if (!netwerk.isGericht())
        throw GraafExceptie("Ongerichte grafen zijn geen stroomnetwerken.");
    
    //this->zetAantalKnopen(netwerk.aantalKnopen());
    this->knopen.resize(netwerk.aantalKnopen());
    
    int capaciteit = 0;
    
    // oorspronkelijk restnetwerk is origineel netwerk
    StroomNetwerk<Takdata> restnetwerk(netwerk);
    
    // oospronkelijk nog geen verbindingen voor oplossing gevonden
    
    
    Pad< Takdata> vergrotendPad;
    
    // zolang vergrotendPad niet leeg is, heeft de padzoeker een pad gevonden.
    Vergrotendpadzoeker<int> padzoeker(restnetwerk, producent, verbruiker, vergrotendPad);
    while(vergrotendPad.size() !=0 ){
        capaciteit += vergrotendPad.geefCapaciteit(); // capaciteit opslaan.
        restnetwerk-=vergrotendPad; // pad uit restnetwerk halen
        *this+=vergrotendPad; // pad toevoegen aan huidig netwerk
        Vergrotendpadzoeker<int> padzoeker(restnetwerk, producent, verbruiker, vergrotendPad);
    }
    return capaciteit;
}

/** += operator overloading
 * @param pad met capaciteit
 */
template <class Takdata>
void StroomNetwerk<Takdata>::operator+=( const Pad<Takdata>& pad ) {
	for (int i = 1; i < pad.size(); i++) {
        Takdata van = pad[i-1];
        Takdata naar = pad[i];
        
		Takdata* verbinding = this->geefTakdata(van, naar);
		if ( verbinding != 0 ) {
			*verbinding += pad.geefCapaciteit();
		} else {
			this->voegVerbindingToe(van, naar, pad.geefCapaciteit());
		}
        
		Takdata* terugverbinding = this->geefTakdata(naar, van);
        if ( terugverbinding != 0 ) {
			*terugverbinding -= pad.geefCapaciteit();
		}
	}
}

/** -= operator overloading
 * @param pad met capaciteit
 */
template <class Takdata>
void StroomNetwerk<Takdata>::operator-=( const Pad<Takdata>& pad ) {
	for (int i = 1; i < pad.size(); i++) {
        Takdata van = pad[i-1];
        Takdata naar = pad[i];
		Takdata* verbinding = this->geefTakdata(van, naar);
		*verbinding -= pad.geefCapaciteit();
        
		Takdata* terugverbinding = this->geefTakdata(naar, van);
		if ( terugverbinding != 0 ) {
			*terugverbinding += pad.geefCapaciteit();
		} else {
			this->voegVerbindingToe(naar, van, pad.geefCapaciteit());
		}
	}
}

#endif
