#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>
#include <queue>
#include "boyermoore.h"

using namespace std;

typedef unsigned int uint;
typedef unsigned char uchar;

int main(){

	ifstream t("bible.txt");
	string bijbel( (istreambuf_iterator<char>(t)) , istreambuf_iterator<char>() );
	t.close();

	const int lengthbijbel = bijbel.length();
	uchar* bijbelu = new uchar[lengthbijbel];
	strcpy( (char*) bijbelu, bijbel.c_str() );
	cout<<"chars van bijbel: "<<lengthbijbel<<endl;
	ifstream ifkapitaal;
	ifkapitaal.open("capital.txt");
	if (!ifkapitaal) {
		cout << "Unable to open file";
		exit(1); // terminate with error
	}
	char c = ifkapitaal.get();
	string woord;
	while (!ifkapitaal.fail()) {
		if(c>0 && isalpha(c)){
			c = tolower(c);
			woord += c;
		} else {
			//cin.get();
			if(!woord.empty()){
				//cout<<woord<<endl;
				const int lengthnaald = woord.length();
				uchar* naaldu = new uchar[lengthnaald];
				strcpy( (char*) naaldu, woord.c_str() );
				cout<<woord<<" -> ";
				BoyerMoore bm(naaldu,lengthnaald);
				queue<const uchar*> gevondenlocaties;
				bm.zoek(gevondenlocaties,bijbelu,lengthbijbel);
				cout<<woord<<"("<<gevondenlocaties.size()<<") "<<bm.boyermoore<<" <-> "<<bm.naief<<endl;
			}
			woord.clear();
		}
		c = ifkapitaal.get();
	}

	ifkapitaal.close();
	return 0;
}
