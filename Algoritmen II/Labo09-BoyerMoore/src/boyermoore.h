#ifndef __BOYERMOORE_H
#define __BOYERMOORE_H

#include <queue>
#include <vector>

typedef unsigned int uint;
typedef unsigned char uchar;

using namespace std;

class BoyerMoore{
public:
	BoyerMoore(const uchar* naald,uint _naaldlengte);
	void zoek(std::queue<const uchar*>& plaats,
		const uchar* hooiberg, uint hooiberglengte);
	//int bereken_suffix(int);
	int naief, boyermoore;
private:
	const uint naaldlengte;
	const uchar* naald;
	int alfabet;
	vector<int> verkeerd_karakter; // eerste heuristiek
	vector<int> juiste_suffix; // tweede heuristiek
	int alphaIndex(char c);
	int alphaIndex(int index, const string & woord);

};

BoyerMoore::BoyerMoore(const uchar* naald,uint _naaldlengte) 
	: alfabet(26), verkeerd_karakter(27,-1), juiste_suffix(_naaldlengte,0), naaldlengte(_naaldlengte),naald(naald),naief(0),boyermoore(0) {
		// vector verkeerd karakter heuristiek invullen:
		// voor elk karakter in naald: meest rechtse positie zoeken
		for(int i = 0; i < _naaldlengte ; i++){
			verkeerd_karakter[ alphaIndex(naald[i]) ] = i+1;
		}


		//heuristiek juiste suffix
		for(int i = naaldlengte-2; i >=0 ; i--) {
			int k = juiste_suffix[i+1];
			while(k>0 && naald[i] != naald[naaldlengte-1-k]){
				k = juiste_suffix[naaldlengte-k];
			}
			if(naald[i] == naald[naaldlengte-1-k])
				k++;

			juiste_suffix[i] = k;
		}
		
}



void BoyerMoore::zoek(std::queue<const uchar*>& plaats, const uchar* hooiberg, uint hooiberglengte){

	int i=naaldlengte-1;
	while(i<hooiberglengte){
		int j=naaldlengte-1;
		int temp_i=i;
		while(j>-1 && (boyermoore++ && naald[j]==hooiberg[temp_i])){
			//boyermoore++;
			j--;
			temp_i--;
		}
		//boyermoore++;
		if(j==-1){
			plaats.push(&hooiberg[i]);
			i++;
		}else{//aanpassen met heuristiek
			int h1 = verkeerd_karakter[alphaIndex(hooiberg[temp_i])];
			int verschH1 = j-h1;
			//if(verschH1<1) verschH1=1;

			int h2=juiste_suffix[j];
			int verschH2 = h2+1;
			//verschH2=-1;

			int versch = max(verschH1,verschH2);
			i+=versch;
		}

	}


	i=naaldlengte-1;
	while(i<hooiberglengte){
		int j=naaldlengte-1;
		int temp_i=i;
		while(j>-1 && (naief++ && naald[j]==hooiberg[temp_i])){
			j--;
			temp_i--;
		}
		i++;

	}


}


int BoyerMoore::alphaIndex(char c){
	if(c < 0 || !isalpha(c))
		return 26;
	else
		return tolower(c) - 'a';
}

int BoyerMoore::alphaIndex(int index, const string & woord){
	if(index >= woord.length()){
		return 26;
	} else {
		return alphaIndex(woord.at(index));
	}
}

#endif

