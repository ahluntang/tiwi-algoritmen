#include <iostream>
#include <vector>
#include <cmath>
#include "csv.h"
#include "prquadtree.h"

using namespace std;

int main()
{
    /*PRquadtree tree(50);
    tree.voegtoe(24,36);
    tree.voegtoe(40,35);
    tree.voegtoe(-10,36);*/
    
    
    PRquadtree spiraal(100001);
    PRquadtree spiraal1(1000001);
    PRquadtree spiraal2(1000001);
    
    
    CsvData grafiek_spiraal1("spiraal1");
	CsvData grafiek_spiraal2("spiraal2");
    
    vector<int> diepte_spiraal;
    vector<double> diepte_spiraal1;
    vector<double> diepte_spiraal2;
    
    int aantal = 0;
    
    for (int i = 0; i < 100001; i++) {
        int x = (10000-5*i)* cos(i*0.25*M_PI);
        int y = (10000-5*i)* sin(i*0.25*M_PI);
        //cout << "(" << x << "," << y << ")" << endl;
        spiraal.voegtoe( x, y );
    }
    
    aantal = 0;
    for (int i = 0; i < 19000; i++) {
        
        int x = (1000000-5*i)* cos(i*0.23*M_PI);
        int y =  (1000000-5*i)* sin(i*0.23*M_PI);
        cout << "(" << x << "," << y << ")" << endl;
        spiraal1.voegtoe( x, y );
        
        diepte_spiraal1.push_back(spiraal1.geefaantalknopen());
    }
    
    aantal = 0;
    for (int i = 0; i < 29000; i++) {
        
        int x = (1000007-3*i)* cos(i*0.27*M_PI);
        int y = (1000007-3*i)* sin(i*0.27*M_PI);
        cout << "(" << x << "," << y << ")" << endl;
        spiraal2.voegtoe( x, y );
        
        diepte_spiraal2.push_back(spiraal2.geefaantalknopen());
    }
    
    
	grafiek_spiraal1.voegDataToe(diepte_spiraal1);
	grafiek_spiraal2.voegDataToe(diepte_spiraal2);

    cout << "Hello World!" << endl;
    return 0;
}

