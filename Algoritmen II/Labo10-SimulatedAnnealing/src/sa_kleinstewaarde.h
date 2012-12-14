/*
 * sa_kleinstewaarde.h
 *
 *  Created on: Dec 14, 2012
 *      Author: ahluntang
 */

#ifndef SA_KLEINSTEWAARDE_H_
#define SA_KLEINSTEWAARDE_H_

#include <cmath>
#include "simulatedannealing.h"

template<class S>
class sa_kleinstewaarde: public SimulatedAnnealing<S> {
public:
	sa_kleinstewaarde(S x, S y);
	S x, y;

protected:
	S* calculateFunction(S x, S y);

	double T0(); //initi‘le temperatuur
	bool terminateCond(); //true als stoppen met zoeken
	double f(const S&); //objectieffunctie. Moet > 0 blijven
	S* newInitialSolution();
	S* newpickAtRandom(const S*);
	double p(double T, double deltaf); //probabiliteit verandering
	void updateT();
private:
};

template<class S>
sa_kleinstewaarde<S>::sa_kleinstewaarde(S x, S y) :
x(x), y(y){
	SimulatedAnnealing<S>::iteraties = 1;
}


template<class S>
double sa_kleinstewaarde<S>::f(const S&s) {
	return s;
}

template<class S>
S* sa_kleinstewaarde<S>::newInitialSolution() {
	x = 0;
	y = 0;
	S* solution = calculateFunction(x, y);
	return solution;
}

template<class S>
double sa_kleinstewaarde<S>::T0() {
	return 1000.0;
}

template<class S>
double sa_kleinstewaarde<S>::p(double T, double deltaf) {
	double exponent = (deltaf / T);
	return exp(-exponent);
}

template<class S>
void sa_kleinstewaarde<S>::updateT() {
	double temp = SimulatedAnnealing<S>::T - 1;
	//std::cout<<"andere temperatuur: "<<temp<<std::endl;
	if (temp > 0) {
		SimulatedAnnealing<S>::T = temp;
	} else {
		SimulatedAnnealing<S>::T = 0.0;
	}
}

template<class S>
bool sa_kleinstewaarde<S>::terminateCond() {
	S endresult(0.11);
	return ((*(SimulatedAnnealing<S>::s) <= endresult) || SimulatedAnnealing<S>::T <= 0);
}

template<class S>
S* sa_kleinstewaarde<S>::calculateFunction(S x, S y) {
	S _function = 1000 * (1 + cos((x / 5 + y / 7.0)))
			+ (1 + cos(0.01 * (x + y))) + 0.0001 * (sqrt(x * x + y * y));
	S* solution = new S(_function);
	//std::cout << "calculated:" << solution << std::endl;
	return solution;
}

template<class S>
S* sa_kleinstewaarde<S>::newpickAtRandom(const S*) {
	S * goX = calculateFunction(x + 1, y);
	S * goY = calculateFunction(x, y + 1);
	if (*goX < *goY) {
		x++;
		return goX;
	} else {
		y++;
		return goY;
	}

}

#endif /* SA_KLEINSTEWAARDE_H_ */
