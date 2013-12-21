
## (Niet) efficiënte oplossingen

* uitvoeringstijd begrensd door *veelterm* 
    * in aantal behandelde gegevens \\(n\\), zoals \\(O(n^2)\\)
    * aantal knopen \\(n\\) en aantal verbindingen \\(m\\) van graaf, zoals \\(O(n^2m)\\)
* er bestaan problemen waarvan men kan aantonen dat ze geen efficiënte oplossing kunnen hebben of helemaal geen oplossingen
    * talloze praktische problemen
        * geen efficiënte oplossing gevonden
        * nog niet aangetoond dat deze niet bestaat
    * P-NP probleem

## Complexiteitsklassen

* onderverdeling naar gelang hun 
    * uitvoeringstijd
    * geheugenvereisten
* beperken tot *beslissingsproblemen*
    * ja/nee resultaat
    * technische reden (geen beperking)
        * elk probleem kan geformuleerd worden als beslissingsprobleem
        * als beslissingsprobleem geen efficiënte oplossing heeft, geldt zeker voor origineel probleem

## Klasse P

* P: Polynoom, Polynomiaal
* problemen waarvan uitvoeringstijd begrensd wordt door *veelterm* in grootte van probleem
    * bij uitvoering op *realistisch* computermodel
* *grootte*: aantal bits nodig om invoergegevens in computer voor te stellen
    * *redelijke* voorstelling wordt gebruikt
        * compact, bevat geen overtollige informatie
        * stelt getallen voor in talstelsel met radix groter dan 1
          (onredelijke voorstelling: getal met waarde \\(n\\) vereist \\(n\\) bits)
* *realistisch* computermodel: polynomiale bovengrens voor werk dat in 1 tijdseenheid kan verricht worden
* alle problemen in P zijn efficiënt oplosbaar

### Veeltermen

* als uitvoeringstijd niet kan begrensd worden door veelterm: probelem zeker niet efficiënt oplosbaar
    * graad van veelterm gewoonlijk heel beperkt
* veelterm: kleinste klasse functies die kunnen gecombineerd worden
    * leveren opnieuw veeltermen op
    * klasse is *gesloten* bij operaties
        * optelling
        * vermenigvuldiging
        * samenstelling
    * efficiënte algoritmen voor eenvoudigere problemen kunnen gecombineerd worden tot efficiënt algoritme voor complexer probleem
* efficiëntiemaat 
    *onafhankelijk van 
        * computermodel
        * invoer die men gebruikt om uitvoeringstijd te bepalen
    * als tijd voor bepaald model en voorstelling begrensd wordt door veelterm
        * ook begrensd bij andere (zolang ze *realistisch* blijven)

## Klasse NP (Niet-deterministisch Polynomiaal)

* trachten efficiënt op te lossen met (hypothetische) niet-deterministische machine
    * in staat om tegelijk elke mogelijke oplossing in polynomicale tijd (deterministisch) te testen
* NP: klasse van alle problemen waarvan oplossing efficiënt kan getest worden
* elk probleem uit P behoort zeker tot NP
* machinekeuze is irrealistisch
* nog altijd niet aantoonbaar dat ze krachtiger is dan een 'klassieke' deterministische machine
    * er is geen enkel probleem in NP dat niet in P **zou kunnen** behoren

## NP-compleet

* NP bevat groot aantal problemen die minstens even *zwaar* zijn dna *elk* ander probleem uit NP
* eigenschap
    * als er één NP-compleet probleem efficiënt oplosbaar is (en dus tot P zou behoren)
    * dan zijn *alle* NP-complete problemen efficiënt oplosbaar
    * NP wordt gelijk aan P

### Polynomiale reductie: aantonen dat probleem NP-compleet is

* aantonen dat elk probleem in NP efficiënt (in polynomiale tijd) kan *getransformeerd* worden tot het nieuwe probleem
    * efficiënte oplossing voor probleem impliceert efficiënte oplossing voor elk probleem in NP
* aantal NP-problemen onbekend, maar zeer groot
* voor allereerste NP-compleet probleem moest andere (lange en ingewikkelde) methode gebruikt worden
    * eenmalig

## NP-hard

* Problemen die minstens even *zwaar* zijn als problemen in NP
* behoren niet tot NP
* Alle problemen in NP kunnen ook polynomiaal gereduceerd worden tto elk NP-hard probleem
* bv: optimalisatieproblemen waarvan beslissingsversie NP-compleet is

## NP-complete problemen oplossen

* als *afmetingen* van probleem *klein* zijn
    * gering aantal invoergegevens
    * alle mogelijkheden onderzoeken (backtracking)
    * werk zoveel mogelijk beperken (snoeien)
* *speciale gevallen* hebben misschien efficiënte algoritmen
* *gemiddelde uitvoeringstijd* kan meevallen
    * ook al is slechtste geval zeer slecht
* *benaderende algoritmen*
    * relaxeren vereisten voor de oplossing
* *heuristische methoden*
    * meestal goede maar niet noodzakelijk optimale oplossing
    * garanderen niets
