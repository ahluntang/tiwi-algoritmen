#ifndef __STROOMNET_H
#define __STROOMNET_H
#include "graaf.h"
#include <cassert>
#include <iostream>
using std::vector;
using std::ostream;
#include <queue>
using std::queue;
using std::priority_queue;
#include <stack>
using std::stack;
#include <map>
using std::map;

typedef map<int,int> Knoop;
typedef Knoop::iterator iter;

template< class T >
class Verbinding{
public:
	Verbinding(int _begin, int _eind, T _capacity):begin(_begin),eind(_eind),capacity(_capacity){}
	int begin, eind;
	T capacity;	
	bool operator<(const Verbinding<T> v) const{
		return (capacity < v.capacity);
	}
};

template< class T >
class Pad:public std::vector< int >{
public:
    T geefCapaciteit() const{
        return capaciteit;
    }
    void zetCapaciteit(const T& _capaciteit){
        capaciteit=_capaciteit;
    }
friend ostream& operator<<(ostream& os, const Pad& p){
    os<<"Capaciteit= "<<p.capaciteit<<" :: ";
    if (p.size() > 0){
        os<<p[0];
    }
    for (int i=1; i<p.size(); i++ ){
        os<<"->"<<p[i];
    }
    os<<"\n";
}
protected:
    T capaciteit;
};
/**********************************************************************

   Class:Vergrotendpadzoeker
   
   beschrijving: Methodeklasse die, gegeven een stroomnetwerk,
                 en vergrotend pad teruggeeft.
                 van en naar zijn de knoopnummers van bron en doel.

   
***************************************************************************/
template <class T>
class Vergrotendpadzoeker{
public:
    Vergrotendpadzoeker(const GraafMetTakdata<GERICHT,T>& stroomnetwerk, int van, int naar, Pad<T>& pad);
protected:
    virtual void foo(int t, int x);
    const GraafMetTakdata<GERICHT,T>& q;
    Pad<T>& p;
    vector<int> l;
    vector<bool> visited;
    int v,v2;
};

template <class T>
Vergrotendpadzoeker<T>::Vergrotendpadzoeker(const GraafMetTakdata<GERICHT ,T>& _q,int _v,int _v2,Pad<T>& _p):
                    p(_p), q(_q),v(_v),v2(_v2),
                    l(q.aantalKnopen()), visited(q.aantalKnopen(),false){
    p.clear();
    assert(v != v2);
    foo(v,0);
    assert(p.size()!=1);
    if (p.size() > 1){
        T g=*q.geefTakdata(p[0],p[1]);
        for (unsigned int i=2; i<p.size(); i++ ){
            T ychg=*q.geefTakdata(p[i-1],p[i]);
            if (ychg<g)
                g=ychg;
        }
        p.zetCapaciteit(g);
    }
}

template <class T>
void Vergrotendpadzoeker<T>::foo(int t,int x){
    visited[t]=true;
	//a = knoop met index t
    const typename GraafMetTakdata<GERICHT,T>::Knoop& knoop=q[t];
    unsigned int distance=x+1;
    for (typename GraafMetTakdata<GERICHT,T>::Knoop::const_iterator it=knoop.begin();it!=knoop.end();it++){
		//u = buurknoop
        unsigned int buur=it->first;
		//controle op niet negativiteit van gewichten
        if (*q.geefTakdata(t,buur)> 0){
			//indien eindbestemming bereikt en aantal doorlopen knopen is groter dan huidig pad
            if (it->first==v2 && distance+1 > p.size()){
                l[v2]=t;
                p.resize(distance+1);
                int ychf=v2;
                int i=distance;
                while (ychf!=v){
                    p[i--]=ychf;
                    ychf=l[ychf];
                }
                p[0]=ychf;
            }
            else if(!visited[buur]){
                l[buur]=t;
                foo(buur,distance);
            }
        }
    }
}

/*****************************************************************************


******************************************************************************/


template <class T>
class Kortstepadzoeker{
public:
    Kortstepadzoeker(const GraafMetTakdata<GERICHT,T>& stroomnetwerk, int van, int naar, Pad<T>& pad);
protected:
    virtual void zoekPad(int t, int x);
    const GraafMetTakdata<GERICHT,T>& q;
    Pad<T>& p;
    int v,v2;
    vector<int> terugweg;
    vector<bool> visited;
};


