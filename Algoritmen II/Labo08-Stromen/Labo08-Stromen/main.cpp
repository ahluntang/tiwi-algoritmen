


#include "stroomnetwerk.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


void stroomvoorbeeld(){
    GraafMetTakdata<GERICHT, int> netwerk(8);
    const int PRODUCENT = 0; // Knoop 0 is PRODUCENT
    const int CONSUMENT = 7; // Knoop 7 is CONSUMENT
    netwerk.voegVerbindingToe(0, 1, 7);
    netwerk.voegVerbindingToe(0, 2, 10);
    netwerk.voegVerbindingToe(3, 0, 2);
    netwerk.voegVerbindingToe(2, 1, 3);
    netwerk.voegVerbindingToe(2, 3, 5);
    netwerk.voegVerbindingToe(1, 4, 4);
    netwerk.voegVerbindingToe(2, 5, 6);
    netwerk.voegVerbindingToe(3, 6, 6);
    netwerk.voegVerbindingToe(4, 5, 6);
    netwerk.voegVerbindingToe(6, 5, 2);
    netwerk.voegVerbindingToe(7, 4, 1);
    netwerk.voegVerbindingToe(5, 7, 8);
    netwerk.voegVerbindingToe(6, 7, 7);
    
    //Pad<int> pad;
    //Vergrotendpadzoeker<int> padzoeker(netwerk, PRODUCENT, CONSUMENT, pad);
    //cout << pad.geefCapaciteit() << endl;
    StroomNetwerk<int> stroomnet;
    int capaciteit = stroomnet.wordMaxStroomVan(netwerk, PRODUCENT, CONSUMENT);
    std::cout << "Capaciteit: " << capaciteit << std::endl;
    //std::cout << stroomnet << std::endl;

}

void bipartiteGraaf() {
    ifstream input("bipartitegraaf.txt");
    std::vector< std::pair<int,int> > koppels;
    
    string lijn;
    getline(input, lijn);
    int aantal = atoi(lijn.c_str());
    GraafMetTakdata<GERICHT, int> netwerk(aantal);
    
    const int PRODUCENT = netwerk.voegKnoopToe();
    const int CONSUMENT = netwerk.voegKnoopToe();
    
    int van;
    int naar;
    input >> van;
    input >> naar;
    
    while ( !input.eof() ) {
        // shortcut: als verbinding producent->van niet bestaat en naar->consument ook niet, dan hebben we al een koppel gevonden.
        if (netwerk.geefTakdata(PRODUCENT, van) == 0 && netwerk.geefTakdata(naar, CONSUMENT) == 0){
            std::pair<int,int> koppel(van,naar);
            koppels.push_back(koppel);
        }
        // BAM, opgelost!
        
        if (netwerk.geefTakdata(PRODUCENT, van) == 0 ) {
            netwerk.voegVerbindingToe(PRODUCENT, van, 1);
        }
		
        netwerk.voegVerbindingToe(van, naar, 1);
        
        if (netwerk.geefTakdata(naar, CONSUMENT) == 0 ) {
            netwerk.voegVerbindingToe(naar, CONSUMENT, 1);
        }
        
        
        input >> van;
        input >> naar;
    }
    
    cout<< "Aantal koppels: "<< koppels.size()<< std::endl;
    
    StroomNetwerk<int> stroomnet;
    cout << "Capaciteit: " << stroomnet.wordMaxStroomVan(netwerk, PRODUCENT, CONSUMENT);
    stroomnet.schrijfPaden(cout);
}

int main() {
    stroomvoorbeeld();
    bipartiteGraaf();
    //cin.get();
    return 0;
}
