
* gesloten omloop in multigraaf die alle verbindingen 1 maal bevat 
* niet elke graaf heeft eulercircuit
* via diepte-eerst zoeken
* duaal probleem: Hamilton-circuit
    * bevat alle knopen 1 maal
    * geen efficiënte oplossing: NP-compleet

## ongericht

### eigenschappen

1. samenhangende multigraaf \\(G\\) is Eulergraaf
1. graad van elke knoop is even
1. verbindingen van \\(G\\) kunnen onderverdeeld worden in lussen

* 2 volgt uit 1:
    * telkens als knoop \\(k\\) voorkomt op Eulercircuit
        * draagt twee bij tot zijn graad
    * elke verbinding komt precies éénmaal voor op circuit
        * elke knoopgraad moet even zijn
* 3 volgt uit 2:
    * stel: \\(G\\) heeft \\(n\\) knopen
        * minstens \\(n-1\\) verbindingen, want \\(G\\) is samenhangend
    * geen enkele knoopgraad = 1: minstens \\(n\\) verbindingen
        * \\(G\\) bevat minstens 1 lus
    * lus verwijderen
        * niet noodzakelijk samenhangende graaf \\(H\\) over waarvan alle knoopgraden nog steeds even zijn
        * elk van de samenhangende componenten van \\(H\\) kan op dezelfde manier onderverdeeld worden in lussen
            * tot volledige graaf in lussen onderverdeeld is
* 1 volgt uit 3:
    * stel \\(L\\) is 1 van de lussen van \\(G\\)
    * als \\(L\\) een Eulercircuit is, dan is \\(G\\) een Eulergraaf
    * zoniet
        * er bestaat een andere lus \\(L'\\) die gemeenschappelijke knoop \\(k\\) heeft met \\(L\\)
            * \\(L'\\) kan bij knoop \\(k\\) tussengevoegd worden in lus \\(L\\)
                * grotere lus
            * herhalen tot je Eulercircuit bekomt
                * elke verbinding behoort tot 1 lus

### constructie

* eerste lus
    * beginnen bij willekeurige knoop
    * verbindingen volgen tot je weer bij die knoop terechtkomt
* volgende lus
    * beginnen bij een van knopen van \\(L\\) waarvan nog niet alle verbindingen doorlopen zijn
    * verbindingen volgen tot we weer bij beginknoop zijn
* testen in volgorde langs lus
* nieuwe lussen genereren zolang niet alle verbindingen van knoop opgebruikt zijn
    * pas dan volgende knoop onderzoeken

### Eulerweg

* geen gesloten circuit
* begin- en eindknoop: graad oneven

## gerichte grafen

* Eulercircuit in gerichte graaf
    * slechts mogelijk als graaf sterk samenhangende Eulergraaf is
* voorwaarden analoog als voor ongerichte graaf
    * ingraad moet gelijk zijn aan uitgraad: graaf is pseudo-symmetrisch
* constructie analoog
