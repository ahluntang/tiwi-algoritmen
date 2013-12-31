
## Principe

* herleidt vergelijken van strings tot vergelijken van getallen
    * enkel zin als getallen sneller vergeleken kunnen worden dan strings
    * snelheidswinst mag niet verloren gaan bij berekenen van getallen
* aan elke mogelijke string met dezelfde lengte \\(m\\) een uniek geheel getal toekennen
* in plaats van `P` en even lange deeltekst op bepaalde positie vergelijken
    * overeenkomstige getallen vergelijken
    * gelijke strings \\( \Rightarrow \\) gelijke getallen
    * gelijke getallen \\( \Rightarrow \\) strings gelijk
* \\(d^m\\) verschillende strings met lengte \\(m\\)
    * getallen kunnen heel groot worden
    * tabellen gebruiken
        * vergelijken is niet efficiënt
        * vereist meer dan \\(O(1)\\) primitieve operaties
        * vergelijken op elke beginpositie zou uitvoeringstijd van methode in alle gevallen groter maken dan gemiddelde tijd vna eenvoudige methode
    * zich beperken tot getallen die wel efficiënt vergeleken kunnen worden
        * die men in één processorwoord (met lengte \\(w\\) bits) kan voorstellen
        * er zijn meestal veel minder getallen dan strings met lengte \\(m\\)
            * meerdere strings komen overeen met hetzelfde getal
            * hetzelfde principe als bij hashing
* net als bij hashtabel: conflicten
    * gelijke strings betekent nog altijd gelijke getallen
    * als getallen gelijk zijn: niet meer zeker of strings gelijk zijn
* toelaten dat algoritme zich af en toe vergist
    * om snel algoritme te bekomen

##  Getallen definiëren

* minstens vergelijkbare (gemiddelde) performantie als die van eenvoudige methode behalen?
    * getal moet voor elk van \\(O(n)\\) deelstrings van tekst in \\(O(1)\\) berekend kunnen worden
* hashwaarde voor string met lengte \\(m\\) berekenen in \\(O(1)\\) is niet realistisch
    * hashwaarde voor deelstring op beginpositie \\(j+1\\) afleiden uit die voor deelstring op positie \\(j\\)
        * in \\(O(1)\\)
    * eerste hashwaarde zal langer duren
* verschillende definities voor hashwaarde mogelijk
* stringelement kan \\(d\\) verschillende waarden aannemen
    * string beschouwen als geheel getal in \\(d\\)-tallig stelstel
    * elk stringelement voorstellen door *cijfer* gelegen tussen \\(0\\) en \\(d-1\\)
    * getal dat `P` voorstelt
      \\[
        H(P) = \sum_{i=1}^{m}{P[i]d^{m-i}}
      \\]
    * berekening vereist slechts \\(m\\) optellingen en evenveel vermenigvuldigingen (Horner)
* beperkte hashwaarde bekomen: module \\(p\\) ( \\( 0 < p \le 2^w \\))
    * fingerprint van P
      \\[
        H_P(P) = H(P)\mod{p}
      \\]
* eerst groot getal \\(H(P)\\) berekenen en dan pas rest bepalen is niet efficiënt
    * rest bij deling door \\(p\\) van som van twee getallen is gelijk aan rest van som van hun resten
      \\[
        (a+b) \mod{p} \equiv \left( a\mod{p}+b\mod{p} \right)\mod{p}
      \\]
    * geldt ook voor verschil en product
    * tussenresultaten die te groot worden steeds kleiner maken dan \\(p\\)
* berekening van fingerprints maakt enkel gebruik van optellen, atrekken en vermenigvuldigingen
    * initiële getallen zijn kleiner dan \\(d\\)
    * alle tussenresultaten kunnen in processorwoord passen (zoals \\(p\\))
    * elke deelbewerking vereist slechts \\(O(1)\\)
    * fingerprint in \\( \Theta(m) \\)
* fingerprint van elke deelstring van `T` berekenen: \\( \Theta(nm) \\)
* eenvoudig verband tussen getal voor deelstring `T[j+1]` bij beginpositie \\(j+1\\) en voor deelstring `T[j]` bij beginpositie \\(j\\)
  `H( T[j+1] ) = ( H(T[j]) - T[j]*d^(m-1) )*d + T[j+m]`
    * modulo \\(p\\) nemen zodat fingerprint klein blijft
    * waarde van \\(d^{m-1}\mod{p}\\) moet slechts eenmaal berekend worden
    * nieuwe fingerprint ka nin \\(O(1)\\) uit vorige gehaald worden
* eenmalige berekening van \\(H_P(T[1])\\) analoog aan die van \\(H_P(P)\\) vereist \\( \Theta(m) \\)
  \\[
    H_P(T[1]) = \left( \sum_{i=1}^{m}{T[i]d^{m-i}} \right)\mod{p}
  \\]

## Performantie

* berekeningen
    * \\(H_P(P)\\), \\(H_P(T[1])\\) en \\(d^{(m-1)}\mod{P}\\) vereisen \\( \Theta(m) \\) operaties
    * berekening alle andere fingerprints vergt in totaal \\(\Theta(n)\\) operaties
    * totaal \\(\Theta(n+m)\\)
