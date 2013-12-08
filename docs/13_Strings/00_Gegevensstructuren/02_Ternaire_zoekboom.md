
![](/assets/ternairezoekboom.png)

* elke knoop bevat een sleutelelement
* zoeken vergelijkt zoeksleutelelement met element in huidige knoop
    * als zoeksleutelelement **kleiner** is dan element in huidige knoop
        * verderzoeken in linkse deelboom, met **hetzelfde** zoeksleutelelement.
    * als zoeksleutelelement **groter** is dan element in huidige knoop
        * verderzoeken in rechtse deelboom, met **hetzelfde** zoeksleutelelement.
    * als zoeksleutelelement **gelijk** is aan element in huidige knoop
        * verderzoeken in middelste deelboom, met **volgende** zoeksleutelelement (als het bestaat)
* opeenvolgende elementen van zoeksleutels via middelste wijzers
