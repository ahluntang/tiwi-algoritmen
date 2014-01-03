## Voor- en nadelen

### Voordeel

* informatie op schijf voor document-level index is kleiner (factor 5): minder schijfoperaties
* geheugenruimte voor accumulators is kleiner (factor 20)
* CPU-tijd om inverted lists te behandelen en accumulators updaten gereduceerd (factor 3 of meer)
* totale schijftrafiek om inverted lists op te halen gereduceerd (factor 5 in volume, factor 2 in tijd)
* queries sneller door beter geheugengebruik (betere caching van woordenschat, lijsten en antwoorden)
* constructietijd en onderhoudstijd voor indexen gereduceerd (factor 2) door reductie in schijftrafiek en aantal runs nodig om index op te bouwen.


### Nadeel

* Compressie: moet gedecodeerd worden
    * schijven worden niet zoveel sneller
    * CPU is veel sneller
