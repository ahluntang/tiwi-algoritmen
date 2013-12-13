
## Toevoegen

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

## Verwijderen

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

### Knoop \\(c\\) heeft minstens één rood kind

* indien eje naar rood kind moet: terug bij beginsituatie
* naar zwart kind \\(c\\)
    * rood maken door ouder \\(p\\) met zijn rood kind \\(b\\) (broer van \\(c\\)) te roteren en kleuren van \\(c\\) en \\(b\\) om te keren  
    ![](/assets/rzboom_td_del_roodkind.png)

### Knoop \\(c\\) heeft twee zwarte kinderen (of geen inwendige kinderen)

* \\(c\\) rood maken via zwarte broer \\(b\\): kijken naar zijn kinderen

#### Zwarte broer \\(b\\) heeft twee zwarte kinderen

* \\(b\\) en \\(c\\) rood maken, ouder \\(p\\) zwart maken  
![](/assets/rzboom_td_del_zwartebroer_zwartekinderen.png)

#### Zwarte broer \\(b\\) heeft rood kind
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

### Beginnen bij (zwarte) wortel

* beschouwen als zwarte knoop \\(c\\) waarheen we moeten vanuit fictieve rode ouder
* dezelfde gevallen
    * als beide kinderen zwart zijn: eenvoudiger
        * wortel kan steeds (tijdelijk) rood worden en die heeft geen broer

### Performantie
* Verwijderen: afdalen in boom waarbij rotaties en kleurwijzigingen kunnen gebeuren
* \\(O(\lg{n})\\)
