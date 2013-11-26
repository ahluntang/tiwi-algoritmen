#ifndef _VERGR_H
#define  _VERGR_H

#include <cassert>
#include <queue>
#include <vector>
#include "pad.h"
#include "graaf.h"
#include "limits.h"

template <class T>
class Vergrotendpadzoeker{
public:
	Vergrotendpadzoeker(const GraafMetTakdata<GERICHT,T>& _gr, int _van, int _naar, Pad<T>& _pad):
		pad(_pad), gr(_gr),van(_van),naar(_naar),
		voorganger(gr.aantalKnopen()), bezocht(gr.aantalKnopen(),false){
			pad.clear();
            verwerk(van,0);

			if (pad.size() > 1){
				T capaciteit=*gr.geefTakdata(pad[0],pad[1]);
				for (int i=2; i<pad.size(); i++ ){
					T nucapaciteit=*gr.geefTakdata(pad[i-1],pad[i]);
					if (nucapaciteit<capaciteit)
						capaciteit=nucapaciteit;
					assert(capaciteit > 0);
				}
				pad.zetCapaciteit(capaciteit);
			}
	}
	void verwerk(int knoopnr, int diepte){
		//    std::cerr <<" knoopnr "<<knoopnr  <<" <? "<< gr.aantalKnopen()<<"\n";
		assert(knoopnr < gr.aantalKnopen());
		bezocht[knoopnr]=true;
		const typename GraafMetTakdata<GERICHT,T>::Knoop& kn=gr[knoopnr];
		int nudiepte=diepte+1;
		for (typename GraafMetTakdata<GERICHT,T>::Knoop::const_iterator it=kn.begin();
			it!=kn.end();it++){
				int kind=it->first;
				if (*gr.geefTakdata(knoopnr,kind)> 0){
					if (it->first==naar && nudiepte+1 >= pad.size()){
						voorganger[naar]=knoopnr;
						pad.resize(nudiepte+1);
						int nunr=naar;
						int i=nudiepte;
						while (nunr!=van){
							pad[i--]=nunr;
							nunr=voorganger[nunr];
						}
						assert(i==0);
						assert(nunr==van);
						pad[0]=nunr;
					}
					else if(!bezocht[kind]){
						assert(*gr.geefTakdata(knoopnr,kind)> 0);
						voorganger[kind]=knoopnr;
						verwerk(kind,nudiepte);
					}
				}//if takdata> 0
		}//for
	}

	const GraafMetTakdata<GERICHT,T>& gr;
	Pad<T>& pad;
	std::vector<int> voorganger;
	std::vector<bool> bezocht;
	int van,naar;
};




enum Kleur {
    WIT, GRIJS, ZWART
};


template<class T>
class Kortstepadzoeker {
public:
	Kortstepadzoeker(const GraafMetTakdata<GERICHT ,T>& _q,int _v,int _v2,Pad<T>& _p);
protected:
	virtual void vindpad(int van, int naar);
	const GraafMetTakdata<GERICHT, T>& stroomnetwerk;
    Pad<T>& pad;
    int van,naar;
	std::vector<T> afstanden;
	std::vector<int> ouders;
	std::vector<Kleur> kleuren;
	std::priority_queue<std::pair<T, int>, std::vector< std::pair<T, int> >, std::less< std::pair<T, int> > > knopen;
	void Dijkstra(int van);
	void voegburentoe(int _van);
};


template <class T>
Kortstepadzoeker<T>::Kortstepadzoeker(const GraafMetTakdata<GERICHT ,T>& _q,int _v,int _v2,Pad<T>& _p)
:pad(_p), stroomnetwerk(_q),van(_v),naar(_v2){
    
	pad.clear();
	//std::cout<<"resized:"<<pad.size()<<std::endl;
	vindpad(van,naar);
	int vorige = naar;
	T capaciteit = afstanden[naar];
	while(ouders[vorige] != -1){
		pad.push_back(vorige);
		vorige = ouders[vorige];
	}
	std::reverse(pad.begin(),pad.end());
	pad.zetCapaciteit(capaciteit);
    
	/*std::cout<<"pad: ";
	for(int i = 0; i< pad.size();i++){
		std::cout<<pad[i]<<" ";
	}
	std::cout<<std::endl;*/
}

template<class T>
void Kortstepadzoeker<T>::vindpad(int _van, int _naar) {
	// kortste pad via Dijkstra
	Dijkstra(_van);
    
}


template<class T>
void Kortstepadzoeker<T>::Dijkstra(int _van) {
	// afstandenvector nodig
	// vector met vorige
    
	// afstandenvector initialiseren op oneindig
	afstanden.resize(stroomnetwerk.aantalKnopen(),
                     std::numeric_limits<T>::max());
	ouders.resize(stroomnetwerk.aantalKnopen(),-1);
	kleuren.resize(stroomnetwerk.aantalKnopen(), WIT);
    
	// afstand naar zichzelf is 0, obviously
	afstanden[_van] = 0;
	ouders[_van] = -1;
	voegburentoe(_van);
	while (!knopen.empty()) {
		std::pair<T, int> p = knopen.top();
		if (kleuren[p.second] != ZWART) {
			voegburentoe(p.second);
		}
		knopen.pop();
	}
}

template<class T>
void Kortstepadzoeker<T>::voegburentoe(int _van) {
	std::map<int, int> k = stroomnetwerk[_van];
	T afstand = afstanden[_van];
	kleuren[_van] = ZWART;
	for (std::map<int, int>::iterator it = k.begin(); it != k.end(); it++) {
		int buurnr = it->first;
        
		if (kleuren[buurnr] != ZWART || *(stroomnetwerk.geefTakdata(_van, buurnr)) != 0 ) {
			T gewicht = *(stroomnetwerk.geefTakdata(_van, buurnr));
			T kost = afstand + gewicht;
            
			if (kost < afstanden[buurnr]) {
				std::pair<T, int> p((kost), buurnr);
				knopen.push(p);
				afstanden[buurnr] = kost;
				ouders[buurnr] = _van;
				kleuren[buurnr] = GRIJS;
			}
		}
	}
}



#endif