#ifndef _VERGR_H
#define  _VERGR_H

#include <cassert>
#include "pad.h"
#include "graaf.h"

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
					if (it->first==naar && nudiepte+1 > pad.size()){
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

#endif