

#ifndef Labo12_GeneratieAlgoritmen_evolutor_h
#define Labo12_GeneratieAlgoritmen_evolutor_h

#include<vector>


template<class P>
class Evolutor{
public:
    //opgelet: geefOplossing geeft een referentie naar tijdelijk object.
    //dit kan maar tijdelijk gebruikt worden!
    const P& geefOplossing(){
        std::vector<P> populatie(N);
        for (int i=0; i<N; i++ ){
            init(populatie[i]);
        }
        for (int i=0; i<AANTALGENERATIES; i++ ){
            for (int j=N/3; j<(2*N)/3 ;j++ ){
                muteer(populatie[rand() % N/3], populatie[j]);
            }
            for (int j=(2*N)/3; j<N ;j++ ){
                kruis(populatie[rand() % (2*N)/3],
                      populatie[rand() % (2*N)/3], populatie[j]);
            }
            zetBesteVooraan(populatie,N/3);
        }
        zetBesteVooraan(populatie,1);
        return populatie[0];
    }
    
protected:
    //probleemafhankelijke functies:
    //evaluatiefunctie: hoe kleiner hoe beter!
    virtual double f(const P& p)=0;
    virtual void muteer(const P& in, P& uit)=0;
    virtual void kruis(const P& ouder1, const P& ouder2, P& kind)=0;
    virtual void init(P&)=0;
    //probleemonafhankelijk:
    //zetbesteVooraan zet de beste (op basis van f) n elementen
    //van de populatie vooraan in de vector
    virtual void zetBesteVooraan(std::vector<P>&p, int n)=0;
    //populatiegrootte. N is deelbaar door 3
    static const int N;
    //aantal generaties
    static const int AANTALGENERATIES;
};

#endif
