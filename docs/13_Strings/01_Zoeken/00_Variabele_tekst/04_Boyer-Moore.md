

* patroon van achter naar voor overlopen
* bij vinden fout: `P` 1 positie naar rechts opschuiven
    * in slechtste geval performantie van \\(O(nm)\\)
* twee heuristieken: maken grote verschuivingen mogelijk
    * verkeerd karakter
        * meest krachtige
        * geeft dikwijls sublineaire performantie, beter dan \\(O(n+m)\\)
        * in slechtste geval nog steeds \\(O(nm)\\)
    * juiste suffix 
        * zorgt voor lineaire performantie \\(O(n+m)\\) (ook in slechtste geval)

## Verkeerd karakter

* `P` naar rechts schuiven tegenover `T` heeft slechts zin als we \\(t\\) in `T` tegenover hetzelfde karakter in `P` kunnen positioneren (anders krijgen we daar zeker een fout)
* van elke karakter: meest rechtse positie in `P` opslaan
    * positie opzoeken en `P` zover naar rechts verschuiven dat die positie tegenover \\(t\\) in `T` terechtkomt
    * als \\(t\\) niet in `P` voorkomt: `P` voorbij \\(t\\) in `T` schuiven (over \\(m\\) posities)
    * na verplaatsen: vergelijken begint opnieuw achteraan
        * verschuivingen over grotere afstanden mogelijk (veel tekstkarakters worden niet getest)
* als fout optreedt op patroonpositie \\(i\\)
    * \\(j\\) = meest rechtse plaats van \\(t\\) in patroon
    * Patroon `P` naar rechts verschuiven over \\(i-j\\) posities
    * als meest rechtse plaats rechts van \\(i\\) is: \\( i - j < 0 \\)
        * 1 plaats verschuiven
* voorbereidend werk
    * vereist tabel van gehele getallen met grootte \\(d\\)
    * tabel invullen \\( \Theta(m+d) \\)

### Uitgebreide heuristiek van verkeerd karakter

![](/assets/boyermoore_uitgebreid.png)

* negatieve veschuiving vermijden
* meest rechtse positie \\(j\\) in `P` van karakter \\(t\\), **links van patroonpositie** \\(i\\) (waar fout gevonden werd)
    * verschuiving: \\(i - j\\) (steeds positief)
* tweedimensionale tabel nodig (of tabel met dalend gerangschikte lijsten)
    * voor elke mogelijke patroonpositie \\(i\\) moet je \\(j\\) bepalen
* compromis tussen tijd en plaats
    * voor elke \\(t\\) een dalend gerangschikte lijst bijhouden met alle posities waar \\(t\\) voorkomt in `P`
    * opstellen in \\( \Theta(m+d) \\)
        * door `P` éénmaal van links naar rechts doorlopen
    * totale gebruikte plaats \\( \Theta(m) \\)
    * \\(j\\) vinden op rij \\(t\\) en kolom \\(i\\) was \\(O(1)\\)
        * nu moet je lijst doorzoeken

### Variant van Horspool
* zelfde tabel als originele methode
* meest rechtse positie \\(j\\) van karakter in `P`, links van positie \\(m\\)
    * als karakter niet voorkomt: `j = 0`
* bij fout in tekst op tekstpositie \\(k\\): `P` opschuiven tegenover `T[ k + m - i ]`
    * nieuw patroonkarakter dat moet gelijk zijn aan tekstkarakter op `T[ k + m - i ]`
        * anders meteen weer fout
        * patroonkarakter ligt links van `P[m]` (als het bestaat)
        * positie \\(j\\) te vinden in tabel met als index `T[ k + m - i ]`
    * verschuiving van `P` wordt: \\(m - j\\)
        * steeds positief
* verschuiving onafhankelijk van foutieve patroonpositie \\(i\\)
    * meestal groter dan oorspronkelijke versie
    * in slechtste geval nog steeds \\(O(nm)\\)

### Variant van Sunday

* in tekst `T` voorbij huidige plaats kijken
* kleine wijziging aan Horspool
* nog steeds identiek dezelfde tabel als originele methode
* als fout optreedt tussen patroonpositie \\(i\\) en tekstpositie \\(k\\)
    * verschuiven zodat gepaste patroonkarakter tegenover tekstkarakter `T[k+m-i+1]` terechtkomt
        * net voorbij `P[m]` op vorige beginplaats van `P`
    * verschuiving steeds positief
