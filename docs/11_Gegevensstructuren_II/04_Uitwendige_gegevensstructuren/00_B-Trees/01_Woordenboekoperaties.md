## Zoeken

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

### Performantie zoeken

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

## Toevoegen

* aanpassingen aan boomstructuur mogelijk
    * kan topdown of bottom-up
    * in slechtste geval vereist bottom-up versie dat hoogte van boom tweemaal doorlopen wordt
        * veel erger dan inwendige boom, maar zeer zeldzaam
        * niet als meest recent gebruikte knopen bijgehouden wordt in inwendig geheugen

### Bottom-up toevoegen

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

### Performantie toevoegen (bottom-up)

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

## Verwijderen

* te verwijderen sleutel kan zowel in blad als in inwendige knoop zitten
    * uiteindelijk steeds uit blad verwijderen
    * anders zou er samen met sleutel een kind en bijbehorende deelboom moeten verdwijnen

### Bottom-up verwijderen

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

### Performantie verwijderen

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
