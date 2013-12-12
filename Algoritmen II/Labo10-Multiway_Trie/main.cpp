#include <iostream>
#include <vector>
using namespace std;
 
int main(){
 
	string prefix = "ababaca";
	vector<int>prefixfunctie (prefix.size(),0);
	int aantal_prefixen = 0;
 
	for (unsigned int i = 1; i < prefix.size(); i++)
	{
		int k = prefixfunctie[i - 1];
 
		while (k > 0 && prefix[i] != prefix[k])
			k = prefixfunctie[k - 1];
 
		if (prefix[i] == prefix[k])
			k++;  
		
		prefixfunctie[i] = k;                                                                                                                                                                                                              
	}	
	
	for(int i = 0; i < prefix.size(); i++)
		cout << prefixfunctie[i] << " ";

	return 0;
}