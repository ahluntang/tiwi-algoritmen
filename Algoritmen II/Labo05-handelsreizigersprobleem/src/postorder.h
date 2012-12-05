#ifndef __POSTORDER_H
#define __POSTORDER_H

class Postorder{
private:
	int k; // het knoopnummer
	int p; // het postordernummer
public:
	Postorder(int _k, int _p): k(_k),p(_p){}
	int get_knoopnummer(){
		return k;
	}
	int get_postordernummer(){
		return this->p;
	}

	bool operator==(const Postorder &b) const{
		return p == b.p;
	}
	bool operator<=(const Postorder &b) const{
		return p <= b.p;
	}
	bool operator<(const Postorder &b) const{
		return p < b.p;
	}
	bool operator>(const Postorder &b) const{
		return p > b.p;
	}
	bool operator>=(const Postorder &b) const{
		return p >= b.p;
	}
};


#endif
