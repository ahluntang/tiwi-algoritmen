//
//  main.cpp
//  Extendible hashing
//
//

#include <iostream>
#include "exhash.h"
#include <limits>
using std::ostream;
using std::cout;
using std::endl;

int main()
{
    //unsigned int imax = std::numeric_limits<unsigned int>::max();
    
    /*
     Schijfpagina<unsigned int, double> pagina;
     pagina.aantalBitsInHashwaarde = 1;
     cout << pagina;
     pagina.voegtoe(imax/2 - 1, 1);
     pagina.voegtoe(imax/2 - 698, 1);
     pagina.voegtoe(imax/2 - 119, 1);
     
     pagina.voegtoe(imax/2 - 16, 1);
     pagina.voegtoe(imax/2 - 19, 1);
     pagina.voegtoe(imax/2 - 112, 1);
     pagina.voegtoe(imax/2 - 15, 1);
     pagina.voegtoe(imax/2 - 14, 1);
     cout << pagina;
     
     Schijfpagina<unsigned int, double> * rechts = new Schijfpagina<unsigned int, double>();
     rechts->aantalBitsInHashwaarde = 1;
     pagina.splits(rechts);
     
     cout << pagina;
     
     cout << *rechts;
     */
    
    Exhash<unsigned int, double> h;
    for(int i = 0 ; i < 9; i++)
    {
        h.voegtoe(i, 1);
        cout << h << endl;
    }
    cout << h;
    
    
    return 0;
}

