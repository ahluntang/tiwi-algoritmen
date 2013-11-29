#include <iostream>
#include <fstream>
#include <queue>
#include <string>

#include "shiftand.h"

std::string lees(std::string bestand){
    std::ifstream file(bestand.c_str());
    std::string hooiberg((std::istreambuf_iterator<char>(file)),
                          std::istreambuf_iterator<char>() );
    return hooiberg;
}

int main(int argc, const char * argv[])
{
    std::string naald = "koran";
    std::string hooiberg = lees("koran.txt");
    
    std::queue<const uchar*> plaats;
    Shiftand sa( (const uchar *) naald.c_str(), (uint) naald.size() );
    
    sa.zoek(plaats, (const uchar *) hooiberg.c_str(),(uint) hooiberg.size());
    
    std::cout << "Aantal gevonden items: " << plaats.size() << std::endl;
    
    return 0;
}

