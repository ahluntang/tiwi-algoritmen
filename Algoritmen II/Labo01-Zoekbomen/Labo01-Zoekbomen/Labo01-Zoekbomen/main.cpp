#include <string>
#include <iostream>

#include "zoekboom.h"

using namespace std;

int main(){
    
	Zoekboom<int, string> b;
    
	b.voegtoe(10, "tien");
	b.voegtoe(20, "twintig");
	b.voegtoe(30, "dertig");
	b.voegtoe(40, "veertig");
    
	cout << b << endl;
    
	cout << *(b.zoekdata(20)) << endl;
    
	cout << endl;
    
	system("pause");
	return 0;
};
