#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <queue>
#include <vector>
#include <map>
#include <list>
#include <cstdlib>
#include "tinyxml.h"
#include "graaf.h"

using namespace std;

void schrijfAttributen(TiXmlElement* el){
    TiXmlAttribute* attr=el->FirstAttribute();
    while (attr!=0){
        cout<<attr->Name()<<" "<<attr->Value()<<"  ";
        attr=attr->Next();
    }
    cout<<endl;
}

/* efficiënte find
 * @param knoopnr
 * @param vertegenwoordigers
 */
int findMethod(int knoopnr, vector<int> & vertegenwoordigers){
    return vertegenwoordigers[knoopnr];
}

/* Union/merge
 * @param verzameling
 * @param lijst1
 * @param lijst2
 * @param vertegenwoordigers
 */
void unionMethod(vector< list<int> > & verzameling,int lijst1, int lijst2, vector<int> & vertegenwoordigers){
    list<int> * kortste = &verzameling[lijst1];
    list<int> * langste = &verzameling[lijst2];
    if(kortste->size() > langste->size()){
        swap(kortste,langste);
        int temp = lijst1;
        lijst1 = lijst2;
        lijst2 = temp;
    }
    
    //Vertegenwoordigers aanpassen
    int vertegenwoordiger = vertegenwoordigers[lijst2];
    for(list<int>::const_iterator it = kortste->begin(); it != kortste->end(); it++){
        vertegenwoordigers[*it]=vertegenwoordiger;
    }
    
    //Voeg lijst 1 bij lijst 2
    langste->merge(*kortste);
}

struct verbinding {
    int distance;
    int nr;
    int van;
    int naar;
    
    bool operator<(const verbinding& v1) const {
        return v1.distance < distance;
    }
};


int main(){
    GraafMetKnoopEnTakdata<ONGERICHT,string,int> graaf;
    map<string,int> knoopnrs;
    vector<int> vertegenwoordiger;
    vector< list<int> > verzameling;
    priority_queue< verbinding > verbindingen;
    TiXmlDocument doc( "zoogdieren.xml" );
    bool loadOkay = doc.LoadFile();
    assert(loadOkay);
    TiXmlNode* netwerk;
    netwerk = doc.RootElement();
    assert( netwerk );
    cout<<netwerk->Value()<<"\n";
    //Graaf opbouwen
    // stap 1: knopen toevoegen
    for (TiXmlElement* knooppunt=netwerk->FirstChildElement(); knooppunt!=0;knooppunt=knooppunt->NextSiblingElement()){
        //Alle knopen toevoegen
        int knoopnr = graaf.voegKnoopToe(knooppunt->Attribute("ID"));
        knoopnrs[knooppunt->Attribute("ID")]=knoopnr;
        
        /* Efficiënte find
         * tabel vertegenwoordiger: op elk element de juiste vertegenwoordiger opslaan
         * tabel met lijst met verzamelingen: tabel indexeren met vertegenwoordiger van verzameling
         * in het begin is elk element zijn eigen vertegenwoordiger.
         */
        vertegenwoordiger.push_back(knoopnr);
        list<int> deelverzameling;
        deelverzameling.push_back(knoopnr);
        verzameling.push_back(deelverzameling);
        //verzameling[knoopnr].push_back(knoopnr);
    }
    
    // stap 2: verbindingen tussen knopen leggen
    for (TiXmlElement* knooppunt=netwerk->FirstChildElement(); knooppunt!=0;knooppunt=knooppunt->NextSiblingElement()){
        //Alle verbindingen tussen de knopen leggen
        int knoopnr = knoopnrs[knooppunt->Attribute("ID")];
        for(TiXmlElement* kind=knooppunt->FirstChildElement();kind!=0;kind=kind->NextSiblingElement()){
            int kindnr = knoopnrs[kind->Attribute("species")];
            map<int,int> knoop = graaf[knoopnr];
            if(knoop.count(kindnr)==0){
                int afstand = atoi(kind->Attribute("distance"));
                int verbindings_nr =graaf.voegVerbindingToe(knoopnr,kindnr,afstand);
                verbinding v;
                v.nr = verbindings_nr;
                v.distance = afstand;
                v.van = knoopnr;
                v.naar = kindnr;
                verbindingen.push(v);
            }
        }
    }
    
    // Kruskal
    // We stellen een MOB op
    // Als we de laatste k verbindingen van de MOB niet toevoegen zullen we k clusters hebben.
    // Kruskal werkt door het samenvoegen van bomen.
    // Dat samenvoegen gebeurt door telkens de verbinding met het kleinste gewicht tussen 2 bomen te kiezen.
    unsigned int k = 200;
    unsigned int merges = 0;
    while (!verbindingen.empty() && merges < (graaf.aantalKnopen() - k)) {
        verbinding v = verbindingen.top();
        
        // Zoek de vertegenwoordiger van de uiteinden van deze verbinding.
        int vertegenw1 = findMethod(v.van, vertegenwoordiger);
        int vertegenw2 = findMethod(v.naar, vertegenwoordiger);
        
        // Als de vertegenwoordigers verschillen, dan zijn dit 2 verschillende bomen.
        if (vertegenw1 != vertegenw2) {
            // We doen een union operatie op deze 2 bomen.
            // merge=union omdat union een reserved keyword is.
            unionMethod(verzameling, vertegenw1, vertegenw2, vertegenwoordiger);
            merges++;
        }
        
        // Deze verbinding hebben we verder niet nodig.
        verbindingen.pop();
    }
    
    // De component van de mens opzoeken.
    int knoop_mens = knoopnrs["S877"];
    int vertegenwoordiger_mens = findMethod(knoop_mens, vertegenwoordiger);
    
    // Heel de list tonen.
    std::list<int> component_boom = verzameling[vertegenwoordiger_mens];
    for (std::list<int>::iterator it = component_boom.begin(); it != component_boom.end();
         it++) {
        string * beest = graaf.geefKnoopdata(*it);
        std::cout << * beest << std::endl;
    }
    std::cout << "Er zitten " << component_boom.size() << " wezens in deze component"
    << std::endl;
    std::cout << std::endl << std::endl << std::endl << std::endl;
    
    //cout<<graaf<<endl;
    return 0;
}
