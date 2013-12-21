
* verwachtingswaarde van performantie van woordenboekoperaties op gewone zoekboom: \\(O(\lg{n})\\)
    * als elke toevoegvolgorde even waarschijnlijk is
    * niet zeer realistisch
    * geldt niet noodzakelijk wanneer men toevoegen afwisselt met verwijderen
* random generator gebruiken om effect van operatievolgorde te neutraliseren
* bomen blijven random
    * ook na elke operatie
* verwachtingswaarde van performantie hangt enkel af van kwaliteit van random generator
    * \\(O(\lg{n})\\)

## Treap

* eenvoudigste boom van deze familie
* combineert binaire zoekboom met heap
* elke knoop krijgt ook nog *prioriteit*
*  *prioriteit* door random generator toegekend bij toevoegen
* prioriteit van knopen voldoen aan *heapvoorwaarde*
    * prioriteit van kind is minstens even groot als die van zijn ouder
* *treap* hoeft niet te voldoen aan *structuurvoorwaarde*
* als alle sleutels en prioriteiten verschillend zijn
    * slechts 1 treap mogelijk
* treap hangt niet af van toevoegvolgorde van sleutels
    * maar van random gegenereerde prioriteiten
* goede randomgenerator: elke reeks van \\(n\\) prioriteiten is even waarschijnlijk
    * treap is random binaire zoekboom

### Woordenboekoperaties

* zoeken
    * houdt geen rekening met prioriteiten
    * identiek aan zoeken in gewone binaire zoekboom
* toevoegen
    * als blad
    * nadien rekening houden met prioriteiten
    * knoop indien nodig naar boven roteren, desnoods tot bij wortel
    * stijgen: vereist ouderwijzers of stapel
    * elke rotatie herstelt heapvoorwaarde tussen kind en zijn ouder zonder heapvoorwaarde elders in boom te storen
    * aantal gevallen zeer beperkt
* verwijderen
    * hoogst mogelijke prioriteit geven
    * naar beneden roteren
    * als blad uit treap verwijderen

#### performantie

* verwachtingswaarde van efficiëntie van woordenboekoperaties: \\(O(\lg{n})\\)
* performantie niet zo goed als die van evenwichtige zoekbomen 
* implementatie veel eenvoudiger
    * prioriteit van knoop moet nooit meer aangepast worden
* moet minder rotaties uitvoeren dan splay trees
    * zelfs geen rotaties bij zoeken
* garanderen geen goede performantie voor reeks operaties
