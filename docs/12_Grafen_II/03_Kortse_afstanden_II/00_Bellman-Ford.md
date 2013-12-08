
## Kortste afstanden vanuit 1 knoop

* dynamisch programmeren
* combinatie van `breedte-eerst` zoeken (*niet-gewogen grafen*) met `kortste afstanden` (*gewogen grafen*)
* als graaf geen negatieve lussen heeft
    * kortste wegen ook geen lussen
    * bevatten hoogstens \\( n - 1 \\) verbindingen
* recursief verband: tussen kortste wegen met max \\(k\\) verbindingen en kortste wegen met max \\(k-1\\) verbindingen.
* als: 
    * \\( d_i(k) = \\) kortste weg met hoogstens \\(k\\) verbindingen vanuit startknoop naar knoop \\( i \\).
    * \\( g_{ij} = \\) gewicht van verbinding \\( (i,j) \\) 
* dan geldt:
    \\[ d_i(k) = \min\\{ d_i(k-1), \min_{j \in V}\\{ d_j(k-1)+g_{ji}\\} \\} \\]
* gezochte afstanden zijn waarden \\( d_i(m-1) \\) voor elke knoop \\( i \\).
* om \\( d_i(k) \\) te bepalen voor elke knoop \\( i \\):
    * telkens afstanden \\( d_j(k-1) \\) nodig  voor verschillende (alle) waarden van \\(j\\).
    * **optimale deelstructuur**: *deeloplossingen* zijn *onafhankelijk* en *overlappend*

## algoritme

* \\(n-1\\) iteraties
* kortste wegen mogen telkens \\(1\\) verbinding langer worden
* voor elke knoop: onderzoeken of kortste afstand verbeterd kan worden via knopen waarvan hij buur is.
    * alle voorlopige afstanden in tabel bijhouden
    * om kortste wegen te reconstrueren: voorlopersknoop op elke voorlopige kortste weg opslaan.
* in principe per iteratie: alle \\(m\\) verbindingen testen: \\(O(nm)\\)
    * slechter dan `Dijkstra`
    * maar gewichten zijn gewoonlijk positief.

## implementatie
### via wachtrij (queue)

* meestal niet nodig om in elke iteratie alle verbindingen te onderzoeken.
    * als in iteratie voorlopige kortste afstand tot knoop niet aangepast wordt: zinloos om bij volgende iteratie verbindingen vanuit die knoop te onderzoeken.
* enkel knopen waarvan afstand door huidige iteratie gewijzigd werd in wachtrij plaatsen.
* enkel buren van deze knopen worden bij volgende iteratie getest
    * ~ `breedte-eerst` zoeken
* knoop moet niet meer nagaan of afstand van knopen waarvan hij buur is verbeterd wrd (*pull-based*), maar wordt door die knopen van de wijziging verwittigd (*push-based*).
    * heeft geen invloed op asymptotische waarden voor performantie
* als: knoop uit wachtrij verwijderd wordt en afstand van \\(1\\) van zijn buren aangepast wordt
    * die buur moet in wachtrij gestopt worden, ook als hij er reeds vroeger uit verwijderd werd
    * als buur reeds in wachtrij zit: kan blijven zitten
    * elke knoop kan hoogstens \\(n-1\\) maal in wachtrij terechtkomen
* niet eenvoudig na te gaan of grote graaf lussen met negatief gewicht heeft
    * met dergelijke lus zou algo nooit stoppen
    * beveiliging
        * aantal iteraties bijhouden
        * als wachtrij niet leeg is na n iteraties: graaf heeft **negatieve lus**

### via deque

*in praktijk zeer snel, maar kan in bepaalde gevallen zeer inefficiënt uitvallen*

* de te onderzoeken knopen in `deque` bewaren in plaats van `queue`.
* knoop wordt:
    * vooraan weggenomen (zoals `queue`)
    * voor- of achteraan toegevoegd:
        * vooraan: als afstand wordt aangepast en knoop **reeds vroeger** in `deque` zat
        * achteraan: als knoop nog niet in `deque` zat
* reden:
    * als knoop \\(i\\) ooit in `deque` zat
        * werd verwijderd en alle buren werden onderzocht.
    * stel: afstand van sommige buren werd aangepast
        * knwamen terecht in `deque`
        * als die nog steeds in `deque` zitten op moment dat afstand opnieuw aangepast wordt
            * mogelijk dat afstand nogmaals zou wijzigen met nieuwe afstand
        * als het achteraan wordt toegevoegd
            * buren worden eerder verwijderd waarbij oude afstand gebruikt wordt om zijn buren te onderzoeken
        * veel minder knopen moeten opnieuw onderzocht worden als men ze vooraan toevoegt.
    * in praktijk onderzoekt deze implementatie minder knopen dan via `queue`.
        * één van snelste methoden voor ijle grafen.
    * slechtste geval: \\( O(\min\\{nmC,m2^n\\}) \\) 
        * waarbij \\(C\\) absolute waarde van grootste gewicht van verbinding voorstelt

## Vergelijking Bellman-Ford met Dijkstra

* `BF`: laat negatieve gewichten toe, flexibeler en gedecentraliseerd dan `Dijkstra`
    * afstand van buren kan ook mogelijks verbeterd worden
    * buren worden verwittigd
    * ideaal voor netwerk (netwerkrouters)
        * elke knoop houdt `vector` van afstanden tot andere knopen bij
            * *distance vector protocol*
            * heeft lokale kennis van netwerk ( \\( \Leftrightarrow \\) Dijkstra: globale kennis)
            * \\( \Leftrightarrow \\) *path vector protocol*: elke knoop houdt volledige weg naar elke andere knoop bij
                * vereist meer geheugen