* stringvergelijkingen ter controle
    * bij gelijke fingerprints moet algoritme nog altijd strings `P` en `T[j]` zelf vergelijken
    * strings met lengte \\(m\\) vergelijken: \\(O(m)\\) operaties
    * in slechtste geval: \\(O(nm)\\)
        * als fingerprints op elke positie gelijk zijn
    * er bestaat \\(O(n)\\) tests die nagaan of alle gelijke fringerprints weldegelijk met gelijke strings overeenstemmen en stopt bij eerste gevonden fout

## Keuze \\(p\\)

* niet zo groot: alle getallen moeten in processorwoord passen
* kans op vergissingen moet kleins zijn
* vaste \\(p\\) of random \\(p\\)

### Vaste \\(p\\)

* zo groot mogelijk priemgetal \\((p \times d \le 2^w)\\)
    * priemgetal: vermijden dat verwante deelstrings dezelfde fingerprints zouden opleveren
* fingerprints
  \\[
    H_P( T[j+1] ) = \left( \left( \left( H_P(T[j]) + p(d-1) - T[j] \times d^{m-1}\right)\mod{p} \right)\mod{p} \right)\times d + T[j+m]
  \\]
* relatief trage modulobewerkingen vermijden
    * impliciete modulo \\(p = 2 \times w\\) operaties van processor gebruiken
    * \\(p\\) is niet meer priem
        * basis: radix zorgvuldig kiezen
        * mag zeker geen macht van twee zijn
            * relatief priem met \\(p\\): 127, 131, 257

### Random \\(p\\)

* vaste \\(p\\) kan nadelig zijn
    * veel vergissingen: demon seed
* random priem \\(p\\) uit bepaald bereik kiezen
    * kans op vergissingen niet langer bepaald door waarschijnlijkheidsverdelingen van patroon en/of tekst
* foutkans klein maken door groot bereik te nemen
* fundamentele eigenschap gebruiken dat aantal priemgetallen \\( \le k\\)
    * bedraagt \\(\frac{k}{\ln{k}}\\) voor grote \\(k\\)
    * slechts klein deel van priemgetallen kan fout veroorzaken
    * bijvoorbeeld: \\(k = n^2m\\)
        * kans op 1 fout: \\(O(\frac{1}{n})\\)

#### Las vegas algoritme

* overgaan op eenvoudige methode wanneer test fout signaleerd
    * gemiddelde uitvoeringstijd wordt \\( \Theta(n+m) \\)
* herbeginnen met nieuwe random priem \\(p\\) wanneer dezelfde test fout signaleert
    * met foutkans van \\(O(\frac{1}{n})\\)
        * algoritme gemiddeld \\(O(\frac{n}{n-1})\\) uitvoeren
    * gemiddelde uitvoeringstijd wordt \\( \Theta(n+m) \\)
* kans op fouten nog kleiner maken
    * meerdere fingerprints tegelijk gebruiken
    * fout treedt slechts op wanneer alle fingerprints (onafhankelijk van elkaar) tegelijk fout opleveren


## Toepassing

* tweedimensionale patroonherkenning
* zelfs met patronen van onregelmatige vorm
* geschikt voor bepaalde vormen van beeldverwerking
* kan ook aangepast worden om tegelijk naar meerdere strings te zoeken in tekst


## Implementatie

```
int d = 256; // alfabet
int Q = 997; // priemgetal

int hash(const uchar* str, uint m) {
    int h = 0;
    for (uint i = 0; i < m; i++)
        h = d * h + str[i] % Q;
    return h;
}

bool controleer(const uchar* hooiberg, uint pos, const uchar* naald, uint m) {
    for (uint i = 0; i < m; i++)
        if (hooiberg[pos + i] != naald[i])
            return false;
    return true;
}

int search(const uchar* hooiberg, uint n, const uchar * naald, uint m, std::queue<uchar*> & resultaten) {
    uint naald_hash = hash(naald,m);
    uint hooiberg_hash = hash(hooiberg, m);

    if ( hooiberg_hash == naald_hash && controleer(hooiberg, 0, naald, m) )
        resultaten.push( &hooiberg[0] );

    //d^(m-1) % Q
    int dm = 1;
    for (uint i = 0; i < m; i++)
        dm = ( dm * d ) % Q;

    for (uint i = m; i < n; i++) {
        // nieuwe hash:
        //  (1) eerste char eraf trekken
        //  (2) volgend char erbij tellen
        hooiberg_hash = ( hooiberg_hash + Q - ( dm* hooiberg[i-m] ) % Q ) % Q; // (1) 
        hooiberg_hash = ( hooiberg_hash * d + hooiberg[i] ) % Q; // (2) 

        // hashes vergelijken
        if ( hooiberg_hash == naald_hash && controleer(hooiberg, i - m + 1, naald, m) )
            resultaten.push( &hooiberg[i - m + 1] );
    }
}
```
