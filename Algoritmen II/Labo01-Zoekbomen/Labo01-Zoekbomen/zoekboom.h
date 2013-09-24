/**********************************************************************

   
   beschrijving: Deze code bevat fouten !!!!!!!!!!!!!!!!1
   
***************************************************************************/
#ifndef __ZOEKBOOM_H
#define __ZOEKBOOM_H
#include <cstdlib>
#include <iostream>
#include <queue>
using std::ostream;
/**********************************************************************

   Klasse: Binboom met Binknoop: binaire boom
   
   beschrijving: Domme klasse om de gegevens van een boom te bevatten
                 Omdat ze enkel in een wrapper wordt gebruikt, heeft ze
                 alles publiek staan. Ze mag dan ook nooit buiten een
                 wrapper gebruikt worden!
   
***************************************************************************/

template <class Sleutel,class Data>
class Binknoop;

template <class Sleutel,class Data>
class Binboom{
public:
    Binboom<Sleutel,Data>():k(0){}
     ~Binboom<Sleutel,Data>(){
        delete k;
    }
     int diepte() const{
        if (k==0)
            return 0;
        else
            return max(k->links.diepte(),k->rechts.diepte())+1;
    };
     void schrijf(ostream&) const;
     void schrijf(ostream& os,Binknoop<Sleutel,Data>* kn) const{
        if (kn!=0)
            os<<"("<<kn->sl<<","<<kn->data<<")";
        else
            os<<"(,)";
    }
     void roteer(bool links);
//pointer naar wortelknoop
     Binknoop<Sleutel,Data>* k;
//     Binknoop* voorloper(Binknoop*);
};

template <class Sleutel,class Data>
class Binknoop{
    public:
        Sleutel sl;
        Data data;
        Binknoop<Sleutel,Data>* ouder;
        Binboom<Sleutel,Data> links,rechts;
        Binknoop():ouder(0){}
        Binknoop(const Sleutel& _sl,const Data& _data):ouder(0),sl(_sl),data(_data){}
};

/**********************************************************************

   klasse: Zoekboom
   
   beschrijving: Dit is een wrapper voor een Binboom,
                 die ervoor zorgt dat de sleutels in de Binboom
                 op volgorde staan
   
***************************************************************************/

template <class Sleutel,class Data>
class Zoekboom{
public:
     virtual void voegtoe(const Sleutel&,const Data&);
     virtual void voegtoe(Binknoop<Sleutel,Data> & knoop, const Sleutel&,const Data&);
//volgende functie doet niets als er geen knoop is met het gegeven Sleutel
     virtual void verwijder(const Sleutel&);
//geef pointer naar data horend bij een sleutel
     virtual Data* zoekdata(const Sleutel&);
     int diepte() const{return deBinboom.diepte();};
     friend ostream& operator<<(ostream& os,Zoekboom<Sleutel,Data>& b){
        b.deBinboom.schrijf(os);
        return os;
    };
protected:
//zoekplaats: geeft adres van boom waaraan knoop hangt, of zou moeten hangen
//en adres van de ouder.
     virtual void zoekplaats(const Sleutel&,Binboom<Sleutel,Data>*&,Binknoop<Sleutel,Data>*&);
//De binaire boom die de data bevat
     Binboom<Sleutel,Data> deBinboom;
//geeft de voorganger. Veronderstelt dat de linkerboom onder de knoop niet leeg is
     Binboom<Sleutel,Data>* ondervoorganger(Binknoop<Sleutel,Data>*);
};

template <class Sleutel,class Data>
void Binboom<Sleutel,Data>::roteer(bool links){
    Binknoop<Sleutel,Data>* op;
    Binknoop<Sleutel,Data>* neer=k;
    if (links){
        op=k->rechts.k;
        neer->rechts.k=op->links.k;
        op->links.k=neer;
        if (op->links.k!=0)
            op->links.k->ouder=neer;
    }
    else{
        op=k->links.k;
        neer->links.k=op->rechts.k;
        op->rechts.k=neer;
        if (op->rechts.k!=0)
            op->rechts.k->ouder=neer;
    }
    k=op;
    op->ouder=neer->ouder;
    neer->ouder=op;
}


template <class Sleutel,class Data>
void Zoekboom<Sleutel,Data>::zoekplaats(const Sleutel& sl,Binboom<Sleutel,Data>*& plaats,
                                         Binknoop<Sleutel,Data>*& ouder){
    plaats=&deBinboom;
    ouder=0;
    while (plaats->k!=0 && plaats->k->sl!=sl){
        ouder=plaats->k;
        if (sl<plaats->k->sl)
            plaats=&(plaats->k->links);
        else
            plaats=&(plaats->k->rechts);
    }
}
        
