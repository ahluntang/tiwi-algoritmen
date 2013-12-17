
## Document-distributed

* elke machine krijgt zijn set documenten
* volledige woordenschat moet beschikbaar zijn op elke machine
    * beperkte set documenten op machine
* query wordt gestuurd naar elke machine
* coördinerende machine krijgt resultaten
    * vergelijkt resultaten en geeft beste resultaten terug
* als machine uitvalt
    * enkele documenten per term vallen weg
    * steeds mogelijk om op elke term te zoeken
* wordt gebruikt door Google (naast mirroring/replication, ...)

## Term-distributed

* enkel machines die term hebben die in query zitten kunnen werk hebben
* nadelen
    * eerst wordt constructie volgens documenten gedaan
        * nadien op termen distribureren
    * coördinerende machine moet veel werk verrichten
        * wordt bottleneck
    * als machine uitvalt: er vallen termen weg
