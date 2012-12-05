#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <cmath>
#include <vector>
#include "csv.h"
#include "zoekboom.h"
#include "splayboomb.h"
#include "puntgenerator.h"
using namespace std;

int aantalDatapunten = 6000;

int main(int argc, char *argv[]) {
	Zoekboom<double, unsigned int> zoekboom;

	Splayboom<double, unsigned int> splayboom;

	CsvData grafiek_zoekboom("dieptedata_zoekboom");
	CsvData grafiek_splayboom("dieptedata_splayboom");
	Puntgenerator dePuntgenerator;
	vector<double> dieptedata_zoekboom;
	vector<double> dieptedata_splayboom;
	int aantal = 0;
	for (int i = 0; i < aantalDatapunten; i++) {
		double nupunt = dePuntgenerator.geefpunt();
		zoekboom.voegtoe(nupunt, i);
		splayboom.voegtoe(nupunt, i);

		zoekboom.kopieerstructuur(*splayboom.binboom());
		aantal++;
		if (aantal * 50 >= aantalDatapunten) {
			dieptedata_zoekboom.push_back(zoekboom.diepte());
			dieptedata_splayboom.push_back(splayboom.diepte());
			aantal = 0;
		}
	}
	grafiek_zoekboom.voegDataToe(dieptedata_zoekboom);
	grafiek_splayboom.voegDataToe(dieptedata_splayboom);

	//zoekboom.kopieerstructuur(*splayboom.binboom());
	return 0;
}
