* keuzes die in oplossingen van slechtere kwaliteit dan huidige oplossing resulteren toch toestaan
    * om te kunnen ontsnappen uit lokale minima
* kans om zulke slechte keuzes te maken verkleint naarmate het aantal iteraties stijgt
* is memory-less (basisversie van SA)

## Pseudocode
```
s ← GenerateInitialSolution()
T ← T0
while termination condition not met do
    s ← PickAtRandom(N(s))
    if( f(s') < f(s) ) then
        s ← s' 
    else
        Accept s' as new solution with probability p(T,s',s)
    endif
    Update(T)
endwhile
```
* beginnen met "bepaalde" oplossing
* initialiseren van temperatuur \\(T\\)
* bij elke iteratie wordt oplossing \\(s' \in \mathcal{N}(s)\\) gezocht
    * nieuwe oplossing wordt geaccepteerd op basis van \\(f(s)\\), \\(f(s')\\) en \\(T\\)
        * als \\(f(s') < f(s)\\)
        * als \\(f(s') \ge f(s)\\) indien kansfunctie `p(T,s',s)` `true` is
    * temperatuur bijwerken
* iteratie herhalen tot stopcriterium voldaan is

* kansfunctie \\(p(T,s',s)\\)
    * vaak wordt Boltzmann distributie gebruikt \\[ e^{-\frac{f(s')-f(s)}{T}} \\]
* temperatuur wordt na elke iteratie verminderd
    * in het begin van het zoekproces is de kans om slechtere keuzes te maken groter

= combinatie van random stappen en *iterative improvement*

### Temperatuur verlagen: cooling schedule

* cruciaal voor de performantie van het algoritme
* definieert waarde van \\(T\\) na elke iteratie \\(k\\): \\(T_{k+1} = Q(T_k,k)\\)
* algoritme moet convergeren naar globaal minimum naarmate k groter wordt
    * logaritmisch: \\( T_{k+1} = \frac{\tau}{\log{(k+k_0)}} \\)
        * te traag voor praktische doeleinden
        * sneller koelschema nodig
    * eenvoudiger koelschema: \\( T_{k+1} = \alpha T_k \\)
* regels uit koelschema kunnen variëren gedurende het zoekproces
    * doel: balans tussen diversificatie en intensificatie verfijnen

### Starttemperatuur \\(T_0\\)

* zoekruimte *samplen*
    * met random stappen
    * om ruwe schatting/evaluatie te maken van het gemiddelde en de variantie van de waarden voor de *objective functions*
