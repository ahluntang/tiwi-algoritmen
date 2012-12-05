#ifndef __SPLAYBOOM_H
#define __SPLAYBOOM_H
#include <cstdlib>
#include <iostream>
#include <queue>
#include "zoekboom.h"
using std::ostream;



/** Splayboom erft van Zoekboom
 * bij toevoegoperatie wordt het toegevoegde element via splay-operaties
 * tot wortel van de boom gemaakt
 */
template <class Sleutel,class Data>
class Splayboom : public Zoekboom<Sleutel,Data>{
public:
	// override function Zoekboom
	virtual void voegtoe(const Sleutel& sl,const Data& data);

};

/** toevoegfunctie van Splayboom, met splay-operaties
 * @param sl sleutel
 * @param data gegeven dat in knoop wordt opgeslagen
 */
template <class Sleutel,class Data>
void Splayboom<Sleutel,Data>::voegtoe(const Sleutel& sl,const Data& data){
	    Binboom<Sleutel,Data>* plaats;
	    Binknoop<Sleutel,Data>* ouder;
	    zoekplaats(sl,plaats,ouder);
	    if (plaats->k == 0){
	        plaats->k=new Binknoop<Sleutel,Data>(sl,data);
	        plaats->k->ouder=ouder;
	    }

	    // splay operaties

	    //tot aan wortel naar boven roteren
	    //1: ouder (p) van c is wortel -> ouder heeft geen ouder
	    //2: c heeft grootouder (g), met p linkerkind van g
	    //2.a: c is rechterkind van p -> zig-zag
	    //2.b: c is linkerkind van p -> zig-zig

	    Binknoop<Sleutel, Data>* kind = plaats->k;
	    while(kind != this->debinboom.k){
	        ouder = kind->ouder;

	        bool kind_links = true;
	        if(ouder->rechts.k == kind)
	            kind_links = false;

	        //geval 1: ouder is wortel
	        if(ouder == this->debinboom.k){
	        	this->debinboom.roteer(!kind_links);
	        }

	        //geval 2: kind heeft grootouder
	        else{
	            Binknoop<Sleutel, Data>* grootouder = ouder->ouder;
	            Binboom<Sleutel, Data>* grootouderb = &(this->debinboom);
	            //grootouder is geen wortel -> controle of grooutouder links of rechts kind van overgrootouder is
	            if(grootouder->ouder != 0){
	                grootouderb = (grootouder->ouder->links.k == grootouder)?
	                        &(grootouder->ouder->links): &(grootouder->ouder->rechts);
	            }

	            bool ouder_links = true;
	            Binboom<Sleutel, Data>* ouderb = &(grootouder->links);
	            if(grootouder->rechts.k == ouder){
	                ouder_links = false;
	                ouderb = &(grootouder->rechts);
	            }

	            if(kind_links == ouder_links){
	                //2.b
	            	// opmerking: bij roteren blijven de bomen op dezelfde plaats staan in de splayboom
	            	// het zijn de knopen die verplaatst worden
	            	// na eerste rotatie rond grootouderb zal knoop van ouder bovenaan staan, onder de boom grootouderb
	            	// tweede rotatie is rond ouder, dus tweede rotatie moet ook op boom grootouderb gebeuren
	                grootouderb->roteer(!ouder_links);
	                grootouderb->roteer(!kind_links);
	            }else{
	                //2.a
	                ouderb->roteer(!kind_links);
	                grootouderb->roteer(!ouder_links);
	            }
	        }
	    }
	}
#endif
