
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
    ![](/assets/btree_knoop.png)
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

## Woordenboekoperaties

### Zoeken

* langs weg vanuit wortel in richting van blad
* in elke knoop meerwegsbeslissing nodig
* knoop op weg moet eerst in geheugen ingelezen worden
    * tenzij reeds in geheugen
* sleutel wordt opgezocht in gerangschikte tabel met sleutels
    * snelste manier
        * binair zoeken: winst vrij onbelangrijk naast schijfoperaties
        * lineair zoeken kan zelfs efficiënter uitvallen
            * interpolerend zoeken om aantal cachefouten te minimaliseren
                * werkt slechts als sleutels niet uniform verdeeld zijn
* bij gevonden sleutel: zoeken stopt
    * resultaat bevat 
        * verwijzing naar knoop op schijf
        * plaats van sleutel in die knoop
* bij niet gevonden sleutel
    * knoop is blad
        * sleutel is niet aanwezig
    * interne knoop
        * verder zoeken in juiste deelboom, waarvan wortel kind is van huidige knoop
        * wijzer naar knoop staat in dezelfde index in kindertabel 
            * waar de niet gevonden sleutel zou moeten staan in sleuteltabel
        * kind wordt ingelezen, zoekproces wordt op knoop herhaald

#### Performantie zoeken

* tijdens afdalen: elke knoop op weg moet ingelezen roden
* aantal schijfoperaties
  \\[
    O(h) = O\left( \log_{\lceil \frac{m}{2} \rceil}{n} \right)
  \\]
* processortijd per knoop (binair zoeken) 
  \\( O(\lg{n}) \\)
  verborgen constante is veel kleiner dan die voor schijfoperaties
* totale performantie
  \\[
    O(h) = O \left( m\log_{\lceil \frac{m}{2} \rceil}{n} \right)
  \\]

### Toevoegen

* aanpassingen aan boomstructuur mogelijk
    * kan topdown of bottom-up
    * in slechtste geval vereist bottom-up versie dat hoogte van boom tweemaal doorlopen wordt
        * veel erger dan inwendige boom, maar zeer zeldzaam
        * niet als meest recent gebruikte knopen bijgehouden wordt in inwendig geheugen

#### Bottom-up toevoegen

* initialisatie ledige B-tree vereist meer werk dan die van inwendige zoekboom
    * wortelknoop in gehugen maken en gedeeltelijk invullen
    * op schijf kopiëren
    * ledige wortel is blad dat geen sleutels bevat
* voor elke nieuwe knoop
    * plaats reserveren op schijf vooraleer kopiëren
    * verwijzing naar plaats permanent bijhouden
        * andere knoop kan wortel worden
* toevoegen steeds aan blad
    * toevoegen aan inwendige knoop
        * zou extra kind met bijbehorende deelboom vereisen
    * vanuit wortel blad zoeken waarin sleutel zou moeten zitten
    * op juiste plaats in tabel toevoegen (met bijbehorende informatie)
* als blad \\(m\\) sleutels bevat
    * splitsen bij middelste sleutel (op index \\( \lceil \frac{m}{2} \rceil \\))
    * nieuwe knoop wordt op hetzelfde niveau aangemaakt
        * in inwenzig gehugen en op schijf
        * krijgt gegevens rechts van middelste sleutel
    * middelste sleutel zelf gaat naar ouder (met bijbehorende informatie)
    * ouder krijgt ook verwijzing naar nieuwe knoop
        * deel van tabellen in ouder moet opgeschoven worden
        * gewoonlijk heeft ouder plaats voor extra sleutel
        * indien niet: ouder splitsen
            * bij kinderen: samen met sleutels over originele en nieuwe knoop verdelen
    ![](/assets/btree_bu_add_nieuweknoop.png)
* soms splitsing uitstellen
    * gegevens overbrengen naar broerknoop
        * over beide knopen zo goed mogelijk verdelen
    * enkel mogelijk als broer plaats heeft voor extra sleutels
    * inorder volgorde moet intact blijven
        * overbrengen via rotatie
        * sleutel gaat van knoop naar ouder, ouder staat sleutel af naar broer, broer krijgt kindwijzer van de knoop
    ![](/assets/btree_bu_add_broerknoop.png)

