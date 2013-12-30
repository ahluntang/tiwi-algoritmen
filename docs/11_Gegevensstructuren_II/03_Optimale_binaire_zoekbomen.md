
* stel
    * gegevens op voorhand gekend en wijzigen niet
    * waarschijnlijkheid gekend waarmee (afwezige) gegevens gezocht zullen worden
* trachten boom zo te schikken dat verwachtingswaarde van zoektijd minimaal wordt
* zoektijd wordt bepaald door lengte van zoekweg
    * voor aanwezig gegeven: diepte van knoop
        * in inwendige knopen opgeslagen
    * voor afwezig gegeven: diepte van ledige deelboom (nullpointer)
        * alle ledige deelbomen als bladeren van zoekboom beschouven
* boom bevat gerangschikte sleutels van
    * \\(n\\) aanwezige gegevens: \\(s_1, s_2,...,s_n\\)
    * \\(n+1\\) bladeren: \\(b_0, b_1,..., b_n\\)
* elk blad: staat voor alle afwezige gegevens die in deelboom op die plaats hadden moeten zitten
    * \\(b_0\\): alle sleutels kleiner dan \\(s_1\\)
    * \\(b_n\\): alle sleutels groter dan \\(s_n\\)
    * \\(b_i\\): alle sleutels groter dan \\(s_i\\) en kleiner dan \\(s_{i+1}\\)
* \\(p_i\\) : waarschijnlijkheid waarmee \\(i^\text{de}\\) aanwezige sleutel \\(s_i\\) gezocht wordt
    * weinig zin om waarschijnlijkheid te kennen waarmee elk afwezig gegeven gezocht wordt
        * voor veel afwezige sleutels zal zoekweg bij hetzelfde blad eindigen
* \\(q_i\\) : waarschijnlijkheid waarmee alle afwezige sleutels voorgesteld door blad \\(b_i\\) gezocht kunnen worden
* zoeken vindt steeds inwendige knoop of blad 
    \\[
        \sum_{i=1}^n{p_i} +\sum_{i=0}^n{q_i} = 1
    \\]
* zoektijd van knoop of blad: gelijkstellen aan aantal knopen op zoekweg (diepte + 1)
    * verwachtingswaarde van zoektijd wordt
    \\[
        \sum_{i=1}^n{\left(diepte(s_i)+1\right)p_i} +\sum_{i=0}^n{\left(diepte(b_i)+1\right)q_i}
    \\]
* zoekboom zoeken die deze uitdrukking minimaliseert
    * boom met minimale hoogte is niet noodzakelijk optimaal
    * inhalige methode die in wortel van elke deelboom sleutel met grootste zoekwaarschijnlijkheid onderbrengt ook niet altijd correct
    * alle mogelijke binaire zoekbomen onderzoeken is ook geen optie
      aantal:   \\[
                    \frac{1}{n+1}\binom{2n}{n} = \Omega\left(\frac{4^n}{n^\frac{3}{2}}\right)
                \\]
* dynamisch programmeren als
    * het optimale deelstructuur heeft
    * deelproblemen onafhankelijk maar overlappend zijn

## Dynamisch programmeren

* optimale deelstructuur
    * elk van de deelbomen moet optimaal zijn
        * suboptimale deelboom vervangen door beter exemplaar
    * optimale oplossing bestaat uit optimale oplossingen voor deelproblemen
    * deelproblemen onafhankelijk
        * ze hebben geen gemeenschappelijke knopen
* overlappend
    * zodat veel optimale deelbomen meermaals in oplossing gebruikt worden
    * oplossingsstrategie
        * hoe optimale deelboom vinden?
        * elke deelboom bevat reeks opeenvolgende sleutels \\(s_i,...,s_j\\) met bijhorende bladeren \\(b_{i-1},..., b_j\\)
        * één van sleutels zal wortel zijn van optimale boom: \\(s_w\\)
            * linkse deelboom van \\(s_w\\) bevat sleutels \\(s_i, ..., s_{w-1}\\)  met bladeren \\(b_{i-1}, ..., b_{w-1}\\)
            * rechtse deelboom van \\(s_w\\) bevat sleutels \\(s_{w+1}, ..., s_{j}\\)  met bladeren \\(b_{w}, ..., b_{j}\\)
            * voor optimale deelboom met wortel \\(s_w\\)
                * beide deelbomen moeten zelf optimaal zijn
        * achtereenvolgens elk van de sleutels \\(s_i, ..., s_j\\) als wortel kiezen
            * zoektijd voor boom berekenen, gebruikmakend van zoektijden van zijn (optimale) deelbomen en minimum bijhouden
            * veel deelbomen komen meermaals voor
                * vooraf hun zoektijden bepalen en opslaan

