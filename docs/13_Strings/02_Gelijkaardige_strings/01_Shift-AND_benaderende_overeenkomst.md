
* Shift-AND methode aanpassen om fouten (gewijzigde en/of ingelaste en/of verwijderde karakters) in gevonden patroon toe te laten

* `P`: Patroon
* `T`: Tekst/hooiberg
* `S`: Letterpatroon
    * bevat Bitpatronen
* `R`: ééndimensionale tabel van \\(m\\) logische waarden
* exacte overeenkomst
    * \\( R_{j+1}[0] = ( P[0] == T[j+1] ) \\)
    * \\(R_{j+1}[i] = R_j[i-1] \text{ EN } ( P[i] == T[j+1] ) \\)

## Hoogstens \\(1\\) fout

### Karakter inlassen/toevoegen

* slechts één karakter op willekeurige plaats in `P`
    * alle deelstrings in `T` niet langer dan \\(m+1\\) die `P`
* dezelfde tabellen `R` en `S` gebruiken
    * twee mogelijkheden om overeenkomst te vinden voor elke prefix
        * exact
        * met één inlassing
    * analoge tabel \\(R_j^1\\) invoeren
        * duidt alle prefixen aan die in tekst te  vinden zijn die eindigen bij positie \\(j\\) met hoogstens één inlassing
          `R` wordt voortaan genoteerd als \\(R^0\\)
        * \\(R_j^1[i] == true \\) : eerste \\(i\\) karakters van `P` overeenkomen met \\(i\\) van de \\(i+1\\) karakters die in tekst eindigen bij positie \\(j\\)
        * \\(R_j^0[m] == true\\) : duidt exacte overeenkomst aan
        * \\(R_j^1[m] == true\\) : duidt overeenkomst met hoogstens één inlassing aan
    * afleiding van \\(R_{j+1}^0\\) uit \\(R_{j}^0\\)blijft gelijk
        * \\(R_{j+1}[i] = Schuif(R_j^0) \text{ EN } ( S[ T[j+1] ] ) \\)
    * voor bepaling van \\(R_{j+1}^1[i]\\)
        * onderscheid maken tussen
            * inlassing aan einde van prefix (na patroonpositie \\(i\\))
            * inlassing op andere plaats
        * eerste \\(i\\) patroonkarakters komen exact overeen tot tekstpositie \\(j\\)
            * als we tekstkarakter `T[j+1]` na die \\(i\\) karakters inlassen
            * overeenkomst van \\(i\\) patroonkarakters met één inlassing tot tekstpositie \\(j+1\\)
        * eerste \\(i-1\\) patroonkarakters komen overeen tot tekstpositie \\(j\\) met hoogstens één inlassing
            * `T[j+1] == P[i]`
            * eventuele inlassing gebeurt elders in prefix en niet aan einde
    * beide gevallen combineren met OF-operatie
        * kunnen apart maar ook samen voorkomen
        * \\( R_{j+1}^1[i] = R_j^0[i] \text{ OF } \left( R_j^1[i-1] \text{ EN } (T[j+1] == P[i]) \right) \\)
    * in eerste geval (eerste \\(i\\) patroonkarakters komen exact overeen, inlassing **na** patroonpositie \\(i\\))
        * \\(R_{j+1}^1\\) is exacte kopie van \\(R_j^0\\)
    * in tweede geval
        * schuifoperatie op \\(R_j^1\\) gevolgd door bit-per-bit EN-operatie met `S[ T[j+1] ]`
    * \\( R_{j+1}^1 = R_j^0 \text{ OF } \left( Schuif(R_j^1) \text{ EN } S[ T[j+1] ] \right) \\)
    * \\(R^1\\) berekenen voor elke tekstpositie vereist ook slechts enkele processorinstructies (`true` bit inschuiven)

### Karakter verwijderen

* stel: toelaten dat er één karakter verwijderd wordt (geen inlassing meer)
    * opnieuw tabellen \\(S, R^0, R^1 \\)
        * laatste tabel duidt prefixen met hoogstens één verwijdering aan
* \\(R_{j}^1[i]\\) = `true` als
    * \\(i-1\\) van de eerste \\(i\\) karakters van `P` overeenkomen met \\(i-1\\) karakters die in tekst eindigen bij positie \\(j\\)
* twee mogelijke gevallen voor overeenkomst van \\(i\\) eerste karakters van `P` eindigend op tekstpositie \\(j+1\\) met hoogstens één verwijdering
    * eerste \\(i-1\\) patroonkarakters komen exact overeen tot tekstpositie \\(j+1\\)
        * `P[i]` wordt verwijderd
        * bit \\(R_{j+1}^0[i-1]\\) uit nieuwe tabel \\(R^0\\) is `true`
    * eerste \\(i-1\\) patroonkarakters met hoogstens één verwijdering komt overeen tot tekstpositie \\(j\\)
        * `T[j+1] == P[i]`
        * verwijdering gebeurt opnieuw ergens binnenin, niet aan einde
