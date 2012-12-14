/*
 * simulatedannealing.h
 *
 *  Created on: Dec 14, 2012
 *      Author: ahluntang
 */

#ifndef __SIMULANNEAL
#define __SIMULANNEAL
#include <cstdlib>
//abstracte klasse voor simulated annealing
//Hier worden GEEN probleemafhankelijke functies gedefinieerd
//deze zijn allemaal virtual.
//Notaties: zie Blum and Roli
//Parameter S: De oplossing (zowel de voorlopige als de uiteindelijke)
//is een S. S staat voor Search space


template <class S>
class SimulatedAnnealing{
public:
	int iteraties;
    S* newOplossing(){
        T=T0();
        s=newInitialSolution();
        //std::cout<<"first:"<<*s<<std::endl;
        while (!terminateCond()){
        	iteraties++;
            S *sprime=newpickAtRandom(s);
            double deltaf=f(*sprime)-f(*s);
            if (deltaf < 0 || rand()<p(T,deltaf)*RAND_MAX){
                delete s;
                s=sprime;
            }else{
                delete sprime;
            }
            updateT();
        }
        return s;
    }

protected:
    double T;//temperatuur;
    S *s;//voorlopige en eindoplossing.
    virtual double T0()=0;//initi‘le temperatuur
    virtual bool terminateCond()=0;//true als stoppen met zoeken
    virtual double f(const S&)=0;//objectieffunctie. Moet > 0 blijven
    virtual S* newInitialSolution()=0;
    virtual S* newpickAtRandom(const S*)=0;
    virtual double p(double T, double deltaf)=0;//probabiliteit verandering
    virtual void updateT()=0;
};



#endif /* SIMULATEDANNEALING_H_ */
