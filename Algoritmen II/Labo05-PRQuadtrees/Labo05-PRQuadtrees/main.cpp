#include <iostream>
#include <cmath>
#include "prquadtree.h"

using namespace std;

int main()
{
    /*PRquadtree tree(50);
    tree.voegtoe(24,36);
    tree.voegtoe(40,35);
    tree.voegtoe(-10,36);*/
    
    
    PRquadtree tree(100001);
    
    for (int i = 0; i < 100001; i++) {
        int x = (10000-5*i)* cos(i*0.25*M_PI); //(1000000-5*i)* cos(i*0.23*M_PI);
        int y = (10000-5*i)* sin(i*0.25*M_PI);
        cout << "(" << x << "," << y << ")" << endl;
        tree.voegtoe( x, y );
    }
    cout << "Hello World!" << endl;
    return 0;
}