* elk deelprobleem: bepalen van kleinste verwachte zoektijd \\(z(i,j)\\) voor (deel)boom met sleutels \\(s_i, ..., s_j\\) en bijbehorende bladeren \\(b_{i-1},...b_j\\)
    * doen voor alle i en j zodat
      \\( 1 \le i \le n+1 \\)
      \\( 0 \le i \le n \\)
      \\( j \ge i-1 \\)
    * gezochte oplossing: \\(z(1,n)\\)
* om \\(z_w(i,j)\\) voor deelboom met wortel \\(s_w\\) te vinden
    * gebruikmaken van optimale zoektijden van zijn deelbomen
        * \\(z(i,w-1)\\)
        * \\(z(w+1,j)\\)
    * zoektijden zijn echter berekend ten opzichte van wortels van die deelbomen
    * alle kinderen van \\(s_w\\):
        * dieptes van al hun knopen en bladeren worden 1 groter
        * hun bijdrage tot zoektijd neemt toe met *som van zoekwaarschijnlijkheden* van al hun sleutels en bladeren
        * som voor willekeurige deelboom met sleutels \\(s_i, ..., s_j\\)
          \\[
            g(i,j) = \sum_{k=i}^{j}{p_k} + \sum_{k=i-1}^{j}{q_k}
          \\]
        * met \\(s_w\\) als wortel: \\(z_w(i,j) = p_w + \left( z(i,w-1) + g(i,w-1) \right) + \left( z(w+1,j) + g(w+1,j) \right) \\)
        * vereenvoudigd: \\( z_w(i,j) = z(i,w-1) + z(w+1,j) + g(i,j) \\)
    * \\(z(i,j)\\) moet minimaal zijn voor optimale deelboom
        * achtereenvolgens elke sleutel van deelboom tot wortel maken en minimum bepalen
        * index \\(w\\) doorloopt alle waarden tussen i en j
          \\[ z(i,j) = \min_{i \le w \le j}{ \left\\{ z_w(i,j) \right\\} } = \min_{i \le w \le j}{ \left\\{ z(i,w-1) + z(w+1,j) \right\\} } +g(i,j) \\]
        * minimum bepalen heeft enkel zin als de deelboom sleutels bevat (als \\(i \le j\\))
            * als \\(j = i-1\\): deelboom heeft geen sleutels, enkel blad \\(b_{i-1}\\)
                * \\( z(i,i-1) = q_{i-1} \\)
    * naast minimale verwachte zoektijd, boom zelf
        * *index* \\(w\\) van wortel van elke optimale deelboom bijhouden
            * deelboom met sleutels \\(s_i, ..., s_j\\): index is \\(r(i,j)\\)

## Implementatie

* recursief
    * zou veel deeloplossingen meermaals bepalen
        * ook bij berekening van alle waarden \\(g(i,j)\\) komen veel deelsommen meermaals voor
* deeloplossingen bottom-up bepalen
    * resultaten opslaan in tabellen
    * resultaten hogerop beschikbaar
