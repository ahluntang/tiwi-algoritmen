#include <vector>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class Tknoop;
class TernaireBoom{
public:
    TernaireBoom(){k=0;};
	void voegtoe(const string&);
	Tknoop* k;
    const static char afsluiter;
};
const char TernaireBoom::afsluiter=char(127);

class Tknoop{
    friend class TernaireBoom;
public:
    char c;
    TernaireBoom kind[3];
};

void TernaireBoom::voegtoe(const string& panda) {
	stringstream ss;
	string naam;
	ss << panda << afsluiter;
	ss >> naam;
	Tknoop** h = &k;
	int index = 0;
	while(*h != 0 && index < naam.length()) {
		if(naam[index] < (*h)->c) {
			h = &(*h)->kind[0].k;
		} else if(naam[index] > (*h)->c) {
			h = &(*h)->kind[2].k;
		} else {
			h = &(*h)->kind[1].k;
			index++;
		}
	}
    
	for(int i=index; i<naam.length(); i++) {
		char karakter = naam[i];
		*h = new Tknoop();
		(*h)->c = karakter;
		h = &((*h)->kind[1].k);
	}
}


void toon(string& str, TernaireBoom& boom){
	if (boom.k !=0){
        char c=boom.k->c;
        string naam;
        stringstream ss;
        ss << str << c;
        ss >> naam;
        if (c==boom.afsluiter){
			cout << str << endl;
        }
        
        toon(str,boom.k->kind[0]);
        toon(naam,boom.k->kind[1]);
        toon(str,boom.k->kind[2]);
	}
}


int main() {
	TernaireBoom zoo;
    
	zoo.voegtoe("hunnen");
	zoo.voegtoe("aarden");
	zoo.voegtoe("aardvarken");
	zoo.voegtoe("hunebed");
	zoo.voegtoe("panda");
    
    
	string c;
	toon(c,zoo);
    
	return 0;
}