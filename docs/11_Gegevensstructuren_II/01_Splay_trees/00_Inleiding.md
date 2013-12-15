
* garanderen niet dat elke afzonderlijke operatie efficiënt is
* opeenvolgende reeks operaties steeds efficiënt
    * uitgemiddeld over de reeks valt performantie per operatie goed uit
    * amortized efficiency: uitgesmeerd over de reeks
* reeks van \\(m\\) operaties verrichten op initieel ledige splay tree
    * \\(n\\) keer toevoegen (\\(m \ge n\\))
        * performantie van reeks: \\(O(m\lg{n})\\)
        * ook in slechtste geval
        * reeks heeft \\(m\\) operatie: per operatie \\(O(\lg{n})\\)
        * bij individuele operatie
            * in slechtste geval slechter dan \\(O(\lg{n})\\)
            * beter dan verwachtingswaarde van \\(O(\lg{n})\\) (sluit niet uit dat elke operatie in reeks slecht kan zijn)
            * individuele operaties mogen inefficiënt zijn
                * na dergelijk operatie vorm van boom aanpassen (anders zou herhalen van diezelfde operatie slechte reeks opleveren)
* vorm van boom aanpassen
    * toe te voegen knoop, te verwijderen knoop of gezochte knoop
        * tot wortel van boom maken
        * volgende operaties op die knoop (of zijn omgeving) worden zeer efficiënt
            * te vergelijken met gelinkte lijsten: move to front
        * via splay operatie: rotaties
    * weg naar diep liggende knoop
        * bevat veel knopen die ook relatief diep liggen
            * structuur van boom wordt zo aangepast dat ook toegangstijd van deze knopen verbetert
* geheugenuitsparing
    * niet nodig om hoogte van knopen of evenwicht over boom bij te houden




