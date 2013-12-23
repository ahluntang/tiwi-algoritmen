
* lineair algoritme, maakt gebruik van de prefixfunctie
* aantal binnenste iteraties beperken
    * sneller dan eenvoudige lineaire methode
* stel: `P` wordt op bepaalde beginpositie vergeleken met `T`
    * geen overeenkomst meer tussen `P[i]` en `T[j]`
    * als foutpositie `i == 1`
        * `P` 1 positie naar rechts schuiven
        * vergelijken met `T` begint weer bij `P[1]`
    * als foutpositie `i > 1`
        * correcte prefix van `P` met lengte `i-1` gevonden
        * eindigen bij positie `j-1`
        * `P` naar zo weinig mogelijk rechts verschuiven
            * kortere prefix van `P` komt overeen met `T` tot bij positie `j-1`
            * kan begin zijn van volledige overeenkomst van `P` met `T`
            * langste van die kortere prefixen gebruiken
            * komt overeen met `P`
                * eindigend bij positie `i-1`
                * lengte is `p(i-1)`
            * als `P[ p(i-1) + 1 ] == T[j]`
                * vergelijking tussen `P` en `T` kan vanaf hier hervat worden
                * anders `P` verder opschuiven
    * als `P[i]` en `T[j]` verschillen
        * er treedt meteen weer fout op wanneer `P[ p(i-1) + 1 ] == P[i]` 
        * kortere (maar langst mogelijke) prefix moet uitgeprobeerd worden
            * waarbij karakter rechts ervan verschilt van `P[i]`
        * verschuiving zal vaak groter zijn dan bij eenvoudige lineaire methode
        * karakter rechts verschilt van `P[i]`
            * garandeert niet dat overeenkomt met `T[j]`
            * eventueel verder doorschuiven is nodig
* bijkomende vereiste voor nieuwe prefix heeft enkel met `P` te maken
    * nieuwe prefixwaarden `p2(i)` voor elke positie in `P` op voorhand bepalen
    * met behulp van foutfunctie `f(i) = p2(i-1) + 1`
    * voor elke mogelijke foutpositie `i`
        * als `i > 1`
            * meteen patroonpositie geven waarmee `T[j]` vergeleken moet worden
        * als `i == 1`
            * `P` moet één positie opgeschoven worden
            * `P[1]` vergelijken met `T[j+1]`
            * `f(1)` moet 1 zijn, dus `p2(0) = 0`

## Performantie

* aantal karaktervergelijkingen van algoritme \\( \Theta(n) \\)
    * na elke *verschuiving* van `P`
        * hoogstens 1 karakter van `T` dat vroeger reeds getest werd wordt getest
    * totaal aantal karaktervergelijkingen
        * hoogstens gelijk aan lengte van `T` + aantal verschuivingen
        * elke verschuiving: over minstens 1 positie
            * aantal verschuivingen \\( O(n) \\)
        * aantal karaktervergelijkingen \\( \Theta(n) \\)
            * elk karakter van `T` wordt minstens éénmaal getest
* voorbereiding \\( \Theta(m) \\)
    * berekening prefixfunctie
    * nieuwe prefixfunctie
    * foutfunctie
* totale performantie \\( \Theta(n+m) \\)

