#ifndef LAND_H
#define LAND_H

#include <string>

using namespace std;

class Land{
public:
	string ID;
	string naam;
	Land(string _ID, string _naam):ID(_ID), naam(_naam){};
	Land(){};
};

	ostream & operator<<(std::ostream &stream, const Land &land) {
		stream<<land.naam;
		return stream;
	};

#endif //LAND_H