template <class T>
Kortstepadzoeker<T>::Kortstepadzoeker(const GraafMetTakdata<GERICHT ,T>& _q,int _v,int _v2,Pad<T>& _p):
                    p(_p), q(_q),v(_v),v2(_v2),terugweg(q.aantalKnopen()), visited(q.aantalKnopen(),false){
    p.clear();
	//bron =/= bestemming
    assert(v != v2);
    zoekPad(v,0);
	//er is een pad gevonden
    assert(p.size()!=1);
    if (p.size() > 1){
        T minCapaciteit=*q.geefTakdata(p[0],p[1]);
        for (unsigned int i=2; i<p.size(); i++ ){
            T lokaleCapaciteit=*q.geefTakdata(p[i-1],p[i]);
            if (lokaleCapaciteit<minCapaciteit)
                minCapaciteit=lokaleCapaciteit;
        }
        p.zetCapaciteit(minCapaciteit);
    }
}

template <class T>
void Kortstepadzoeker<T>::zoekPad(int t,int x){
	//t = index van ontwikkelende knoop
	//x = 'afstand' tot knoop met index t
	visited[t]=true;
	//a = knoop met index t
    const typename GraafMetTakdata<GERICHT,T>::Knoop& knoop=q[t];
    unsigned int distance=x+1;
    for (typename GraafMetTakdata<GERICHT,T>::Knoop::const_iterator it=knoop.begin();it!=knoop.end();it++){
		//u = buurknoop
        unsigned int buur=it->first;
		//controle op niet negativiteit van gewichten
        if (*q.geefTakdata(t,buur)> 0){
			//indien eindbestemming bereikt en aantal doorlopen knopen is kleiner dan huidig (vergrotend) pad
			if (it->first==v2 && (p.empty() || distance+1 < p.size())){
                terugweg[v2]=t;
                p.resize(distance+1);
                int deelbestemming=v2;
                int i=distance;
                while (deelbestemming!=v){
                    p[i--]=deelbestemming;
                    deelbestemming=terugweg[deelbestemming];
                }
                p[0]=deelbestemming;
            }
            else if(!visited[buur]){
                terugweg[buur]=t;
                zoekPad(buur,distance);
            }
        }
    }
}

/*****************************************************************************


******************************************************************************/

template <class T>
class breedstepadzoeker{
	
public:
    breedstepadzoeker(const GraafMetTakdata<GERICHT,T>& stroomnetwerk, int van, int naar, Pad<T>& pad);
protected:
    virtual void zoekPad();
    const GraafMetTakdata<GERICHT,T>& q;
    Pad<T>& p;
    int v,v2;
    vector<int> backtrack;
	vector<T> maxCapacity;
    vector<bool> visited;
	priority_queue< Verbinding<T> > toDevelop;
};

template <class T>
breedstepadzoeker<T>::breedstepadzoeker(const GraafMetTakdata<GERICHT ,T>& _q,int _v,int _v2,Pad<T>& _p):
                    p(_p), q(_q),v(_v),v2(_v2),backtrack(q.aantalKnopen()), visited(q.aantalKnopen(),false), maxCapacity(q.aantalKnopen()){
    p.clear();
	p.zetCapaciteit(0);
    assert(v != v2);
    zoekPad();
}

template <class T>
void breedstepadzoeker<T>::zoekPad(){
	Knoop k = q[v];
	iter it;
	for (it = k.begin(); it != k.end(); it++){
		Verbinding<T> conn(v, it->first, *q.geefTakdata(v,it->first));
		if (conn.capacity > 0){
			toDevelop.push(conn);
		}
	}
	visited[v] = true;
	while(!toDevelop.empty()){
		Verbinding<T> conn = toDevelop.top();
		toDevelop.pop();
		if (!visited[conn.eind]){
			backtrack[conn.eind] = conn.begin;
			if(maxCapacity[conn.begin] == 0){
				maxCapacity[conn.eind] = conn.capacity;
			} else {
				maxCapacity[conn.eind] = (maxCapacity[conn.begin] < conn.capacity ? maxCapacity[conn.begin] : conn.capacity);
			}
			Knoop k = q[conn.eind];
			iter it;
			for (it = k.begin(); it != k.end(); it++){
				Verbinding<T> conn(conn.eind, it->first, *q.geefTakdata(conn.eind,it->first));
				if (conn.capacity > 0){
					toDevelop.push(conn);
				}
			}
			visited[conn.eind] = true;
		}
	}
	if (maxCapacity[v2] > 0) {
		Pad<T> inverse;
		int i = v2;
		while (i != v){
			inverse.push_back(i);
			i = backtrack[i];
		}
		inverse.push_back(v);
		p.resize(inverse.size());
		int j = 0;
		for (i = inverse.size() - 1; i >= 0; i--){
			p[i] = inverse[j];
			j++;
		}
		p.zetCapaciteit(maxCapacity[v2]);
	}
}


