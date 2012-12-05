#include <iostream>
#include <fstream>
#include <iomanip>
#include "graaf.h"
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

int main() {
	Graaf<GERICHT> graaf(5000);

	ifstream rss_file;
	rss_file.open("rss");
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
		} catch ( GraafExceptie & ex ) {
			cerr << "[error] " << ex << endl;
		}
		getline(rss_file, line);
	}
	rss_file.clear();
	rss_file.close();

	return 0;
}
