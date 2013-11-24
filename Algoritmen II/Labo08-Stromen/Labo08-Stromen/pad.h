#ifndef _PAD_H
#define  _PAD_H

#include<ostream>
#include<vector>

template< class T >
//Een Pad is een reeks van knoopnummers.
class Pad:public std::vector< int >{
public:
	T geefCapaciteit() const{
		return capaciteit;
	}
	void zetCapaciteit(const T& _capaciteit){
		capaciteit=_capaciteit;
	}
	friend std::ostream& operator<<(std::ostream& os, const Pad& p){
		os<<"Capaciteit= "<<p.capaciteit<<" :: ";
		if (p.size() > 0){
			os<<p[0];
		}
		for (int i=1; i<p.size(); i++ ){
			os<<"->"<<p[i];
		}
		os<<"\n";
	}
protected:
	T capaciteit;
};

#endif