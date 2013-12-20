
* Gebruikt expliciet de zoekgeschiedenis (geheugen)
    * om te ontsnappen aan lokale minima
    * voor een verkennende strategie (exploration)

## Basisconcepten: *local search*

### Short-term memory

* *short-term memory*: om te ontsnappen van lokale minima en om cycli te vermijden
    * geïmplementeerd als *tabu list*: houdt recent bezochte oplossingen bij
        * verbiedt bewegingen/keuzes (in richting) naar deze oplossingen
* buurt met mogelijke oplossingen bevat enkel oplossingen die niet behoren tot de *tabu list*.
  = *allowed set*
* na elke iteratie wordt de beste oplossing gekozen uit de *allowed set*
    * deze oplossing wordt toegevoegd aan de *tabu list*
    * oudste oplossing in *tabu list* wordt verwijderd (FIFO)
* dynamische restrictie: dynamic neighborhood search
* algoritme stopt wanneer stopcriterium voldaan is
    * of als de *allowed set* leeg is (dus wanneer alle oplossingen in \\(\mathcal{N}(s)\\) verboden zijn door de *tabu list*)

* De *tabu list* zorgt ervoor dat we niet terugkeren naar recent bezochte oplossingen
    * voorkomt oneindige cycli.
    * zorgt ervoor dat er ook schijnbaar minder interessante keuzes gemaakt worden

### Tabu tenure

* lengte \\(l\\) van *tabu list* (*tabu tenure*): beïnvloedt het geheugen van het zoekproces
    * kleine *tabu tenures*: zoekproces concentreert zich op kleine gebieden in de zoekruimte
    * grote *tabu tenures*: zoekproces moet grotere gebieden verkennen
        * want aantal verboden oplossingen is veel groter
* *tabu tenure* kan variëren tijdens het zoekproces
    * zorgt voor een meer robuust algoritme
    * bv herinitialiseren via random in het interval \\( [l_{min}, l_{max}] \\)

### Attributes

* implementatie als lijst met complete oplossingen niet praktisch
    * lijst van oplossing beheren is zeer inefficiënt
* praktischer: bewaren van *attributes* van oplossing.
    * meerdere *attributes*: voor elk attribuut een *tabu list* gebruiken
    * *attribuut*: een component van de oplossing/keuze of verschil met vorige oplossing
    * verlies van informatie: een attribuut verbieden kan meer dan 1 oplossing verbieden
* set van *attributes* en hun *tabu lists* definiëren de *tabu conditions*
    * worden gebruikt om de buurt van een oplossing te filteren en de *allowed set* te genereren

### Aspiration criteria

* een attribuut verbieden kan meer dan 1 oplossing verbieden
    * onbezochte oplossingen van goede kwaliteit zouden niet bij de *allowed set* komen
* *aspiration criteria* definieert de *aspiration conditions* om te gebruiken om de *allowed set* te construeren
    * kan ervoor zorgen om een oplossing toe te voegen aan de *allowed set* ook al wordt het verboden door de *tabu conditions*
* *asperation criteria*
    * oplossingen selecteren die beter zijn dan de huidige beste

### Long-term memory

* gebruiken van informatie dat verzameld wordt gedurende het voledig zoekproces
    * handig om het algoritme te begeleiden
* 4 principes
    * *recency*: geeft aan hoe lang (in welke iteratie) het geleden is dat een oplossing/attribuut in betrokken is geweest
    * *frequency*: geeft aan hoe vaak een oplossing/attribuut bezocht werd
        * deze informatie identificeert de regios of subsets van de oplossingenruimte waarin het zoekproces zich beperkt
        * toont ook aan waar er gedurende een groot aantal iteraties is gebleven
        * gebruiken om het zoekproces te diversifiëren
    * *quality*: in history van alles trends ontdekken en zien wat er beter wordt
        * kan gebruikt worden voor de constructie van de oplossing
    * *influence*: als je ooit een bepaalde keuze maakte en de oplossing is veel beter dan de vorige: keuze bewaren

