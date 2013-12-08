
## Binaire tries

![](/assets/binairetrie.png)

* opeenvolgende bits gebruiken om juiste weg te volgen
* aantal? tot je onderscheidende bit gevonden hebt.
* nadeel: lange prefixen, weg wordt zeer lang
* voordeel: inorder geeft sleutels in volgorde

## Meerwegstries

* splitsen op meerdere bits, bv. karakter
* m wegen per knoop
* \\( O(\log_m{n}) \\)
* c-string: prefix kan gebruikt worden: eindigen met afsluitkarakter of nullchar: \\(\varnothing \\)
    * aard\\(\varnothing \\)
    * aardappel\\(\varnothing \\)

## Patricia tries

![](/assets/patriciatrie.png)

* enkel knopen met meer dan 1 kind
    * bij elke knoop index van de te testen sleutelelement opslaan
* slechts 1 soort knopen
    * sleutels in inwendige knopen opslaan
    * wijzers naar bladeren: wijzers naar inwendige knopen, hoger gelegen in boom

