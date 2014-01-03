## Maximale stroomprobleem

* zoveel mogelijk materiaal van producent naar verbruiker laten stromen
    * zonder capaciteit van verbindingen te overschrijden
* klassieke methode: Ford-Fulkerson
    * geen algoritme: laat meerdere implementaties toe (met verschillende performanties)
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
* stroomverdeling
    * geheel van alle stromen voor alle mogelijke knopenparen in beide richtingen
* `Ford-Fulkerson` start met stroomverdeling die overal \\(0\\) is.
* bij elke iteratie
    * gebruikt huidige stroomverdeling en verschillende capaciteiten om *overzicht* op te stellen van mogelijke stroomtoename tussen elk paar knopen.
        * overzicht = nieuw stroomnetwerk
            * met dezelfde knopen
            * niet noodzakelijk dezelfde verbindingen en capaciteiten
            * = **restnetwerk**
    * in **restnetwerk**
        * weg van *producent* naar *verbruiker* zoeken die stroom toelaat = **vergrotende weg**
            * extra stroom wordt in oorspronkelijke stroomverdeling aangepast
        * als geen vergrotende weg gevonden wordt
            * netwerkstroom is maximaal
* voor elke mogelijke stroomverdeling: overeenkomstig **restnetwerk**:
    * met dezelfde knopen
    * met enkel verbindingen die meer stroom toelaten
* meer stroom van knoop \\(i\\) naar knoop \\(j\\)
    * als capaciteit van verbinding \\((i,j)\\) nog niet volledig gebruikt werd:
        * \\(s(i,j) \lt c(i,j)\\) en/of: er loopt stroom over \\((j,i)\\) die kleiner kan gemaakt worden
* in restnetwerk
    * verbinding \\((i,j)\\) krijgt restcapaciteit: \\( c_r(i,j) = c(i,j) - s(i,j) + s(j,i) \\)
      = positief
    * restcapaciteit: kan groter zijn dan originele capaciteit
        * als \\( s(i,j) \lt s(j,i) \\)
        * als er geen verbinding \\((i,j)\\) is, maar wel \\((j,i)\\)
            * restnetwerk heeft toch verbinding \\((i,j)\\)
    * verbindingen vormen niet noodzakelijk deelverzameling van originele verbindingen
* vergrotende weg = enkelvoudige weg (zonder lus) van *producent* naar *verbruiker*
    * elke verbinding op weg
        * heeft positieve (rest)capaciteit
        * kan nog meer stroom doorlaten
    * tussen producent en verbruiker is via deze weg extra stroom mogelijk
        * gelijk aan kleinste restcapaciteit op die weg
        * stroom in overeenkomstige verbindingen van stroomnetwerk aanpassen
        * stroomtoename van knoop \\(i\\) naar knoop \\(j\\)
            * door toename van \\(s(i,j)\\) of door afname van \\(s(j,i)\\) of combinatie

### Correctheid van Ford-Fulkerson

* snede \\((P,V)\\): verdeelt verzameling \\(K\\) van alle knopen in twee deelverzamelingen \\(P\\) en \\(V\\)
    * producent \\(p\\) behoort steeds tot \\(P\\)
    * verbruiker \\(v\\) tot \\(V\\)
* capaciteit \\(c(P,V)\\) van snede \\((P,V)\\)
    * is som van alle voorwaartse stromen \\(s(i,j)\\) min som van alle achterwaartse stromen \\(s(j,i)\\)
        * met \\(i\\) in \\(P\\) en \\(j\\) in \\(V\\)
          \\(f(P,V) \le c(P,V)\\) (aangezien \\(s(i,j) \le c(i,j)\\))
* conservatieve eigenschap: netwerkstroom \\(f\\) is gelijk aan nettostroom \\(f(P,V)\\) van elke mogelijke snede
    * stroom van netwerk is bij definitie nettostroom vanuit producent \\(p\\)
      \\[
        f = \sum_{j \in K}{ \left( s(p,j) - s(j,p) \right) }
      \\]
    * stroom is conservatief in alle andere knopen \\(i\\) van \\(P\\)
      \\[
        \sum_{j \in K}{ \left( s(i,j) - s(j,i) \right) } = 0
      \\]
    * som van deze betrekkingen voor alle knopen van \\(P\\) (\\(p\\) inbegrepen)
      \\[
        f = \sum_{i \in P}{ \sum_{j \in K}{ \left( s(i,j) - s(j,i) \right) } }
      \\]
    * voor alle knopen \\(j\\) uit \\(P\\) komt elke stroom \\(s(i,j)\\) tweemaal voor, met tegengesteld teken
        * enkel knopen \\(J\\) uit \\(V = K \setminus P \\) blijven over
          is nettostroom van snede \\((P,V)\\)
          \\[
            f = \sum_{i \in P}{ \sum_{j \in V}{ \left( s(i,j) - s(j,i) \right) } } = f(P,V)
          \\]
* nettostroom kan nooit groter zijn dan haar capaciteit
    * netwerkstroom kan niet groter zijn dan capaciteit van elke snede
    * netwerkstroom kan niet groter zijn dan minimale snedecapaciteit
* *max-flow min-cut*: maximale stroom minimale snede stelling
    * maximale netwerkstroom bereikt als overeenkomstig restnetwerk geen vergrotende weg meer heeft
* equivalente eigenschappen
    1 netwerkstroom \\(f\\) is maximaal
    2 er is geen vergrotende weg meer te vinden in restnetwerk
    3 netwerkstroom \\(f\\) is gelijk aan capaciteit van snede
* eigenschap 2 volgt uit 1
    * als er nog een vergrotende weg overblijft, dan kan netwerkstroom \\(f\\) zeker groter gemaakt worden
* eigenschap 3 volgt uit 2
    * beschouw snede \\((P,V)\\) in stroomnetwerk waarvan \\(P\\) alle knopen bevat die in restnetwerk bereikbaar zijn vanuit producent \\(p\\)
    * er is geen vergrotende weg meer
        * verbruiker \\(v\\) behoort zeker niet tot \\(P\\)
    * restcapaciteit van elke verbinding \\((i,j)\\) moet 0 zijn (met \\(i \in P\\) en \\(j \in V\\))
        * anders: knoop \\(j\\) zou bereikbaar zijn vanuit \\(p\\) in restnetwerk en dus niet in \\(V\\) liggen
    * in stroomnetwerk zelf moet \\(f(P,V) = c(P,V)\\) zijn
        * want als
          \\[
            \sum_{i \in P}{ \sum_{j \in V}{ c_r(i,j) } } = \sum_{i \in P}{ \sum_{j \in V}{ \left( c(i,j) - s(i,j) + s(j,i) \right) } } = 0
          \\]
        * dan
          \\[
            c(P,V) = \sum_{i \in P}{ \sum_{j \in V}{ c(i,j) } } = \sum_{i \in P}{ \sum_{j \in V}{ \left( s(i,j) - s(j,i) \right) } } = f(P,V)
          \\]
* eigenschap 1 volgt uit 3
    * netwerkstroom is gelijk aan nettostroom doorheen elke snede
    * maximum dat nettostroom van snede bereikt
        * moet snede zijn met kleinste capaciteit
* methode van Ford-Fulkerson specificeert niet hoe vergrotende weg gezocht moet worden


### Implementatie

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
