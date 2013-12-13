
## Definitie

* binaire zoekboom die 2-3-4 bomen simuleert
    * 3-knoop: 2 binaire knopen
    * 4-knoop: 3 binaire knopen
* 2 soorten ouder-kind verbindingen
    * originele verbindingen van 2-3-4 boom: zwart
    * nieuwe verbindingen: rood
* kleur kan opgeslagen worden bij
    * verbindingen
    * kinderknopen
* hoogte laag houden
    * beperkingen opleggen aan manier waarop knopen op elke (dalende) weg vanuit wortel gekleurd worden
* knoopstructuur ~ binaire zoekboom
    * nieuw veld voor kleur
    * ontbrekende kinderen: nullpointer
        * conceptueel beschouwen als wijzers naar uitwendige (kinderloze) knopen
            * bevatten geen gegevens
            * wel kleur
    * gewone knopen: inwendig

> ### binaire boom waarbij
> * elke knoop rood of zwart gekleurd is
> * elk blad (uitwenidge knoop) zwart is
> * rode knoop steeds 2 zwarte kinderen heeft
> * elke mogelijke weg vanuit knoop naar blad heeft steeds evenveel zwarte knopen
>   * zwarte hooogte van knoop (knoop zelf wordt niet meegerekend, blad wel)
> * wortel is zwart

## Eigenschappen

* deelboom met wortel \\(w\\) en zwarte hoogte \\(z(w)\\) heeft tenminste \\(2^{z(w)}-1\\) inwendige knopen
* inductie op gewone hoogte van deelboom
    * hoogte = 0
        * bevat enkel blad: 
            * zwarte hoogte = 0
        * geen inwendige knopen: \\(2^0-1\\) 
    * positieve hoogte
        * veronderstel dat eigenschap geldt voor elke kleinere hoogte
        * wortel \\(w\\) van deelboom met positieve hoogte is inwendige knoop die steeds 2 kinderen heeft (eventueel bladeren)
        * zwarte hoogte van
            * rood kind: \\(z(w)\\)
            * zwart kind: \\(z(w)-1\\)
        * hoogte van beide kinderen is kleiner dan die van \\(w\\)
        * bij veronderstelling geldt de eigenschap voor de deelbomen waarvan ze wortel zijn
            * deelboom met wortel \\(w\\) heeft minstens \\( 2 \times (2^{z(w)-1}-1) +1 = 2^{z(w)}-1 \\) inwendige knopen
    * stel dat 
        * rood-zwarte boom met \\(n\\) inwendige knopen hoogte \\(h\\) heeft (blad meegerekend)
        * er geen 2 opeenvolgende rode knopen op elke weg vanuit knoop naar blad mogen voorkomen
    * dit impliceert dat langste van die wegen hoogstens 2 maal zo lang is als kortste
        * voor wortel \\(w\\) betekent dat \\(z(w) \ge \frac{h}{2} \\)
        * zodat
            * \\( n \ge 2^{z(w)}-1 \ge 2^{\frac{h}{2}} -1 \\)
            * \\( h \le 2\lg{(n+1)} \\)
    * hoogte van rood-zwarte boom met \\(n\\) knopen is steeds \\(O(\lg{n})\\)
    * boom is slechts bij benadering evenwichtig, eisen zijn minster streng dan bij AVL boom
        * operaties zijn eenvoudiger en efficiënter te implementeren
