
* bij elke iteratie: nettostroom vanuit producent neemt toe
    * tot max bereikt wordt
* betekent niet dat stroom en verbindingen telkens toeneemt
    * soms vindt men alternatieve wegen
    * in bepaalde verbindingen moet stroom zelfs dalen
* capaciteit van elke verbinding \\((i,j)\\): positief getal \\(c(i,j)\\)
* stroom \\(s(i,j)\\) loopt door verbinding
    * stroom beperkt door capaciteit: \\( 0 \le s(i,j) \le c(i,j) \\)
* \\(K\\) : verzameling van alle knopen.
* totale nettostroom/netwerkstroom \\(f\\) uit producent \\(p\\) moet maximaal worden:
\\[
f = \sum_{j \in K}{s(p,j)-s(j,p)}
\\]
* som van alle \\(j \in K\\) waarvoor verbinding \\((p,j)\\) en/of \\((j,p)\\) bestaat
    *  stel: verbinding tussen elk paar knopen bestaat
        * niet bestaande verbindingen krijgen capaciteit \\(0\\)
* `Ford-Fulkerson` start met stroomverdeling die overal \\(0\\) is.
* bij elke iteratie
    * gebruikt huidige stroomverdeling en verschillende capaciteiten om *overzicht* op te stellen van mogelijke stroomtoename tussen elk paar knopen.
        * overzicht = nieuw stroomnetwerk
            * met dezelfde knopen
            * niet noodzakelijk dezelfde verbindingen en capaciteiten
            * = **restnetwerk**
    * in **restnetwerk**
        * weg van *producent* en *verbruiker* zoeken die stroom toelaat = **vergrotende weg**
            * extra stroom wordt in oorspronkelijke stroomverdeling aangepast
        * als geen vergrotende weg gevonden wordt
            * netwerkstroom is maximaal


## Implementatie

```
Stroomnetwerk(const GraafMetTakdata<GERICHT, T>& gr, int _van, int _naar, int option):
    Graaf<GERICHT>(gr.aantalKnopen()),van(_van),naar(_naar), graaf(gr) {

    capaciteit = 0;
    Stroomnetwerk<T> restnetwerk(gr);
    Pad<T> vergrotendpad;
    zoekPad(restnetwerk, van, naar, vergrotendpad, option);
    while (vergrotendpad.size() !=0 ) {
        restnetwerk -= vergrotendpad;
        *this += vergrotendpad;
        zoekPad(restnetwerk, van, naar, vergrotendpad, option);
    }
}

Stroomnetwerk &operator-=(const Pad<T> pad) {
    for (unsigned int i = 0; i < pad.size() - 1; i++) {
        int van = pad[i];
        int naar = pad[i+1];
        int *data = this->geefTakdata(van, naar);
        *data -= pad.geefCapaciteit();
        int verbinding = this->verbindingsnummer(naar, van);
        if (verbinding == -1)
            this->voegVerbindingToe(naar, van,0);
        data = this->geefTakdata(naar, van);
        *data += pad.geefCapaciteit();
    } 
    return *this;
}

Stroomnetwerk &operator+=(const Pad<T> pad){
    for (unsigned int i = 0; i < pad.size() - 1; i++) {
        int van = pad[i];
        int naar = pad[i+1];
        int verbinding = graaf.verbindingsnummer(van, naar);
        if (verbinding != -1) {
            verbinding = this->verbindingsnummer(van, naar);
            if (verbinding == -1)
                this->voegVerbindingToe(van, naar, 0);
            int *data = this->geefTakdata(van, naar);
            *data += pad.geefCapaciteit();
            verbinding = this->verbindingsnummer(van, naar);
        } else {
            verbinding = this->verbindingsnummer(naar, van);
            if (verbinding != -1){
                int *data = this->geefTakdata(naar, van);
                *data -= pad.geefCapaciteit();
                if (*data == 0)
                    this->verwijderVerbinding(naar, van);
            }
        }
    } 
    this->capaciteit += pad.geefCapaciteit();
    return *this;
}
```
