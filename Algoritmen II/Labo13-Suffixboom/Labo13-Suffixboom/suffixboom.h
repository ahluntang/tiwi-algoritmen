#ifndef __SUFFIXTREE_H
#define __SUFFIXTREE_H
#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <cstring>
#include <deque>
using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::string;
using std::map;
using std::deque;
using std::cerr;
using std::cin;
using std::cout;
using std::endl;

class Sknoop;
class Sboom;

/**********************************************************************

   Class: Kind
   
    het doel van Kind is om het eigenaardige gedrag van een map op te vangen dat maakt
    dat het opvragen van van een mapelement de map kan veranderen. Zorgt ook voor een
    nette destructor.
    
   
***************************************************************************/

class Kind: public map<char, Sknoop*>{
public:
    ~Kind();
    void set(char a, Sknoop* p);
    //geeft nulpointer terug als a geen beeld heeft in de map
    Sknoop* get(char a) const;
};


/**********************************************************************

   Class: Presuffix
   
   De klasse Presuffix heeft alleen belang bij het opstellen van de Sboom.
   Beschrijving: Verwijst naar een expliciete of een impliciete knoop, anders gezegt naar
   de prefix van een suffix. De  boven-pointer wijst naar een expliciete knoop, de string
   die het zoekpad vanaf *boven  aangeeft wordt aangeduid door de indices startc en eindc
   die respectievelijk het  eerste karakter en de plaats na het laatste karakter in de
   hooiberg aangeven.
   plaatsInHooiberg duidt de startplaats van de suffix aan.
   Als boven naar de juiste knoop wijst geldt dat startc==eindc.
   De knoopwijzer is in canonische vorm of canoniek als startc==einde of als
   de Presuffix wijst naar een impliciete knoop die tussen *boven en een van
   zijn kinderen ligt.
   Het algoritme verlengt de presuffixen die in een boom zitten; maakCanoniek
   past de presuffix aan als we zeker weten dat de suffix al tot einde in de boom zit.
   
***************************************************************************/
class Presuffix{
public:
    Presuffix(Sknoop* _boven=0, int _plaats=0);                           ;
    bool isExpliciet() const;
    //volgende functie ontploft (soms) als knoopwijzer niet canonisch is
    bool heeftKind(char c, const char* hooiberg) const;
    Sknoop* boven;
    int plaatsInHooiberg;
    int lengteTotBoven;//lengte van string die tot boven-knoop leidt
    int startc,eindc;
    //als het stuk van plaatsInHooiberg tot eind gekend is,
    //ga zo ver mogelijk naar beneden
    void maakCanoniek(int eind, const char* hooiberg);
    void schrijf(ostream& os, const char* hooiberg) const;
};



/**********************************************************************

   Class: Sknoop
   
   beschrijving: Vermits een Sboom gecomprimeerd is moet er een plaats zijn waar
   de gecomprimeerde takdata worden opgeslagen. Dit gebeurt  door de indices startc en
   eindc die respectievelijk het eerste karakter en de plaats na  het laatste karakter in
   de hooiberg aangeven.
   
   Noot: in de bovenliggende Sknoop moet Kind[hooiberg[startc]] dan ook naar deze knoop wijzen.
   Noot: volgendeNummer en het staticveld alle, evenals schrijfAlle dienen alleen
   voor debugdoeleinden en veronderstellen dat er maar 1 Sboom wordt aangemaakt.
   
***************************************************************************/
class Sknoop{
friend class Sboom;
//alles publiek omwille van debugdoeleinden
public:
    Sknoop();                                      ;
    int startc;
    int eindc;
    int nummer;//knopen worden genummerd omwille van debugdoeleinden
    Kind kind;
    static int volgendeNummer;
    void schrijf(ostream& os, const char* hooiberg) const;
    static void schrijfAlle(ostream& os, const char* hooiberg);
    static vector<Sknoop*> alle;//debug
//debugfunctie
    void schrijfAlsBoom(ostream& os, char*hooiberg) const{
//        os<<"("<<nummer<<")["<<startc<<" - "<<eindc<<"]";
        for (int i=startc; i<eindc; i++ ){
            os<<hooiberg[i];
        }
        if (!kind.empty()){
            os<<"{";
            for (Kind::const_iterator it=kind.begin(); it !=kind.end();/*++ staat later*/ ){
                it->second->schrijfAlsBoom(os,hooiberg);
                it++;
                if (it!=kind.end())
                    os<<"&\n";
                else
                    os<<"}";
            }
        }
    }
};




