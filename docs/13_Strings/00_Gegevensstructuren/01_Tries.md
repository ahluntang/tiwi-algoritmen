
* digitale zoekstructuur die wél volgorde van opgeslagen sleutels behoudt

## Binaire tries

* zoekweg volledig bepaald door opeenvolgende bits van zoeksleutel
* verschil met digitale zoekbomen
    * slaan sleutels niet op in inwendige knopen, enkel in bladeren
* in-order overlopen van boom levert opgeslagen sleutels in gerangschikte volgorde
* zoeksleutel moet niet meer vergeleken worden met sleutel in elke knoop op zoekweg

![](/assets/binairetrie.png)

* zoeken en toevoegen gebruiken enkel opeenvolgende bits van zoeksleutel om juiste weg te volgen
    * bij ledige deelboom terechtkomen (nullwijzer)
        * boom bevat zoeksleutel niet
        * eventueel op deze plaats toevoegen (in nieuw blad)
    * in blad terechtkomen
        * blad bevat enige sleutel in boom die gelijk kan zijn aan zoeksleutel
            * hebben dezelfde beginbits
            * vergelijking van beide sleutels geeft uisluitsel
        * als zoeksleutel niet aanwezig is
            * sleutel in blad en zoeksleutel hebben minstens dezelfde beginbits (bepaald door weg van wortel tot bij blad)
            * als volgend bit verschilt
                * blad vervangen door knoop met twee kinderen (één voor elke sleutel)
            * als er nog meer bits van beide sleutels gelijk zijn
                * blad vervangen door reeks opeenvolgende (inwendige) knopen tot er verschillende bits zijn 
                * weg tussen die knopen komt overeen met gemeenschappelijke bits
                * bij eerste verschillende bit: laatste knoop krijgt twee kinderen/bladeren
* nadeel: wanneer opgeslagen sleutels veel gelijke beginbits hebben
    * veel knopen met slechts 1 kind
    * weg wordt zeer lang bij lange prefixen
    * aantal knopen is hoger dan aantal sleutels
    * trie met \\(n\\) gelijkmatig verdeelde sleutels: gemiddeld \\(\frac{n}{\ln{2}}\\) inwendige knopen
* sleutels mogen geen prefix van andere sleutel zijn
    * als langere sleutel reeds in boom it
    * kortere sleutel zoeken/toevoegen
        * er blijven geen bits meer over om hem van eerste te onderscheiden
* voordeel: 
    * inorder geeft sleutels in volgorde
        * structuur van tries onafhankelijk van volgorde waarin sleutels werd toegevoegd
        * voor elke verzameling sleutels slechts één trie mogelijk
    * geen sleutelvergelijkingen langs zoekweg
        * enkel opeenvolgende bits van zoeksleutel wordt getest
        * pas op einde eventueel één sleutelvergelijking
        * interessant als sleutels lange strings zijn


### Performantie

* trie met \\(n\\) gelijkmatig verdeelde sleutels
    * zoeken/toevoegen: gemiddeld \\(O(\lg{n})\\) bitoperaties
        * nooit hoger dan bitlengte van zoeksleutel
    * hoogte beperkt door bitlengte van langste opgeslagen sleutel

## Meerwegstries

* hoogte van trie met lange sleutels beperken
    * in elke knoop meerdere (opeenvolgende) sleutelbits tegelijk behandelen
    * maakt radix sort sneller
* splitsen op meerdere bits, bv. karakter
stel: sleutelelement kan \\(m\\) verschillende waarden aannemen
    * elke inwendige knoop van trie krijg (potentieel) \\(m\\) kinderen
        * \\(m\\) wegen per knoop
    * \\(m\\)-wegsboom
* zoeken/toevoegen
    * analoog als bij binaire trie
    * in elke knoop van zoekweg \\(m\\)-wegsbeslissing nemen
        * op grond van volgend sleutelelement
    * operaties \\(O(1)\\)
        * wijzers naar kinderen opslaan in tabel en indexeren met sleutelelement
* toevoegen
    * kan aanmaak vereisen van opeenvolgende reeks inwendige knopen met slechts één kind
    * tabellen in elke knoop: veel plaatsverlies
* kinderen van knopen zijn geordend volgens waarde van sleutelelementen
    * sleutels kunnen opnieuw in *alfabetische* volgorde uit boom opgehaald worden
* prefix: informatie in inwendige knopen opslaan
    * elk van knopen komt overeen met sleutelprefix
    * elke knoop moet extra kind krijgen
    * eindigen met afsluitkarakter of nullchar: \\(\varnothing \\)
        * aard\\(\varnothing \\)
        * aardappel\\(\varnothing \\)

### Performantie meerwegstries

* analoog met binaire tries
* zoeken of toevoegen
    * in boom met uniform verdeelde sleutels
        * gemiddeld \\( O(\log_m{n}) \\) testen
    * aantal testen nooit groter dan lengte van zoeksleutel
    * boomhoogte beperkt door lengte van langst opgeslagen sleutel
* \\(m\\)-wegstrie voor \\(n\\) gelijkmatig verdeelde sleutels
    * slechts \\(\frac{n}{\ln{m}}\\) inwendige knopen
        * aantal wijzers in knopen: \\( \frac{nm}{\ln{m}} \\)

