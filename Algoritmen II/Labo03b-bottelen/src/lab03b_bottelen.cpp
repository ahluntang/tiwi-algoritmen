
#include <iostream>
#include <vector>
using namespace std;



int main() {
	vector<int> maten;
	maten.push_back(200);
	maten.push_back(100);
	maten.push_back(50);

	int hoeveelheid;
	cin>>hoeveelheid;
	while(hoeveelheid != 0){
		int gevuld = 0;
		int maatnr =0;
		vector<int> frequentie(maten.size());
		while(gevuld < hoeveelheid && maatnr<maten.size()){
			if(gevuld+maten[maatnr] <= hoeveelheid){
				gevuld = gevuld+maten[maatnr];
				frequentie[maatnr]++;
			} else {
				maatnr++;
			}
		}
		cout<<"Je kan "<<hoeveelheid<<" cl in:"<<endl;
		for(int i = 0; i< frequentie.size() ; i++){
			cout<<frequentie[i]<<" flessen van "<<maten[i]<<endl;
		}

		cin>>hoeveelheid;
	}

	return 0;
}
