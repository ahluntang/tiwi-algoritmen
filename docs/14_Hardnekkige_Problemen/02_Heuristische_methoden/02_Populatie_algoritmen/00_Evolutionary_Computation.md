
*  *Evolutionary Computation* (EC): geïnspireerd op de natuur
    * levende wezens kunnen evolueren
    * passen zich aan op hun omgeving
* kunnen gekarakteriseerd worden als computermodellen van evolutionaire processen
* bij elke iteratie een aantal bewerkingen toepassen aan de individuen van de huidige populatie
    * genereert de individuen voor de volgende generatie/iteratie
* bewerkingen
    * *recombination* of *crossover*: twee of meer individuen te combineren om nieuwe individuen te produceren
    * *mutation* of *modification*: zorgen ervoor dat individuen zichzelf aanpassen
* drijvende kracht in *evolutionary algoritmen*: *selectie* van individuen gebaseerd op hun *fitness*
    * individuen met hogere fitheid hebben grotere kans om gekozen te worden als (ouders van) leden bij de populatie voor de volgende iteratie
    * **survival of the fittest**
* categorieën
    * *Evolutionary Programming* (EP)
        * ontwikkeld voor machine intelligentie
        * oorspronkelijk voor discrete representaties van eindige staten machines
        * meeste huidige varianten voor continue optimalisatieproblemen
    * *Evolutionary Strategies* (ES)
        * voor continue optimalisatieproblemen
    * *Genetic Algorithms* (GA)
        * voor combinatorische optimalisatieproblemen

## Genetic Algorithms

* om combinatorisch optimalisatieproblemen op te lossen
* \\(P\\) : populatie van individuen
* populatie van nakomelingen genereren via *recombination* en *mutation*
* individuen voor volgende populatie worden geselecteerd uit de unie van de vorige populatie en de nakomelingen.

```
P ← GenerateInitialPopulation()
Evaluate(P)
while termination condition not met do
    P'  ← Recombine(P)
    P'' ← Mutate(P`)
    Evaluate(P``)
    P ← Select(P`` U P) // selectieschema
endwhile
```

### Beschrijving van de individuen

* populatie van individuen
    * individuen zijn niet noodzakelijk de oplossingen van het probleem
    * er kunnen gedeeltelijke oplossingen zijn of (meerdere) set(s) van oplossingen of elk object getransformeerd worden in 1 of meerdere oplossingen
* meest gebruikelijke oplossingsvoorstelling van combinatorische optimalisatie
    * bit-strings
    * permutaties van \\(n\\) integer getallen
    * boomstructuren of complexere structuren
* *genotypes*: individuen
* *phenotypes*: oplossingen gecodeerd door individuen
* *genotypes* en *phenotypes* worden gebruikt om een verschil tussen de voorstellingen van oplossingen en de oplossingen zelf te verduidelijken
    * keuze voor een juiste representatie is cruciaal voor een EC algoritme

### Evolutieproces

* tijdens elke iteratie beslissen welke individuen geselecteerd worden voor de populatie in de volgende iteratie
    * selectie schema
        * *generational replacement*: enkel individuen selecteren uit de nakomelingen
        * *steady state*: als ook individuen uit de huidige populatie geselecteerd kunnen worden
* populaties van vaste grootte
    * tenminste de beste individuen zitten altijd in de populatie
* populaties van variabele grootte
    * krimpende populatie
        * populatie van grootte 1 kan als stopcriterium dienen


### Neighborhood Structure

* *neighborhood function*: kent aan elke individu \\(i\\) een set van individuen toe die toegestaan zijn om als *recombination partner* voor \\(i\\)
    * om een nakomeling te maken
* als een individu met elke andere individu kan gerecombineerd worden: *unstructured populations*
    * anders *structured populations*


### Information Sources

* *two-parent crossover*
    * offspring komt van een koppel ouders
* recombinaties mogelijk met meer dan twee individuen om nieuwe individu te maken
    * *multi-parent crossover*
* populatiestatistieken kunnen gebruikt worden

### Infeasibility

* is oplossing aanvaardbaar, ondoenbaar?
    * wat als er geen volledig juiste oplossing is?
        * verbeteren?
        * toch laten meespelen?
* *infeasible individuals*
    * *reject*
    * *penalise*: tijdens het meten van de kwaliteit van een individu
    * *repair*

### Intensification Strategy

* fitheid van individuen verbeteren
* methodes
    * goede gebieden identificeren in zoekruimte via *local search* technieken
    * proberen goede onderdelen van individuelen expliciet te combineren
        * kan het zoekalgoritme begeleiden naar gebieden met individuen met bepaalde "goede" eigenschappen
        * *linkage learning* of *building block learning*

### Diversification Strategy

* voorkomen van vroegtijdige convergentie naar sub-optimale oplossingen
* *mutation*
    * simpele vorm: *random pertubation* van individu
        * produceert ruis (*noise*)
    * *crowding*
    * *preselection*
    * *fitness sharing* (*niching*)
        * fitheid om te reproduceren toegekend aan individu
        * aangepast aan andere individuen die zich in dezelfde regio bevinden in de zoekruimte



