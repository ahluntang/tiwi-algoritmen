

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
* afwerken: expliciete suffixboom maken
    * door alle suffixen te verlengen met afsluitkarakter
    * geen enkele inwendige knoop heeft er een uitweg voor

### Vinden van suffix

![](/assets/suffixtree_suffixlink.png)

* in elke expliciete inwendige knoop
    * als \\(x\alpha\\) erin zit: dan zit \\(\alpha\\) er ook in
    * pointer naar volgende kortere suffix
        * er was geen uitweg na \\(x\alpha\\) voor nieuw karakter
    * als daar nodig was om expliciete knoop te maken, dan zal volgende kortere suffix ook geen uitweg hebben en zal daar ook een expliciete knoop gemaakt worden.
    * wachten tot volgende ronde om suffixlink te leggen
* als inwendige knoop impliciet is
    * geen uitweg: welke eerstvolgende kortere start met \\(\alpha\\)?
    * in midden van een tak
        * vorige expliciete knoop had suffixlink
            * wijst naar volgende kortere suffix dat start met \\(\alpha\\)
            * vanaf daar opnieuw de weg volgen
        * je weet wat er staat in de volgende wegen: je weet hoe ver je moet dalen
            * van knoop naar knoop gaan kost \\(O(1)\\)
            * per knoop \\(O(1)\\): dalen tot je op juiste plaats bent
    * elke expliciete knoop op weg heeft link naar kortere suffixknoop
        * link kan hoogstens 1 knoop in weg doen dalen
* vinden: \\(O(n)\\)
    * max \\(O(n)\\) keer dalen per ronde
    * max \\(O(n)\\) ker stijgen per ronde

### Voorbeeld

![](/assets/suffixtree_rondesvb.png)

## Toepassingen

### Klassieke deelstringprobleem: zoeken naar patroon

![](/assets/suffixtree_toepassing_patroon.png)

* zoeken naar patroon **ab** uit tekst **abababø**
* kijken naar deelboom onder **ab**
    * alle bladeren hieronder hebben dezelfde prefix
    * bladeren verwijzen naar index 1, 3 en 5.
    * op plaats 1, 3 en 5 start van patroon te vinden

|   a   |   b   |   a   |   b   |   a   |   b   |   ø   |
|-------|-------|-------|-------|-------|-------|-------|
| **1** |   2   | **3** |   4   | **5** |   6   |   7   |


### Langste gemeenschappelijke deelstring

* langste gemeenschappelijke string
* **veralgemeende suffixboom** voor verzameling strings bevat al de suffixen van al de strings uit de verzameling
    * hetzelfde suffix kan tot meerdere strings behoren
    * bladeren bevatten
        * beginpositie van suffix
        * string waartoe die behoort
    * takken
        * duiden begin- en eindindex in string aan en in welke string
    * elke inwendige knoop komt overeen met prefix van suffix
        * deelstring komt voor in elke string die vermeld wordt bij blad dat opvolger is van die knoop
    * boom wordt systematisch overlopen om 
        * lengte van de prefixen te bepalen
        * aantal **verschillende strings** te bepalen waarin ze voorkomen

* boom in postorder doorlopen
    * kijken bij elkek noop of die eronder in voorkomen
    * diepste van die knopen is langst gemeenschappelijke deelstring