* gevallen combineren met OF-operatie
    * \\( R_{j+1}^1[i] = R_{j+1}^0[i-1] \text{ OF } \left( R_j^1[i-1] \text{ EN } (T[j+1] == P[i]) \right) \\)
* eerste geval vereist enkel schuifoperatie op nieuwe tabel \\(R_{j+1}^0\\) (moet reeds bepaalds zijn)
* \\( R_{j+1}^1 = Schuif(R_{j+1}^0) \text{ OF } \left( Schuif(R_j^1) \text{ EN } S[ T[j+1] ] \right) \\)

### Karakter vervangen

* toelaten dat er één karakter van `P` vervangen wordt door tekstkarakter
* vervanging kan gesimuleerd worden met verwijdering en inlassing
    * beschouwen als slechts 1 fout
* als \\( R_j^1[i] == true \\)
    * \\(i-1\\) van eerste \\(i\\) karakters van `P` komen overeen met \\(i-1\\) van \\(i\\) karakters die in tekst eindigen bij positie \\(j\\)
* twee gevallen
    * eerste \\(i-1\\) patroonkarakters komen exact overeen tot bij tekstpositie \\(j\\)
        * karakter `P[i]` werd vervangen door `T[j+1]`
    * eerste \\(i-1\\) patroonkarakters komen met hoogstens één vervanging overeen tot bij tekstpositie \\(j\\) en `P[i] == T[j+1]`
        * vervanging gebeurt binnenin
* \\( R_{j+1}^1[i] = R_j^0[i-1] \text{ OF } \left( R_j^1[i-1] \text{ EN } (T[j+1] == P[i]) \right) \\)
* voor geval 1
    * \\(R_j^0\\) naar rechts schuiven
* geval twee is hetzelfde als bij inlassing en verwijdering
* \\( R_{j+1}^1 = Schuif(R_{j}^0) \text{ OF } \left( Schuif(R_j^1) \text{ EN } S[ T[j+1] ] \right) \\)

### Gevallen combineren

* hoogstens 1 willekeurige fout toelaten
* drie gevallen combineren met OF-operatie
* \\( R_{j+1}^1 = R_j^0  \\text{ OF } Schuif(R_{j+1}^0) \text{ OF } Schuif(R_{j}^0) \text{ OF } \left( Schuif(R_j^1) \text{ EN } S[ T[j+1] ] \right) \\)

## Hoogstens \\(f\\) fouten

* elk van fouten kan inlassing, verwijdering of vervanging zijn
* in plaats van tabel \\(R^1\\)
    * \\(f\\) tabellen: \\(R^1, R^2, ..., R^f\\)
        * waarbij \\(R^k\\) alle mogelijke overeenkomende prefixen met hoogstens \\(k\\) fouten aanduidt
* \\(R_{j+1}^k\\) af te leiden met behulp van \\( R_j^k \\)
    * er kan fout bijkomen, dus ook \\(R_j^{k-1}\\) en \\(R_{j+1}^{k-1}\\) nodig
* overgangen tussen tabellen voor posities \\(j\\) en \\(j+1\\) moeten bepaald worden volgens stijgende \\(k\\)
* vier mogelijke gevallen om overeenkomst te vinden voor eerste \\(i\\) karakters met hoogstens \\(k\\) fouten, eindigend bij tekstpositie \\(j+1\\)
  eerste drie gevallen: fout treedt op aan einde van `P`
  bij vierde geval: alle eventuele fouten komen elders in `P` voor
    * overeenkomst van eerste \\(i\\) patroonkarakters met hoogstens \\(k-1\\) fouten tot bij tekstpositie \\(j\\)
        * tekstkarakter `T[j+1]` wordt ingelast na `P[i]`
    * overeenkomst van eerste \\(i-1\\) patroonkarakters met hoogstens \\(k-1\\) fouten tot bij tekstpositie \\(j+1\\)
        * verwijdering van `P[i]`
    * overeenkomst van eerste \\(i-1\\) patroonkarakters met hoogstens \\(k-1\\) fouten tot bij tekstpositie \\(j\\)
        * vervanging van `P[i]` door `T[j+1]`
    * overeenkomst van eerste \\(i-1\\) patroonkarakters met hoogstens \\(k\\) fouten tot bij tekstpositie \\(j\\) en `P[i] == T[j+1]`
* alles samen (voor \\(k > 0\\))
  \\[
        R_{j+1}^k = R_j^{k-1} \text{ OF } Schuif(R_{j+1}^{k-1}) \text{ OF } Schuif(R_{j}^{k-1}) \text{ OF } \left( Schuif(R_{j}^{k}) \text{ EN } S[ T[j+1] ] \right) \\\
        R_{j+1}^k = R_j^{k-1} \text{ OF } Schuif(R_{j+1}^{k-1} \text{ OF } R_{j}^{k-1}) \text{ OF } \left( Schuif(R_{j}^{k}) \text{ EN } S[ T[j+1] ] \right) \\\
        R_0^k = \overset{\mbox{m}}{\overbrace{\underset{\mbox{k}}{\underbrace{11...1}}00...0}}
  \\]
