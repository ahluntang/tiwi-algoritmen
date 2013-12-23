
* uitwendige evenwichtige zoekboom
* efficiëntie van meeste operaties op zoekbomen begrensd door hoogte van boom
    * B-tree moet in alle omstandigheden perfect in evenwicht blijven
        * zeer kleine hoogte
* aantal sleutels \\(n\\) zeer groot
    * minimale hoogte van binaire boom \\( \lfloor \lg(n) \rfloor \\)
        * bomen met meer dan twee kinderen per knoop gebruiken
* informatie-overdracht van en naar schijf via pagina's
    * knoopgrootte: moet volledige schijfpagina beslaan
* eerst inwendig geheugen inlezen vooraleer met knoop van B-tree gewerkt kan worden
    * gewijzigde knopen nadien op schijf aanpassen
* schijfoperaties uitsparen
    * geheugenruimte voor meest recent gebruikte knopen voorzien
    * elke operatie gebruikt slechts gering aantal knopen
        * wortel in geheugen houden
        * eventueel ook volledig eerste niveau in geheugen
* op te slagen gegevens
    * sleutel met bijbehorende informatie
    * sleutel wordt dikwijls enkel vergezeld van wijzer naar bijbehorende informatie
    * sleutels moeten ook geordend kunnen worden
* B-tree is meerwegszoekboom
    * alle bladeren hebben dezelfde diepte
    * bij toevoegen en verwijderen van sleutels: perfecte evenwicht van boom behouden
        * door aantal kinderen in knopen te manipuleren
        * zoals 2-3 boom
    * ingrijpende structuurwijzigingen zeldzaam
    * hoogte inperken
        * voor genoeg kinderen zorgen in elke knoop

## Definitie: B-tree van orde \\(m\\)

* elke inwendige knoop
    * heeft hoogstens \\(m\\) kinderen
    * heeft minstens \\( \lceil \frac{m}{2} \rceil \\) kinderen
        * behalve wortel: minstens \\(2\\) kinderen, tenzij het een blad is
    * bij \\(k\\) kinderen: bevat \\(k-1\\) sleutels
        * bladeren bevatten hoogstens \\(m-1\\) en minstens \\( \lceil \frac{m}{2} \rceil - 1 \\) sleutels
    * als wortel blad is
        * bevat minstens één sleutel
        * tenzij B-tree ledig is
* alle bladeren op zelfde niveau
* elke knoop bevat
    * geheel getal \\(k\\)
        * duidt aantal sleutels in knoop aan (niet elke knoop heeft kinderen)
    * logische waarde \\(b\\)
        * duidt aan of knoop blad of inwendige knoop is
        * door perfecte evenwicht geen behoefte aan *nullwijzers* voor ontbrekende kinderen van blad
            * logische waarde: duidt aan of laagste niveau is of niet
    * tabel voor maximaal \\(m\\) *wijzers* naar kinderen van knoop
        * bij blad: tabel ongedefinieerd
    * tabel voor maximaal \\(m-1\\) sleutels die stijgend gerangschikt zijn
        * eventueel met extra tabel met bijhorende informatie of verwijzing ernaar
        * \\(k-1\\) geordende sleutels van inwenidge knoop
            * verdelen sleutelbereik in k gebieden
            * sleutels van elk deelgebied zitten in deelboom met als wortel kind van deze knoop
* eenvoudigste B-trees: 2-3 bomen (orde \\(3\\)) en 2-3-4 bomen (orde \\(4\\))
    * normaal is orde \\(m\\) veel groter (reden: grotere \\(m\\) betekent kleinere hoogte)
* knopen moeten plaats reserveren voor maximale grote van tabellen
    * waarde van \\(m\\) hangt af van grootte van
        * schijfparina
        * sleutel
        * bijbehorende gegevens

## Eigenschappen

* langst afgelegde weg bij woordenboekoperaties op B-tree
    * evenredig met hoogte
* toegang tot elke knoop op weg vereist schijfoperatie
    * tweede schijfoperatie als die gewijzigd wordt
* hoogte zeer klein: ook voor heel veel sleutels
* stel: boom met hoogte \\(h\\) niet ledig
    * minimaal aantal sleutels \\(n\\)?
        * wortel van minimale boom: slechts één sleutel
            * twee kinderen ( als \\(h > 0\\) )
        * elk van kinderen heeft minimaal \\( g = \\lceil \frac{m}{2} \rceil \\) kinderen
            * hebben op hun beurt ook elk minimaal \\(g\\) kinderen
        * aantal knopen tenminste \\[ 1 + 2 + 2g + ... + 2g^{h-1} = 1 + 2 \sum_{i=0}^{h-1}{g^i} \\]
        * elke knoop: heeft minstens \\(g-1\\) sleutels
            * behalve wortel: minstens \\(1\\)
              \\[
                n \ge 1 + 2(g-1)\left( \frac{g^h-1}{g-1} \right)
              \\]
              zodat \\( n \ge 2g^h-1 \\)
            *  bij log met basis \\(g = \lceil \frac{m}{2} \rceil \\):
               \\[
                    h \le \log_{\lceil \frac{m}{2} \rceil}{\left( \frac{n+1}{2} \right)}
               \\] 
        * hoogte is dus \\(O(\lg{n}\\)
            * zoals bij rood-zwarte boom
            * verborgen constante is factor \\( \log_{\lceil \frac{m}{2} \rceil} \\) kleiner
* B-tree met \\(n\\) uniform verdeelde sleutels gebruikt gemiddeld \\( \frac{n}{m\ln{2}} \\) schijfpagina's
