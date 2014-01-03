
* definieert (eventueel oneindig grote) verzameling strings over alfabet \\(\sum\\)
    * bestaat uit *primitieve reguliere uitdrukkingen* die gecombineerd worden via *operatoren*

## Primitieve uitdrukkingen

* alfabetsymbolen
    * als \\(a\\) symbool uit alfabet is
        * \\(a\\) is reguliere uitdrukking 
            * die verzameling \\(\lbrace a \rbrace\\) definieert
            * \\(\lbrace a \rbrace\\) bevat één triviale string
* ledige string
    * verzameling strings die enkel ledige string \\(\epsilon \\) bevat
    * niet te verwarren met ledige verzameling \\(\emptyset\\)
        * ledige verzameling \\(\emptyset\\) is ook reguliere uitdrukking

## Mogelijke operaties op \\(r\\) en \\(s\\)

* \\(r\\) en \\(s\\) stellen reguliere uitdrukkingen voor

### Unie: \\(r|s\\)

* unie van verzamelingen gedefinieerd door \\(r\\) en \\(s\\)

### Concatenatie: \\(rs\\) of \\(r \cdot s\\)

* verzameling van alle strings opgebouwd door concatenatie van string uit \\(r\\) met string uit \\(s\\)

### Herhaling: \\(r*\\)

* **Kleene** sluiting
* verzameling van alle stringsgevormd door concatenatie van nul of meer strings
    * elk behorend tot \\(r\\)
* \\(r* = r|r|r|r... \\)

### Groepering: \\((r)\\)

* dezelfde verzameling als \\(r\\)
* haakjes om
    * evaluatievolgorde te wijzigen
    * operaties op deeluitdrukking uit te voeren


## Prioriteit

1 haakjes: grootste prioriteit
2 herhaling (soort machtsverheffing)
3 concatenatie (soort vermenigvuldiging)
4 unie (soort optelling)

## Verkorte notatie

* Minstens éénmaal herhalen
    * \\(r+ = rr*\\)
* Optionele uitdrukking
    * \\(r? = r|\epsilon\\)
        * duidt optionele string uit \\(r\\) aan
* Unies van symbolen
    * \\( [abc] \\)
        * \\(a|b|c\\)
    * \\( [a-z] \\)
        * \\(a|b|c|...|z\\)
    * \\( [a-zA-Z0-9] \\)
        * willekeurig alfanumeriek teken

## Automaten

* automatentheorie bestudeert abstracte machines
    * om grenzen van mogelijkheden van computers vast te leggen
    * complexiteit van algoritmen catalogren
    * formele talen herkennen (verzameling van strings)
    * model voor talrijke processen
* formele taal
    * herkennen taal: kunnen beslissen of string tot taal behoort
    * reguliere uitdrukking definieert taal
    * kan herkend worden door eenvoudigste automaat
        * met beperkt aantal toestanden: *finite state automaton*
* twee soorten automaten
    * deterministische
    * niet-deterministische

### Deterministische Automaten: DA

* beperkt (eindig) aantal toestanden
    * abstract model voor schakeling of programma dat zich in één van aantal toestanden kan bevinden
* symbool voor elke toestand
* kan afhankelijk van symbool van toestand veranderen
* DA bestaat uit
    * (eindige) verzameling *invoersymbolen* \\(\sum \\) (invoeralfabet)
    * (eindige) verzameling *toestanden* \\(S\\)
    * *begintoestand* \\(s_0\\) behorend tot \\(S\\)
    * verzameling *eindtoestanden* \\(F\\) 
        * is deelverzameling van \\(S\\)
    * overgangsfunctie \\(m(t,a)\\)
        * geeft nieuwe toestand wanneer automaat in toestand \\(t\\) symbool \\(a\\) ontvangt
            * elke toestand heeft precies één overgang voor elk invoersymbool
* DA kan voorgesteld worden door gerichte gewogen overgangsgraaf (multigraaf)
    * knopen: toestanden
    * verbindingen: overgangen
    * gewicht: overeenkomstig invoersymbool
* multigraaf
    * vanuit knoop meerdere verbindingen mogelijk naar andere
    * er kunnen ook *lusverbindingen* voorkomen
