

* geen hashtabel om trie te elimineren
    * pagina's met opeenvolgende adressen gebruiken
* \\(d\\) eindbits van hashwaarde worden rechtstreeks als logisch adres van pagina gebruikt
    * \\(2^d\\) adressen:  evenveel pagina's
    * wanneer \\(d\\) toeneemt: aantal pagina's verdubbelt **niet** (in tegenstelling tot hashtabel uit extendible hashing)
* pagina vol: splitsen
    * niet noodzakelijk volle pagina splitsen
    * pagina's worden in sequentiële volgorde gesplitst (ongeacht of ze vol zijn of niet)
    * als volle pagina niet gesplitst wordt maar andere
        * *overflow* pagina gebruiken
    * als volle pagina gesplitst wordt
        * gegevens van volle pagina en *overflow* pagina verdelen aan de hand van \\(d+1^\text{de}\\) eindbit
    * adresse nvan nog niet gesplitste pagina's blijven nog steeds \\(d\\) bits lang

## Woordenboekoperaties

### Zoeken

* hashwaarde van sleutel berekenen
* aantal eindbits van hashwaardig nodig om te adresseren
    * logisch adres van volgende te splitsen pagina wordt bijgehouden in variabele \\(p\\)
    * adres gevormd door \\(d\\) eindbits vergelijken met dat in \\(p\\) (telt ook \\(d\\) bits)
        * als kleiner: gezochte pagina is reeds gesplitst
        * \\(d+1\\) eindbits voor adres gebruiken
* pagina bevat gerangschikte tabel van sleutels
    * huidig aantal sleutels bijhouden (maximaal \\(m\\))
* sleutel lokaliseren via binair of lineair zoeken
    * soms nodig om in *overflow* pagina(s) te zoeken
* zoeken vereist meestal één schijfoperatie
    * tenzij in één of meerdere *overflow* pagina's moet gezocht worden
* *overflow* pagina's kunnen ook bij extendible hashing gebruikt worden

### Toevoegen

* eerst pagina lokaliseren zoals bij zoeken
* als pagina niet vol
    * gegeven tussenvoegen in gerangschikte tabel
* als pagina vol
    * er wordt een pagina gesplitst
    * adres van volgende te splitsen pagina zit in \\(p\\)
        * initieel 0
        * bij elke splitsing \\(p\\) incrementeren
            * tot alle \\(2^d\\) pagina's gesplitst zijn
                * volgende expansieronde
                * \\(p\\) wordt terug 0 en \\(d\\) wordt geïncrementeerd
    * als volle pagina niet gesplitst werd
        * gegeven toevoegen aan *overflow* pagina

### Verwijderen

* eerst pagina lokaliseren
* gegeven uit tabel halen
    * eventueel uit *overflow* pagina
* onderbezette pagina's verdwijnen in omgekeerde volgorde als waarin ze gecreëerd werden
    * gegevens komen terecht in pagina waarvan ze origineel afgesplitst werden
* vermijden dat bij toevoegen snel weer gesplitst wordt
    * gezamenlijk aantal gegevens moet kleiner zijn dan \\(m\\)