* drie tweedimensionale tabellen (driehoeksmatrix volstaat)
    * tabel \\( z[1..n+1, 0..n] \\)
        * voor waarden \\(z(i,j)\\): kleinste verwachte zoektijd voor (deel)boom met sleutels \\(s_i, ..., s_j\\)
        * beide grenzen gaan niet van \\(1\\) tot \\(n\\), plaats nodig voor
            * \\(z(1,0)\\): deelboom met enkel blad \\(b_0\\)
            * \\(z(n+1,n)\\): deelboom met enkel blad \\(b_n\\)
        * driehoeksmatrix volstaat want \\(j \ge i-1 \\)
    * tabel \\( g[1..n+1, 0..n] \\)
        * voor waarden \\(g(i,j)\\): som van zoekwaarschijnlijkheden van de sleutels en bladeren
        * om efficiëntieredenen
        * voor bepaling van \\(z(i,j)\\)
            * minimum voor alle mogelijke indices \\(w\\) van wortel zoeken waarbij telkens dezelfde waarde \\(g(i,j)\\) voorkomt
            * steeds opnieuw berekenen zou onnodig veel werk betekenen
        * invulling tabel g:
            * \\( g(i,j) = g(i,j-1) + p_j + q_j \text{ voor } i \le j \\)
            * en \\( g(i,i-1) = q_{i-1} \\)
    * tabel \\( r[1..n, 1..n] \\)
        * voor indices \\(r(i,j)\\) van wortels van optimale deelbomen
        * driehoeksmatrix: \\( 1 \le i \le j \le n \\)
* waarden \\(z(i,j)\\) en \\(g(i,j)\\) in juiste volgorde bepalen
    * eerst alle elementen \\(z(i,i-1)\\) en \\(g(i,i-1)\\) op diagonaal invullen (de triviale gevallen)
    * dan achtereenvolgens elementen op elke evenwijdige diagonaal invullen
        * in richting van tabelhoek linksboven
        * voor \\(z(i,j)\\) zijn alle mogelijke waarden
            * \\(z(i,i-1), z(i,i), ..., z(i,j-1)\\) van linkse deelbomen nodig
            * en \\(z(i+1,j), ..., z(j,j), z(j+1,j)\\) van rechtse deelbomen nodig
        * waarden staan op diagonalen onder deze van \\(z(i,j)\\)
    * voor \\(g(i,j)\\) volstaat één waarde: \\(g(i,j-1)\\) op diagonaal eronder
    * \\(z(i,j)\\) maakt gebruik van \\(g(i,j)\\)
        * \\(g(i,j)\\) moet eerst bepaald worden

## Performantie

* \\(3\\) vernestelde herhalingen
    * elk niet meer dan \\(n\\) iteraties: zeker \\(O(n^3)\\)
* ondergrens
    * meeste werk in binnenste herhaling
    * alle mogelijke wortels voor elke deelboom testen
    * deelboom met sleutels \\(s_i, .., s_j\\) heeft \\(j-i+1\\) mogelijke wortels
        * elke test si \\(O(1)\\)
    * werk is evenredig met
        \\[
            \sum_{i=1}^{n}{ \sum_{j=1}^{n}{ j-i+1 } }
        \\]
    * is ook evenredig met \\(n^3\\)
        * reden: 
        \\[
            \sum_{i=1}^{n}{ \frac{n(n+1)(2n+1)}{6} }
        \\]
* totale performantie: \\( \Theta(n^3) \\)
* performantie kan sterk verbeterd worden met bijkomende eigenschap om aantal te testen wortels te reduceren
    * wordt \\( \Theta(n^2) \\)

## Pseudocode: bepalen van optimale binaire zoekboom

```
// gegeven n, en de reële tabellen p[1..n] en q[0..n]
double z[1..n+1, 0..n]; // minimale verwachtingswaarde van zoektijden
int g[1..n+1, 0..n];
int r[1..n, 1..n]; // indices van wortelelementen van optimale deelbomen

// initialisatie van diagonale nz en g
for (int i = 1; i <= n+1; i++) {
    z[i, i-1] = g[i, i-1] = q[i-1];
}

// invullen van tabellen g, z en r
for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n-k+1; i++) {
        int j = i+k-1;
        g[i,j] = g[i, j-1] + p[j] + q[j];

        // index w van wortelelement zoeken dat minimum oplevert
        z[i,j] = oneindig;
        for (int w=i; w<=j; w++) {
            double t = z[i, w-1] + z[w+1, j] + g[i,j];
            if (t<z[i,j]) {
                z[i,j] = t;
                r[i,j] = w;
            }
        }
    }

}
```



