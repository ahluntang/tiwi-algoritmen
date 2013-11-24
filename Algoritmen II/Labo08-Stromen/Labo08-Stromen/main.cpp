


#include "stroomnetwerk.h"
#include <iostream>
using namespace std;

int main() {
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
    std::cout << stroomnet << std::endl;
	//cin.get();
	return 0;
}