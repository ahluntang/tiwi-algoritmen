/*
 * VergrotendPadZoeker.h
 *
 *  Created on: Nov 19, 2012
 *      Author: ahluntang
 */

#ifndef VERGROTENDPADZOEKER_H_
#define VERGROTENDPADZOEKER_H_

#include "graaf.h"
#include <cassert>
#include "Pad.h"

using std::vector;

/**********************************************************************

   Class:Vergrotendpadzoeker

   beschrijving: Methodeklasse die, gegeven een stroomnetwerk,
                 en vergrotend pad teruggeeft.
                 van en naar zijn de knoopnummers van bron en doel.


***************************************************************************/
template <class T>
class Vergrotendpadzoeker {
public:
    Vergrotendpadzoeker(const GraafMetTakdata<GERICHT,T>& stroomnetwerk, int van, int naar, Pad<T>& pad);
protected:
    virtual void vindpad(int _van, int _naar);
    const GraafMetTakdata<GERICHT,T>& stroomnetwerk;
    Pad<T>& pad;
    vector<int> l;
    vector<bool> m;
    int van,naar;
};


template <class T>
Vergrotendpadzoeker<T>::Vergrotendpadzoeker(const GraafMetTakdata<GERICHT ,T>& _q,int _v,int _v2,Pad<T>& _p):
                    pad(_p), stroomnetwerk(_q),van(_v),naar(_v2),
                    l(stroomnetwerk.aantalKnopen()), m(stroomnetwerk.aantalKnopen(),false){
    pad.clear();
    assert(van != naar);
    vindpad(van,0);
    assert(pad.size()!=1);
    if (pad.size() > 1){
        T g=*stroomnetwerk.geefTakdata(pad[0],pad[1]);
        for (int i=2; i<pad.size(); i++ ){
            T ychg=*stroomnetwerk.geefTakdata(pad[i-1],pad[i]);
            if (ychg<g)
                g=ychg;
        }
        pad.zetCapaciteit(g);
    }
}


template <class T>
void Vergrotendpadzoeker<T>::vindpad(int _van,int _naar){
    m[_van]=true;
    const typename GraafMetTakdata<GERICHT,T>::Knoop& a=stroomnetwerk[_van];
    int ychx=_naar+1;
    for (typename GraafMetTakdata<GERICHT,T>::Knoop::const_iterator it=a.begin();
                it!=a.end();it++){
        int u=it->first;
        if (*stroomnetwerk.geefTakdata(_van,u)> 0){
            if (it->first==naar && ychx+1 > pad.size()){
                l[naar]=_van;
                pad.resize(ychx+1);
                int ychf=naar;
                int i=ychx;
                while (ychf!=van){
                    pad[i--]=ychf;
                    ychf=l[ychf];
                }
                pad[0]=ychf;
            }
            else if(!m[u]){
                l[u]=_van;
                vindpad(u,ychx);
            }
        }
    }
}



#endif /* VERGROTENDPADZOEKER_H_ */
