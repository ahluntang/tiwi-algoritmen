//
//  Schijfpagina.h
//  Extendible hashing
//
//  Created by Robrecht Plaisier on 07/10/13.
//  Copyright (c) 2013 Robrecht Plaisier. All rights reserved.
//

#ifndef Extendible_hashing_Schijfpagina_h
#define Extendible_hashing_Schijfpagina_h
#include <iostream>
using std::ostream;
using std::cout;
using std::endl;

template <class T,class D>
class Exhash;
/*
 Volgende code is correct, maar geeft problemen; daarom worden
 de constanten buiten de klasse gedefinieerd.
 
 template <class T,class D>
 class Schijfpagina;
 
 template <class T,class D>
 const unsigned int Schijfpagina<T,D>::EEN=1;
 
 template <class T,class D>
 const int Schijfpagina<T,D>::AANTBITS=sizeof(unsigned int)*8;
 
 template <class T,class D>
 const int Schijfpagina<T,D>::PAGINAGROOTTE=8;
 */
const unsigned int EEN=1;
const int AANTBITS=sizeof(unsigned int)*8;
const int PAGINAGROOTTE=8;
template <class T,class D>
class Schijfpagina{
    //static const unsigned int EEN;
    //static const int PAGINAGROOTTE;
    //static const int AANTBITS;
    friend class Exhash<T,D>;
    friend int main();
    friend ostream& operator<<(ostream& os,Schijfpagina<T,D>& b){
        b.schrijf(os);
        return os;
    };
    
private:
    int aantalKnopen;//aantal dat nu in pagina zit;
    int aantalBitsInHashwaarde;           //aantal bits in hashwaarde;
    unsigned int index;//laatste k bits zijn belangrijk, die daarvoor zijn nul
    
    struct knoop{
        T sleutel;
        D data;
    };
    
    friend ostream& operator<<(ostream& os,knoop& k){
        os << k.sleutel;
        return os;
    };
    //we werken hier rechtstreeks; andere oplossing zou zijn een tabel
    //met pointers naar de eigenlijke waarden bij te houden.
    knoop kn[PAGINAGROOTTE];
    int geefk(){
        return aantalBitsInHashwaarde;
    }
    Schijfpagina():index(0),aantalBitsInHashwaarde(0),aantalKnopen(0){
        /*cout<<"--startconstructor--"<<endl;
        for (int i=0; i<aantalKnopen; i++)
        {
            cout << kn[i] << " ";
        }
        for (int i=aantalKnopen;i<PAGINAGROOTTE;i++)
        {
            cout << "-" << " ";
            
        }
        cout << endl;
        
        cout<<"--eindconstructor--"<<endl;*/
    }
    
    void schrijf(ostream& os)
    {
        for (int i=0; i<aantalKnopen; i++)
        {
            os << kn[i] << " ";
        }
        for (int i=aantalKnopen;i<PAGINAGROOTTE;i++)
        {
            os << "-" << " ";
            
        }
        os << endl;
    }
    
    //de huidige Schijfpagina wordt in twee gesplitst. De nieuwe hashindex is
    //dus een bit langer; *this krijgt de sleutelwaarden met hashindex
    //eindigend op nul. De nieuwe pagina, met hasindex eindigend op 1,
    //wordt aan eenbit gehangen.
    
    void splits(Schijfpagina<T,D>*& eenbit)
    {
        aantalBitsInHashwaarde++;
        int startEindigenOpEen = 0;
        bool eindigdNietOpEen = true;

        unsigned int mask = 1;
        mask = 1 << (AANTBITS - aantalBitsInHashwaarde -1);
        cout << "mask: " << mask << endl;

        while(startEindigenOpEen < aantalKnopen && eindigdNietOpEen)
        {
            eindigdNietOpEen = ((kn[startEindigenOpEen].sleutel.geef_exhashindex() & mask) == 0);
            if(aantalKnopen > 0 &&  eindigdNietOpEen)
            {
                startEindigenOpEen++;
            }
        }
        eenbit->aantalBitsInHashwaarde = aantalBitsInHashwaarde;
        
        for(int i = startEindigenOpEen; i < aantalKnopen; i++)
        {
            eenbit->voegtoe(kn[i].sleutel, kn[i].data);
        }
        
        aantalKnopen = (startEindigenOpEen);
        
    }
    
    bool isVol() const{
        return (aantalKnopen==PAGINAGROOTTE);
    }
    
    void zoek(const T& sleutel,int& plaats, bool& gevonden) const{
        plaats=0;
        while (plaats<aantalKnopen && kn[plaats].sleutel < sleutel)
            plaats++;
        gevonden=(plaats!=aantalKnopen && kn[plaats].sleutel==sleutel);
    }
    
    D* zoekData(const T& sleutel){
        int plaats;
        bool gevonden;
        zoek(sleutel,plaats,gevonden);
        if (gevonden)
            return &(kn[plaats].data);
        else
            return 0;
    }
    
    //deze functie checkt *expliciet niet* of de pagina al vol is
    // dit is de taak van Exhash
    
    void voegtoe(const T& sleutel,const D& data){
        int plaats;
        bool gevonden;
        zoek(sleutel,plaats,gevonden);
        if (!gevonden){
            for (int i=aantalKnopen;i>plaats;i--)
                kn[i]=kn[i-1];
            kn[plaats].sleutel=sleutel;
            kn[plaats].data=data;
            aantalKnopen++;
        }
    }
    
    void verwijder(const T& sleutel){
        int plaats;
        bool gevonden;
        zoek(sleutel,plaats,gevonden);
        if (gevonden){
            aantalKnopen--;
            for (int i=plaats;i<aantalKnopen;i++)
                kn[i]=kn[i+1];
        }
    }
    
    
};

#endif
