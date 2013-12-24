
* bitgeoriënteerde methode
    * zeer efficiënt voor kleine patronen
    * eenvoudig uit te breiden om patronen te zoeken waarin fouten geslopen zijn
* maakt gebruik van dynamisch programmeren
* voor elke positie \\(j\\) in tekst `T` bijhouden welke prefixen van patroon `P` overeenkomen met tekst, eindigend op positie \\(j\\)
    * ééndimensionale tabel `R` van \\(m\\) logische waarden
    * \\(i^\text{de}\\) element van tabel komt overeen met prefix van lengte \\(i\\)
* \\(R_j\\) is waarde van tabel `R` die hoort bij tekstpositie \\(j\\)
    * \\(R_j[i]\\) is waar
        * als eerste \\(i\\) karakters van `P` overeenkomen met de \\(i\\) tekstkarakters eindigend in \\(j\\)
    * `P` eindigt op postitie \\(j\\) als 
        * \\(R_j[m]\\) waar is
        * \\(R_j[m]\\) komt voor in tekst bij beginpositie \\(j - m + 1 \\)
* volgend tekstkarakter `T[j+1]` kan sommige van prefixen verlengen tot aan nieuwe positie \\(j+1\\)
    * nieuwe tabel \\(R_{j+1}\\) kan uit vorige \\(R_j\\) afgeleid worden
        * eerste element
            \\[
                R_{j+1}[1] = 
                    \begin{cases}
                        true  & \text{als $P[1] == T[j+1]$} \\\
                        false & \text{als $P[1] != T[j+1]$}  \\\
                    \end{cases}
            \\]
        * volgende elementen
            \\[
                R_{j+1}[i] = 
                    \begin{cases}
                        true  & \text{als $R_j[i-1] == true$ && $P[i] == T[j+1]$} \\\
                        false & \text{in alle andere gevallen}  \\\
                    \end{cases}
            \\]
* lijkt op eerste zich veel werk
    * tabel bij elke tekstpositie bepalen
    * telkens \\(m\\) tabelelementen berekenen op \\(n\\) plaatsen zou \\(\Theta(nm)\\) opleveren
* bewerkingen voor elk tabelelement analoog
    * elementen zijn logische waarden
    * er bestaan processorinstructies die op alle bits van processorwoorden tegelijk inwerken
        * afzonderlijke bits van processorwoord gebruiken om waarden voor te stellen
            * \\(m\\) mag niet groter zijn dan breedte \\(w\\) van processorwoord
* bij berekening van \\(R_{j+1}\\) kijken of nieuw tekstkarakter als `T[j+1] == P[i]`
    * voor elke mogelijke waarde van \\(i\\)
    * bits gelijktijdig bepalen
        * informatie in bits van processorwoord opslaan
* `P` verandert niet: woord kan op voorhand bepaald worden voor elk mogelijk tekstkarakter
    * tabel `S` opstellen met \\(d\\) woorden (grootte alfabet)
    * bit \\(i\\) van woord `S[s] == true` als karakter \\(s\\) op plaats \\(i\\) in `P` voorkomt 
* bit \\(i\\) van \\(R_{j+1}\\) berekenen
    * bit \\(i-1\\) van \\(R_j\\) nodig
    * samen met bit \\(i\\) van woord `S` dat overeenkomt met `T[j+1]`
* alle bits van \\(R_{j+1}\\) gelijktijdig berekenen
    * schuifoperatie naar rechts op \\(R_j\\) uitvoeren
    * bit \\(i\\) wordt bit \\(i+1\\)
    * vooraan `true`-bit inschuiven
    * nadien bit-per-bit EN-operatie met `S[ T[j+1] ]`
    * \\(R_{j+1} = Schuif(R_j)\ EN\ S[ T[j+1] ]\\)
    * of \\(R_{j+1} = R_j\downarrow \ \&\&\ S[ T[j+1] ]\\)
    * waarde van \\(R_{j+1}[1]\\) volledig bepaald door eerste bit van `S[ T[j+1] ]`
        * `true` als `T[j+1] == P[1]` 
* elk van de operaties kan met één processorinstructie
    * aantal operaties \\(O(1)\\) in plaats van \\(O(m)\\)
* \\(R_1\\) bepalen (heeft geen voorloper)
    * \\(R_0\\) invoeren: met elke bit `false`

## Performantie

* in totaal \\( \Theta(nm) \\) bitoperaties
    * \\( \Theta(n) \\) woordoperaties (processorinstructies) als \\(m \le w\\)
    * geldt ook als \\(m\\) klein veelvoud van \\(w\\) is
        * slechts enkele woorden vereist om tabel op te slaan
* opstellen tabel `S`
    * initialisatie \\( \Theta(d) \\)
    * opvullen \\( \Theta(m) \\)
* performantie wordt \\( \Theta(n+m) \\) (\\(d\\) is te verwaarlozen) 
    * snelle methode voor kleine patronen
    * gebruikt weinig geheugen

## Implementatie

```
//constructor
ShiftAnd(const uchar* naald, int _naaldlengte) : naaldlengte(_naaldlengte) {
    for(uint i = 0; i < naaldlengte; i++)
        letterpatroon[ naald[i] ] |= Bitpatroon::eenbit(i); // letterpatroon = S-tabel
}

//zoek
zoek(std::queue<const uchar*> & resultaten, const uchar * hooiberg, uint hooiberglengte) {
    Bitpatroon oplossing = Bitpatroon::eenbit( naaldlengte - 1 );
    Bitpatroon R(0);
    for (uint i = 0; i < hooiberglengte; i++) {
        R  = R.shiftrechts(1); // shift
        R |= Bitpatroon::eenbit(0); // bit 1 inschuiven op positie 0
        R &= letterpatroon[ hooiberg[i] ];
        if (oplossing.en(R))
            resultaten.push( &hooiberg[ i - naaldlengte + 1 ] );
    }
}
```
