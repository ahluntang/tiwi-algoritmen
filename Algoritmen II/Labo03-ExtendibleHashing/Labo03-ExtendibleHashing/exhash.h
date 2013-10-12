//
//  exhas.h
//  Extendible hashing
//
//  Created by Robrecht Plaisier on 07/10/13.
//  Copyright (c) 2013 Robrecht Plaisier. All rights reserved.
//

#ifndef Extendible_hashing_exhas_h
#define Extendible_hashing_exhas_h
#include <cstdlib>
#include <iostream>
#include <queue>
#include "Schijfpagina.h"

template <class T,class D>
class Exhash{
    friend class Schijfpagina<T,D>;
    friend ostream& operator<<(ostream& os,Exhash& k){
        k.schrijf(os);
        return os;
        };
    
    void schrijf(ostream& os)
    {
        Schijfpagina<T, D> * laatste = 0;
        int aantalvorige= 0;
        for (int i=0; i<grootte; i++)
        {
            if(tab[i] == laatste){
                aantalvorige++;
            } else {
                os << "aantal:" << aantalvorige <<endl;
                os << "pagina " << i << ":" << endl;
                os << *(tab[i]);
                aantalvorige = 1;
                laatste = tab[i];
            }
        }
        os << endl;
    }

private: Schijfpagina<T,D>** tab;
private: int maxk;
private: int grootte;//grootte tabel; volgt uit maxk, maar alla
private: int aantalSleutels;
public: Exhash():maxk(0),grootte(1),aantalSleutels(0){
    tab=new Schijfpagina<T,D>*[1];
    tab[0]=new Schijfpagina<T,D>;
};
    
public: ~Exhash()
    {
        
    }
    
    //index geeft de index in de tabel. kan als voorbeeld dienen
    //voor schuifoperaties
private: unsigned int index(const T& sleutel) const{
    if (maxk==0)//computer weigert 32 plaatsen shift
        return 0;
    else{
        unsigned int q=sleutel.geef_exhashindex();
        //unsigned int q=sleutel;
        return (q>>(AANTBITS-maxk));
    }
};
    
private: void verdubbel()
    {
        Schijfpagina<T,D>** tempTab = new Schijfpagina<T,D>*[grootte* 2];
        for (unsigned int i = 0; i < grootte; i++)
        {
            tempTab[i*2]    = tab[i];
            tempTab[i*2+1]  = tab[i];
            
        }
        Schijfpagina<T,D>** teVerwijderenTab = tab;
        tab = tempTab;
        delete teVerwijderenTab;
        grootte *= 2;
        maxk++;

    }
    
public:
    void voegtoe(const T& sleutel,const D& data)
    {
        
        unsigned int gevondenIndex = index(sleutel);
        //cout << gevondenIndex << endl;
        //cout << &sleutel << endl;
        Schijfpagina<T,D>  * gevondenPagina = tab[gevondenIndex];
        if(gevondenPagina->aantalKnopen == PAGINAGROOTTE)
        {
            Schijfpagina<T,D> * rechts = new Schijfpagina<T,D>();
            //cout<<"gevonden: voor splitsen:";
            //cout<<*rechts<<endl;
            gevondenPagina->splits(rechts);
            
            //cout<<"gevonden: na splitsen:";
            //cout<<*rechts<<endl;
            if (maxk < gevondenPagina->aantalBitsInHashwaarde)
            {
                verdubbel();
                gevondenIndex *= 2;
            }
            tab[gevondenIndex+1]  = rechts;
            
            voegtoe(sleutel, data);
            
            //cout<< *tab[gevondenIndex+1]<<endl;
        }
        gevondenPagina->voegtoe(sleutel, data);
        
    }
    
    // verwijder: lege pagina's blijven bestaan.
public: void verwijder(const T& sleutel){
    unsigned int gevondenIndex = index(sleutel);
    cout << gevondenIndex << endl;
    Schijfpagina<T,D>  * gevondenPagina = tab[gevondenIndex];
    cout<<"pagina " << gevondenIndex << " voor verwijderen:" << *gevondenPagina << endl;
    gevondenPagina->verwijder(sleutel);
    cout<<"pagina " << gevondenIndex << " na verwijderen:" << *gevondenPagina << endl;
}
    
public: D* zoekData(const T& sleutel);
};

#endif