* DA start steeds in begintoestand
    * maakt gepaste toestandsovergangen bij elk ingevoerd symbool
        * komt overeen met weg in overgangsgraaf
    * weg voor elke string van invoersymbolen
* als DA in eindtoestand bevindt
    * string werd herkend door DA
    * gewichten op weg tussen knoop \\(s_0\\) en eindknoop zijn opeenvolgende symbolen van string
* snelle implementatie van overgangsfunctie
    * tweedimensionale overgangstabel
        * rijen: toestanden
        * kolommen: symbolen
* als \\(\sum\\) en aantal toestanden groot zijn
    * tabel kan teveel plaats vereisen
    * lijst zo kort mogelijk houden
        * afsluiten met meest voorkomende overgang als *default*
    * compacter, maar trager

### Niet-deterministische automaten: NA

* verschil met DA
    * vanuit elke toestand meerdere overgangen voor hetzelfde invoersymbool mogelijk
        * of zelfs geen overgang
        * resultaat van overgangsfunctie \\(m(t,a)\\) is geen toestand meer
            * maar verzameling van toestanden (kan leeg zijn)
    * vanuit elke toestand
        * één of meerdere overgangen mogelijk zonder dat er symbool werd ingevoerd
        * met ledige string \\(\epsilon\\) als invoersymbool
* overgangstabel voor NA 
    * moet verzamelingen van toestanden bevatten (in plaats van toestand)
    * moet extra kolom voor invoersymbool \\(\epsilon\\) bevatten
* vertrekkend vanuit begintoestand
    * NA kan in aantal toestanden *tegelijk* bevinden bij inlezen van symbolen
    * bij elk nieuw invoersymbool
        * verzameling van alle toestanden moet bepaald worden die vanuit huidige verzameling toestanden voor dat symbool bereikt kunnen worden
    * met elke string van invoersymbolen
        * meerdere wegen in overgangsgraaf kunnen overeenkomen
* strings herkennen
    * als NA minstens één eindtoestand bevat na inlezen van string
    * als er weg bestaat tussen beginknoop \\(s_0\\) en eindtoestand
        * met opeenvolgende symbolen van string als gewicht van verbindingen (met eventueel \\(\epsilon\\)-verbindingen)
    * er kunnen ook wegen met string overeenkomen die niet tot eindtoestand leiden

## Deelverzamelingsconstructie

* vanuit elke deelverzameling toestanden (waarin NA zich kan bevinden)
    * is er voor elk invoersymbool precies één overgang naar andere deelverzameling
        * eventueel ook ledige verzameling of zichzelf
    * is aantal deelverzamelingen beperkt
        * eindige verzameling heeft eindig aantal deelverzamelingen
