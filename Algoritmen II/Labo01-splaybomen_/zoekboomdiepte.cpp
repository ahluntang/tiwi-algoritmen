#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <cmath>
#include <vector>
#include "csv.h"
#include "splayboomb.h"
#include "puntgenerator.h"
using namespace std;

int aantalDatapunten=6000;

int main(int argc, char *argv[]){


	CsvData grafiek("dieptedata",',');
    Puntgenerator dePuntgenerator;
	Splayboom<double,unsigned int> deboom;
	//Zoekboom<double,unsigned int> deboom;
    vector<double> dieptedata;
    int aantal=0;
	
    for (int i=0; i<aantalDatapunten; i++ ){
        double nupunt=dePuntgenerator.geefpunt();
		deboom.voegtoe(nupunt,i);
        aantal++;
        if (aantal*50 >= aantalDatapunten){
            dieptedata.push_back(deboom.diepte());
            aantal=0;
        }
    }

    grafiek.voegDataToe(dieptedata);
	cout << "ok";
	
    return 0;
}