#### Performantie toevoegen (bottom-up)

* in slechtste geval
    * elke knoop op (terug)weg moet gesplitst worden
* soms ook nodig om wortel te splitsen
    * geen ouder meer om middelste sleutel in onder te brengen
    * nieuwe wortel aanmaken met slechts 1 sleutel
* B-trees groeien bovenaan
* alle nieuwe en alle gewijzigde knopen moeten op schijf aangepast worden
* \\(h+1\\) knopen splitsen (zeer zeldzaam)
    * totaal aantal splitsingen sinds initialisatie van boom
      \\( = \text{aantal knopen} - (h+1) \\)
        * veel minder dan aantal toegevoegde sleutels
* aantal sleutels
    * boom met \\(p\\) knopen
      minstens \\( 1+(p-1)\left( \lceil \frac{m}{2} \rceil -1 \right) \\) sleutels
      \\[ p \le  1 + \frac{n-1}{\lceil \frac{m}{2} \rceil -1} \\]
    * per toegevoegde sleutel
        * gemiddeld aantal splitsingen kleiner dan \\( \frac{1}{\lceil \frac{m}{2} \rceil -1} \\)
* knoop splitsen
    * vereist drie schijfoperaties
        * als de te splitsen knoop en ouder reeds ingelezen zijn
    * vereist processortijd van \\(O(m)\\)
        * alle kopieer- en opschuifbewerkingen begrensd door maximaal aantal kinderen in knoop
* in slechtste geval tweemaal volledige hoogte van boom doorlopen
    * per niveau slechts constant aantal schijfoperaties
* aantal schijfoperaties
  \\[
    \Theta(h) = \Theta{ \left( \log_{\lceil \frac{m}{2} \rceil}{(n)} \right) }
  \\]

### Verwijderen

* te verwijderen sleutel kan zowel in blad als in inwendige knoop zitten
    * uiteindelijk steeds uit blad verwijderen
    * anders zou er samen met sleutel een kind en bijbehorende deelboom moeten verdwijnen

#### Bottom-up verwijderen

* als blad te weinig sleutels overhoudt: sleutel aan ouder ontlenen
* in slechtste geval: ontlenen tot bij wortel
* sleutel ontlenen aan wortel met slechts één sleutel
    * wortel wordt ledig
    * verwijderen
    * B-tree krimpt bovenaan
* als te verwijderen sleutel in inwendige knoop zit
    * structuur van knoop niet wijzigen
    * sleutel vervangen door voorloper of opvolger die dan werkelijk verwijderd wordt
        * zit in blad
    * eerst helemaal afdalen om achteraf nog wijziging aan te brengen in hoger gelegen knoop
    * zeldzaam: meeste sleutels van B-tree zitten in bladeren
* alternatief: sleutel ontlenen aan broerknoop
    ![](/assets/btree_del_broerknoop.png)
    * met rotatie
        * sleutel van broer naar ouder
        * sleutel van ouder naar knoop die ook kindwijzer van broer overneemt
    * 3 knopen moeten aangepast worden
        * vaak meerdere sleutels overbrengen van broer
        * elk ongeveer even sleutels
        * opnieuw verwijderen geeft niet meteen weer problemen
    * er kan enkel sleutels ontleend worden aan broer die sleutels kan missen
        * anders bij andere broer
        * als beide broers geen sleutels kan missen
            * samenvoegen met broer
            * knoop verdwijnt uit boom
            * ouder verlist kind
            * sleutel tussen twee broers moet verdwijnen
                * wordt toegevoegd aan samengevoegde knoop
                * mogelijk gevolg: ouder houdt te weinig sleutels over

#### Performantie verwijderen

* bij roteren of samenvoegen
    * 3 knopen betrokken
        * drie schijfoperaties
