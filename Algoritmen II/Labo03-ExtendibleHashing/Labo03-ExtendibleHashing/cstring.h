//
//  cstring.h
//  Labo03-ExtendibleHashing
//
//  Created by Ah-Lun Tang on 11/10/13.
//  Copyright (c) 2013 Ah-Lun Tang. All rights reserved.
//

#ifndef Labo03_ExtendibleHashing_cstring_h
#define Labo03_ExtendibleHashing_cstring_h

#include <string>

class cstring {

public:
    unsigned int geef_exhashindex() const{
        unsigned int even=0;
        int len=std::strlen(s.c_str());
        for (int i=0;i<len;i++){
            unsigned int pl=s[i];
            pl=pl*8+pl/32;//eerste  4 bits achteraan;
            even=even*253+pl;
            //pl*((unsigned int)1 << 24)+even/37;
        }
        unsigned int even2=0;
        int aantbits=sizeof(int)*8;
        for (int i=0;i < aantbits/2;i++)
            even2+=(even>>i)*((unsigned int)1 << (aantbits-1-i));
        return even2^even;
    }
    cstring(std::string & _s):s(_s){}
    
    cstring(){}
    
    friend ostream& operator<<(ostream& os,cstring & cstr){
        os << cstr.s;
        return os;
    };
    
    bool operator<(const cstring & cstr) const{
        return s < cstr.s;
    }
    
    bool operator==(const cstring & cstr) const{
        return s == cstr.s;
    }
private:
    std::string s;
    
};

#endif