template <class Sleutel,class Data>
Data* Zoekboom<Sleutel,Data>::zoekdata(const Sleutel& sl){
    Binboom<Sleutel,Data>* plaats;
    Binknoop<Sleutel,Data>* ouder;
    zoekplaats(sl,plaats,ouder);
    if (plaats->k==0)
        return 0;
    else return &(plaats->k->data);
}

template <class Sleutel,class Data>
void Zoekboom<Sleutel,Data>::voegtoe(const Sleutel& sl,const Data& data){
	if(deBinboom.k==0){
        deBinboom.k=new Binknoop<Sleutel,Data>(sl,data);
        deBinboom.k->ouder=0;
    }
    else
        voegtoe(*deBinboom.k,sl,data);
}

template <class Sleutel,class Data>
void Zoekboom<Sleutel,Data>::voegtoe(Binknoop<Sleutel,Data> & knoop, const Sleutel& sl,const Data& data){
    Binboom<Sleutel,Data> *kind;
    if (sl < knoop.sl)
        kind=&knoop.links;
    else
        kind=&knoop.rechts;
    if (kind->k==0){
        kind->k=new Binknoop<Sleutel,Data>(sl,data);
        kind->k->ouder=&knoop;
    }
    else
        voegtoe(*(kind->k), sl,data);
}


template <class Sleutel,class Data>
void Zoekboom<Sleutel,Data>::verwijder(const Sleutel& sl){
    Binboom<Sleutel,Data>* plaats;
    Binknoop<Sleutel,Data>* ouder;
    zoekplaats(sl,plaats,ouder);
    Binknoop<Sleutel,Data>* weg=plaats->k;
    if (plaats->k != 0){
        if (weg->links.k==0){
            plaats->k=weg->rechts.k;
            if (plaats->k != 0)
                plaats->k->ouder=ouder;
            weg->rechts.k=0;
            delete weg;
        }
        else if (weg->rechts.k==0){
            plaats->k=weg->links.k;
            if (plaats->k != 0)
                plaats->k->ouder=ouder;
            weg->links.k=0;
            delete weg;
        }
        else{
            //vervangen door voorganger
            Binboom<Sleutel,Data>* voorlink=ondervoorganger(weg);
            Binknoop<Sleutel,Data>* voorganger=voorlink->k;
            if (voorlink!=&(weg->links)){
                voorlink->k=voorganger->links.k;
                if (voorganger->links.k !=0)
                    voorganger->links.k->ouder=voorganger->ouder;
                //geen test voor volgende twee: deze bestaan!
                plaats->k=voorganger;
                voorganger->ouder=ouder;
                voorganger->links.k=weg->links.k;
                voorganger->links.k->ouder=voorganger;
                voorganger->rechts.k=weg->rechts.k;
                voorganger->rechts.k->ouder=voorganger;
            }
            else{
                voorganger->rechts.k=weg->rechts.k;
                weg->rechts.k->ouder=voorganger;
                voorganger->ouder=weg->ouder;
                plaats->k=voorganger;
            }
            weg->links.k=0;
            weg->rechts.k=0;
            delete weg;
        }
    }
}


template <class Sleutel,class Data>
Binboom<Sleutel,Data>* Zoekboom<Sleutel,Data>::ondervoorganger(Binknoop<Sleutel,Data>* kn){
    Binboom<Sleutel,Data>* onder=&(kn->links);
    while (onder->k->rechts.k!=0)
        onder=&(onder->k->rechts);
    return onder;
}


template <class Sleutel,class Data>
void Binboom<Sleutel,Data>::schrijf(ostream& os) const{
    if (k!=0){
       std::queue<Binknoop<Sleutel,Data>*, std::deque<Binknoop<Sleutel,Data>*> > q;
       q.push(k);
       while(!q.empty()){
           Binknoop<Sleutel,Data>* nu=q.front();
           schrijf(os,nu);
           os<<" links: ";
           schrijf(os,nu->links.k);
           os<<" rechts: ";
           schrijf(os,nu->rechts.k);
           os<<" ouder: ";
           schrijf(os,nu->ouder);
           os<<std::endl;
           if (nu->links.k!=0)
               q.push(nu->links.k);
           if (nu->rechts.k!=0)
               q.push(nu->rechts.k);
           q.pop();
       }
    }
    else{
        schrijf(os,k);
    }
}

#endif

