
## Boyer-Moore

* patroon van achter naar voor overlopen
* bij vinden fout: \\(P\\) 1 positie naar rechts opschuiven
* twee heuristieken: *verkeerd karakter* en *juiste suffix*

### Verkeerd karakter

* \\(P\\) naar rechts schuiven tegenover \\(T\\) heeft slechts zin als we \\(t\\) in \\(T\\) tegenover hetzelfde karakter in \\(P\\) kunnen positioneren.
* van elke karakter: meest rechtse positie in \\(P\\) opslaan
    * positie opzoeken en \\(P\\) zover naar rechts verschuiven dat die positie tegenover \\(t\\) in \\(T\\) terechtkomt
    * als \\(t\\) niet in \\(P\\) voorkomt: \\(P\\) voorbij  \\(t\\) in \\(T\\) schuiven (over \\(m\\) posities)
    * na verplaatsen: vergelijken begint opnieuw achteraan
* als fout optreedt op patroonpositie i
    * \\(j\\) = meest rechtse plaats van \\(t\\) in patroon
    * als meest rechtse plaats rechts van \\(i\\) is: \\( i - j < 0 \\)
        * 1 plaats verschuiven

#### Uitgebreide heuristiek van verkeerd karakter

![](/assets/boyermoore_uitgebreid.png)

* meest rechtse positie \\(j\\) in \\(P\\) van karakter \\(t\\), links van patroonpositie \\(i\\)
    * \\(i - j \ge 0\\)
* 2D tabel nodig (of tabel met dalend gerangschikte lijsten)

#### Variant van Horspool
* zelfde tabel als originele methode
* meest rechtse positie \\(j\\) van karakter in \\(P\\), links van positie \\(m\\)
* als karakter niet vookomt: \\(j = 0\\)
* bij fout in tekst op tekstpositie \\(k\\): \\(P\\) opschuiven tegenover \\(T[ k + m - i ]\\)
    * verschuiving van \\(P\\) wordt: \\(m - j\\)

#### Variant van Sunday

* in tekst \\(T\\) voorbij huidige plaats kijken

### Juiste suffix

* als je bij \\(i\\) verkeerd karakter \\(t\\) in \\(T\\) vindt
    * suffix van \\(P\\) in \\(T\\) gevonden met lengte \\(m - i\\)
* \\(P\\) verschuiven
    * gedeelte dat tegenover dit juiste suffix in \\(T\\) terechtkomt moet ermee overeenkomen
* juiste suffix: weten of het nog ergens in P voorkomt en waar
    * meermaals: meest rechtse nemen


### Implementatie Boyer-Moore

```
int d = 256; // alfabet
// constructie
BoyerMoore(const uchar * naald, uint _naaldlengte): naaldlengte(_naaldlengte){
    // verkeerd karakter, horspool en sunday
    for(int i = 0; i < naaldlengte; i++)
        verkeerd_karakter[ naald[i] ] = i+1;
    
    // uitgebreide verkeerd karakter
    for(int i = 0; i < d; i++)  
        for(int j = 0; j < naaldlengte; j++)
            for(int k = j; k < naaldlengte; k++)
                uitgebreide_vk[i][k] = j + 1;

    // juiste suffix
    for(int i = naaldlengte - 2; i >= 0; i--){  
        int k = juiste_suffix[i+1];
        while( k > 0 && naald[i] != naald[naaldlengte - 1 - k] )
            k = juiste_suffix[ naaldlengte - k ];
        if( naald[i] == naald[ naaldlengte - 1 - k ] )
            k++;
        juiste_suffix[i] = k;
    }
}


void zoek(std::queue<const uchar*> & resultaten, const uchar* hooiberg, uint hooiberglengte){
    int n = hooiberglengte;
    int m = naaldlengte;
    int i = 0;

    while( i < n - m + 1 ){
        int k = 1;
        int j = m - 1;
        bool good = true;
        while( j >= 0 && good ){
            char c = hooiberg[ i + j ];
            if( c =! naald[j] ){
                char ch = hooiberg[ i + m ]; // voor horspool
                int vk = j + 1 - verkeerd_karakter[c]; // verkeerd karakter
                int uvk = j + 1 - uitgebreide_vk[c][j]; // uitgebreide heuristiek verkeerd karakter
                int hor = naaldlengte - verkeerd_karakter[ch]; // horspool
                int js = juiste_suffix[j]; // juiste suffix
                k = std::max( vk , std::max( uvk , std::max( hor , js ) ) );
            } else {
                j--;
            }
            if( j == -1 ){
                resultaten.push( &hooiberg[i] );
            }
            i += k;
        } // /while( j >= 0 && good )
    } // /while( i < n - m + 1 )
}


```