* verschuiving onafhankelijk van foutieve patroonpositie \\(i\\)
    * volgorde waarin karakters van `P` met karakters van `T` vergeleken worden speelt geen rol meer
    * niet meer noodzakelijk dat `P` van achter naar voor doorlopen wordt
        * beste volgorde: deze die zo snel mogelijk fouten tussen `P` en `T` ontdekt
        * als men kans kent waarmee patroonkarakter in tekst voorkomt
            * karakters van `P` testen volgens stijgende kansen

## Juiste suffix

* als je bij \\(i\\) verkeerd karakter \\(t\\) in `T` vindt
    * suffix van `P` in `T` gevonden met lengte \\(m - i\\)
* `P` verschuiven
    * gedeelte dat tegenover dit juiste suffix in `T` terechtkomt moet ermee overeenkomen
* juiste suffix: weten of het nog ergens in P voorkomt en waar
    * meermaals: meest rechtse nemen (anders zou je correcte beginpositie voor `P` kunnen overslaan)
* als \\(i\\) foutpositie in `P` is
    * juiste suffix `s` met lengte \\(m-i\\) begint op positie \\(i+1\\)
    * meest rechtse positie \\(k\\) in `P` gezocht (\\(k \le i\\)) waar deelstring gelijk aan `s` begint
        * waar suffix van `P` met lengte \\(m-i\\) begint
        * overeenkomst tussen twee deelstrings van `P`
        * kan in voorbereidende fase gevonden worden
* suffixfunctie `s()` analoog als prefixfunctie
    * voor elke index \\(j\\) in `P`
        * lengte `s(j)` van grootste (echte) suffix gekend
    * als `s(j)` < \\(m-i\\) (kleiner dan lengte van juiste suffix)
        * \\(j\\) komt zeker niet in aanmerking voor gezochte positie \\(k\\)
    * als `s(j)` > \\(m-i\\)
        * kortere juiste suffix komt achteraan in langere suffix voor
        * is rechts van \\(j\\) in `P` terug te vinden
    * enkele indices \\(j\\) waar `s(j)` gelijk is aan \\(m-i\\) zijn kandidaten voor \\(k\\)
* meest rechtse positie nodig
    * \\(k\\) moet grootste van die \\(j\\) waarden zijn
* verschuiving voor foutpositie \\(i\\) bij juiste suffix
    * \\(i+1-k\\)
    * verschuivingen voor \\(m\\) mogelijke foutposities \\(i\\) in tabel `V` opslaan
        * om even snel te vinden als verschuivingen voor eerste heuristiek

### Speciale gevallen

* patroon `P` werd gevonden
    * foutieve patroonpositie \\(i\\) is 0
    * juiste suffix is `P` zelf
        * komt slechts eenmaal in `P` voor
    * geen verkeerd karakter
        * eerste heuristiek kan geen verschuiving geven (tenzij veilige 1)
    * `P` mag niet zomaar over \\(m\\) posities verschoven worden
        * nieuwe `P` in `T` kan vorige gedeeltelijk overlappen
        * grootst mogelijke overlapping komt overeen met eerstvolgende positie waarop `P` zou kunnen voorkomen
        * maximale overlapping is **langst mogelijke suffix** van `P`, korter dan \\(m\\)
        * komt overeen met `P` beginnend bij positie 1
            * lengte van suffix is `s(1)`
* geen juiste suffix
    * als fout optreedt bij patroonpositie \\(m\\)
    * geen verschuiving te bepalen
    * verschuiving eerste heuristiek is zeker positief
        * verkeerd tekstkarakter \\(t\\) kan onmogelijk rechts van positie \\(m\\) in `P` liggen
    * juiste suffix verschuiving minimale waarde 1 geven: `V[m] = 1`
* juiste suffix komt niet meer in `P` voor
    * geen index \\(j\\) gevonden waarvoor `s(j) == m-i`
    * `P` mag over meer dan \\(i\\) posities naar rechts verschoven worden
        * niet noodzakelijk over \\(m\\) posities
        * altijd mogelijk dat suffix van juiste suffix overeenkomt met prefix van `P`
        * als er meerdere dergelijke suffixen zijn
            * grootste nemen
            * geeft kleinste verschuiving
        * lengte van gezochte suffix `s(1)`
            * overeenkomstige verschuiving `V[i]` ( \\(0 < i < m\\) ) wordt `m-s(1)`
            * is steeds positief
                * gelijk aan \\(m\\) als er geen suffix/overlapping bestaat

### Performantie Juiste suffix

