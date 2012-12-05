#ifndef __PUNT_2_H__
#define __PUNT_2_H__
#include <iostream>
#include <iomanip>
using std::setw;

struct punt2 {
    int x, y;

    punt2() {}
    punt2(int _x, int _y) : x(_x), y(_y) {}
    punt2(const punt2& p):x(p.x),y(p.y){}
    void set(int _x, int _y) { x = _x; y = _y; }
    bool operator==(const punt2& p) const{
        return p.x==x && p.y==y;
    }
    friend std::ostream& operator<<(std::ostream& os, const punt2 p2){
        return os<<"("<<setw(3)<<p2.x<<","<<setw(3)<<p2.y<<")";
    }
    unsigned int kwadafstand(const punt2& p) const{
        return (p.x-x)*(p.x-x) + (p.y-y)*(p.y-y);
    }
};

#endif
