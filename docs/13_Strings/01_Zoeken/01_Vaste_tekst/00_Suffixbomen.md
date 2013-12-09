

* Verwant aan (meerwegs)patricia trie
    * oorspronkelijk ook gebruikt om alle suffixen van lange tekst op te slaan
* Geen binaire boom
    * uitweg mogelijk voor elk karakter

## Alle suffixen opslaan in gegevensstructuur

![](/assets/suffixtree.png)

* \\(b\\) bladeren = aantal suffixen
* \\(i\\) inwendige knopen
* Als suffix in tree zit
    * er is maar 1 weg om die te vinden
* Op elk stuk waar knopen komen met maar 1 weg
    * geen knopen op die weg
    * in inwendige knoop: \\(b:e\\)
        * duidt aan dat het overeenkomt met tekst tussen \\(b\\) en  \\(e\\)
    * in blad: \\(i\\)
        * duidt begin van suffix aan dat tot einde van tekst gaat.

## Oorspronkelijke constructie

* Suffixboom opbouwen door tekst van achter naar voor te overlopen
* Recent kan dit ook efficiënt door van voor naar achter te overlopen
    * door impliciete suffixboom op te bouwen
        * suffix dat erin zit kan prefix zijn van een andere (enkel tijdens constructie toegelaten)
            * op einde ervoor zorgen dat het niet kan (extra afsluitkarakter gebruiken)
        * tak: pointer naar volgende expliciete knoop
        * als suffix eindigt in midden van tak: impliciete knoop (inwendig)

![](/assets/suffixtree_tekst.png)

* als je bij \\(i\\) komt
    * alle suffixen tot \\(i-1\\) zit in tekst (expliciet of impliciet)
    * \\(i\\) verwerken
        * alle suffixen moeten verlengd worden met \\(i\\) zodat karakter op \\(i\\) ook in suffixboom zit en verwerkt is

### Verlengen van suffix

* alle \\(i\\) suffixen moeten verlengd worden met 1 karakter
    * inefficiënt?
        * stap \\(i\\): \\(i\\) suffixen verlengen
            * als verlengen \\(O(1)\\) zou zijn  
            \\(
                \Rightarrow i \times O(1)
            \\)  
            \\(
                \Rightarrow O(1) + O(2) + ... + O(n) = O(n^2) 
            \\)
    * efficiënter: beginnen met langste suffix te verlengen (van lang naar kort)
* suffix kan eindigen op 3 verschillende manieren
    * blad: geen werk
    * inwendige knoop
        * met uitweg : geen werk
        * zonder uitweg
            * blad maken: waar \\(i\\) begon als index
                * tak naar blad: bevat enkel index met nieuw karakter
            * blad hangen aan inwendige knoop via tak
                * inwendige knoop moet expliciet zijn/worden
                * impliciete knoop omvormen tot expliciete knoop
                    * tak wordt in twee "gesplitst"
                    * tak van \\(b\\) tot \\(e\\) wordt
                        * tak van \\(b\\) tot \\(i\\)
                        * en tak van \\(i\\) tot \\(e\\) (tak van nieuwe expliciete knoop naar blad)
* wat als te verlengen suffix in blad eindigt?
    * in blad staat bv. \\(j\\)
    * op laatste tak komt er iets bij
        * \\(e\\) index op laatste knoop wordt met 1 verlengd
        * uiteindelijk gaat dit tot \\(n\\)
        * beter: vaneerste keer tot \\(n\\) laten gaan
            * bladeren duiden aan tot einde van tekst (volledige suffix)
    * als suffix eindigt in blad: blijft eindigen in blad.
* totale werk: \\(O(n)\\) voor verlengen
    * er kunnen maar \\(n\\) bladeren aangemaakt worden.
* ronde \\(i\\)
    * eerste suffix dat je moet verlengen is de langste
        * eindigt altijd in blad (begint bij index 1)
    * volgende suffixen: **kunnen** eindigen in blad  
      ![](/assets/suffixtree_verlengen.png)
        * als het ooit stopt met eindigen in blad, dan zullen alle volgende niet meer eindigen in blad
            * je vindt suffix op weg \\(x\alpha\\) met daarachter nog \\(\beta\\)
                * karakter \\(x\\): niet leeg
                * \\(\alpha\\): kan leeg zijn
                * \\(\beta\\): te verlengen karakter (niet leeg)
            * volgende te verlengen start met \\(\alpha\\)
                * als \\(x\alpha\beta\\) er al in zat: dan zit \\(\alpha\beta\\) er ook al in
                    * zal dus ook niet eindigen in blad.
* als je geen uitweg hebt voor karakter \\(z\\)
    * nieuwe uitweg voor \\(z\\) dat na \\(x\alpha\\) komt
    * als er suffix in zit
        * alle volgende suffixen die korter zijn zitten er zeker al in (omdat je van langste naar kortste verlengt)    
          ![](/assets/suffixtree_geenuitweg.png)
* werk dat gebeurt: bladeren aanmaken, keert nooit terug
    * bij bladeren of knopen met uitweg moet je niets doen
    * naarmate ronddes vordert, komen er meer bladeren
    * enige werk dat er is: bij impliciete/expliciete knopen zonder uitweg
        * eventueel expliciet maken en dan blad maken
    * bij volgende ronde(s)
        * start vanaf waar je in vorige ronde voor het eerst een niet-blad tegenkwam: actief punt van ronde  
          ![](/assets/suffixtree_actiefpunt.png)

### Vinden van suffix


