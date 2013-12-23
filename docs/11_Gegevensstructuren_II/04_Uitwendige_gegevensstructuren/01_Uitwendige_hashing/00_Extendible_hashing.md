
## Uitwendige hashing

* hashing: als men niet geïntereseerd is in volgorde van sleutels
* eenvoudiger en efficiënter alternatief dan B-trees
* woordenboekoperaties vereisen (gemiddeld) slechts \\(O(1)\\) schijfoperaties
* informatie-overdracht bij schijf: in pagina's
    * aan elk hashtabelelement schijfpagina toewijzen
    * alle sleutels met dezelfde hashwaarde komen in dezelfde pagina terecht
    * streefdoel: \\(O(1)\\) schijfoperaties
* wat als er zoveel conflicten zijn dat pagina vol geraakt
    * technieken van inwendige hashtabellen?
        * aantal schijfoperaties zou stijgen
    * boom: flexibele structuur
        * alle gegevens opgeslagen in schijfpagina's
            * zo snel mogelijk bij juiste pagina terechtkomen
        * trie
            * zoeken
                * niet vergelijken met sleutels in knopen, maar met opeenvolgende bits
            * elke deelboom bevat alle sleutels met gemeenschappelijke prefix
            * bladeren zijn schijfpagina's
                * kunnen veel sleutels bevatten
                * alle sleutels van deelboom in 1 pagina onderbrengen
                * weg naar pagina in trie korter
            * pas als pagina vol geraakt: splitsen
                * beide pagina's krijgen nieuwe trieknoop als ouder
            * vorm van trie onafhankelijk van toevoegvolgorde
                * volledig bepaald door bits van sleutels
            * boom kan zeer onevenwichtig uitvallen
                * hashwaarden
                * goede hashfunctie: hashwaarden zo random mogelijk
                    * meer evenwichtige boom

## Extendible hashing

* elimineert zoeken in trie
    * langst mogelijke prefix uit trie als index gebruiken in hashtabel
    * kortere prefixen komen overeen met meerdere tabelelementen (elke index heeft evenveel bits)
        * bevatten allemaal verwijzing naar dezelfde pagina
    * vinden van pagina: \\(O(1)\\)
* tabel bevat wijzers naar schijfpagina's die maximaal \\(m\\) sleutels met bijbehorende gegevens bevatten
    * sleutels worden stijgend gerangschikt en in tabel opgeslagen
* hashwaarden: gehele getallen
    * bereik bepaald door breedte \\(w\\) van processorwoord
    * laatste \\(d\\) bits van getallen: als indices in hashtabel gebruiken
        * tabel bevat \\(2^d\\)  elementen \\( (d < w) \\)
* sleutels waarvan hashwaarde met dezelfde \\(d\\) bits eindigt
    * komen bij hetzelfde tabelelement terecht
    * in overeenkomstige pagina opslaan
* eenzelfde pagina kan sleutels met hashwaarden bevatten waarvan laatste \\(d\\) bits verschillend zijn
    * meerdere tabelelementen mogen naar dezelfde pagina verwijzen
    * per pagina aantal bits \\(k\\) bijhouden waarmee al haar hashwaarden eindigen (lokale diepte)
    * \\( 0 \le k < d\\) 
    * aantal tabelelementen dat naar dezelfde pagina wijst: \\(2^{d-k}\\)

### Woordenboekoperaties

#### Zoeken

* berekenen van hashwaarde
* pagina vinden via hashtabel (en inlezen)
* sequentieel (of binair) zoeken in sleuteltabel
* zolang hashtabel in geheugen past: slechts 1 schijfoperatie

#### Toevoegen

* analoog, eenvoudig zolang pagina niet vol is
* gemiddeld helft van gegevens in tabel moet opgeschoven worden om volgorde intact te houden
    * verwaarloosbaar naast tijd vereist voor schijfoperatie