* slechtste geval: tweemaal volledige hoogte van boom doorlopen
    * slechts constant aantal schijfoperaties per niveau
* totaal aantal schijfoperaties
  \\[
    \Theta(h) = \Theta{ \left( \log_{ \lceil \frac{m}{2} \rceil }{(n)} \right) }
  \\]
* per knoop: processortijd \\(O(m)\\)
* totale performantie
  \\[
    \Theta(mh) = \Theta{ \left( m\log_{ \lceil \frac{m}{2} \rceil }{(n)} \right) }
  \\]

## Varianten

### B<sup>+</sup>-tree

* nadelen gewone B-tree
    * bladeren moeten plaats reserveren voor kindwijzers 
        * toch niet gebruikt en niet ingevuld
    * inwendige knopen kunnen gegevens bevatten
        * maakt verwijderen ingewikkelder
        * zowel toevoegen als verwijderen moet uiteindelijk toch in blad gebeuren
    * zoeken naar opvolger van sleutel: vereist \\(O\left( \log_{ \lceil \frac{m}{2} \rceil }{(n)} \right) \\) schijfoperaties
* B<sup>+</sup>-tree: alle gegevens in bladeren opslaan
* inwendige knopen als index g ebruiken die tolaat om gegevens snel te lokaliseren
* bladeren en inwendige knopen: verschillende structuur
    * mogen in grootte verschillen
* *sequence set*: gelinkte lijst van alle bladeren, in stijgende sleutelvolgorde
    * zorgt ervoor dat zoeken naar opvolger van sleutel hoogstens één schijfoperatie vereist
    * sequentieel doorlopen van alle gegevens efficiënter
        * elke knoop wordt slechts éénmaal bezocht
        * in inwendig geheugen slechts plaats nodig voor 1 knoop
![](/assets/bplustree.png)
* scheiden van index en sequence set
    * inwendige knopen dienen uitsluitend om juiste weg te vinden
        * bevatten enkel sleutels en kindwijzers, zonder bijbehorende informatie
        * maximale graad kan groter worden
    * bladeren moeten niet plaats reserveren voor kindwijzers
        * kunnen meer gegevens bevatten
        * aantal gegevens in blad: tussen twee grenzen
            * verschillen meestal van deze voor inwendige knopen
    * hoogte van boom wordt kleiner
        * woordenboekoperaties worden sneller
* zeer geschikt voor zowel random als sequentiële operaties
* woordenboekoperaties verlopen nagenoeg zoals bij gewone B-tree
* zoeken steeds van wortel tot aan blad
    * stopt niet bij inwendige knoop die sleutel bevat
* toevoegen in blad
    * als blad gesplitst wordt
        * middelste sleutel blijft in één van twee knopen
    * enkel kopie van sleutel naar ouder
* verwijderen in blad
    * zolang blad genoeg sleutels overhoudt
        * hoger gelegen knopen moeten niet gewijzigd worden
        * ook als ze kopie van verwijderde sleutel bevatten
    * enige taak van inwendige knopen is leiden naar juiste blad
    * soms nodig om knopen aan te passen
        * wanneer blad gegevens moet ontlenen of samengevoegd worden met buur

### Prefix B<sup>+</sup>-tree

* als sleutels strings zijn
    * nemen teveel plaats in
* functie vna sleutel
    * sleutels in twee deelbomen van elkaar onderscheiden
* Prefix B<sup>+</sup>-tree gebruikt zo'n kort mogelijke string (prefix)
* meer plaats voor sleutels in inwendige knopen
* boom wordt minder hoog
* betere zoektijd

### B<sup>*</sup>-tree

* sleutels van knoop en volle buur verdelen over drie knopen
    * elk voor \\(\frac{2}{3}\\) gevuld
* wortel heeft geen buur
    * wachten met splitsen tot twee knopen voor \\(\frac{2}{3}\\) gevuld kunnen worden
    * toelaten dat wortel tot \\(\frac{4}{3}\\) van normale grootte opgevuld wordt
        * beter gevulde knopen betekend minder hoge boom
            * betere zoektijd

