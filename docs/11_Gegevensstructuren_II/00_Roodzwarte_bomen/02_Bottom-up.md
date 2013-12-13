## Toevoegen

* op gewone manier toevoegen met rode kleur
* als ouder ook rood is: twee opeenvolgende rode knopen
    * storing verwijderen door rotaties en kleurwijzigingen
    * desnoods tot bij wortel naar boven schuiven
* als ouder \\(p\\) van nieuwe knoop \\(c\\) rood is: ouder kan geen wortel zijn
    * er is steeds grootouder \\(g\\) die zwart is
    * zes mogelijke gevallen, vallen uiteen in twee groepen van drie (naargelang \\(p\\) linker- of rechterkind is van \\(g\\))

### stel: \\(p\\) is linkerkind van \\(g\\)

* rode ouder \\(p\\) elimineren
    * door zwart te maken (vereist zwarte knoop die rood moet worden)
    * door weg te nemen via rotatie naar rechts (als die niet opnieuw twee opeenvolgende rode knopen oplevert in rechterdeelboom)
* twee hoofdgevallen: naargelang **kleur van broer** \\(b\\) van \\(p\\)

#### broer \\(b\\) van ouder \\(p\\) is rood

* ligging van knoop \\(c\\) tegenover ouder \\(p\\) is onbelangrijk
* rode ouder \\(p\\) kan zwart worden
    * zwarte grootouder \\(g\\) moet rood worden
    * rode broer \\(b\\) moet zwart worden
* als rood geworden grootouder \\(g\\) ook een rode ouder heeft, dan is het **probleem opgeschoven** in richting van wortel
    * oplossen door een van andere gevallen
    * of verder omhoog schuiven (in slechtste geval tot bij wortel)
![](/assets/rzboom_bu_add_rodebroer.png)

#### broer \\(b\\) van ouder \\(p\\) is zwart

* knoop \\(c\\), ouder \\(p\\) en grootouder \\(g\\) moeten op één lijn liggen
    * indien niet geval, knoop \\(c\\) met zijn ouder \\(p\\) roteren naar links  
    ![](/assets/rzboom_bu_add_cpglijn.png)
* rode ouder p wegnemen via rotatie naar rechts
    * bezorgt extra knoop in rechterdeelboom
* \\(p\\) komt bovenaan: heeft invloed op twee wegen
    * **zwarte kleur overnemen** van grootouder \\(g\\)
* overgebrachte **grootouder \\(g\\) moet rood** worden om zwarte hoogte niet te ontregelen

![](/assets/rzboom_bu_add_zwartebroer.png)

### performantie

* in totaal 
    * hoogstens twee rotatie nodig om boom te herstellen
    * eventueel voorafgegaan door \\(O(\lg{n})\\) keer opschuiven (hoogte boom)
* roteren en opschuiven: \\(O(1)\\)
* initieel afdalen: \\(O(\lg{n})\\)
* toevoegen steeds \\(O(\lg{n})\\)


## Verwijderen

* ingewikkelder: steeds nagaan of bepaalde knopen wel bestaan
    * **nullknoop** gebruiken: die blad (nullpointer) voorstelt
        * structuur is dezelfde als die van gewone knopen
        * kleur is steeds zwart
        * in praktijk: één nullknoop voor alle bladeren
            * alle nullwijzers worden door wijzer naar deze knoop vervangen
        * kind kan nu steeds naar ouder verwijzen, ook als het blad is
    * verwijderen via rotaties
* eerst knoop (voorloper  of opvolger) verwijderen zoals bij gewone zoekboom

### te verwijderen knoop: rood

* heeft geen 'echte' kinderen (enkel zwarte bladeren)
* heeft geen gevolgen voor zwarte hoogten

### te verwijderen knoop: zwart

* kijken naar kinderen
    * één rood kind
    * of geen 'echte' kinderen

#### te verwijderen zwart kind heeft rood kind

* rood kind kan zwarte kleur van verdwenen ouder overnemen
* zwarte hoogte blijft intact

#### te verwijderen zwart kind heeft geen 'echte' kinderen

