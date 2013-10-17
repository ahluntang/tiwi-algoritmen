//
//  main.cpp
//  Labo04-Eieren_dynamischprogrammeren
//
//  Created by Ah-Lun Tang on 14/10/13.
//  Copyright (c) 2013 Ah-Lun Tang. All rights reserved.
//

#include <iostream>
using std::cout;
using std::endl;
#include <iomanip>
using std::setw;
#include <vector>
using std::vector;
#include <cmath>
using std::pow;
#include <algorithm>
using std::max;

void printmatrix(vector< vector<int> > & resultaten)
{
    for (int i = 0; i < resultaten.size(); i++)
    {
        for (int j = 0; j < resultaten[i].size(); j++)
        {
            cout << setw(4) << resultaten[i][j];
        }
        cout << endl;
    }
}

/**
 * Berekent op basis van aantal eieren en verdiepingen aantal pogingen
 * @param e aantal eieren
 * @param v aantal verdiepingen
 * @return aantal pogingen
 */
int goedkoopste_strategie(int e, int v)
{
    
    // initialisatie resultatenmatrix
    vector< vector<int> > resultaten(v); // v verdiepingen, indexering vanaf 0: grootte tabel v+1
    for (int i = 0; i < v; i++)
    {
        vector<int> rij(e); // e eieren
        resultaten[i] = rij;
    }
    
    // triviale gevallen: 0 of 1 verdieping
    for (int i = 0; i < e ; i++)
    {
        resultaten[0][i] = 0; // 0 verdiepingen: 0 keer laten vallen
        resultaten[1][i] = 1; // 1 verdieping: 1 keer laten vallen
    }
    
    // triviaal geval: 1 ei
    for (int j = 1; j < v ; j++)
    {
        // aantal keer laten vallen: j keer
        // j = aantal verdiepingen, onderaan bij laagste verdieping beginnen
        resultaten[j][0] = j;
    }
    
    // andere gevallen
    for (int i = 1; i < e; i++)
    {
        for (int j = 2; j < v; j++)
        {
            // op max initialiseren
            resultaten[j][i] = INT_MAX;
            for (int x = 1; x < j; x++)
            {
                // resultaten uit tabel halen: maximum + 1
                int pogingen =  1 + max( resultaten[x-1][i-1] , resultaten[j-x][i] );
                if ( pogingen < resultaten[j][i])
                {
                    resultaten[j][i] = pogingen;
                }
            }
        }
    }
    
    
    // volledige matrix uitprinten
    printmatrix(resultaten);
    
    // resultaat teruggeven
    return resultaten[v-1][e-1];
}

int main(int argc, const char * argv[])
{

    int e = 20;
    int v = 36;
    int resultaat = goedkoopste_strategie(e, v);
    cout << endl;
    cout << "Resultaat: " << resultaat << endl;
    return 0;
}

