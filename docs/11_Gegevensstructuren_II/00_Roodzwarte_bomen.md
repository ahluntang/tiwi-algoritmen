
## Definitie

* binaire zoekboom die 2-3-4 bomen simuleert
    * 3-knoop: 2 binaire knopen
    * 4-knoop: 3 binaire knopen
* 2 soorten ouder-kind verbindingen
    * originele verbindingen van 2-3-4 boom: zwart
    * nieuwe verbindingen: rood
* kleur kan opgeslagen worden bij
    * verbindingen
    * kinderknopen
* hoogte laag houden
    * beperkingen opleggen aan manier waarop knopen op elke (dalende) weg vanuit wortel gekleurd worden
* knoopstructuur ~ binaire zoekboom
    * nieuw veld voor kleur
    * ontbrekende kinderen: nullpointer
        * conceptueel beschouwen als wijzers naar uitwendige (kinderloze) knopen
            * bevatten geen gegevens
            * wel kleur
    * gewone knopen: inwendig

### binaire boom waarbij

* elke knoop rood of zwart gekleurd is
* elk blad (uitwenidge knoop) zwart is
* rode knoop steeds 2 zwarte kinderen heeft
* elke mogelijke weg vanuit knoop naar blad heeft steeds evenveel zwarte knopen
    * zwarte hooogte van knoop (knoop zelf wordt niet meegerekend, blad wel)
* wortel is zwart

## Eigenschappen

* deelboom met wortel \\(w\\) en zwarte hoogte \\(z(w)\\) heeft tenminste \\(2^{z(w)}-1\\) inwendige knopen
* inductie op gewone hoogte van deelboom
    * hoogte = 0
        * bevat enkel blad: 
            * zwarte hoogte = 0
        * geen inwendige knopen: \\(2^0-1\\) 
    * positieve hoogte
        * veronderstel dat eigenschap geldt voor elke kleinere hoogte
        * wortel \\(w\\) van deelboom met positieve hoogte is inwendige knoop die steeds 2 kinderen heeft (eventueel bladeren)
        * zwarte hoogte van
            * rood kind: \\(z(w)\\)
            * zwart kind: \\(z(w)-1\\)
        * hoogte van beide kinderen is kleiner dan die van \\(w\\)
        * bij veronderstelling geldt de eigenschap voor de deelbomen waarvan ze wortel zijn
            * deelboom met wortel \\(w\\) heeft minstens \\( 2 \times (2^{z(w)-1}-1) +1 = 2^{z(w)}-1 \\) inwendige knopen
    * stel dat 
        * rood-zwarte boom met \\(n\\) inwendige knopen hoogte \\(h\\) heeft (blad meegerekend)
        * er geen 2 opeenvolgende rode knopen op elke weg vanuit knoop naar blad mogen voorkomen
    * dit impliceert dat langste van die wegen hoogstens 2 maal zo lang is als kortste
        * voor wortel \\(w\\) betekent dat \\(z(w) \ge \frac{h}{2} \\)
        * zodat
            * \\( n \ge 2^{z(w)}-1 \ge 2^{\frac{h}{2}} -1 \\)
            * \\( h \le 2\lg{(n+1)} \\)
    * hoogte van rood-zwarte boom met \\(n\\) knopen is steeds \\(O(\lg{n})\\)
    * boom is slechts bij benadering evenwichtig, eisen zijn minster streng dan bij AVL boom
        * operaties zijn eenvoudiger en efficiënter te implementeren

## Woordenboekoperaties

### Zoeken

* kleur  van knopen speelt geen rol
* zoals bij gewone binaire zoekboom
* hoogte steeds \\(O(\lg{n})\\)
    * bij binaire boom zoeken: \\(O(h)\\)
    * bij rood-zwarte boom: zoeken gegarandeerd \\(O(\lg{n})\\)

### Toevoegen en verwijderen

* Zonder rekening houden met kleur: \\(O(\lg{n})\\)
    * niet zeker of boom na toevoegen/verwijderen nog steeds rood-zwarte boom is
* operaties die rekening houden met regels rood-zwarte boom kunnen ook efficiënt gebeuren
* twee manieren
    * bottom-up
        * eerst toevoegen zonder op kleur te letten (zoals bij gewone binaire zoekboom)
        * blad wordt vervangen door nieuwe knoop
        * nadien rood-zwarte boom herstellen vanaf nieuwe knoop
            * desnoods tot bij wortel
        * afdalen om nadien terug te stijgen
            * ouderwijzers of stapel nodig
    * top-down
        * boom reeds aanpassen langs dalende zoekweg
        * in praktijk efficiënter
* structuurwijzigingen gebeuren via rotaties

## Rotaties

* wijzigen vorm van boom
    * behouden **inorder** volgorde van sleutels
    * kleur van knopen blijft onveranderd
* lokale operatie waarbij twee inwendige knopen betrokken zijn
    * draait rond de ouder-kind verbinding
* rotatie naar links (voor rechterkind)
* rotatie naar rechts (voor linkerkind)

