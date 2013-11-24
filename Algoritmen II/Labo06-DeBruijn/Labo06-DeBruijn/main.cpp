//
//  main.cpp
//  Labo06-DeBruijn
//
//

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <string>
using std::string;
#include <vector>
using std::vector;

#include "graaf.h"
#include "debruijn.h"



int main(int argc, const char * argv[])
{
    /* const char* knoopnamen[]={
     "nul","een","twee","drie","vier"};
     int aantal=sizeof(knoopnamen)/sizeof(char*);
     GraafMetKnoopdata<ONGERICHT,const char*> g(knoopnamen,knoopnamen+aantal);
     g.voegVerbindingToe(0,1);
     g.voegVerbindingToe(1,2);
     g.voegVerbindingToe(2,3);
     g.voegVerbindingToe(1,3);
     std::cerr<<g<<'\n';
     GraafMetTakdata<GERICHT,std::string> gg(5);
     gg.voegVerbindingToe(0,1);
     gg.voegVerbindingToe(1,2,"hallo");
     gg.voegVerbindingToe(2,3);
     gg.voegVerbindingToe(1,3,"wereld");
     std::cerr<<gg<<'\n';
     */
    
	DeBruijnreeks<int> dbr(2,2);
    cout << "reeks: " << dbr.resultaat << endl;
    
    /*
     string s;
     cin >> s;
     */
    return 0;
}