/**********************************************************************

   Class: Stroomnetwerk
   
   beschrijving: Een stroomnetwerk gaat uit van een gewogen gerichte graaf
                 die in de constructor wordt opgegeven
   
***************************************************************************/

template <class T>//T = takdata
class Stroomnetwerk:public GraafMetTakdata<GERICHT, T >{
public:
//Copyconstructor. Let op: Graaf<GERICHT>(gr) moet toegevoegd,
//anders roept de copyconstructor van GraafMetTakdata de defaultconstructor
//van Graaf op en krijgen we een lege graaf.
Stroomnetwerk(const GraafMetTakdata<GERICHT, T>& gr):
                    Graaf<GERICHT>(gr),GraafMetTakdata<GERICHT, T>(gr){};


Stroomnetwerk(const GraafMetTakdata<GERICHT, T>& gr, int _van, int _naar, int option):
                    Graaf<GERICHT>(gr.aantalKnopen()),van(_van),naar(_naar), graaf(gr){
	
	capaciteit = 0;
    Stroomnetwerk<T> restnetwerk(gr);
    Pad<T> vergrotendpad;
	zoekPad (restnetwerk, van, naar, vergrotendpad, option);
    while(vergrotendpad.size() !=0 ){
        restnetwerk-=vergrotendpad;
        *this+=vergrotendpad;
		zoekPad (restnetwerk, van, naar, vergrotendpad, option);
    }
}
T geefCapaciteit(){
	return capaciteit;
}

Stroomnetwerk &operator-=(const Pad<T> pad){
	for (unsigned int i = 0; i < pad.size() - 1; i++){
		int *data = this->geefTakdata(pad[i],pad[i+1]);
		*data -= pad.geefCapaciteit();
		int verbinding = this->verbindingsnummer(pad[i+1],pad[i]);
		if (verbinding == -1){
			this->voegVerbindingToe(pad[i+1],pad[i],0);
		}
		data = this->geefTakdata(pad[i+1],pad[i]);
		*data += pad.geefCapaciteit();
	} 
	return *this;
}

Stroomnetwerk &operator+=(const Pad<T> pad){
	for (unsigned int i = 0; i < pad.size() - 1; i++){		
		int verbinding = graaf.verbindingsnummer(pad[i],pad[i+1]);
		if (verbinding != -1){
			verbinding = this->verbindingsnummer(pad[i],pad[i+1]);
			if (verbinding == -1){
				this->voegVerbindingToe(pad[i],pad[i+1],0);
			}
			int *data = this->geefTakdata(pad[i],pad[i+1]);
			*data += pad.geefCapaciteit();
			verbinding = this->verbindingsnummer(pad[i],pad[i+1]);
		} else {
			verbinding = this->verbindingsnummer(pad[i+1],pad[i]);
			if (verbinding != -1){
				int *data = this->geefTakdata(pad[i+1],pad[i]);
				*data -= pad.geefCapaciteit();
				if (*data == 0){
					this->verwijderVerbinding(pad[i+1],pad[i]);
				}
			}
		}
	} 
	this->capaciteit += pad.geefCapaciteit();
	return *this;
}

protected:
int van,naar;
T capaciteit;
Graaf<GERICHT> graaf;
private:
	void zoekPad (Stroomnetwerk<T> &restnetwerk,int van,int naar,Pad<T> &vergrotendpad,int option);
};

template <class T>
void Stroomnetwerk<T>::zoekPad(Stroomnetwerk<T> &restnetwerk,int van,int naar,Pad<T> &vergrotendpad,int option){
	if (option == 0){
		Vergrotendpadzoeker<T> vg(restnetwerk,van, naar, vergrotendpad);
	} else if (option == 1){
		Kortstepadzoeker<T> vg(restnetwerk,van, naar, vergrotendpad);
	} else {
		breedstepadzoeker<T> vg(restnetwerk,van, naar, vergrotendpad);
	}
}

#endif
