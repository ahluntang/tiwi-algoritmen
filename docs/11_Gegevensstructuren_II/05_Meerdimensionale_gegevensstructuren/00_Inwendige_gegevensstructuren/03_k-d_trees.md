
* vermijdt grote vertakkingsgraad van point quadtree
    * binaire boom
* elke inwendige knoop bevat punt dat (deel)zoekruimte verdeelt in slechts 1 dimensie
* opeenvolgende knopen kunnen opeenvolgende dimensies gebruiken om te splitsen
    * zoekruimte opnieuw in \\(k\\)-dimensionale rechthoeken verdeeld
    * opdeling wordt bepaald door opgeslagen punten
* in elke knoop beslissen volgens welke dimensie opgedeeld wordt (die met grootste spreiding)
    * om rechthoekige gebieden zo regelmatig mogelijke vorm te geven
    * gelijkmatige verdeling van zowel vlak als van punten
        * niet voor elke collectie punten mogelijk
* opdeling kan doorgaan tot elk gebied slechts één punt bevat
    * er kan vroeger gestopt worden
        * per gebied gelinkte lijst van punten bijhouden
* statisch geval (als men de \\(n\\) punten op voorhand kent)
    * evenwichtige \\(k-d\\)-tree met hoogte \\(O(\lg{n})\\) opbouwen in tijd van \\( O(kn\lg{n}) \\)
        * beide deelbomen van elke knoop moeten evenveel punten bevatten
* dynamisch: boom heeft gemiddelde hoogte van \\(O(\lg{n})\\)
    * als elke toevoegvolgorde even waarschijnlijk is
    * slechtste geval: gelinkte lijst \\(O(n)\\)
* afwisselende dimensies
    * geen rotaties mogelijk om dergelijke boom evenwichtig te maken
        * deelboom evenwichtig reconstrueren
    * *lazy deletion*
        * als verwijderen markeren
        * bij reconstructie effectief verwijderen
* zoeken naar punten in rechthoekig zoekgebied
    * vinden van alle gebieden in boom die gegeven gebied overlappen
    * bij groot zoekgebied of als slecht gelegen
        * soms nodig om heel boom te doorlopen
    * zoeken/toevoegen: \\(O(h)\\)
        * afhankelijk van evenwicht van boom
    * efficiëntie van zoeken in gebied
        * bepaald door evenwicht
        * bepaald door aantal gevonden punten \\(r\\) (resultaatafhankelijk)
    * boom met perfect evenwicht
        * performantie in slechtste geval \\( O(r+\sqrt{n}) \\)
    * boom random opgebouwd
        * gemiddelde performantie \\( O(r+r^\alpha) \\) met \\( \alpha = \frac{\sqrt{17}-3}{2} \\)