* suffixfunctie bepalen op analoge manier als prefixfunctie \\( \Theta(m) \\)
* voor elke verschuiving `V[i]`
    * grootste \\(j\\) in suffixtabel van `P` zoeken waarvoor `s(j) == m-i`
    * vereiste tijd voor opstellen van tabel `V` : \\(O(m^2)\\)
    * suffixtabel eenmaal overlopen
        * voor elke index \\(j\\)
            * foutpositie `i = m-s(j)` bepalen
        * kleinste verschuiving voor elke \\(i\\) bijhouden
    * indices in dalende volgorde overlopen
* minimum bepalen voor foutposities
    * verschuiving initialiseren
* ook verschuiving voor foutposities waarvoor geen juiste suffix te vinden is moet ingevuld worden
* heel tabel `V` initialiseren met `m-s(1)`
* voor foutposities \\(0 < i < m\\)
    * waarbij juiste suffix wel nog voorkomt
    * `m-s(1)` is bovengrens voor verschuiving
    * als \\( s(1) < m-i\\) (lengte van `s`)
        * verschuiving zou juiste suffix niet eens gebruiken
    * als \\( s(1) > m-i\\)
        * `s` is ook suffix van suffix
        * levert mogelijke kandidaat voor `s'`
        * initiële waarde wordt aangepast als het overlopen van suffixtabel kleinere verschuiving vindt
* voor foutpositie \\(0 \le i < m\\)
    * juiste suffix komt niet meer voor
    * `m-s(1)` is juiste verschuiving
    * bij overlopen van suffixtabel
        * waarden worden niet meer gewijzigd
* na initialisatie tabel `verschuivingen`
    * overloopt slechts eenmaal suffixtabel
    * werk per index \\(j\\): \\(O(1)\\)
    * totaal \\(\Theta(m)\\)
    * voorbereidend werk voor tweede heuristiek  \\(\Theta(m)\\)
        * vereist  \\(\Theta(m)\\) plaats

### Lineaire performantie in slechtste geval

* bijkomende voorwaarde voor suffix
* *strong good suffix heuristic*
* karakter links van \\(s'\\) in \\(P\\)
    * moet verschillend zijn van karakter \\(P[i]\\) dat links van \\(s\\) ligt in \\(P\\)
    * anders: na verschuiving van \\(P\\) zal op die plaats zeker geen overeenkomst met \\(T\\) gevonden worden
     (\\(i\\) was plaats van de fout)
* verschuivingen kunnen groter worden
* analoog met Knuth-Morris-Pratt


## Implementatie

```
int d = 256; // alfabet
// constructie
BoyerMoore(const uchar * naald, uint _naaldlengte): naaldlengte(_naaldlengte) {
    // verkeerd karakter, horspool en sunday
    for (int i = 0; i < naaldlengte; i++)
        verkeerd_karakter[ naald[i] ] = i+1;
    
    // uitgebreide verkeerd karakter
    for (int i = 0; i < d; i++)  
        for (int j = 0; j < naaldlengte; j++)
            for (int k = j; k < naaldlengte; k++)
                uitgebreide_vk[i][k] = j + 1;

    // juiste suffix
    for (int i = naaldlengte - 2; i >= 0; i--){  
        int k = juiste_suffix[i+1];
        while (k > 0 && naald[i] != naald[naaldlengte - 1 - k])
            k = juiste_suffix[ naaldlengte - k ];
        if (naald[i] == naald[ naaldlengte - 1 - k ])
            k++;
        juiste_suffix[i] = k;
    }
}


void zoek(std::queue<const uchar*> & resultaten, const uchar* hooiberg, uint hooiberglengte) {
    int n = hooiberglengte;
    int m = naaldlengte;
    int i = 0;

    while (i < n - m + 1){
        int k = 1;
        int j = m - 1;
        bool good = true;
        while (j >= 0 && good) {
            char c = hooiberg[i+j];
            if (c =! naald[j]) {
                char ch = hooiberg[i+m]; // voor horspool
                int vk = j+1-verkeerd_karakter[c]; // verkeerd karakter
                int uvk = j+1-uitgebreide_vk[c][j]; // uitgebreide heuristiek verkeerd karakter
                int hor = naaldlengte-verkeerd_karakter[ch]; // horspool
                int js = juiste_suffix[j]; // juiste suffix
                k = std::max( vk , std::max( uvk , std::max( hor , js ) ) );
            } else {
                j--;
            }
            if (j == -1){
                resultaten.push( &hooiberg[i] );
            }
            i += k;
        }
    }
}


```