* volle pagina splitsen
    * geen boomstructuur
        * hashtabel: kan ingrijpende gevolgen hebben
    * alle hashwaarden in pagina eindigen met dezelfde \\(k\\) bits
        * splitsen door sleutels onder te verdelen volgens waarde van bit \\(k+1\\)
            * als \\(k+i^\text{de}\\) bit 1 is
                * overbrengen naar nieuwe pagina
        * daarna wordt waarde van \\(k\\) één groter
            * zowel in nieuwe als oude pagina
        * hashtabel aanpassen: \\(k\\) wordt groter: \\(k + 1\\)
            * als \\( k + 1 < d \\)
                * helft van wijzers naar oude pagina verwijzen naar nieuwe pagina
            * als \\( k + 1 > d \\)
                * er was één wijzer naar oude pagina
                * \\(k\\) wordt groter dan \\(d\\)
                * \\(d\\) moet ook toenemen
                    * grootte van hashtabel verdubbelt
                * elke index wordt één bit langer
                    * twee nieuwe indices ontstaan
                * tabelelementen bij beide indices moeten naar dezelfde pagina verwijzen als oorspronkelijke index
                * bij gesplitste pagina
                    * ene tabelelement verwijst naar oude pagina
                    * andere tabelelement verwijst naar nieuwe pagina
        * als hashwaarden niet te onderscheiden zijn op grond van bit \\(k+1\\)
            * al hun sleutels komen in dezelfde pagina terecht
            * verdelen op volgende bit, indien nodig met nog meer bits
            * grootte van hashtabel kan telkens verdubbelen
* methode werkt niet als \\(m\\) gelijke hashwaarden in dezelfde pagina terechtkomen
    * ook wanneer hashwaarden in pagina teveel identieke eindbits hebben
    * hashtabel wordt oneindig groot
    * goede hashfunctie kiezen
        * toegekende bits moeten zo *random* mogelijk zijn
* inhoud van hashtabel hangt enkel af van waarde van opgeslagen sleutels
    * niet van volgorde waarin sleutels toegevoegd werden

#### Verwijderen

* lastiger dan toevoegen
* wanneer pagina en haar ooit afgesplitste buur samen minder dan \\(m\\) sleutels bevatten
    * samenvoegen
* pagina verdwijnt
    * hashtabelelement moet naar andere pagina verwijzen
    * \\(k\\) wordt met 1 verminderd
* zodra hashtabel minstens twee verwijzingen naar elke pagina bevat
    * elke \\(k\\) is kleiner dan \\(d\\)
    * kan gehalveerd worden (\\d \\) vermindert met 1
* soms pagina's met wenig elementen tolereren
    * werkt in praktijk vaak goed

### Performantie

* wanneer er \\(n\\) uniform verdeelde sleutels opgeslagen zijn
    * aan te tonen dat verwachtingswaarde van aantal pagina's \\( \frac{n}{m\ln{2}} \approx \frac{1,44n}{m} \\) bedraagt
    * elke pagina is gemiddeld voor \\(69%\\) gevuld
* grootte van hashtabel heeft verwachtingswaarde van \\( 3,92\frac{n}{m}\sqrt[m]{n} \\)
    * voor praktische waarden van \\(m\\): \\(\sqrt[m]{n} \approx 1\\)
      resultaat bedraagt ongeveer \\( \frac{4n}{m} \\)
* als hashtabel te groot
    * hashtabel op analoge manier in twee niveaus' implementeren
        * wortel in geheugen houden
        * indexeren met kleiner aantal eindbits
            * delen van eigenlijke hashtabel in uitwendig gehugen te vinden
        * zoeken vereist extra schijfoperatie
    * maximaal aantal gegevens \\(m\\) in elke pagina vergroten
        * door naast sleutels enkel wijzers naar bijbehorende informatie op te slaan
        * minder pagina's nodig
        * hashtabel wordt kleiner
        * extra schijfoperatie nodig

