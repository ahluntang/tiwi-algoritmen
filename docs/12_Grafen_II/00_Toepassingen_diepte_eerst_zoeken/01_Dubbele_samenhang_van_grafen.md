## ongerichte graaf

### dubbel lijnsamenhangend

* graaf zonder bruggen
    * brug: verbinding die ongerichte graaf doet uiteenvallen in twee gescheiden deelgrafen wanneer ze wordt weggenomen
* als alle bruggen uit graaf wordt weggenomen
    * dubbel lijnsamenhangende componenten
* tussen elk paar knopen
    * minstens twee wegen zonder gemeenschappelijke verbindingen
    * gemeenschappelijke knopen wel toegelaten

### dubbel samenhangend

* graaf zonder scharnierpunten
    * scharnierpunt: doet graaf uiteenvallen in tenminste twee gescheiden deelgrafen
* graaf met scharnierpunten
    * kan onderverdeeld worden in bruggen en dubbel samenhangende componenten
    * zijn verbonden in scharnierpunten, eventueel via bruggen
* twee componenten: kunnen gemeenschappelijke knoop hebben, nooit gemeenschappelijke verbinding
    * elke verbinding behoort tot 1 component, of het is een brug
* tussen elk paar knopen
    * twee onafhankelijke wegen, zonder gemeenschappelijke verbindingen en knopen

### diepte-eerst zoeken

* `diepte-eerst` boom opstellen: knopen preorder nummeren
* voor elke knoop \\(u\\) 
    * de laagst genummerde knoop bepalen die vanuit \\(u\\) bereikt kan worden via weg bestaande uit nul of meerdere dalende boomtakken, gevolgd door 1 terugverbinding
    * kan via tweede postordernummering
* als alle kinderen van knoop een knoop kunnen bereiken die hoger ligt in boom
    * knoop is zeker geen scharnierpunt
    * wortel = speciaal geval: scharnierpunt als die meer dan 1 kind heeft
* eenzelfde knoop kan meermaals scharnierpunt zijn
* diepte eerst zoeken
    * ijle graaf: \\( \Theta(n+m) \\)
    * dichte graaf: \\( \Theta(n^2) \\)

### zoek scharnierpunten en zoek bruggen

```
void rec_zoek_scharnierpunten(int i){ // rec_zoek_bruggen
    ontdekt[i] = true;
    pre[i] = num++;
    laagst[i] = pre[i]; // initialisatie: elke knoop bereikt minstens zichzelf
    for(alle buren j van knoop i){
        if(!ontdekt[j]){
            // boomtak, dus kint van i
            ouder[j] = i;
            rec_zoek_scharnierpunten(j); // recursief oproepen
            if( laagst[j] < laagst[i] )
                laagst[i] = laagst[j] ; // nieuw minimum
            else if ( laagst[j] >= pre[i] ) // voor bruggen: laagst[j] > pre[i]
                cout << "Knoop " << i << "is scharnierpunt voor" << j << endl;
        } else {
            if( j != ouder[i] ) // eventueel terugverbinding
                if( pre[j] < laagst[i] ) // dan is zeker pre[j] < pre[i] : dus terugverbinding
                    laagst[i] = pre[j]; // nieuw minimum
        }
    }
}

void zoek_scharnierpunten() { // zoek_bruggen
    for(int i = 0; i < n; i++){ // initialisatie
        ontdekt[i] = false;
        ouder[i] = -1; // nog geen ouder
    }
    int num = 0; // initialisatie preordernummering
    rec_zoek_scharnierpunten(0); // rec_zoek_bruggen(0)
}
```
