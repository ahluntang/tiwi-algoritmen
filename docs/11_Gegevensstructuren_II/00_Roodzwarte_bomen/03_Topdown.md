
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
* oplossen via één van rode kinderen van \\(c\\)
