//
//  main.cpp
//  Extendible hashing
//
//

#include <iostream>
#include "exhash.h"
#include "cstring.h"
#include <limits>
#include <string>
using std::ostream;
using std::cout;
using std::endl;
using std::string;

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
    
    srand(time(NULL));
    
    Exhash<cstring, double> h;
    
    string teverwijderen;
    string str = "a";
    for(int i = 0 ; i < 100; i++)
    {
        /*int antl = rand() % 100;
        char randomstr[antl] ;
        for (int j =0; j<antl; j++) {
            randomstr[j] = rand() % (255 * 255);
        }*/
        
        str += (char) 65 + (rand() % 26) ;
        
        //string str = randomstr;
        teverwijderen = str;
        cstring s(str);
        h.voegtoe(s, i);
        //cout << h << endl;
     }
    cout << h;
    h.verwijder(teverwijderen);
    cout<< endl << "done";
    
    return 0;
}

