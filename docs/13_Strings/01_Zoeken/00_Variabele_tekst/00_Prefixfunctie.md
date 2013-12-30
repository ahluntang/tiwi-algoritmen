
* prefixfunctie `p(i)` van string `P` bepaalt 
    * voor elke stringpositie `i`
    * lengte van langste prefix van `P` die overeenkomst met (deelstring van) diezelfde `P`
    * eindigend bij `i`
* `p(i)` is steeds kleiner dan `i`
* `p(1)` is gelijk aan nul
* `p(i+1)` kan bepaald worden als waarden voor alle vorige posities reeds gekend zijn
    * grootst mogelijke prefixlengte voor positie `i+1` is `p(i) + 1`
        * verlenging van vorige prefixwaarde `p(i)`
    * slechts mogelijk als karakters `P[ p(i) + 1 ]` en `P[ i + 1 ]` overeenkomen
        * als ze niet overeenkomen: kortere (maar zo lang mogelijke) prefix verlengen
            * eindigt ook bij positie `i`
    * elke prefix korter dan `p(i)` die eindigt bij index `i` in `P` is tevens prefix van originele prefix
        * lengte van dat kortere prefix bedraagt `p( p(i) )`
            * als karakters `P[ p(p(i)) + 1 ]` en `P[i+1]` overeenkomen
                * prefix verlengen: `p(i+1)` wordt gelijk aan `p(p(i)) + 1`
            * als karakters niet overeenkomen: vorige herhalen
                * langste kortere prefix trachten te  verlengen dat eindigt in positie `p(p(i))`
                    * heeft als lengte `p(p(p(i)))`
    * herhaling doordoen tot blijkt dat er geen enkele prefix eindigend bij positie `i` verlengd kan worden
        * laatste bekomen prefixwaarde was dan 0
        * `p(i+1)` hangt dan uitsluitend af van `P[1]`
            * als karakter gelijk is aan `P[i+1]`
                * `p(i+1)` = 1
            * anders: `p(i+1)` = 0
* alle gebruikte prefixwaarden horen bij posities kleiner dan `i+1`
    * zijn gekend 
    * prefixwaarden kunnen voor stijgende indices berekend worden
        * `p(1)` is steeds 0

## Efficiëntie

* er moeten \\(m\\) prefixwaarden berekend worden
    * voor elke waarde is er mogelijks een herhaling die vorige prefixwaarden overloopt
    * op eerste zicht \\(O(m^2)\\)
        * na zorgvuldige analyse slechts \\(\Theta(m)\\)
    * buitenste herhaling is geamortiseerd gemiddeld \\(O(1)\\)
* potentiaalfunctie
    * keuze potentiaal: prefixfunctie
    * vormt bovengrens voor uitvoeringstijd
        * initieel 0
        * wordt nooit negatief
    * in elke buitenste herhaling
        * wordt hoogstens 1 groter
    * in elke binnenste herhaling
        * wordt minstens 1 kleiner
    * afname van potentiaal in binnenste herhaling
        * minstens zo groot als werk in die herhaling
    * geamortiseerde tijd van buitenste herhaling
        * echte tijd + toename van potentiaal: \\(O(1)\\)
    * \\(m-1\\) buitenste herhalingen
    * totale performantie \\( \Theta(m) \\)

## Eenvoudige lineaire methode

* met prefixfunctie eenvoudig lineair zoekalgoritme construeren
* string samenstellen bestaande uit `P` gevolgd door `T`
    * met scheidingskarakter ertussen (mag niet in patroon of tekst voorkomen)
* nadien prefixfunctie bepalen van nieuwe string
    * vereist lineaire tijd \\( \Theta(n+m) \\)
* telkens wanneer prefixwaarde van positie `i` in string gelijk is aan `m`
    * `P` gevonden, beginnend bij index `i-2m` in `T`
* geen enkele prefix kan langer zijn dan `m`
    * door speciaal scheidingskarakter
* enkel eerste `m` waarden van prefixfunctie bewaren
    * methode vereist slechts \\( \Theta(m)\\) plaats
    * naast plaats voor `T` en `P`

### Implementatie

```
std::string hooiberg;
std::string naald;
int begin = naald.size();

std::vector<int> prefix(naald.length());
int j = prefix[0] = 0;
for (int i = 1; i < naald.length(); i++) {
    while (j > 0 && naald[i] != naald[j])
        j = prefix[j-1];
    if (naald[i] == naald[j])
        j++;
    prefix[i] = j;
}

j = 0;

for (int i = begin; i < hooiberg.length(); i++) {
    while (j > 0 && naald[j] != hooiberg[i])
        j = prefix[j-1];
    if (hooiberg[i] == naald[j])
        j++;
    if (j == naald.length())
        resultaat.push( &hooiberg[ i - 2 * m ] );
}
```


