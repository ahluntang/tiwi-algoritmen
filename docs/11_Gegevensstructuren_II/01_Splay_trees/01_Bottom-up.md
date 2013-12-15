
* eerst knoop zoeken, daarna splay-operatie van onder naar boven
    * ouderwijzers of stapel nodig

## Methodes

* knoop telkens met ouder op zoekweg roteren
    * niet voldoende om steeds performantie van \\(O(m\lg{n})\\) te verzekeren
    * knoop zelf wordt wortel, situatie voor andere knopen op zoekweg nauwelijks verbeterd
    * mogeljk om reeks van \\(m\\) operaties te vinden die \\(\Theta(mn)\\) duurt
        * bv: \\(1, 2, 3, ... n\\) toevoegen in ledige boom: resultaat is gelinkte lijst
            * knopen opzoeken in dezelfde volgorde: \\(\Theta(n^2)\\) bewerkingen
            * nadien weer precies dezelfde gelinkte lijst
* rotaties zorgvuldiger aanpakken
    * zig, zig-zag en zig-zig
    * op kleine voorbeelden
        * diepte van meeste knopen op toegangsweg wordt gehalveerd
        * slechts enkele ondiepe knopen zakken hoogstens twee niveau's
    * op grotere bomen
        * inefficiënte operaties worden gevolgd door rotaties die gunstig zijn voor volgende operaties
        * na efficiënte operaties kunnen minder goede of zelfs slecht uitvallende rotaties gebeuren
        * performantie van reeks blijft goed

### Zig

* ouder van knoop \\(c\\) is wortel
    * beide knopen roteren  
    ![](/assets/splaytrees_bu_zig.png)

### Zig-zag en zig-zig

* knoop \\(c\\) heeft nog grootouder \\(g\\)
* vier gevallen die uiteenvallen in twee groepen van twee (naargelang ouder \\(p\\) linker- of rechterkind is van grootouder \\(g\\))
* stel \\(p\\) is linkerkind van \\(g\\)
    * knoop \\(c\\) is rechterkind van \\(p\\) : zig-zag
        * \\(p\\) en \\(c\\) naar links
        * \\(g\\) en \\(c\\) naar rechts  
        ![](/assets/splaytrees_bu_zigzag.png)
    * knoop \\(c\\) is linkerkind van \\(p\\) (drie knopen lagen op 1 lijn): zig-zig
        * eerst \\(g\\) en \\(p\\) naar rechts
        * dan \\(p\\) en \\(c\\) naar rechts  
        ![](/assets/splaytrees_bu_zigzig.png)

## Woordenboekoperaties

### Zoeken

* zoals bij gewone zoekboom zoeken
    * nadien laatste knoop wortel maken via splay-operaties
* wortel bevat ofwel gezochte sleutel ofwel voorloper/opvolger

### Toevoegen

* zoals bij gewone binaire zoekboom
    * nadien nieuwe knoop wortel maken via splay-operaties
* alternatieve manier (geamortiseerd trager)
    * eerst toe te vogen sleutel zoeken
    * wortel bevat ofwel sleutel ofwel opvolger/voorloper
    * als sleutel niet aanwezig is: opslaan in nieuwe wortelknoop
        * linkerkind: wordt voorloper met zijn linkse deelboom
            * rechterkind wordt zijn rechtse deelboom
        * rechterkind: wordt opvolger met zijn rechtse deelboom
            * linkerkind wordt zijn linkse deelboom

### Verwijderen

* zoals bij gewone binaire zoekboom
    * ouder van de fysisch verwijderde knoop wortel maken, via splay-operaties
    * als sleutel niet gevonden wordt: laatste knoop op zoekweg wortel maken
* alternatieve methode (geamortiseerd trager)
    * knoop zoeken met te verwijderen sleutel via splay-operatie
    * als wortel gezochte sleutel bevat
        * verwijderen
        * deelbomen samenvoegen
    * samenvoegen van splay trees (join operatie)
        * grootste element in linkse deelboom zoeken en wortel maken via splay-operatie
        * kleinste element in rechtse deelboom zoeken en wortel maken via splay-operatie