* zwarte kleur mag niet zomaar verdwijnen
    * kleur geven aan één van kinderen (zwart blad)
    * kind wordt dubbel zwart: anomalie moet verwijderd worden
* dubbel zwarte kleur kan opgeschoven worden
    * als wortel dubbel zwart wordt: overtollig zwarte kleur kan verdwijnen
        * wortel telt in geen enkele zwarte hoogte mee
* als dubbel zwarte knoop \\(c\\) geen wortel is: er is ouder \\(p\\)
    * acht mogelijke gevallen, twee groepen van vier, naargelang \\(c\\) linker- of rechterkind is van \\(p\\)

##### stel: \\(c\\) is linkerkind van \\(p\\)

* kleur van ouder \\(p\\) is willekeurig
* broer \\(b\\) van \\(c\\) moet zwart zijn
* indien broer \\(b\\) van \\(c\\) rood is
    * knoop \\(c\\) nieuwe zwarte broer bezorgen
    * zwart linkerkind \\(l\\) van broer \\(b\\) gebruiken
        * zwarte hoogte van broer \\(b\\) is minstens twee want \\(c\\) is dubbelzwart  
         \\( \Rightarrow l \\) is inwendige knoop
    * ouder \\(p\\) en broer \\(b\\) naar links roteren
        * \\(b\\) zwart maken
        * \\(p\\) rood maken
    * dubbelzwarte knoop heeft nu nieuwe zwarte broer \\(l\\) en rood geworden ouder \\(p\\)  
    ![](/assets/rzboom_bu_del_rodebroer.png)

###### Zwarte broer \\(b\\) van \\(c\\) heeft twee zwarte kinderen

* \\(b\\) kan rood worden
* vrijgekomen zwarte kleur samen met overtollig zwart van \\(c\\) **doorschuiven naar ouder** \\(p\\)
    * als ouder zwart was, probleem is doorgeschoven
    * desnoods tot bij wortel

###### Zwarte broer \\(b\\) van \\(c\\) heeft rood kind

* broer \\(b\\) moet samen met zijn ouder \\(p) en zijn rood kind **op 1 lijn** liggen
    * kind van broer \\(b\\) met broer \\(b\\) roteren als rood kind niet op 1 lijn ligt met broer \\(b\\) en ouder \\(p\\)
    * broer \\(b\\) en rood linkerkind \\(l\\) roteren naar rechts
    * \\(b\\) rood maken en \\(l\\) zwart
    * nieuwe broer \\(l\\) van \\(c\\) is zwart en heeft rood rechterkind \\(b\\)
     ![](/assets/rzboom_bu_del_kbplijn.png)
* broer \\(b\\) heeft rood rechterkind
    * kleur van linkerkind \\(l\\) van \\(b\\) is willekeurig
    * linkerdeelboom extra knoop bezorgen via rotatie naar links
        * kan overtollige zwarte kleur overnemen
    * rechterdeelboom verliest zwarte knoop
    * rood rechterkind \\(r\\) van \\(b\\) kan zwart worden
    * roteer ouder \\(p\\) en broer \\(b\\) naar links
        * broer \\(b\\) krijgt kleur vna ouder \\(p\\)
        * \\(p\\) en \\(r\\) worden zwart  
    ![](/assets/rzboom_bu_del_roodrechterkind.png)

### Performantie

* als broer \\(b\\) van \\(c\\) is zwart is
    * één of twee rotaties
    * of probleem naar boven schuiven
* als broer \\(b\\) van \\(c\\) is rood is 
    * voor zwarte broer \\(b\\) zorgen
        * ofwel met één of twee rotaties
        * ofwel met twee kleurwijzigingen (zonder op te schuiven)
* verwijderen heeft hoogstens drie rotaties nodig, eventueel voorafgehaan door \\(O(\lg{n})\\) keer opschuiven
    * roteren en opschuiven: \\(O(1)\\)
    * initieel afdalen: \\(O(\lg{n})\\)
* verwijderen is steeds \\(O(\lg{n})\\)




