#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using std::vector;
#include "DNASequentie.h"
using namespace std;

int main() {
	DNASequentie chimp_test("chimp");
	DNASequentie human_test("human");
	int i = human_test.d(chimp_test);
	cout << "Distance between string '"<<human_test<<"' and '"<<chimp_test<<"' is " << i << endl;

	//
	vector<DNASequentie> humans;
	vector<DNASequentie> chimps;

	// read human dna strings
	ifstream human_input;
	human_input.open("human.dna");
	if (!human_input) {
		cout << "Unable to open file";
		exit(1); // terminate with error
	}
	string human;
	getline(human_input, human);
	while (!human_input.fail()) {
		humans.push_back(human);
		getline(human_input, human);
	}
	human_input.close();

	// read chimp dna strings
	ifstream chimp_input;
	chimp_input.open("chimp.dna");
	if (!chimp_input) {
		cout << "Unable to open file";
		exit(1); // terminate with error
	}
	string chimp;
	getline(chimp_input, chimp);
	while (!chimp_input.fail()) {
		chimps.push_back(chimp);
		getline(chimp_input, chimp);
	}
	chimp_input.close();


	cout << "start matching..." << endl;
	//vector<int> match;
	for (uint i = 0; i < humans.size(); i++) {
		int min = humans[i].d(chimps[0]);
		int min_index = 1;
		for (uint j = 1; j < chimps.size(); j++) {
			//if (chimps[j] != "IGNORE") {
				int distance = humans[i].d(chimps[j]);
				if (distance < min) {
					min = distance;
					min_index = j + 1;
				}
			//}
		}
		//chimps[min_index - 1] = "IGNORE";

		cout<<"Bij human "<<i+1<<" hoort chimp "<<min_index<<endl;
		//match.push_back(min_index);
	}
	//cout<<endl<<endl<<endl;
	//for (int i = 0; i < match.size(); i++) {
	//	cout << "Bij human " << i + 1 << " hoort " << match[i] << endl;
	//}
	return 0;
}
