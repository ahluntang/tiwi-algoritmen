* deelverzameling van verbindingen waarin elke knoop hoogstens eenmaal voorkomt
    * eindknopen van verbindingen heten gekoppeld
* maximale koppeling
    * koppeling met grootste aantal verbindingen (gekoppelde knopen)
* verbindingen met gewicht: drukken voorkeur voor bepaalde koppelingen uit
    * gewoen koppelingsprobleem zoekt koppeling met grootste totale gewicht

* `bipartite graph` ( tweeledig)
    * knopen kunnen verdeeld worden in twee deelverzamelingen \\(L\\) en \\(R\\)
* als elke uitvoerder slechts één tak tegelijk kan verrichten
    * maximale ongewogen koppeling zorgt ervoor dat er zoveel mogelijk taken tegelijk uitgevoerd worden
* nauw verband tussen koppelingen en maximale stroom
    * op te lossen met dezelfde efficiëntie
* tweeledige graaf transformeren tot stroomnetwerk
    * producent invoeren die met alle knopen van \\(L\\) verbonden wordt
    * verbruiker invoeren die met alle knopen van \\(R\\) verbonden wordt
    * oorspronkelijke verbindingen van graaf richting geven
        * van \\(L\\) naar \\(R\\)
    * elke verbinding krijgt een capaciteit gelijk aan \\(1\\)
* voor elke koppeling met \\(k\\) verbindingen bestaat een overeenkomstige gehele stroomverdeling in dat nieuw stroomnetwerk, met als netwerkstroom \\(k\\)
    * producent stuurt éénheid stroom naar elke knoop van \\(L\\) die tot koppeling behoort
    * eenheid loopt via koppeling naar overeenkomstige knoop van \\(R\\)
    * eenheid loopt van die knoop uit \\(R\\) naar verbruiker
* voor elke gehele stroomverdeling in stroomnetwerk met netwerkstroom \\(k\\) is er koppeling met \\(k\\) verbindingen
    * stroomverdeling is geheel en capaciteiten van verbindingen is één
        * stroom in elke verbinding: \\(1\\) of \\(0\\)
    * als eenheid stroom van producent in knoop van \\(L\\) aankomt
        * moet over precies één verbinding naar overkant
    * elke knoop van \\(R\\) kan slechts stroom ontvangen van één enkele knoop uit \\(L\\)
        * verbinidngen bepalen overeenkomstige koppeling
        * netwerkstroom = \\(k\\)
        * evenveel verbindingen in deze koppeling
* maximale koppeling komt overeen met maximale gehele stroomverdeling
    * oplossen met methode van Ford-Fulkerson
    * levert stroomverdeling op die capaciteiten respecteert
        * geheel als capaciteiten geheel zijn
        * stroom in elke vergrotende weg is geheel
* aantal verbindingen \\(k\\) van maximale koppeling is niet groter dan aantal knopen in kleinste van twee  verzamelingen \\(L\\) en \\(R\\): zeker \\(O(n)\\)
    * breedte-eerst zoeken voor vergrotende wegen: max koppelingsprobleem \\(O(nm)\\)
