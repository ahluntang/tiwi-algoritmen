#ifndef DNASEQUENTIE_H_
#define DNASEQUENTIE_H_

#include<string>
#include<vector>
typedef unsigned int uint;
class DNASequentie: public std::string {
public:
	// string constructor
	DNASequentie() : std::string() { }
	DNASequentie( const std::string& s ) : std::string( s ) { }
	DNASequentie( const std::string& s, std::size_t n ) : std::string( s,n ) { }
	DNASequentie( const char *s, std::size_t n ) : std::string( s,n ) { }
	DNASequentie( const char *s ) : std::string( s ) { }
	DNASequentie( std::size_t n, char c ) : std::string ( n,c ) { }
		template <class InputIterator>
		DNASequentie( InputIterator first, InputIterator last ) : std::string( first,last ) { }

	//
	int d(const std::string&) const;
};
int DNASequentie::d(const std::string& to) const {
	std::string from = *this;
	int from_size = this->size() + 1;
	int to_size = to.size() + 1;

	// dimensions of matrix:
	// rows: from_size (string size + 1)
	// columns: to_size (string size +1)
	std::vector< std::vector<int> > distances(from_size, std::vector<int>(to_size) );

	//
	//     c h i m p
	//   0 1 2 3 4 5
	// h 1 1 1 2 3 4
	// u 2 2 2 2 3 4
	// m 3 3 3 3 2 3
	// a 4 4 4 4 3 3
	// n 5 5 5 5 4 4
	//
	//
	for(uint row = 0; row < distances.size();row++){
		distances[row][0] = row;
		for(uint col = 0; col < distances[row].size();col++){
			distances[0][col] = col;
		}
	}
	for(uint row = 1; row < distances.size();row++){
		for(uint col = 1; col < distances[row].size();col++){
			// find minimum distance of operations
			// three operations
			// operation 1: E(row  ,col-1) + 1 // go down
			// operation 2: E(row-1,col  ) + 1 // go right
			// operation 3: E(row-1,col-1) + s // go diagonal
			// with s = 0 (if char[row]=char[col]), if not equal: s = 1
			int down,right,diagonal,s,minimum;
			s = ( from[row] == to[col]) ? 0 : 1;
			down = distances[row  ][col-1] + 1;
			right = distances[row-1][col  ] + 1;
			diagonal = distances[row-1][col-1] + s;
			minimum = std::min(down,std::min(right,diagonal));
			distances[row][col] = minimum;
		}
	}

	return distances[from_size-1][to_size-1];
}

#endif /* DNASEQUENTIE_H_ */
