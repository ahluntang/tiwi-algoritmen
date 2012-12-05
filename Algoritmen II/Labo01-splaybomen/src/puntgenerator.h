#ifndef __PUNTGENERATOR_H
#define __PUNTGENERATOR_H
#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::string;
using std::cerr;
using std::cin;
using std::cout;
using std::endl;

class Puntgenerator{
public: Puntgenerator():a(0),d(0.5),q(1),r(1.008){};
    double geefpunt(){
        return (a+d<q?(a+=d)*sin(r):(a=-d,d*=r,q*=r*r));
    }
protected:
    double  a;
    double r,q,d;
};

#endif

