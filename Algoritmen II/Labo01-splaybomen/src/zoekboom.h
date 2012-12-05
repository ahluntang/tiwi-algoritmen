#ifndef __ZOEKBOOM_H
#define __ZOEKBOOM_H
#include <cstdlib>
#include <iostream>
#include <queue>
#include <math.h>
using namespace std;
using std::ostream;
/**********************************************************************

 Klasse: Binboom met Binknoop: binaire boom

 beschrijving: Domme klasse om de gegevens van een boom te bevatten
 Omdat ze enkel in een wrapper wordt gebruikt, heeft ze
 alles publiek staan. Ze mag dan ook nooit buiten een
 wrapper gebruikt worden!

 ***************************************************************************/

template<class Sleutel, class Data>
class Binknoop;

template<class Sleutel, class Data>
class Binboom {
public:
	Binboom<Sleutel, Data>() :
			k(0) {
	}
	~Binboom<Sleutel, Data>() {
		delete k;
	}
	int diepte() const {
		if (k == 0)
			return 0;
		else
			return max(k->links.diepte(), k->rechts.diepte()) + 1;
	}
	;
	void schrijf(ostream&) const;
	void schrijf(ostream& os, Binknoop<Sleutel, Data>* kn) const {
		if (kn != 0)
			os << "(" << kn->sl << "," << kn->data << ")";
		else
			os << "(,)";
	}
	void kopieerstructuur(Binboom<Sleutel,Data>&);
	void inorder(Binboom<Sleutel,Data>&b,vector<Sleutel>& sleutels);
	void controle_inorder(Binboom<Sleutel,Data>&b,const vector<Sleutel>& sleutels, int&,bool&);
	void roteer(bool links);
//pointer naar wortelknoop
	Binknoop<Sleutel, Data>* k;
//     Binknoop* voorloper(Binknoop*);
protected:
	void kopieerstructuur_topdown(Binboom<Sleutel,Data>& b,Binboom<Sleutel,Data>& positie);
	void kopieerstructuur_bottomup(Binboom<Sleutel,Data>& b,Binboom<Sleutel,Data>& positie);
};
template<class Sleutel, class Data>
void Binboom<Sleutel,Data>::kopieerstructuur(Binboom<Sleutel,Data>& b){
	vector<Sleutel> sleutels;
	inorder(*this,sleutels);
	int positie = 0;
	bool gelijk = true;
	controle_inorder(b, sleutels,positie,gelijk);
	if(gelijk){
		//cout<<"gelijk"<<endl;
		kopieerstructuur_bottomup(b,*this);
	} else {
		//cout<<"fail"<<endl;
	}
}
template<class Sleutel, class Data>
void Binboom<Sleutel,Data>:: kopieerstructuur_bottomup(Binboom<Sleutel,Data>& b, Binboom<Sleutel,Data> & p){
    Binboom<Sleutel,Data>* plaats;
    Binknoop<Sleutel,Data>* ouder;

    //zoeken
	plaats = &p;
	ouder = 0;
	while (plaats->k != 0 && plaats->k->sl != b.k->sl) {
		ouder = plaats->k;
		if (b.k->sl < plaats->k->sl)
			plaats = &(plaats->k->links);
		else
			plaats = &(plaats->k->rechts);
	}

	//cout<<"p: "<<p.k->sl<<" b: "<<b.k->sl<<endl;
    // splay operaties

    //tot aan wortel naar boven roteren
    //1: ouder (p) van c is wortel -> ouder heeft geen ouder
    //2: c heeft grootouder (g), met p linkerkind van g
    //2.a: c is rechterkind van p -> zig-zag
    //2.b: c is linkerkind van p -> zig-zig

    Binknoop<Sleutel, Data>* kind = plaats->k;
    while(p.k->sl != b.k->sl){
        ouder = kind->ouder;

        bool kind_links = true;
        if(ouder->rechts.k == kind)
            kind_links = false;

        //geval 1: ouder is wortel
        if(ouder == p.k){
        	p.roteer(!kind_links);
        }

        //geval 2: kind heeft grootouder
        else{
            Binknoop<Sleutel, Data>* grootouder = ouder->ouder;
            Binboom<Sleutel, Data>* grootouderb = &(p);
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

	//cout<<"NA: p: "<<p.k->sl<<" b: "<<b.k->sl<<endl;
	if(b.k->links.k !=0)
		kopieerstructuur_bottomup(b.k->links,p.k->links);

	if(b.k->rechts.k !=0)
		kopieerstructuur_bottomup(b.k->rechts,p.k->rechts);
}

template<class Sleutel, class Data>
void Binboom<Sleutel,Data>:: kopieerstructuur_topdown(Binboom<Sleutel,Data>& b, Binboom<Sleutel,Data> & p){
	if(p.k !=0 && b.k !=0){
		while(p.k->sl != b.k->sl){
			cout<<"p: "<<p.k->sl<<" b: "<<b.k->sl<<endl;
			if(p.k->sl < b.k->sl){
				p.roteer(true);
			} else if(p.k->sl > b.k->sl){
				p.roteer(false);
			}
		}
		kopieerstructuur_topdown(b.k->links,p.k->links);
		kopieerstructuur_topdown(b.k->rechts,p.k->rechts);
	}
}

template<class Sleutel, class Data>
void Binboom<Sleutel,Data>::controle_inorder(Binboom<Sleutel,Data>&b,const vector<Sleutel>& sleutels, int& positie, bool &gelijk){
	if(gelijk && b.k != 0 ){
		controle_inorder(b.k->links,sleutels,positie,gelijk);
		if(sleutels[positie]==b.k->sl){
			positie++;
		} else {
			gelijk=false;
		}
		controle_inorder(b.k->rechts,sleutels,positie,gelijk);
	}
}

template<class Sleutel, class Data>
void Binboom<Sleutel,Data>::inorder(Binboom<Sleutel,Data>&b,vector<Sleutel>& sleutels){
	if(b.k != 0 ){
		inorder(b.k->links,sleutels);
		sleutels.push_back(b.k->sl);
		inorder(b.k->rechts,sleutels);
	}
}

template<class Sleutel, class Data>
class Binknoop {
public:
	Sleutel sl;
	Data data;
	Binknoop<Sleutel, Data>* ouder;
	Binboom<Sleutel, Data> links, rechts;
	Binknoop() :
			ouder(0) {
	}
	Binknoop(const Sleutel& _sl, const Data& _data) :
			ouder(0), sl(_sl), data(_data) {
	}
};

/**********************************************************************

 klasse: Zoekboom

 beschrijving: Dit is een wrapper voor een Binboom,
 die ervoor zorgt dat de sleutels in de Binboom
 op volgorde staan

 ***************************************************************************/

template<class Sleutel, class Data>
class Zoekboom {
public:
	virtual void voegtoe(const Sleutel&, const Data&);
//volgende functie doet niets als er geen knoop is met het gegeven Sleutel
	virtual void verwijder(const Sleutel&);
//geef pointer naar data horend bij een sleutel
	virtual Data* zoekdata(const Sleutel&);
	int diepte() const {
		return debinboom.diepte();
	}
	;
	void kopieerstructuur(Binboom<Sleutel,Data>&);
	friend ostream& operator<<(ostream& os, Zoekboom<Sleutel, Data>& b) {
		b.debinboom.schrijf(os);
		return os;
	}
	;
	Binboom<Sleutel,Data>* binboom();
protected:
//zoekplaats: geeft adres van boom waaraan knoop hangt, of zou moeten hangen
//en adres van de ouder.
	virtual void zoekplaats(const Sleutel&, Binboom<Sleutel, Data>*&,
			Binknoop<Sleutel, Data>*&);
//De binaire boom die de data bevat
	Binboom<Sleutel, Data> debinboom;
//geeft de voorganger. Veronderstelt dat de linkerboom onder de knoop niet leeg is
	Binboom<Sleutel, Data>* ondervoorganger(Binknoop<Sleutel, Data>*);
};

template<class Sleutel, class Data>
void Zoekboom<Sleutel,Data>::kopieerstructuur(Binboom<Sleutel,Data>& b){
	debinboom.kopieerstructuur(b);
}


template<class Sleutel, class Data>
Binboom<Sleutel,Data>* Zoekboom<Sleutel,Data>::binboom(){
	return &debinboom;
}

template<class Sleutel, class Data>
void Binboom<Sleutel, Data>::roteer(bool links) {
	Binknoop<Sleutel, Data>* op;
	Binknoop<Sleutel, Data>* neer = k;
	if (links) {
		op = k->rechts.k;
		neer->rechts.k = op->links.k;
		if (op->links.k != 0)
			op->links.k->ouder = neer;
		op->links.k = neer;
	} else {
		op = k->links.k;
		neer->links.k = op->rechts.k;
		if (op->rechts.k != 0)
			op->rechts.k->ouder = neer;
		op->rechts.k = neer;
	}
	k = op;
	op->ouder = neer->ouder;
	neer->ouder = op;
}

template<class Sleutel, class Data>
void Zoekboom<Sleutel, Data>::zoekplaats(const Sleutel& sl,
		Binboom<Sleutel, Data>*& plaats, Binknoop<Sleutel, Data>*& ouder) {
	plaats = &debinboom;
	ouder = 0;
	while (plaats->k != 0 && plaats->k->sl != sl) {
		ouder = plaats->k;
		if (sl < plaats->k->sl)
			plaats = &(plaats->k->links);
		else
			plaats = &(plaats->k->rechts);
	}
}

template<class Sleutel, class Data>
Data* Zoekboom<Sleutel, Data>::zoekdata(const Sleutel& sl) {
	Binboom<Sleutel, Data>* plaats;
	Binknoop<Sleutel, Data>* ouder;
	zoekplaats(sl, plaats, ouder);
	if (plaats->k == 0)
		return 0;
	else
		return &(plaats->k->data);
}

template<class Sleutel, class Data>
void Zoekboom<Sleutel, Data>::voegtoe(const Sleutel& sl, const Data& data) {
	Binboom<Sleutel, Data>* plaats;
	Binknoop<Sleutel, Data>* ouder;
	zoekplaats(sl, plaats, ouder);
	if (plaats->k == 0) {
		plaats->k = new Binknoop<Sleutel, Data>(sl, data);
		plaats->k->ouder = ouder;
	}
}

template<class Sleutel, class Data>
void Zoekboom<Sleutel, Data>::verwijder(const Sleutel& sl) {
	Binboom<Sleutel, Data>* plaats;
	Binknoop<Sleutel, Data>* ouder;
	zoekplaats(sl, plaats, ouder);
	Binknoop<Sleutel, Data>* weg = plaats->k;
	if (plaats->k != 0) {
		if (weg->links.k == 0) {
			plaats->k = weg->rechts.k;
			if (plaats->k != 0)
				plaats->k->ouder = ouder;
			weg->rechts.k = 0;
			delete weg;
		} else if (weg->rechts.k == 0) {
			plaats->k = weg->links.k;
			if (plaats->k != 0)
				plaats->k->ouder = ouder;
			weg->links.k = 0;
			delete weg;
		} else {
			//vervangen door voorganger
			Binboom<Sleutel, Data>* voorlink = ondervoorganger(weg);
			Binknoop<Sleutel, Data>* voorganger = voorlink->k;
			if (voorlink != &(weg->links)) {
				voorlink->k = voorganger->links.k;
				if (voorganger->links.k != 0)
					voorganger->links.k->ouder = voorganger->ouder;
				//geen test voor volgende twee: deze bestaan!
				plaats->k = voorganger;
				voorganger->ouder = ouder;
				voorganger->links.k = weg->links.k;
				voorganger->links.k->ouder = voorganger;
				voorganger->rechts.k = weg->rechts.k;
				voorganger->rechts.k->ouder = voorganger;
			} else {
				voorganger->rechts.k = weg->rechts.k;
				weg->rechts.k->ouder = voorganger;
				voorganger->ouder = weg->ouder;
				plaats->k = voorganger;
			}
			weg->links.k = 0;
			weg->rechts.k = 0;
			delete weg;
		}
	}
}

template<class Sleutel, class Data>
Binboom<Sleutel, Data>* Zoekboom<Sleutel, Data>::ondervoorganger(
		Binknoop<Sleutel, Data>* kn) {
	Binboom<Sleutel, Data>* onder = &(kn->links);
	while (onder->k->rechts.k != 0)
		onder = &(onder->k->rechts);
	return onder;
}

template<class Sleutel, class Data>
void Binboom<Sleutel, Data>::schrijf(ostream& os) const {
	if (k != 0) {
		std::queue<Binknoop<Sleutel, Data>*,
				std::deque<Binknoop<Sleutel, Data>*> > q;
		q.push(k);
		while (!q.empty()) {
			Binknoop<Sleutel, Data>* nu = q.front();
			schrijf(os, nu);
			os << " links: ";
			schrijf(os, nu->links.k);
			os << " rechts: ";
			schrijf(os, nu->rechts.k);
			os << " ouder: ";
			schrijf(os, nu->ouder);
			os << std::endl;
			if (nu->links.k != 0)
				q.push(nu->links.k);
			if (nu->rechts.k != 0)
				q.push(nu->rechts.k);
			q.pop();
		}
	} else {
		schrijf(os, k);
	}
}

#endif

