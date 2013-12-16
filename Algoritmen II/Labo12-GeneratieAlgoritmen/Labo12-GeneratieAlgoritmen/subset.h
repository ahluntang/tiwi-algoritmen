
//

#ifndef Labo12_GeneratieAlgoritmen_subset_h
#define Labo12_GeneratieAlgoritmen_subset_h


class Subset: public std::vector<bool>{
    void init(int n){
        resize(n);
        for (int i=0;i<size();i++)
            (*this)[i]=(rand()%2==1);
    };
    //kruis alleen oproep als *this en de twee argumenten even groot zijn!!
    void kruis(const Subset& s1, const Subset& s2){
        const Subset* oud[2]={&s1,&s2};
        for (int i=0;i<size();i++)
            (*this)[i]=(*oud[rand()%2])[i];
    }
};

#endif
