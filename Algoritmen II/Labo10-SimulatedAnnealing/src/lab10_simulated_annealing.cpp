//============================================================================
// Name        : lab10_simulated_annealing.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "simulatedannealing.h"
#include "sa_kleinstewaarde.h"
using namespace std;

int main() {
	srand(time(NULL));
	cout << "" << endl; // prints 
	sa_kleinstewaarde<double> kw(0,0);
	double * oplossing = kw.newOplossing();
	cout<<"f("<<kw.x<<","<<kw.y<<") = "<<*oplossing<<" (in "<<kw.iteraties<<" iteraties)"<<endl;
	cin.get();
	return 0;
}
