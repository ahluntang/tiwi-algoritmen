#include "bplustree.h"
#include "schijf.h"

#include <fstream>
#include <iostream>
#include <string>
#include <ctype.h>
#include <functional>
#include <cctype>

using namespace std;

struct Woord {
	string w;
	bool operator<(const Woord &t) const {
		int o = w.compare(t.w);
		return (o < 0) ? true : false;
	}

	bool operator>(const Woord &t) const {
		int o = w.compare(t.w);
		return (o < 0) ? false : true;
	}

	bool operator<=(const Woord &t) const {

		int o = w.compare(t.w);
		return (o <= 0) ? true : false;
	}

	bool operator==(const Woord &t) const {
		int o = w.compare(t.w);
		return (o == 0);
	}

	void operator=(const Woord & t) {
		this->w = t.w;
	}

	friend ostream& operator<<(ostream& os, const Woord& woord) {
		os << woord.w;
		return os;
	}
};
string convert_lower(string str) {
	for (uint i = 0; i < strlen(str.c_str()); i++)
		if (str[i] >= 0x41 && str[i] <= 0x5A)
			str[i] = str[i] + 0x20;
	return str;
}
static inline std::string &ltrim(std::string &s) {
	s.erase(s.begin(),
			std::find_if(s.begin(), s.end(),
					std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

static inline std::string &rtrim(std::string &s) {
	s.erase(
			std::find_if(s.rbegin(), s.rend(),
					std::not1(std::ptr_fun<int, int>(std::isspace))).base(),
			s.end());
	return s;
}

static inline std::string &trim(std::string &s) {
	return ltrim(rtrim(s));
}

int main() {

	const bool VERBOSE = false;
	const uint mtussen = 10;
	const uint mblad = 666;
	Schijf<Bplusknoop<Woord, uint, mtussen, mblad> > schijf;
	Bplustree<Woord, uint, mtussen, mblad> bplustree(schijf);

	ifstream ifile;
	ifile.open("bible.txt");
	if (!ifile) {
		cout << "Unable to open file";
		exit(1); // terminate with error
	}

	string woord;
	ifile >> woord;
	int i = 0;
	while (!ifile.fail()) {
		woord = convert_lower(trim(woord));
		Woord my_woord;
		my_woord.w = woord;
		int aantal = bplustree.zoek(my_woord);
		if (VERBOSE)
			cout << "searched for " << woord << " (" << aantal
					<< "), inserting with " << aantal + 1 << endl;
		aantal++;
		i++;
		if (VERBOSE && i % 1000 == 0)
			cout << woord << ":" << aantal << endl;
		bplustree.voegtoe(my_woord, aantal);
		if (VERBOSE && i % 10000 == 0)
			cout << i << endl;
		ifile >> woord;
	}

	ifile.close();

	bplustree.overloop_gelinktelijst();
	cout << "aantal ingelezen woorden: " << i << endl;
	return 0;
}