/**********************************************************************

   Class: Sboom
   
   beschrijving: Suffixboom. Wordt opgebouwd vanuit een cstring die uiteraard
   geen nulkarakter bevat.
   Noteer: de wortelknoop representeert de lege string, die uiteraard een
   geldige suffix is van een willekeurige string en dus steeds aanwezig is.
   
***************************************************************************/
class Sboom{
public:
    Sboom(const char* c=0, char afsluiter=-1);                  ;
    ~Sboom();
    void voegtoe (const char* c, char afsluiter=-1);
//hooiberg staat public voor debugdoeleinden
    char* hooiberg;//let op: niet afgesloten met nulkarakter
    int lengte;//lengte van de hooiberg.

//debugfunctie
void schrijfAlsBoom(ostream& os){
    wortel->schrijfAlsBoom(os,hooiberg);
}
protected:
    Sknoop* wortel;
};

/**********************************************************************


    Implementatie


*********************************************************************/


/**********************************************************************
     Klasse Sknoop
*********************************************************************/


Sknoop::Sknoop():startc(eindc),nummer(volgendeNummer++){
alle.push_back(this);}

void Sknoop::schrijf(ostream& os,const char* hooiberg) const{
    os<<"\nKnoop nummer "<<nummer<<" met tak \"";
    for (int i=startc; i<eindc; i++ ){
        os<<hooiberg[i];
    }
    os<<"\"\nKinderen:";
    for (map<char, Sknoop*>::const_iterator it=kind.begin(); it !=kind.end(); it++) {
        os<<" ("<<it->first<<" , "<<it->second->nummer<<")";
    }
    os<<"\n";
}

void Sknoop::schrijfAlle(ostream& os,const char* hooiberg){
    os<<"-------Lijst van Knopen----------\n";
    for (int i=0; i<volgendeNummer; i++ ){
        alle[i]->schrijf(os, hooiberg);
    }
    os<<"-------Einde lijst van Knopen----------\n";
}


int Sknoop::volgendeNummer=0;

vector<Sknoop*> Sknoop::alle;

/**********************************************************************
     Klasse Kind
*********************************************************************/

Kind::~Kind(){
    for (map<char, Sknoop*>::iterator it=this->begin(); it != this->end(); it++){
        delete it->second;
    }
}

void Kind::set(char a,Sknoop* p){
    map<char, Sknoop*>::operator[](a)=p;
}

Sknoop* Kind::get(char a) const{
    map<char, Sknoop*>::const_iterator plaats=find(a);
    if (plaats==map<char,Sknoop*>::end())
        return 0;
    else
        return plaats->second;
}

/**********************************************************************
     Klasse Presuffix
*********************************************************************/


bool Presuffix::isExpliciet() const{
    return startc==eindc;
}

bool Presuffix::heeftKind(char c, const char* hooiberg) const{
    bool gevonden;
    if (isExpliciet())
        gevonden=boven->kind.get(c) != 0;
    else{
        Sknoop* kind=boven->kind.get(hooiberg[startc]);
        int index=kind->startc-startc+eindc;
        gevonden=(hooiberg[index]==c);
    }
        
    return gevonden;
    
}



Presuffix::Presuffix(Sknoop* _boven,int _plaats):boven(_boven),plaatsInHooiberg(_plaats),
                                    startc(_plaats),eindc(startc),lengteTotBoven(0){}


void Presuffix::maakCanoniek(int eind, const char* hooiberg){
    eindc=eind-lengteTotBoven-plaatsInHooiberg+startc;
    if (boven !=0 && eindc > startc){
        Sknoop* kind=boven->kind.get(hooiberg[startc]);
        if (kind==0 && startc < eindc){
            cerr<<"NULL-knoop in maakCanoniek "
                <<" startc "<<startc <<" eindc "<<eindc <<"\n"
                <<"bovenknoop nummer "<<boven->nummer<<"\n";
            Sknoop::schrijfAlle(cerr, hooiberg);
            cerr<<"\n";
        }
        int verkorting=kind->eindc-kind->startc;
        while ((verkorting) <= (eindc-startc)){
            lengteTotBoven+=verkorting;
            boven=kind;
//            cerr <<" startc "<<startc <<" verkorting "<<verkorting ;
            startc=startc+verkorting;
//            cerr<<"hooiberg[startc] = "<<hooiberg[startc]<<"\n";
            kind=boven->kind.get(hooiberg[startc]);
            if (kind==0 && startc < eindc){
                cerr<<"NULL-knoop in maakCanoniek "
                    <<" startc "<<startc <<" eindc "<<eindc <<" verkorting "<<verkorting<<"\n"
                    <<"bovenknoop nummer "<<boven->nummer<<"\n";
                Sknoop::schrijfAlle(cerr, hooiberg);
                cerr<<"\n";
            }
            assert(kind!=0 || startc==eindc);
            if (startc < eindc)
               verkorting=kind->eindc-kind->startc;
        }
    }
}


