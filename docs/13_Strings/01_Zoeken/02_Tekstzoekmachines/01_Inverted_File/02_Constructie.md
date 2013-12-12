
## Hoe opbouwen/construeren?

* op basis van documenten die toegevoegd worden aan collectie
* inlezen documenten
    * termen eruithalen.
* moet geïnverteerd worden
    * op basis van termen moet je document kunnen krijgen
    * matrix inversie

![](/assets/tekstzoekmachines_matrixinversie.png)

## In-Memory Inversion

* voor de verschillende termen: lengte van lijsten bepalen ( \\(f_t\\) )
    * geeft aan hoeveel documenten de term bevat
    * geeft idee hoe lang lijst moet zijn
* geheugen alloceren voor al de lijsten
    * lengte gekend
    * tweede keer documenten overlopen en lijsten opvullen
    * in-memory ipv op schijf
        * anders zouden de lijsten te ver kunnen staan op schijf (fragmentatie)
    * alternatief: opvullen tot er geen geheugen meer is en dan wegschrijven
* nadeel: 
    * twee keer documenten overlopen
    * woordenschat moet in geheugen blijven zitten tijdens constructie

## Sort-Based Inversion

* collectie triples \\( \langle t, d, f_{d,t} \rangle \\) aanmaken tijdens inlezen documenten
    * triples bevatten precies de informatie om de lijsten op te vullen
* na aanmaak triples: gesorteerd op documenten \\(d\\)
* moet gesorteerd worden op termen \\(t\\)
    * mergesort gebruiken
* nadeel: woordenschat moet in geheugen blijven zitten tijdens constructie

## Merge-Based inversion

* gedeeltelijke index in geheugen opbouwen
* inverted lists met termen opbouwen per document
    * en volgende documenten tot geheugen vol is
* eens geheugen vol is: opslaan op schijf
    * als **reeks**/**run**
* verderdoen met volgende documenten (en nieuwe termen)
* uiteindelijk verschillende **reeksen**/**runs**
    * **mergen** tot een grotere run
    * uiteindelijk hou je 1 run over.
