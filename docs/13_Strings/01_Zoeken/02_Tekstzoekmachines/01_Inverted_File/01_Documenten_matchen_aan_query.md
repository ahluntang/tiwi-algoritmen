
## Stappenplan

* \\(A_d\\) accumulator voor elk document aanmaken
* voor elke term \\(t\\) uit query \\(q\\)
    * \\(w_{q,t}\\) berekenen (elementen van vector q (IDF: inverse document frequenty)) en inverted list voor \\(t\\) ophalen
    * voor elk paar \\( \langle d, f_{d,t} \rangle \\) uit de inverted list
        * \\(w_{d,t}\\) berekenen (elementen van vector d (TF: term frequency)  )
        * \\(w_{d,t} \times w_{q,t}\\) optellen bij accumulator \\(A_d\\)
    * \\(W_d\\)-waarden ophalen (lengte van vector d)
    * voor elke \\(A_d > 0 \\)
        * relevantie document met query berekenen
        * \\(S_{q,d}\\) bepalen  \\[ S_{q,d} = \sum_{t}{ \frac{w_{d,t}.w_{q,t}}{W_d.W_q} } \\]

 = Document level index

* geeft aan dat term in document voorkomt
* geeft niet aan waar in document
    * niet mogelijk om te weten of termen dicht bij elkaar staan.

## Word Level Index

* ook locaties van woord in document opslaan
* handig als je woordposities nodig hebt
    * woorden dicht bij elkaar?
    * zoeken naar zinnen
* posities moeten gebaseerd zijn op aantal woorden (niet op bytes)
* aanpassing inverted lists
    * in plaats van tuples met documentnummer en aantal keer dat term gevonden werd
    * ook pointers bewaren
        * verwijzen naar locatie in het document
    * als document hierarchische structuur heeft (hoofdstukken, secties, paragrafen...)
        * locatie opslaan als hoofdstukken-gaps, secties-gaps, paragrafen-gaps
        * laat zoeken toe binnen dezelfde paragraaf/zin.

## Aandachtspunten betreffende implementatie

* Documenten worden geïdentificeerd met **rangschikbare** getallen, startend vanaf 1.
* woordenschat: bevat **elke term** uit de documenten
    * opgeslagen in een **gemakkelijk uitbreidbare** structuur (B-tree)
    * kan vooraf bewerkt zijn (stemming, stopping)
* inverted lists: lijsten worden **zonder fragmentatie** opgeslagen
    * bevat sequentie van
        * **pairs/tuples** met **documentnummers** en **aantal** keer dat term in document voorkomt
        * eventueel aangevuld met **woordposities**
* **ranking**: relevantie document met query
    * aan de hand van **accumulators** en **term-by-term processing** van inverted lists.

## Zinnen zoeken

* zin: elk woord moet in document staan
* zin als term in B-tree gebruiken?
    * moeilijk, niet schaalbaar

### Methodes

* eerst bag-of-words gebruiken
    * documenten zoeken waar ze elke term in voorkomt (AND-operators)
    * kijken of woorden samen staan (woordposities nodig)  
    = False match
* woordposities al erbij nemen tijdens evaluatie van query
* **gedeeltelijke** woordparen opnemen in lijst van termen