### Geheugengebruik meerwegstries beperken

* gelinkte lijst
    * in plaats van tabel met \\(m\\) wijzers in elke knoop
    * meeste zijn vaak toch nullwijzers
    * ten koste van snelheidsverlies
    * lijst bevat sleutelelement en wijzer
    * lijst is gerangschikt volgens sleutelelementen
    * als sleutelelement veel waarden kan aannemen (\\(m\\) is groot)
        * verschillende mechanismen gebruiken, afhankelijk van niveau in boom
        * op eerste niveau
            * veel kinderen: tabel
        * op laagste niveaus
            * weinig kinderen: gelinkte lijst
        * intermediaire niveaus
            * hashtabellen of efficiënte zoekbomen
* enkel trie voor eerste niveaus, dan overschakelen op andere gegevensstructuur
    * stoppen wanneer deelboom niet meer dan \\(s\\) sleutels bevat
    * sleutels in korte lijst opslaan
    * aantal inwendige boomknopen daalt met factor \\(s\\)
      \\( \frac{n}{s\ln{m}} \\)

## Patricia tries

* vermijdt 
    * onnodig veel geheugenverbruik
    * twee soorten knopen
* enkel knopen met meer dan 1 kind behouden
    * bij elke knoop index van de te testen sleutelelement opslaan
* slechts 1 soort knopen
    * sleutels in inwendige knopen opslaan
    * wijzers naar bladeren: wijzers naar inwendige knopen, hoger gelegen in boom

### Binaire Patricia tries

![](/assets/patriciatrie.png)

* knopen bevatten
    * sleutel
    * index
    * twee wijzers
* wijzers
    * kunnen kinderen aanduiden of refereren naar sleutel (hoger gelgen knoop)
    * kan afgeleid worden uit indices bij betrokken knopen
* voor \\(n\\) sleutels: \\(n\\) knopen vereist
    * die \\(2n\\) wijzers bevatten
        * \\(n\\) wijzers naar sleutel
        * \\(n-1\\) wijzers naar kindknoop
* zoeken
    * negeert sleutels in knopen op zoekweg
    * test in elke knoop aangeduide zoeksleutelbit
    * eindigt met sleutelvergelijking wanneer wijzer naar hoger gelegen knoop refereert
        * of naar eigen knoop
        * is enige plaats waar gezochte sleutel zou kunnen staan
* elke sleutel ligt opgeslagen op eigen zoekweg
    * wordt 2 maal ontmoet
    * tijdens zoeken
    * op einde vna zoeken
* toevoegen
    * begint met zoeken
        * eindigt steeds met sleutelvergelijking (geen nullpointers)
    * als sleutels niet gelijk zijn: toevoegen
    * meest linkse bit zoeken waarin beide sleutels verschillen
    * sleutel tweede maal in boom zoeken
        * bij knoop komen met hogere bitpositi dan onderscheidende bit
            * nieuwe knoop tussenvoegen waar bit getest wordt
            * bij die bit zou onderliggende trie een knoop met nullwijzer hebben
                * daar moet sleutel terechtkomen (in nieuw blad)
            * sleutel wordt in nieuwe knoop opgeslagen
            * gepaste wijzer vanuit knoop moet ernaar refereren
        * geen enkele knoop met hogere bitpositie gevonden
            * zoeken in onderliggende trie zou geëindigd zijn bij blad
            * laatste sleutelwijzer vervangen door wijzer naar nieuwe knoop met
                * nieuwe sleutel
                * index van onderscheidende bit
                * wijzers naar 
                    * nieuwe sleutel 
                    * sleutel die zoekweg afsloot
* slechts één knoop toevoegen (met nieuwe sleutel)
    * die meest linkse onderscheidende bit tussen zoeksleutel en gevonden sleutel aanduidt
* structuur hangt af van volgorde waarin sleutels werden toegevoegd
    * structuur van knopen blijft onafhankelijk van volgorde
* zoeken of toevoegen vereist gemiddeld \\(O(\lg{n})\\) bitvergelijkingen
    * nooit meer dan bitlengte van zoeksleutel
* hoogte van boom en maximaal aantal bitvergelijkingen beperkt door lengte van langst opgeslagen sleutel
* patricia tries testen meteen belangrijkste bits
    * zoektijd neemt niet toe met sleutellengte
    * geschikt voor lange sleutels
* alternatieve voorstelling van gewone trie
    * volgorde van opgeslagen sleutels blijft intact
* patricia tries combineren voordelen van digitale zoekbomen en tries
    * digitale (en gewone) zoekbomen gebruiken niet meer geheugen dan nodig
        * om \\(n\\) sleutels op te slaan: vereisen slechts \\(n\\) knopen
        * nullwijzers worden nuttig gebruikt
    * zijn even efficiënt als tries
        * zoeken vereist gemiddeld \\(O(\lg{n})\\) bittesten
            * gevolgd door één sleutelvergelijking
    * respecteren volgorde van sleutels
        * net zoals tries en gewone zoekbomen
        * bijkomende operaties zijn mogelijk




