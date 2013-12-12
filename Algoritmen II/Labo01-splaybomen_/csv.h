#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cassert>
#include <cmath>
#include <vector>

class CsvData{
public:
//scheidingsteken: teken in vlottendekommagetallen
//noot: voor een Nederlandstalige excel, scheidingsteken ',' opgeven
    CsvData(const std::string& _bestandsnaam, char _scheidingsteken='.'):
                    bestandsnaam(_bestandsnaam),scheidingsteken(_scheidingsteken){};
template<class T>//T kan int zijn, unsigned int, float, enz
void voegDataToe(const std::vector<T>& nieuwedata){
        std::vector<double>& nuvector=data[data.size()-1];
        nuvector.resize(nieuwedata.size());
        for (int i=0; i<nieuwedata.size(); i++ ){
            nuvector[i]=static_cast<double>(nieuwedata[i]);//dataconversie
        }
        data.push_back(nuvector);
    }

//speciaal geval: geen dataconversie nodig
void voegDataToe(const std::vector<double>& nieuwedata){
        data.push_back(nieuwedata);
    }
char* formatteer(char* buf, double x){
    char formstring[12];
    sprintf(formstring,"%%%ie",kolombreedte);
    sprintf(buf,formstring,x);
    for (int i=0; i<kolombreedte; i++ ){
        if (buf[i]=='.')
            buf[i]=scheidingsteken;
    }
    return buf;
}

~CsvData(){
     char besnaam[256];
     strcpy(besnaam,bestandsnaam.c_str());
     if (!strstr(besnaam,".csv")){//geen extensie? toevoegen!
        strcat(besnaam,".csv");
     }
     std::ofstream uit(besnaam);
     assert(uit);
     unsigned int maxlengte=0;//lengte langste kolom
     for (int i=0; i<data.size(); i++ ){
        if (maxlengte < data[i].size())
            maxlengte=data[i].size();
     }
//Noot: Visual C++ accepteert `char uitbuf[kolombreedte+1]' niet voor de waarde van
//kolombreedte gekend is.
//vreemd genoeg geeft een dynamisch aangemaakte tabel met voldoende breedte,
//
//     char *uitbuf=new char[kolombreedte+1];
//
//Ook runtimefouten. De tabel een pak groter maken lost dit op (!!)
     char uitbuf[1000];
     for (int i=0; i<maxlengte; i++ ){//maxlengte=aantal rijen
         for (int j=0; j<data.size() ;j++ ){
            if (data[j].size() > i)//blanco als te kort
                uit<<formatteer(uitbuf,data[j][i]);
            uit<< (j==data.size()-1?
                                    '\n':
                                    '\t');
         }
     }
//    delete [] uitbuf;
 }
protected:
    std::vector<std::vector<double> > data;
    char scheidingsteken;
    std::string bestandsnaam;
    static const int kolombreedte;
};
const int CsvData::kolombreedte=12;