![](/assets/rzboom_rotatie.png)

## Bottom-up implementatie

### Toevoegen

* op gewone manier toevoegen met rode kleur
* als ouder ook rood is: twee opeenvolgende rode knopen
    * storing verwijderen door rotaties en kleurwijzigingen
    * desnoods tot bij wortel naar boven schuiven
* als ouder \\(p\\) van nieuwe knoop \\(c\\) rood is: ouder kan geen wortel zijn
    * er is steeds grootouder \\(g\\) die zwart is
    * zes mogelijke gevallen, vallen uiteen in twee groepen van drie (naargelang \\(p\\) linker- of rechterkind is van \\(g\\))

#### stel: \\(p\\) is linkerkind van \\(g\\)

* rode ouder \\(p\\) elimineren
    * door zwart te maken (vereist zwarte knoop die rood moet worden)
    * door weg te nemen via rotatie naar rechts (als die niet opnieuw twee opeenvolgende rode knopen oplevert in rechterdeelboom)
* twee hoofdgevallen: naargelang **kleur van broer** \\(b\\) van \\(p\\)

##### broer \\(b\\) van ouder \\(p\\) is rood

* ligging van knoop \\(c\\) tegenover ouder \\(p\\) is onbelangrijk
* rode ouder \\(p\\) kan zwart worden
    * zwarte grootouder \\(g\\) moet rood worden
    * rode broer \\(b\\) moet zwart worden
* als rood geworden grootouder \\(g\\) ook een rode ouder heeft, dan is het **probleem opgeschoven** in richting van wortel
    * oplossen door een van andere gevallen
    * of verder omhoog schuiven (in slechtste geval tot bij wortel)
![](/assets/rzboom_bu_add_rodebroer.png)

##### broer \\(b\\) van ouder \\(p\\) is zwart

* knoop \\(c\\), ouder \\(p\\) en grootouder \\(g\\) moeten op één lijn liggen
    * indien niet geval, knoop \\(c\\) met zijn ouder \\(p\\) roteren naar links  
    ![](/assets/rzboom_bu_add_cpglijn.png)
* rode ouder p wegnemen via rotatie naar rechts
    * bezorgt extra knoop in rechterdeelboom
* \\(p\\) komt bovenaan: heeft invloed op twee wegen
    * **zwarte kleur overnemen** van grootouder \\(g\\)
* overgebrachte **grootouder \\(g\\) moet rood** worden om zwarte hoogte niet te ontregelen

![](/assets/rzboom_bu_add_zwartebroer.png)

#### performantie

* in totaal 
    * hoogstens twee rotatie nodig om boom te herstellen
    * eventueel voorafgegaan door \\(O(\lg{n})\\) keer opschuiven (hoogte boom)
* roteren en opschuiven: \\(O(1)\\)
* initieel afdalen: \\(O(\lg{n})\\)
* toevoegen steeds \\(O(\lg{n})\\)


### Verwijderen

* ingewikkelder: steeds nagaan of bepaalde knopen wel bestaan
    * **nullknoop** gebruiken: die blad (nullpointer) voorstelt
        * structuur is dezelfde als die van gewone knopen
        * kleur is steeds zwart
        * in praktijk: één nullknoop voor alle bladeren
            * alle nullwijzers worden door wijzer naar deze knoop vervangen
        * kind kan nu steeds naar ouder verwijzen, ook als het blad is
    * verwijderen via rotaties
* eerst knoop (voorloper  of opvolger) verwijderen zoals bij gewone zoekboom

#### te verwijderen knoop: rood

* heeft geen 'echte' kinderen (enkel zwarte bladeren)
* heeft geen gevolgen voor zwarte hoogten

#### te verwijderen knoop: zwart

* kijken naar kinderen
    * één rood kind
    * of geen 'echte' kinderen

##### te verwijderen zwart kind heeft rood kind

* rood kind kan zwarte kleur van verdwenen ouder overnemen
* zwarte hoogte blijft intact

##### te verwijderen zwart kind heeft geen 'echte' kinderen

* zwarte kleur mag niet zomaar verdwijnen
    * kleur geven aan één van kinderen (zwart blad)
    * kind wordt dubbel zwart: anomalie moet verwijderd worden
* dubbel zwarte kleur kan opgeschoven worden
    * als wortel dubbel zwart wordt: overtollig zwarte kleur kan verdwijnen
        * wortel telt in geen enkele zwarte hoogte mee
* als dubbel zwarte knoop \\(c\\) geen wortel is: er is ouder \\(p\\)
    * acht mogelijke gevallen, twee groepen van vier, naargelang \\(c\\) linker- of rechterkind is van \\(p\\)

###### stel: \\(c\\) is linkerkind van \\(p\\)

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

####### Zwarte broer \\(b\\) van \\(c\\) heeft twee zwarte kinderen

* \\(b\\) kan rood worden
* vrijgekomen zwarte kleur samen met overtollig zwart van \\(c\\) **doorschuiven naar ouder** \\(p\\)
    * als ouder zwart was, probleem is doorgeschoven
    * desnoods tot bij wortel

