#ifndef __BRUIJN_H
#define __BRUIJN_H

#include <vector>
#include <map>
#include <queue>
#include <string>
#include "graaf.h"

template <class T>
class DeBruijnreeks : public std::string {
private:
	std::string shift_string(const std::string& v, T data);
    void zoekknoop( int startknoop, int buur, std::vector< std::vector <int> > & knopenrijen,
                    std::map<int,bool> & verbinding_bezocht, std::map<int,int> & knoop_behandeld);
public:
    std::string resultaat;
	DeBruijnreeks(int N,int M); // N= orde , M=alfabet
	
};


/**
 * Genereert een DeBruijnreeks
 * @param N orde van DeBruijnreeks
 * @param M alfabet
 */
template <class T>
DeBruijnreeks<T>::DeBruijnreeks(int N,int M){ // N= orde , M=alfabet
    // initialisatie
    // graaf aanmaken aan de hand van orde N en alfabet M
    std::map<string,bool> behandeld;
	GraafMetKnoopEnTakdata<GERICHT,std::string,T> g;
    char c = '0';
	std::string beginknoopdata;
    beginknoopdata.resize(N);
    for(int i = 0; i < beginknoopdata.size(); i++){
        beginknoopdata[i] = c;
    }
	std::map<std::string,int> knoopnrs; // data => knoopnr
	std::queue<int> knopen;
	int begin = g.voegKnoopToe(beginknoopdata);
    
	knoopnrs[beginknoopdata]=begin;
	knopen.push(begin);
	while(!knopen.empty()){
		int van = knopen.front();
		knopen.pop();
		for(T i=0;i<M;i++){
			std::string new_v=shift_string(*g.geefKnoopdata(van),i);
			if( knoopnrs.count(new_v) > 0 ){ // knoop bestaat al
				g.voegVerbindingToe(van,knoopnrs[new_v],i);
			} 
			else{
				int naar = g.voegKnoopToe(new_v);
				g.voegVerbindingToe(van,naar,i);
				knopen.push(naar);
				knoopnrs[new_v]=naar;
			}
            
        }
	}
    // eulercircuit uit graaf halen
    
    // starten met eerste knoop
    // verbindingen overlopen tot je terug bij dezelfde knoop aankomt
    // volgende verbinding van knoop overlopen.
    // als alle verbindingen van een knoop overlopen zijn, knoop markeren als behandeld
    // volgende niet-behandelde knoop (waarvan verbindingen nog niet bezocht zijn) nemen en herhalen.
    
    // initialisatie
    /*bool knoop_behandeld[g.aantalKnopen()];
    for(int i = 0; i < g.aantalKnopen(); i++){
        knoop_behandeld[i] = false;
    }*/
    std::map<int,int> knoop_behandeld ; // knoopnr, behandeldeverbindingen
    
    /*bool verbinding_bezocht[g.aantalVerbindingen()];
    for(int i = 0; i < g.aantalVerbindingen(); i++){
        verbinding_bezocht[i] = false;
    }*/
    std::map<int, bool> verbinding_bezocht;
    
    // knopen overlopen
    
    std::vector< std::vector<int> > knopenrijen;
    for(int i = 0; i < g.aantalKnopen(); i++){
        std::map<int, int> knoop = g[i]; // knoop: sleutel buurnr ; value: verbindingsnummer
        if(knoop_behandeld[i] < knoop.size()){
            // alle verbindingen van knoop i overlopen.
            std::map<int, int>::const_iterator it = knoop.begin();
            while(it != knoop.end()){
                int startverbinding = it->second;
                if (verbinding_bezocht.count(startverbinding) == 0){
                    verbinding_bezocht[startverbinding] = true;
                    
                    std::vector<int> lus;
                    //lus.push_back(i);
                    // als verbinding al bezocht is zal count groter zijn dan 0
                    // verbinding behandelen: lus maken
                    int buur = it->first;
                    lus.push_back(buur);
                    //zoekknoop(i, buur, knopenrijen, verbinding_bezocht, knoop_behandeld);
                    
                    // zoek vanuit buur de startknoop
                    while( buur != i ){ //TODO: oneindige lus voorkomen
                        std::map<int,int>::const_iterator b_it = g[buur].begin();
                        while(b_it != g[buur].end() && verbinding_bezocht[b_it->second]){
                            b_it++;
                        }
                        verbinding_bezocht[b_it->second] = true;
                        buur = b_it->first;
                        lus.push_back(buur);
                    }
                    knopenrijen.push_back(lus);
                    
                    // als we terug bij startknoop zitten: lus gevonden
                    
                    verbinding_bezocht[it->second] = true;
                }
                it++;
            }
            // alle verbindingen van knoop behandeld
            //knoop_behandeld[i] = true;
        }
    }
    std::string _resultaat;
    for(int i = 0; i < knopenrijen.size(); i++){
        for(int j = 0; j < knopenrijen[i].size(); j++){
            std::string lus = * g.geefKnoopdata(knopenrijen[i][j]);
            std::cout << lus[0] << " ";
            _resultaat += lus[0];
        }
        std::cout << std::endl;
    }
    resultaat = _resultaat;
    
    for(int i = 0; i < knopenrijen.size(); i++){
        for(int j = 0; j < knopenrijen[i].size(); j++){
            std::cout << * g.geefKnoopdata(knopenrijen[i][j]) << " ";
        }
        std::cout << std::endl;
    }
    

}

template<class T>
void DeBruijnreeks<T>::zoekknoop( int startknoop, int buur, std::vector< std::vector <int> > & knopenrijen,
                                 std::map<int,bool> & verbinding_bezocht, std::map<int,int> & knoop_behandeld){
    //std::map<int,int> buurknoop = g[buur];
    
}

template <class T>
std::string DeBruijnreeks<T>::shift_string(const std::string &v, T data){
    //std::cout << v << " ";
	std::string new_v(v);
	for(int i=0;i<v.size()-1;i++){
		new_v[i]=new_v[i+1];
	}
	new_v[v.size()-1]=data + '0';
    //std::cout<< new_v << endl;
	return new_v;
}



#endif 