
* splay-operatie tijdens afdaling
    * gezochte knoop zal wortel zijn als we hem bereiken
    * geen ouderwijzers of stapel nodig
    * eenvoudiger te implementeren en efficiënter
* tijdens afdaling wordt boom in 3 zoekbomen opgedeeld
    * alle sleutels in linkse boom \\(L\\) zijn kleiner dan sleutels in middelste boom \\(M\\)
    * alle sleutels in rechtse boom \\(R\\) zijn groter dan die in \\(M\\)
    * initieel is \\(M\\) oorspronkelijke boom en \\(L\\) en \\(R\\) zijn ledig
* zoeken begint bij wortel van \\(M\\)
    * huidige knoop op zoekweg blijft steeds wortel van \\(M\\)
* stel: vanuit \\(p\\) naar zijn linkerkind \\(c\\)
    * twee hoofdgevallen
        * linkerkind \\(c\\) is laatste knoop op zoekweg
        * linkerkind \\(c\\) is niet laatste knoop op zoekweg

## Naar laatste knoop op zoekweg: zig

* \\(c\\) is gezochte knoop of \\(c\\) mist minstens één kind en we moeten net die kant op
* knoop \\(p\\) wordt nieuwste kleinste element in \\(R\\) (rechtse deelboom van \\(p\\) gaat mee)
* linkse deelboom van \\(p\\) wordt nieuwe \\(M\\) (met \\(c\\) als wortel)  
  ![](/assets/splaytrees_td_zig.png)

## Niet naar laatste knoop op zoekweg: zig-zig of zig-zag

* naar linkerkind \\(l\\) van \\(c\\) (\\(p\\), \\(c\\) en \\(l\\) liggen op één lijn): zig-zig
    * eerst \\(p\\) en \\(c\\) naar rechts roteren (bovenste knopen)
    * daarna wordt \\(c\\) kleinste element van \\(R\\) (nieuwe rechtse deelboom van \\(c\\) gaat mee)
    * linkse deelboom van \\(c\\) wordt nieuwe \\(M\\), met \\(l\\) als wortel  
      ![](/assets/splaytrees_td_zigzig.png)
* naar rechterkind \\(r\\) van \\(c\\) (\\(p\\), \\(c\\) en \\(l\\) niet op één lijn): zig-zag
    * \\(p\\) wordt kleinste element van \\(R\\) (rechtse deelboom van \\(p\\) gaat mee)
    * \\(c\\) wordt nieuwe grootste element in \\(L\\) (linkse deelboom van \\(c\\) gaat mee)
    * rechtse deelboom van \\(c\\) wordt nieuwe \\(M\\), met \\(r\\) als wortel
      ![](/assets/splaytrees_td_zigzag.png)
    * geen rotatie: kan ook behandeld worden als zig
        * \\(p\\) wordt nieuwe kleinste element van \\(R\\) (rechtse deelboom van \\(p\\) gaat mee)
        * linkse deelboom van \\(p\\) wordt nieuwe \\(M\\), met \\(c\\) als wortel
        * slechts 1 niveau afgedaald in plaats van twee
            * meer iteraties nodig
        * minder gevallen te onderscheiden

## Splay-operatie voltooien

* als gezochte knoop \\(c\\) wortel van \\(M\\) geworden is
* drie deelbome nsamenvoegen tot één boom met wortel \\(c\\)
* alle sleutels in linkse deelboom van \\(c\\) zijn groter dan sleutels in \\(L\\)
    * wortel van \\(L\\) word meest rechtse plaats in die deelboom
* analoog: wortel van \\(R\\) wordt meest linkse plaats in rechterdeelboom van \\(c\\)

## Woordenboekoperaties

### Zoeken

* maakt knoop met sleutel wortel
* als sleutel niet gevonden wordt, dan wordt voorloper of opvolger wortel

### Toevoegen

* analoog als alternatieve versie van bottom-up
* voorloper of opvolger van nieuwe sleutel wordt wortel
* nieuwe knoop met toegevoegde sleutel krijgt
    * als linkerkind voorloper met zijn linkse deelboom en als rechterkind zijn rechtse deelboom
    * als rechterkind opvolger met zijn rechtse deelboom en als linkerkind zijn linkse deelboom

### Verwijderen

* analoog als alternatieve versie van bottom-up
* eerst sleutel zoeken
* als gevonden: staat bij wortel
* wortel verwijderne en deelbomen samenvoegen via **join**operatie

## Performantie

* na topdown operatie is boom niet noodzakelijk dezelfde als analoge bottom-up operatie
* geammorteerde efficiëntie van alle operaties: \\(O(\lg{n})\\)
