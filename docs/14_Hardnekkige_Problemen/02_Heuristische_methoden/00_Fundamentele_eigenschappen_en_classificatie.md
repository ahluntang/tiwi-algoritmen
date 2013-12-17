
## Karakteristieken van metaheuristieken

* Metaheuristieken zijn strategieën die het zoekproces "begeleiden"
* doel: efficiënt de zoekruimte verkennen om (bijna) optimale oplossingen te vinden
* technieken: variëren van simpele lokale zoekprocedures tot complexe leerprocessen
* algoritmes zijn benaderend en vaak niet-deterministisch
* bevatten mechanismes om te voorkomen men in bepaalde gebieden van zoekruimte vastzit
* basisconcepten van metaheuristieken worden beschreven op een abstract niveau
* kunnen gebruikmaken van domein-specifieke kennis in de vorm van heuristieken die op een hoger niveau bestuurd worden
* meer geavanceerde metaheuristieken gebruiken **search experience** om het zoekproces te begeleiden
    * waar je al geweest zijt onthouden (bewaren)

### Balans tussen diversification & intensification

* Diversification: zoekruimte verkennen (exploration) en rondkijken of je toch niet in lokale put zit
* Intensification: gebruikmaken (exploitation) van vergaderde **search experience** om naar juiste oplossing te gaan

## Classificatie

### Nature-inspired vs. non-nature inspired

* Op basis van oorsprong van algoritme
* Natuurgebaseerd: 
    * **Genetic Algorithms**
    * **Ant Algorithms**
* Niet-natuurgebaseerd: 
    * **Tabu Search**
    * **Iterated Local Search**
* Niet elk algoritme kan zo ingedeeld worden (zoals hybride algoritmen)
    * soms onduidelijk om kenmerken en eigenschappen aan één van de klassen toe te kennen.

### Population-based vs. single point search

* werkt het algoritme met een populatie of een enkele oplossing?
* single solution: **trajectory methods**
    * gebruiken *local search*gebaseerde metaheuristieken
    * **Tabu Search**
    * **Iterated Local Search**
    * **Variable Neighborhood Search**
    * beschrijven traject in zoekruimte tijdens de zoektocht
* population-based
    * zoekprocessen beschrijven evolutie van een **set punten** in de zoekruimte
        * werkt steeds op collectie goede oplossingen

### Memory usage vs. memory-less methods

* gebruikmaken van zoekgeschiedenis
    * recente stappen bijhouden
    * parameters over zoekproces bijhouden en optellen
* memory-less
    * Markov proces: volgende oplossing vinden en al de rest vergeten
        * volgende oplossing moet dus gezocht worden aan de hand van huidige staat