* elke \\(R^k (k > 0)\\) kan bepaald worden met twee schuifoperaties, één EN- en drie OF-operaties

### Performantie

* voorbereidend werk
    * opstellen van tabel `S`
    * initialiseren van de \\(f+1\\) tabellen
        * vereist \\( O( f \lceil \frac{m}{w} \rceil ) \\) operaties
    * daarna \\( O( f \lceil \frac{m}{w} \rceil ) \\) operaties per tekstkarakter
* totale performantie \\( O( n f \lceil \frac{m}{w} \rceil ) \\)
* bij niet al te grote \\(m\\):
    * \\( O( nf ) \\)

## Uitbreidingen

* verzameling van karakters
* jokers
* onbekend aantal fouten
* combinatie van exacte en benaderende overeenkomst
* fouten met verschillende kost

### Verzameling van karakters

* in plaats van welbepaald karakter in patroon
    * verzameling van toegelaten karakters specificeren
* voorbeeld: patroon `ABC[0-9]XYZ` met hoogstens \\(k\\) fouten zoeken
    * aanpassing: om elk mogelijk cijfer te aanvaarden op vierde positie van zoekstring
        * in elke rij van tabel `S` die overeenkomt met cijfer `true` bit voorzien op vierde index
* complement van karakter
    * speciaal geval van verzameling karakters
    * kan op analoge manier behandeld worden

### Jokers

* één enkele joker
    * karakter dat overeenkomt met elk mogelijk karakter
* kan als speciaal geval van *verzameling van karakters* beschouwd worden

### Onbekend aantal fouten

* stel: alle plaatsen in tekst zoeken waar patroon met zo weinig mogelijk fouten voorkomt
* eerst exacte overeenkomst zoeken
    * als er geen is: overeenkomst met twee fouten
    * ...
* performanter
    * telkens dubbel zoveel fouten + 1 toelaten: \\(( 2 \times f ) + 1\\)
        * eerst zonder fouten, dan 1 fout, dan 3 fouten, 7 fouten ...
          ~ binair zoeken
        * als \\(k\\) minimaal aantal fouten is
            * uitvoeringstijd \\(O(n + 2n + 4n + ... + 2^bn)\\)
              waarbij \\(2^b\\) kleinste macht van 2 is dat groter is dan \\(k\\)
              \\(b = \lfloor \lg{k} \rfloor + 1\\)
        * in slechtste geval 4 maal meer operaties dan wanneer \\(k\\) op voorhand gekend was
            * in praktijk slechts 2 of 3 maal zoveel

### Combinatie van exacte en benaderende overeenkomst

* in bepaalde delen van patroon mogen geen fouten optreden
* stel: nummerplaat `ABC123` zoeken
    * letters zijn zeker
    * één van cijfers kan verkeerd zijn
* gedeelte van patroon moet afgeschermd worden tegen optreden van fouten
* extra tabel `M` van \\(m\\)  logische waarden
    * masker
    * `true` op patroonposities waar fout mag optreden
    * `false` op als er geen fout mag optreden
* berekening van \\(R_{j+1}^k\\)
    * inlassingen, verwijderingen en vervangingen enkel mogelijk op posities waar masker `M` een `true` bit bevat
      \\[
        R_{j+1}^k = \left( \left( R_j^{k-1} \text{ OF } Schuif(R_{j+1}^{k-1} OF R_{j}^{k-1}) \right) \text{ EN } M \right) \text{ OF } \left( Schuif(R_{j}^{k}) \text{ EN } S[ T[j+1] ] \right)
      \\]

### Fouten met verschillende kost

* *edit-distance*
    * veronderstelt dat inlassingen, verwijderingen en vervangen evenveel kosten
* als kosten van verschillende operaties kleine gehele getallen zijn
    * berekening van \\(R_{j+1}^k\\) kan hiermee rekening houden door bijdrage van bepaalde soort fout tot aantal fouten groter dan 1 maken
* stel: kost van inlassing en verwijdering bedraagt 3, kost van vervanging slechts 1
    * zeven fouten kunnen bestaan uit
        * 1 verwijdering en 4 vervangingen
        * 1 inlassing, 1 verwijdering en 1 vervanging
    * voor vervanging verandert niets
    * andere fouten kosten 3 maal zoveel
        * inlassing of verwijdering die tot overeenkomst met hoogstens \\(k\\) fouten leidt
            * moet nu afkomstig zijn van overeenkomst met hoogstens \\(k-3\\) fouten
        * aanpassing: vervang \\(k-2\\) door \\(k-3\\) in de termen die overeenkomen met inlassen en verwijderen
* kan aangepast worden
    * om naar aantal patronen tegelijk te zoeken
    * om naar patroon te zoeken beschreven door reguliere uitdrukking


















