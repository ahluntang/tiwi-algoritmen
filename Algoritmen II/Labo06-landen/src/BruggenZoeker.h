#ifndef __BRUG_H
#define __BRUG_H

#include "graaf.h"
#include "Land.h"
#include <vector>
#include <limits.h>

using namespace std;


class BruggenZoeker{
public:
	void zoek_bruggen(GraafMetKnoopEnTakdata<ONGERICHT, Land, int>& g);
private:
	void rec_zoek_bruggen(int i, GraafMetKnoopEnTakdata<ONGERICHT, Land, int>& g);
	vector<bool> ontdekt;
	vector<int> ouder;
	vector<int> pre;
	vector<int> laagst;
	vector<int> opvolgers;
	vector<int> hoogst;
	int num;
};


void BruggenZoeker::zoek_bruggen(GraafMetKnoopEnTakdata<ONGERICHT, Land, int>& g){
	ontdekt.clear();
	ouder.clear();
	pre.clear();
	laagst.clear();
	ontdekt.resize(g.aantalKnopen(),false);
	ouder.resize(g.aantalKnopen(),-1);
	pre.resize(g.aantalKnopen());
	laagst.resize(g.aantalKnopen(),INT_MAX);
	num = 0;
	for(int i=0; i < g.aantalKnopen();i++){
		if(!ontdekt[i])
			rec_zoek_bruggen(i, g);
	}
	
}

void BruggenZoeker::rec_zoek_bruggen(int i, GraafMetKnoopEnTakdata<ONGERICHT, Land, int>& g){
	ontdekt[i]=true;
	pre[i] = num++;
	laagst[i] = pre[i];
	for(std::map<int,int>::const_iterator it = g[i].begin(); it != g[i].end();it++){
		int knoopnr = it->first;
		if(!ontdekt[knoopnr]){
			ouder[knoopnr] = i;
			rec_zoek_bruggen(knoopnr, g);
			if(laagst[knoopnr] < laagst[i]){
				laagst[i] = laagst [knoopnr];
			}else if (laagst[knoopnr] > pre[i]){
				std::cout << "Verbinding " << g.geefKnoopdata(i)->naam << " " <<  g.geefKnoopdata(knoopnr)->naam << " is brug" << endl;
			}
		}else{
			if(knoopnr != ouder[i]){
				if(pre[knoopnr] < laagst[i])
					laagst[i]=pre[knoopnr];
			}
		}
	}
}


#endif