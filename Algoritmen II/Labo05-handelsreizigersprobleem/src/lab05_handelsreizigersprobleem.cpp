#include <iostream>
#include <fstream>
#include <iomanip>
#include <queue>
#include "graaf.h"
#include "postorder.h"

using namespace std;
typedef unsigned int uint;

/*
 * 1. inlezen in graaf
 * 2. graaf omkeren
 * 3. omgekeerde graaf met postordernummering overlopen (DEZ)
 * 4. gewone graaf overlopen (DEZ), telkens nieuw component starten met
 *    resterend hoogste postordernummer.
 * 5. verbindingen tussen componenten (zwakke samenhang) omzetten naar
 *    nieuwe graaf.
 * 6. nieuwe graaf topologisch sorteren
 * */


void verwerk_regel(const string & regel, int & lezer, int & blog){
	uint i = 0;
	bool eerstegetal(false), tweedegetal(false);
	stringstream sslezer, ssblog;
	while( i < regel.size() ){
		if( !isdigit(regel[i]) ){
			i++;
			if( eerstegetal ){
				tweedegetal = true;
			}
		} else if ( tweedegetal ){
			ssblog << regel[i++];
		} else {
			sslezer << regel[i++];
			eerstegetal = true;
		}
	}
	lezer = atoi( sslezer.str().c_str() );
	blog = atoi( ssblog.str().c_str() );
}

int postordernummer = 0;
void behandel_knoop(int knoopnummer, Graaf<GERICHT> &g, vector<bool> &ontdekt, bool nummer_postorder, priority_queue<Postorder> &postordernummering){
	ontdekt[knoopnummer] = true;
	for(std::map<int, int>::const_iterator it = g[knoopnummer].begin() ; it != g[knoopnummer].end(); it++ ){ //alle buren overlopen
		if(!ontdekt[it->first]){ // knoop nog niet ontdekt
			//behandel knoop
			behandel_knoop(it->first,g,ontdekt,nummer_postorder, postordernummering);
		}
	}
	// postordernummering toekennen
	if(nummer_postorder){
		Postorder p(knoopnummer, postordernummer++);
		postordernummering.push(p);
	}
}

void dez(Graaf<GERICHT> &g, priority_queue<Postorder> &postordernummering){
	//DEZ1
	vector<bool> ontdekt(g.aantalKnopen());
	// volgorde van de knopen:
	for( int i = 0; i < g.aantalKnopen(); ++i){
		if(!ontdekt[i]){
			behandel_knoop(i,g,ontdekt,true, postordernummering);
		}
	}
}

void dez(Graaf<GERICHT> &g, priority_queue<Postorder> &postordernummering, vector<int> &o_volgorde){
	//DEZ2
	vector<bool> ontdekt(g.aantalKnopen());
	while(!postordernummering.empty()){
		Postorder knoop = postordernummering.top();
		int nummer = knoop.get_knoopnummer();
		postordernummering.pop();
		if(!ontdekt[nummer]){
			behandel_knoop(nummer,g,ontdekt,false,postordernummering);
			// omgekeerde volgorde bijproppen in de vector
			o_volgorde.push_back(nummer);
		}
	}
}

void verkoop(Graaf<GERICHT> &g, Graaf<GERICHT> &og){
	/*
	0 nodige structuren:
	-> vector<int> ontdekt; (0= wit, 1= grijs, 2= zwart) (in de recursieve functie geinitialiseerd)
		-> vervangen door vector<bool> we hebben de tussentoestanden in deze opgave niet nodig
	-> pqueue<Postorder> postordernummering; (priority queue van postordernummering)
		(Posterder wil een knoopnummer en postordernummering in de constructor)
	-> vector<int> o_volgorde ==> de omgekeerde oplossing
	*/
	priority_queue<Postorder> postordernummering;
	vector<int> o_volgorde;

	//1 DEZ (op de omgekeerde) + postordernummering
	dez(og, postordernummering);
	//2 DEZ (op de gewone) + topologisch rangschikken
	dez(g, postordernummering, o_volgorde);

	//uitschrijven (van de goede volgorde)
	for(int i = o_volgorde.size()-1; i>=0; i--){
		cout<<o_volgorde[i]<<endl;
	}
	cout<<"1e associale familie: "<< o_volgorde[o_volgorde.size()-1]<<endl;
	cout<<"Aantal stofzuigers: "<<o_volgorde.size();
}



int main() {

	Graaf<GERICHT> graaf(5000);
	Graaf<GERICHT> omgekeerd(5000);

	ifstream rss_file;
	rss_file.open("rss.txt");
	if (!rss_file) {
		cout << "bestand kon niet geopend worden." << endl;
		exit(1);
	}
	string line;
	getline(rss_file, line);
	while ( !rss_file.fail() ) {
		int lezer, blog;
		verwerk_regel(line, lezer, blog);
		//cout << line << endl;
		//cout << setw(5) << lezer << setw(5) << "=>" << setw(5) << blog << endl;
		try{
			graaf.voegVerbindingToe(lezer, blog);
			omgekeerd.voegVerbindingToe(blog, lezer);
		} catch ( GraafExceptie & ex ) {
			cerr << "[error] " << ex << endl;
		}
		getline(rss_file, line);
	}
	rss_file.clear();
	rss_file.close();
	cout<<"klaar, unleash the beast!";
	cin.get();

	verkoop(graaf, omgekeerd);

	cin.get();

	return 0;
}
