
* per dimensie
    * gegevensstructuur die alle punten gerangschikt bijhoudt volgens die dimensie
* punten worden geprojecteerd op elke dimensie
    * inverted file
        * in plaats van coördinaten bij punten opslaan
        * punten opslaan bij coördinaten
* wanneer punten gelijkmatig verdeeld zijn
    * één gegevensstructuur volstaat voor eender welke dimensie
* wanneer niet gelijkmatig verdeeld
    * beter om telkens op alle dimensies te zoeken
    * kleinste van puntenverzamelingen sequentieel overlopen
* werkt best wanneer zoekrechthoek zijde heeft die meeste punten uitsluit
* gemiddelde performantie: \\( O(n^{1-\frac{1}{k}}) \\)
    * voor uniform verdeelde punten
    * met nagenoeg kubusvormig zoekgebied en klein aantal gevonden punten
