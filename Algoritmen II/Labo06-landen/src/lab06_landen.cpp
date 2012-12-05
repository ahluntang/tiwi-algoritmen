#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <list>
#include <queue>
#include <limits>

#include "graaf.h"
#include "BruggenZoeker.h"
#include "tinystr.h"
#include "tinyxml.h"

#include "Land.h"

const int MAX_INT = 10000000;

struct Border {
    int length;
    int nr;
    int van;
    int naar;

    bool operator<(const Border& v1) const {
        return v1.length < length;
    }
};

int find(int knoop, std::vector<int>& vertegenwoordigers) {
    return vertegenwoordigers[knoop];
}

// De union operatie
// van en naar zijn indexes naar de vertegenwoordigers
void merge(int van, int naar, std::vector<std::list<int> >& componenten,
        std::vector<int>& vertegenwoordigers) {

    std::list<int>* a = &(componenten[van]);
    std::list<int>* b = &(componenten[naar]);

    if (a->size() > b->size()) {
        swap(a, b);
        int temp = van;
        van = naar;
        naar = temp;
    }

    // a is nu de list met het minste elementen.
    // We gaan alle A knopen naar de vertegenwoordiger van b zetten.
    for (std::list<int>::iterator it = a->begin(); it != a->end(); it++) {
        vertegenwoordigers[*it] = vertegenwoordigers[naar];
    }

    // a aan b hangen.
    // De merge operatie zorgt ervoor dat a leeg wordt.
    b->merge(*a);
}

void behandel(int i, vector<bool> &ontdekt, vector<int> &vertegenwoordigers,
		GraafMetKnoopEnTakdata<ONGERICHT, Land, int> & graaf, int vertegenwoordiger){
	ontdekt[i]=true;
	vertegenwoordigers[i] = vertegenwoordiger;
	// verbindingen overlopen
	for(std::map<int,int>::const_iterator it = graaf[i].begin(); it != graaf[i].end();it++){
		if(!ontdekt[it->first]){
			behandel(it->first,ontdekt,vertegenwoordigers,graaf,vertegenwoordiger);
		}
	}

}

void rec_zoek_bruggen (vector<bool> &ontdekt, vector<int> &ouder, int i){
	ontdekt[i] = true;

}

int main() {
    GraafMetKnoopEnTakdata<ONGERICHT, Land, int> graaf;
    std::map<std::string, int> knoopnrs;

	//vertegenwoordigers nodig voor disjuncte deelverzamelingen
	vector<int> vertegenwoordigers;
    std::vector<std::list<int> > componenten;
    std::priority_queue<Border> grenzen;


    TiXmlDocument doc("LandenEnGrenzen.xml");
    bool loadOK = doc.LoadFile();

    if (loadOK) {
        TiXmlNode *network = doc.RootElement();

        // Alle knopen inlezen
        for (TiXmlElement *n = network->FirstChildElement(); n != 0;
                n = n->NextSiblingElement()) {
            std::string id = n->Attribute("id");
            Land land(id, n->Attribute("name"));
            int knoop_nr = graaf.voegKnoopToe(land);
            knoopnrs[id] = knoop_nr;

			//lijst van vertegenwoordigers voor disjuncte deelverzamelingen aanvullen;
			//vertegenwoordigers.push_back(knoop_nr);

			// Iedere knoop is ook een boom op zich.
            std::list<int> lijst;
            lijst.push_back(knoop_nr);
            componenten.reserve(graaf.aantalKnopen());
            componenten.push_back(lijst);

		}


        for (TiXmlElement *n = network->FirstChildElement(); n != 0;
                n = n->NextSiblingElement()) {
            int van = knoopnrs[n->Attribute("id")];

            for (TiXmlElement *pad = n->FirstChildElement(); pad != 0;
                    pad = pad->NextSiblingElement()) {
                int naar = knoopnrs[pad->Attribute("country")];
                int length = atoi(pad->Attribute("length"));
                try {
                    int verbindings_nr = graaf.voegVerbindingToe(van, naar, length);

                    Border v;
                    v.nr = verbindings_nr;
                    v.length = length;
                    v.van = van;
                    v.naar = naar;
                    grenzen.push(v);
                } catch (GraafExceptie e) {
                    // Swallow it.
					//cout << n->Attribute("id") << endl;
					//cout<<e<<endl;
                }
            }
        }
    }
    else {
        throw "kon het xml bestand niet inlezen.";
    }

	//initialisatie disjuncte deelverzamelingen
	vector<bool> ontdekt(graaf.aantalKnopen(), false);
	vertegenwoordigers.resize(graaf.aantalKnopen());
	for(int i=0; i < graaf.aantalKnopen(); i++){
		if(!ontdekt[i]){
			behandel(i, ontdekt, vertegenwoordigers,graaf,i);
		}
	}
	// groepen die met elkaar verbonden zijn
	map<string, vector<string> > groepen;
	for(int i = 0; i<vertegenwoordigers.size();i++){
		cout<<*(graaf.geefKnoopdata(i))<<" heeft vertegenwoordiger "<<*(graaf.geefKnoopdata(vertegenwoordigers[i]))<<endl;
		groepen[graaf.geefKnoopdata(vertegenwoordigers[i])->naam].push_back(graaf.geefKnoopdata(i)->naam);
	}
	cout << "aantal groepen: " << groepen.size() << endl;

	// gevoelige grenzen zoeken
	cout<<endl;
	BruggenZoeker bz;
	bz.zoek_bruggen(graaf);

    return 0;
}