####### Zwarte broer \\(b\\) van \\(c\\) heeft rood kind

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

#### Performantie

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

## Top-down implementatie

### Toevoegen

* nieuwe knoop wordt rood
    * vervangt blad (nullwijzer)
    * geeft enkel problemen als ouder ook rood is
    * met rotaties en kleurwijzigingen op te lossen als oom van nieuwe knoop zwart is
        * bij rode oom soms terugkeren in boom
    * bij afdalen ervoor zorgen dat oom steeds zwart is
* bij weg naar beneden **geen rode broers toelaten**
    * nieuwe rode knoop zou kind van een van beide kunnen worden
* voorbij zwarte knoop met twee rode kinderen
    * knoop rood maken en kinderen zwart maken
* als nieuwe rode knoop zelf rode ouder heeft
    * oplossen met rotaties en kleurwijzigingen (want oom is gegarandeerd zwart)
        * nieuwe rode broers liggen hogerop in de boom
* als er rotatie moet gebeuren: 4 generaties knopen bij betrokken
    * om twee opeenvolgende rode knopen te elimineren
        * ouder en grootouder moet geroteerd worden
        * overgrootouder moet ook aangepast worden
    * tijdens afdaling steeds wijzers naar 4 opeenvolgende knopen bijhouden
* toevoegen daalt enkel in boom waarbij rotaties en kleurwijzigingen kunnen gebeuren
    * \\(O(\lg{n})\\)

### Verwijderen

* te verwijderen knoop moet vervangen worden door voorloper of opvolger
* zwarte hoogte van fysisch te verwijderen knoop = 1
    * minstens één van kinderen is zwart blad (nullpointer)
* ervoor zorgen dat volgende knoop op zoekweg zeker rood is
* stel: tijdens afdalen in rood gemaakte knoop \\(p\\) beland en er moet verder afgedaald worden
* zwart kind \\(c\\) moet rood worden
* naargelang \\(c\\) linker- of rechterkind van ouder \\(p\\) is: twee groepen van mogelijke gevallen
* stel: \\(c\\) is linkerkind van \\(p\\)
* oplossen via 
    * ofwel één van rode kinderen van \\(c\\)
    * ofwel via broer \\(b\\)

#### Knoop \\(c\\) heeft minstens één rood kind

* indien eje naar rood kind moet: terug bij beginsituatie
* naar zwart kind \\(c\\)
    * rood maken door ouder \\(p\\) met zijn rood kind \\(b\\) (broer van \\(c\\)) te roteren en kleuren van \\(c\\) en \\(b\\) om te keren  
    ![](/assets/rzboom_td_del_roodkind.png)

#### Knoop \\(c\\) heeft twee zwarte kinderen (of geen inwendige kinderen)

* \\(c\\) rood maken via zwarte broer \\(b\\): kijken naar zijn kinderen

##### Zwarte broer \\(b\\) heeft twee zwarte kinderen

* \\(b\\) en \\(c\\) rood maken, ouder \\(p\\) zwart maken  
![](/assets/rzboom_td_del_zwartebroer_zwartekinderen.png)

##### Zwarte broer \\(b\\) heeft rood kind

* rood kind moet aan rechterkant (moet samen met broer \\(b\\) op 1 lijn liggen met ouder \\(p\\))
    * indien rood kind aan linkerkant en rechts zwart kind: roteren en kleuren wisselen  
    ![](/assets/rzboom_td_zwartebroer_roodlinkerkind.png)
* \\(c\\) moet rood worden: bijkomende zwarte knoop in linkse deelboom nodig
    * rotatie naar links
    * rechterdeelboom verliest zwarte knoop
        * kleur wordt bewaard door rood rechterkind \\(r\\) van broer \\(b\\) zwart te maken
    * roteer ouder \\(p\\) en broer \\(b\\) naar links
    * \\(c\\) en \\(b\\) rood maken
    * ouder \\(p\\) en rechterkind \\(r\\) zwart maken  
    ![](/assets/rzboom_td_del_zwartebroer_roodrechterkind.png)

#### Beginnen bij (zwarte) wortel

* beschouwen als zwarte knoop \\(c\\) waarheen we moeten vanuit fictieve rode ouder
* dezelfde gevallen
    * als beide kinderen zwart zijn: eenvoudiger
        * wortel kan steeds (tijdelijk) rood worden en die heeft geen broer

#### Performantie
* Verwijderen: afdalen in boom waarbij rotaties en kleurwijzigingen kunnen gebeuren
* \\(O(\lg{n})\\)

## Vereenvoudigde Roodzwarte bomen

* AA-boom: enkel rechterkind mag rood zijn
* Binary B-trees: dezelfde beperking als Symmetric binary B-trees
    * zonder rood-zwarte terminologie te gebruiken
* reduceren aantal gevallen, maar behouden dezelfde (asymptotische) efficiëntie



