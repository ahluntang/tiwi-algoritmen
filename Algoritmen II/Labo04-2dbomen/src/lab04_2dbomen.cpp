#include <iostream>
#include <fstream>
#include <string>
#include "Boom2D.h"
#include "punt2.h"
using namespace std;

int main() {
	Boom2D<punt2> boom;
	ifstream punten_file;
	punten_file.open("puntenverz.txt");
	if (!punten_file) {
		cout<<"bestand kon niet geopend worden."<<endl;
		exit(1);
	}
	cout << "punten ingelezen, toevoegen..."<<endl;
	int x, y;
	punten_file >> x;
	punten_file >> y;
	while (!punten_file.fail()) {
		punt2 punt = punt2(x, y);
		//cout<<"Punt "<<punt<<" ingelezen."<<endl;
		boom.voeg_toe(punt);
		punten_file >> x;
		punten_file >> y;

	}
	punten_file.clear();
	punten_file.close();
	cout << "punten toegevoegd aan boom" << endl;
	punt2 punt(83,289);
	if(boom.bevat(punt)){
		cout<<"punt zit in boom"<<endl;
	} else {
		cout<<"punt niet gevonden"<<endl;
	}
	int aantal_knopen = 0;
	punt2 buur(80,120);
	boom.zoek_buur(punt,buur,aantal_knopen);
	cout<<"Punt "<<punt<<" heeft buur "<<buur<<" via "<<aantal_knopen<<endl;

	return 0;
}
