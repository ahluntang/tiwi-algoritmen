#include <queue>
#include <iostream>

#include "bitpatroon.h"


typedef unsigned int uint;
typedef unsigned char uchar;

class Shiftand{
public:
//naaldlengte moet kleiner dan patroonlengte zijn,
//anders wordt een exceptie opgegooid.
    Shiftand(const uchar* naald,uint _naaldlengte);
    void zoek(std::queue<const uchar*>& plaats,
                     const uchar* hooiberg, uint hooiberglengte);
private:
    Bitpatroon letterpatroon[256];
    uint naaldlengte;
};

// IMPLEMENTATIE

Shiftand::Shiftand(const uchar* naald,uint _naaldlengte)
:naaldlengte(_naaldlengte){
    for(uint i = 0; i < naaldlengte; i++){
        // case insensitive
        letterpatroon[tolower(naald[i])] |= Bitpatroon::eenbit(i);
        letterpatroon[toupper(naald[i])] |= Bitpatroon::eenbit(i);
    }
}
void Shiftand::zoek(std::queue<const uchar*>& plaats, const uchar* hooiberg, uint hooiberglengte){
    Bitpatroon oplossing = Bitpatroon::eenbit(naaldlengte - 1);
    Bitpatroon R(0);
    for(uint i = 0; i < hooiberglengte; i++){
        R = R.shiftrechts(1);
        R |= Bitpatroon::eenbit(0);
        R &= letterpatroon[hooiberg[i]];
        
        if(oplossing.en(R)){
            plaats.push( &hooiberg[ i - naaldlengte + 1 ] );
        }
    }
}

