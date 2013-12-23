
* standaardoperaties prioriteitswachtrij
    * **toevoegen**
    * **minimum verwijderen**
* bijkomende operaties
    * prioriteit verminderen
    * samenvoegen van prioriteitswachtrijen
* gebruikelijke implementatie is binaire heap in tabel
    * met \\(n\\) elementen
        * performantie van alle operaties \\(O(\lg{n})\\)
        * behalve voor samenvoegen: \\(O(n)\\)
            * één van tabellen moet gekopieerd worden
* als bepaalde operaties frequenter gebeurt dan toevoegen of minimum verwijderen
    * andere heap implementaties kunnen voor betere performantie zorgen
    * boom met expliciete wijzers naar knopen (tabel is te rigide structuur)
        * samenvoegen is efficiënt, terwijl andere operaties even efficiënt blijven
            * sommigen verbeteren efficiëntie van prioriteit verminderen

## Leftist heaps

* binaire bomen met heapvoorwaarde voor opgeslagen sleutels
* geen complete binaire bomen: trachten zo onevenwichtig mogelijk te zijn
    * linkerkant diep
    * rechterkant ondiep
* operaties efficiënt
    * al het werk gebeurt in rechterkant
* fundamentele operatie
    * samenvoegen van heaps
* toevoegen
    * samenvoegen van heap met triviale heap (bevat enkel element)
* minimum verwijderen
    * wortel verwijderen
    * deelbomen samenvoegen
* alle operaties \\(O(\lg{n})\\)
* construeren uit \\(n\\) elementen
    * op zelfde manier als bij binaire heap: \\(O(n)\\)
    * binaire heap slechts mogelijke leftist heap

## Skew heaps

* zelforganiserende versies van leftist heaps
* zeer eenvoudige implementatie
* fundamentele operatie
    * samenvoegen van heaps
* binaire bomen met heapvoorwaarde
    * zonder vormbeperkingen
* slechtste geval
    * individuele operaties \\(O(n)\\)
* reeks van \\(m\\) operaties
    * \\(O(m\lg{n})\\)
* geamortiseerde efficiëntie \\(O(\lg{n})\\)
    * van samenvoegen en toevoegen: \\(O(1)\\)

## Binomial queues

* bos van binomiaalbomen
    * elk met heapvoorwaarde
    * binomiaalboom met hoogte \\(h\\) heeft \\( \binom{h}{d} \\) knopen op diepte \\(d\\)
* slechtste geval
    * \\(O(\lg{n})\\) voor samenvoegen, toevoegen en minimum verwijderen
* geamortiseerd toevoegen \\(O(1)\\)
* performantie bijkomende operaties op gelokaliseerd element \\(O(\lg{n})\\)

## Fibonacci heaps

* veralgemening van binomial queues
* verstoren structuur van binomial queue door knopen met te weinig deelbomen toe te laten
* gebruiken snellere implementatie voor verminderen van prioriteit
* binomiaalbomen enkel samenvoegen wanneer nodig (lazy merging)
    * bevatten soms veel meer bomen
* geamortiseerde performantie
    * samenvoegen/toevoegen/prioriteit verminderen: \\(O(1)\\)
    * minimum verwijderen en gelokaliseeerd element verwijderen: \\(O(\lg{n})\\)
* interessant wanneer verminderen van prioriteit frequenter gebeurt dan verwijderen minimum
* verborgen constante van implementatie te groot
    * enkel theoretisch van belang

## Pairing heaps

* zelforganiserende, gestroomlijnde versie van binomial queue
* sneller dan andere heapstructuren wanneer verminderen van prioriteit vereist is
* gebruikt in `GNU C++` lib en `LEDA` lib
* analyse performantie is niet voltooid
* geamortiseerde performantie is niet voltooid
* geamortiseerde performantie van samenvoegen, toevoegen, minimum verwijderen en prioriteit verminderen
    * \\(O(\lg{n})\\)
* minimum verwijderen optimaal: bovengrens kan niet verbeterd worden
* reden efficiëntie
    * waarschijnlijk de eenvoud

## Relaxed heaps

* veralgemening van binomial queues
* twee soorten
    * *rank-relaxed heap*
        * zelfde geamortiseerde performantie als Fibonacci heap
    * *run-relaxed heap*
        * overtredingen toelaten tegen heapvoorwaarde
        * houdt alle overtreders bij in aparte gegevensstructuur
* performantie van minimum verwijderen en prioriteit geldt ook in slechtste geval