void Presuffix::schrijf(ostream& os, const char* hooiberg) const{
    if (boven==0)
        os<<"-----";
    else{
        os<<"Suffix startend op "<<plaatsInHooiberg<<" lengteTotBoven "<<lengteTotBoven<<"\n";
        os<< "knoop "<<boven->nummer<<" string \"";
        for (int i=startc;i<eindc;i++ ){
            os<<hooiberg[i];
        }
        os<<"\"("<<startc<<" - "<<eindc<<")";
    }
    
}

/**********************************************************************
     Klasse Sboom
*********************************************************************/



Sboom::Sboom(const char* c, char afsluiter):wortel(new Sknoop){
    hooiberg=0;
    if (c !=0)
        voegtoe(c, afsluiter);
}

Sboom::~Sboom(){
    delete []hooiberg;
    delete wortel;
}

void Sboom::voegtoe (const char* c,char afsluiter){
    int oudelengte;
    if (hooiberg==0){
        oudelengte=0;
        lengte=strlen(c)+1;
        hooiberg=new char[lengte];
        strcpy(hooiberg,c);
        hooiberg[lengte-1]=afsluiter;
        cerr<<"eerste keer, lengte is "<<lengte<<"\n";
    }
    else{
        oudelengte=lengte;
        lengte+=strlen(c)+1;
        char* nieuw=new char[lengte];
        strncpy(nieuw,hooiberg,oudelengte);
        delete []hooiberg;
        hooiberg=nieuw;
        strcpy(hooiberg+oudelengte,c);
        hooiberg[lengte-1]=afsluiter;
        cerr<<"volgende keer, lengte is "<<lengte<<" afluiter is !"<<afsluiter<<"!\n";
    }
    cerr<<"Voor?\n";
    deque<Presuffix> actief;//lijst van suffixen waar eventueel nog moet aan gewerkt worden
                            //een presuffix blijft actief tot bewezen is dat het suffix
                            //zelf niet een echt prefix is van een ander suffix.
    cerr<<"..Na!\n";
    actief.push_front(Presuffix(wortel,oudelengte));
    for (int i=oudelengte; i<lengte; i++ ){
        if (i%1000==1)
            cerr<<"*";
        char nuchar=hooiberg[i];
        Presuffix* nuSuffix=&actief.back();
        nuSuffix->maakCanoniek(i, hooiberg);
        while ( !actief.empty() && !actief.back().heeftKind(nuchar, hooiberg)){
            nuSuffix=&actief.back();
            if (!nuSuffix->isExpliciet()){//tak opsplitsen
                Sknoop* kind=nuSuffix->boven->kind.get(hooiberg[nuSuffix->startc]);
                char naarkind=hooiberg[kind->startc - nuSuffix->startc + nuSuffix->eindc];
                kind->startc+=nuSuffix->eindc-nuSuffix->startc;
                Sknoop *tussen=new Sknoop;
                tussen->startc=nuSuffix->startc;
                tussen->eindc=nuSuffix->eindc;
                tussen->kind.set(naarkind,kind);
                nuSuffix->boven->kind.set(hooiberg[nuSuffix->startc],tussen);
                nuSuffix->boven=tussen;
                nuSuffix->lengteTotBoven-=nuSuffix->eindc-nuSuffix->startc;
                nuSuffix->startc=nuSuffix->eindc;

            }//daarmee wijst nuSuffix naar een expliciete knoop
            //maken van blad
            Sknoop* nieuw=new Sknoop;
            nieuw->startc=i;
            nieuw->eindc=lengte;
            nuSuffix->boven->kind.set(nuchar,nieuw);
            actief.pop_back();
            if (!actief.empty()){
                actief.back().maakCanoniek(i, hooiberg);
            }
        }
        actief.push_front(Presuffix(wortel,i+1));
    }
}




#endif