* deelverzamelingen gedragen als toestanden van DA
* NA kan met DA gesimuleerd worden
* **transformatie van NA in DA**: *deelverzamelingsconstructie*/*subset construction*
* verzameling van \\(n\\) NA toestanden
    * heeft \\(2^n\\) deelverzamelingen
    * aantal toestanden van DA kan in principe groot uitvallen
    * NA blijkt in praktijk slechts klein aantal van deelverzamelingen te bereiken
        * aantal toestanden van DA is vergelijkbaar met dat van NA
        * er zijn meer overgangen
* constructie maakt gebruik van 2 hulp operaties
    * \\(\epsilon -sluiting(T) \\)
        * deelverzameling van NA toestanden bereikbaar via \\(\epsilon\\)-overgangen vanuit verzameling van NA toestanden \\(T\\)
        * speciaal geval: \\(\epsilon-sluiting(t)\\) als T slechts één NA toestand \\(t\\) bevat
    * \\( m(T,a) \\)
        * overgangsfunctie \\(m(t,a)\\) uitbreiden voor verzameling van NA toestanden \\(T\\) tot \\(m(T,a)\\)
        * resultaat is deelverzameling van alle NA toestanden rechtstreeks bereikbaar vanuit elke toestand \\(t\\) uit \\(T\\), voor invoersymbool \\(a\\)

### \\(\epsilon-sluiting(T)\\) bepalen

* in (gerichte) graaf 
    * zoeken van alle knopen bereikbaar vanuit deelverzameling van knopen
    * stapel gebruiken voor NA toestanden waarvan \\(\epsilon\\)-vergangen nog moeten onderzocht worden

```
Set esluiting; // verzameling voor het resultaat, initieel ledig
Stack st; // voor toestanden met nog te bepalen overgangen

for (elke toestand t uit T) {
    esluiting.voegtoe(t);
    st.push(t);
}

while (!st.ledig()) {
    Toestand t = st.top();
    st.pop();

    for (elke toestand u bereikbaar vanuit t voor epsilon) {
        if (!esluiting.bevat(u)) {
            esluiting.voegtoe(u);
            st.push(u);
        }
    }
}
```

### DA construeren

* verzameling van zijn toestanden \\(D\\) (met begin- en eindtoestanden) en overgangstabel \\(M\\) opstellen
* begintoestand van DA is \\(\epsilon-sluiting(s_0)\\)
    * NA kan zich zowel in begintoestand \\(s_0\\) bevinden als in alle van daaruit voor \\(\epsilon\\) bereikbare toestanden
* om overgang van DA vanuit toestand \\(T\\) voor invoersymbool \\(a\\) te bepalen
    * alle NA toestanden bereikbaar vanuit NA toestanden van \\(T\\) vinden voor \\(a\\)
    * alle van daaruit bereikbare NA toestanden vinden via \\(\epsilon\\)-overgangen
* nieuwe DA toestand is \\(\epsilon-sluiting(m(T,a))\\)
    * eindtoestand van DA bevat tenminste één eindtoestand van NA
* zowel bepaling van \\(\epsilon\\)-sluiting als deelverzamelingsconstructie zijn voorbeelden van een *sluiting*

```
Set D; // verzameling van DA-toestanden, initieel ledig
Stack st; // DA-toestanden met nog te bepalen overgangen
Set T = esluiting(s0); // begintoestand van DA
D.voegtoe(T);
st.push(T);
while (!st.ledig()) {
    T = st.top();
    st.pop();

    for (elk invoersymbool a) {
        Set U = esluiting(m(T,a)); // mogelijks ledig
        M[T,a] = U; // overgangstabel van DA invullen

        if (!D.bevat(U)) {
            D.voegtoe(U); // nieuwe toestand
            st.push(U);
        }
    }
}
```

## Automaten voor reguliere uitdrukkingen: constructie van Thompson

* gebruikt structuur van reguliere uitdrukking als leidraad om NA op te bouwen
* werkt bottom-up
* primitieve NA's definiëren die overeenstemmen met basiselementen van reguliere uitdrukking
* complexe reguliere uitdrukking samenstellen uit eenvoudigere uitdrukkingen met behulp van operatoren
    * mechanisme om NA samen te stellen uit eenvoudigere NA's voor elke operator
* primitieve elementen van reguliere uitdrukking: symbolen uit \\(\sum\\) en \\(\epsilon\\)
    * NA die dergelijk element herkent is triviaal
        * bestaat uit begin- en eindtoestand waartussen één overgang bestaat
        * gemerkt met element
* er worden evenveel NA's aangemaakt als er primitieve elementen zijn in reguliere uitdrukking
* samenstellen van NA's voor elk van vier basisoperatoren
    * andere operatoren zoals positieve sluiting kunnen
        * ofwel via basisoperatoren gesimuleerd worden
        * ofwel aparte constructie op analoge manier definiëren
* stel: \\(r\\) en \\(s\\) zijn reguliere uitdrukkingen waarvoor reeds overeenkomstige NA's \\(R\\) en \\(S\\) construeerd werden
    * NA voor \\(r|s\\)
        * nieuwe begin- en eindtoestand invoeren
        * begintoestand met beide begintoestanden van \\(R\\) en \\(S\\) via \\(\epsilon\\)-overgangen verbinden
        * eindtoestanden van \\(R\\) en \\(S\\) via \\(\epsilon\\)-overgangen met nieuwe eindtoestand verbinden
          ![](/assets/thompson_unie.png)
    * NA voor \\(r \cdot s\\)
        * begintoestand: begintoestand van \\(R\\)
        * eindtoestand: eindtoestand van \\(S\\)
        * eindtoestand van \\(R\\) met begintoestand van \\(S\\) verbinden via \\(\epsilon\\)-overgang
          ![](/assets/thompson_concatenatie.png)
    * NA voor \\(r*\\)
        * nieuwe begin- en eindtoestand invoeren
        * zowel nieuwe begintoestand als eindtoestand van R worden via \\(\epsilon\\)-overgangen verbonden met
            * begintoestand van \\(R\\)
            * nieuwe eindtoestand
        ![](/assets/thompson_kleene.png)
* NA op deze manier geconstrueerd zal alle strings gegenereerd door de reguliere uitdrukking herkennen en geen andere

### Eigenschappen

* NA heeft slechts één eindtoestand
    * er zijn geen interne overgangen naar begintoestand en ook niet vanuit eindtoestand
    * geldt eveneens voor begin- en eindtoestanden van elke intermediaire NA
    * wanneer kleinere automaten samengevoegd worden tot grotere
        * aanhechtingspunten zijn ondubbelzinnig
        * er worden geen onvoorziene wegen gecreëerd
* aantal toestanden van NA is niet groter dan tweemaal aantal elementen in reguliere uitdrukking
    * elke stap in constructie correspondeert met alfabetsymbool of operator
    * introduceert hoogstens twee nieuwe toestanden
* vanuit elke toestand van NA vertrekken niet meer dan twee overgangen
    * ofwel één overgang voor symbool uit \\(\sum\\)
    * ofwel hoogstens twee overgangen voor \\(\epsilon\\)
### Efficiëntie

* constructie \\(O(|r|)\\)
    * \\(|r|\\) : lengte van \\(r\\)
* syntactische ontleding van reguliere uitdrukking \\(r\\)
    * \\(O(|r|)\\)
    * met elk gevonden symbool of operator één construtiestap ( \\(O(1)\\) )
* aantal toestanden van NA \\(O(|r|)\\)

### Herkenner voor abstract model

* DA implementeren met programma of digitale schakeling
    * NA transformeren in DA via deelverzamelingsconstructie
        * implementeren in soft- of hardware
    * eens DA geconstrueerd: herkenning van string \\(s\\) met lengte \\(|s|\\) in \\(\Theta(|s|)\\)
    * zeldzame gevallen waarbij DA exponentieel aantal toestanden heeft
        * vereiste geheugenruimte \\(O(2^{|r|})\\)
* NA rechtstreeks simuleren
    * bepalen van alle toestanden waarin NA zich na elk ingelezen symbool kan bevinden (zoals bij deelverzamelingsconstructie)
    * alle overgangen worden bepaald die de DA voor string zou maken
    * sommige overgangen kunnen meermaals bepaald worden
        * niet-gebruikte overgangen worden nooit bepaald
    * simulatie gebruikt dezelfde functies \\(m(T,a)\\) en \\(\epsilon-sluiting(T)\\) als deelverzamelingsconstructie
    * grootte van deelverzamelingen \\(O(|r|)\\)
    * vanuit elke NA-toestand hoogstens twee overgangen
        * efficiënte voorstelling van overgangstabel vereist slechts \\(O(|r|)\\) plaats
    * herkennen van string \\(s\\)
        \\(|s|\\) overgangen bepalen
    * totale uitvoeringstijd: \\( O(|s| \times |r|) \\)
* Hybride methode
    * eerste herkenner is snel, maar vereist veel voorbereidend werk
    * tweede herkenner is \\(O(|r|)\\) maal trager, maar vraagt minder voorbereidend werk
    * (gedeeltelijke) deelverzamelingsconstructie bij elke string
        * reeds bepaalde overgangen bijhouden in cachegeheugen
        * om later opnieuw te gebruiken
    * slechts deel van DA construeren
        * enkel werkelijk gebruikte overgangen eenmalig bepalen
        * lazy transition evaluation
    * telkens er overgang moet gebeuren
        * zoeken in cache
        * als niet gevonden: overgang bepalen en opslaan in cache
    * plaatsgebruik beperken
        * oude overgangen uit volle cache verwijderen
* alle methoden vertrekken vanuit NA
    * mogelijk om rechtstreeks DA te construeren vanuit reguliere uitdrukking

## Minimalisatie van automaat

### constructie van Thompson

* eenvoudig
* geeft indruk dat er onnodig veel NA toestanden gebruikt worden
    * grote gevolgen voor aantal toestanden van equivalente DA

### DA transformeren in equivalente DA

* elke DA kan getransformeerd worden in equivalente DA
    * die zelfde taal herkent
    * met minimaal aantal toestanden
* equivalente toestanden groeperen
    * elke groep bevat alle toestanden die hetzelfde gedrag vertonen en niet van elkaar te onderscheiden zijn
    * equivalentierelatie
        * groepen equivalente toestanden vormen partitie van verzameling toestanden van DA

#### nagaan of twee toestanden equivalent zijn

* alle mogelijke strings uitproberen
* omgekeerd te werk gaan
    * alle paren toestanden opsporen die niet equivalent zijn (die in verschillende groepen thuishoren)
* stel:
  toestand \\(t\\) gaat voor invoersymbool \\(a\\) over naar toestand \\(v\\)
  toestand \\(u\\) gaat voor diezelfde \\(a\\) over naar toestand \\(w\\)
    * als \\(v\\) en \\(w\\) niet equivalent zijn
        * \\(t\\) en \\(u\\) zijn ook niet equivalent
    * minstens één string \\(s\\) bestaat waarmee \\(v\\) en \\(w\\) onderscheiden kunnen worden
        * zodat \\(t\\) en \\(u\\) met string \\(as\\) te onderscheiden zijn
* voor elk paar toestanden dat voorlopig niet te onderscheiden valt
    * nagaan naar welke paren toestanden ze overgaan, voor elk invoersymbool
    * testen worden herhaald tot er niets meer verandert
    * beginnen met minstens één paar niet-equivalente toestanden
        * elke eindtoestand onderscheidt zich van elke gewone toestand
    * wanneer men geen niet-equivalente toestanden meer kan vinden
        * overige paren zijn equivalent
* \\(O(n^2)\\) paren toestanden
    * elke iteratie vindt minstens één nieuw paar niet-equivalente toestanden
    * \\( O(\left|\sum\right| \times n^4) \\)
* betere implementatie
    * voor elk paar toestanden gelinkte lijst opstellen met paren toestanden die ervan afhangen
    * als paar niet-equivalent bevonden wordt
        * geldt meteen voor alle paren op lijst
    * lijst eenmalig opstellen \\( O(\left|\sum\right| \times n^2) \\)
    * elke lijst nadien slechts eenmaal overlopen wanneer overeenkomstig paar toestanden niet-equivalent blijkt \\( O(\left|\sum\right| \times n^2) \\)
    * totale lengte van alle lijsten \\( O(\left|\sum\right| \times n^2) \\)
    * elk paar toestanden kan tot hoogstens \\(\left|\sum\right|\\) lijsten behoren
    * methode wordt \\( O(\left|\sum\right| \times n^2) \\)
* nog sneller
    * partitie vinden door iteratieve verfijning
    * telkens nagaan of toestanden van eenzelfde groep nog steeds equivalent zijn
        * indien niet: groep splitsen
    * proces stopt wanner geen groep meer opgesplitst kan worden
    * alle toestanden in dezelfde groep zijn equivalent
    * initieel slechts twee groepen
        * groep met alle eindtoestanden
        * groep met de rest
    * bij goede implementatie \\( O(\left|\sum\right| \times n\lg{n}) \\)
        * volgorde is cruciaal
    * eens partitie gekend is: gereduceerde DA opstellen
        * in elke groep een toestand als vertegenwoordiger kiezen
        * vertegenwoordigers worden toestanden van nieuwe DA
        * begintoestand van nieuwe DA is vertegenwoordiger van groep die begintoestand van originele DA bevat
        * elke groep van partitie bestaat volledig uit eindtoestanden van originele DA
            * of bevat geen enkele eindtoestand
        * eindtoestanden van nieuwe DA zijn vertegenwoordigers van groepen met originele eindtoestanden
    * overgangen tussen toestanden moeten overgangen tussen groepen worden
        * tussen hun vertegenwoordigers
    * alle toestanden uit nieuwe DA verwijderen die onbereikbaar zijn vanuit begintoestand

