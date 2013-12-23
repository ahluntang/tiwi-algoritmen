
## B<sup>+</sup>-tree

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

## Prefix B<sup>+</sup>-tree

* als sleutels strings zijn
    * nemen teveel plaats in
* functie vna sleutel
    * sleutels in twee deelbomen van elkaar onderscheiden
* Prefix B<sup>+</sup>-tree gebruikt zo'n kort mogelijke string (prefix)
* meer plaats voor sleutels in inwendige knopen
* boom wordt minder hoog
* betere zoektijd

## B<sup>*</sup>-tree

* sleutels van knoop en volle buur verdelen over drie knopen
    * elk voor \\(\frac{2}{3}\\) gevuld
* wortel heeft geen buur
    * wachten met splitsen tot twee knopen voor \\(\frac{2}{3}\\) gevuld kunnen worden
    * toelaten dat wortel tot \\(\frac{4}{3}\\) van normale grootte opgevuld wordt
        * beter gevulde knopen betekend minder hoge boom
            * betere zoektijd
