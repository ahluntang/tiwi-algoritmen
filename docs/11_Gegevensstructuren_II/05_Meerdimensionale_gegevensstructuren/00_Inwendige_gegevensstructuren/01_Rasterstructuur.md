
* verdeelt zoekruimte met behulp van raster
* voor elk van rastergebieden (hyperrechthoek)
    * gelinkte lijst bijhouden met punten die erin liggen
* alle punten opsporen in zoekrechthoek
    * vinden van alle rastergebieden die rechthoek overlappen
    * nagaan welke van punten in hun gelinkte lijsten binnen rechthoek vallen
* voor uniform verdeelde punten
    * regelmatig raster kiezen: meerdimensionale tabel
        * om rastergebieden die zoekrechthoek overlappen zeer snel te vinden
* rest van zoekoperatie enkel efficiënt als
    * er niet al te veel dergelijke rastergebieden zijn
    * hun gelinkte lijsten gemiddeld kort zijn
* compromis vinden tussen grootte van rastergebied en lengte van lijsten
    * te fijne rasterverdeling
        * veel lijsten
        * veel geheugen nodig om op te slaan
* aantal rastergebieden
    * best constante fractie van aantal punten \\(n\\)
    * gemiddeld aantal punten in elk rastergebied wordt kleine constante
* als er nogal wat rastergebieden ledig blijven
    * meerdimensionale tabel neemt onnodig veel geheugen in beslag
        * andere gegevensstructuur kiezen die enkel niet-ledige rastergebieden bevat
        * moet toelaten om snel gebieden te vinden die zoekrechthoek overlappen
* regelmatig raster: ongeschikt voor ongelijkmatig verdeelde punten
    * meerdimensionaal tabel kan gebruikt worden
    * verband tussen positie van rastergebied en die van overeenkomstig tabelelement is ingewikkelder
    * per dimensie gerangschikte positie van raster(hyper)vlakken bijhouden
    * zoekoperatie per dimensie
        * geeft indices in die dimensie van gezochte rastergebieden
* vast raster (al dan niet regelmatig)
    * veronderstelt statische gegevens
* bij dynamische gegevens
    * er kunnen zowel overvolle als ledige rastergebieden ontstaan
    * overvolle gebieden vermijden
        * raster aanpassen door rastergrenzen te verplaatsen of toe te voegen
            * kan weer ledige gebieden opleveren
        * andere gegevensstructuur met enkel niet-ledige rastergebieden gebruiken
            * zoals bij regelmatig raster
        * raster adaptief maken
            * zodat naburige ledige gebieden samengevoegd kunnen worden en overvolle gebieden gesplitst
            * tabel is hiervoor niet geschikt
                * boomstructuur gebruiken
                * basis van *quadtrees* (combinatie van \\(2^k\\)-wegsboom met raster)
