## Vertex cover

* ongerichte graaf
* kleinste groep knopen die minstens één eindknoop van elke verbinding bevat
* nauw verwant met 
    * *edge cover*: kleinste groep verbindingen waarin elke knoop voorkomt
    * *independent set*: verzameling knopen - vertex cover

## Dominating set

* ongerichte graaf
* kleinste groep knopen zodat elke andere knoop met minstens een van de knopen uit groep verbonden is

## Graph coloring

### Vertex coloring

* ongerichte graaf
* knopen kleuren (met minimum aantal kleuren)
    * eindknopen van elke verbinding moeten verschillende kleur hebben
* bij plannings- en clusteringstoepassingen
* backtracking
* eenvoudige gevallen efficiënt oplosbaar: 
    * tweeledige grafen met twee kleuren
    * vlakke grafen
    * grafen met knopen met lage graad

### Edge coloring

* ongerichte graaf
* verbindingen kleuren (met minimum aantal kleuren)
    * verbindingen met gemeenschappelijke eindknoop hebben verschillende kleur
* bij planningstoepassingen
* benaderend algoritme van *Vizing*: \\(O(n^2)\\)
    * gebruikt hoogstens één kleur teveel

## Clique

* gegeven
    * ongerichte graaf
* grootste groep knopen die allemaal met elkaar verbonden zijn
* om clusters van verwante objecten op te sporen
* backtracking
* heuristieken
    * simulated annealing
* eenvoudigere gevallen efficiënt op te lossen
    * maximale clique (die niet meer uitgebreid kan worden)
    * grote dichte deelgrafen zoeken (niet noodzakelijk compleet)
    * cliques in vlakke grafen (bevatten geen clique groter dan vier)

## Independent set

* gegeven
    * ongerichte graaf
* grootste groep knopen zonder onderlinge verbindingen
* in codeertheorie of bij planningsproblemen
    * conflicten tussen elementen vermijden
* verwant met kleuren van knopen
    * verdeelt graaf in klein aantal groepen van knopen die onafhankelijk zijn
* identiek aan zoeken van clique in complementaire graaf
    * heeft alle verbindingen die originele niet heeft en omgekeerd
* duaal met maximaal koppelingsprobleem in grafen
    * grootste groep verbindingen zonder gemeenschappelijke knopen
    * kan soms zo geformuleerd worden en efficiënt opgelost worden

## Hamilton circuit/path

* gegeven
    * gericht of ongerichte graaf
* circuit dat elke knoop 1 maal bevat
* verwant met zoeken naar langste weg/circuit
* backtracking
    * eerst testen of graaf dubbel lijnsamenhangend is
* eenvoudigere gevallen gemakkelijker op te lossen
    * Eulercircuit: circuit dat elke verbinding 1 maal bevat
    * knopen meermaals bezoeken, maar zo weinig mogelijk
    * dichte grafen waarin snel een circuit kan gevonden worden
* Hamiltonweg: niet gesloten
    * efficiënt op te lossen als graaf gericht is zonder lussen
