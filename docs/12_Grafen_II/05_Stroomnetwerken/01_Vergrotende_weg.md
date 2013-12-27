
* voor elke mogelijke stroomverdeling: overeenkomstig **restnetwerk**:
    * met dezelfde knopen
    * met enkel verbindingen die meer stroom toelaten
* meer stroom van knoop \\(i\\) naar knoop \\(j\\)
    * als capaciteit van verbinding \\((i,j)\\) nog niet volledig gebruikt werd:
        * \\(s(i,j) \lt c(i,j)\\) en/of: er loopt stroom over \\((j,i)\\) die kleiner kan gemaakt worden
* in restnetwerk
    * verbinding \\((i,j)\\) krijgt restcapaciteit: \\( c_r(i,j) = c(i,j) - s(i,j) + s(j,i) \\)
      = positief
    * restcapaciteit: kan groter zijn dan originele capaciteit
        * als \\( s(i,j) \lt s(j,i) \\)
        * als er geen verbinding \\((i,j)\\) is, maar wel \\((j,i)\\)
            * restnetwerk heeft toch verbinding \\((i,j)\\)
    * verbindingen vormen niet noodzakelijk deelverzameling van originele verbindingen
* vergrotende weg = enkelvoudige weg (zonder lus) van *producent* naar *verbruiker*
    * elke verbinding op weg
        * heeft positieve (rest)capaciteit
        * kan nog meer stroom doorlaten
    * tussen producent en verbruiker is via deze weg extra stroom mogelijk
        * gelijk aan kleinste restcapaciteit op die weg
        * stroom in overeenkomstige verbindingen van stroomnetwerk aanpassen
        * stroomtoename van knoop \\(i\\) naar knoop \\(j\\)
            * door toename van \\(s(i,j)\\) of door afname van \\(s(j,i)\\) of combinatie

## performantie afhankelijk van capaciteiten

\\[
 pseudopolynomiaal \Rightarrow
\begin{cases}
    \text{complexiteit van graaf ($n \times m$)} \\\
    \text{grootte van capaciteiten}  \\\
\end{cases}
\\]

### diepte-eerst of breedte-eerst vergrotend pad zoeken

* gehele capaciteiten: maximale netwerkstroom: \\(O(nC)\\)
* bij elke iteratie van `Ford-Fulkerson`: stroomtoename langs gevonden weg geheel
* restnetwerk bepalen \\(O(m)\\)
* totaal: \\(O(nmC)\\)
    * goed voor kleine \\(C\\)

### ~ Dijkstra: vergrotend pad met grootste stroomtoename

* aantal iteraties wordt \\(O(m\lg{C})\\)
* per iteratie: \\(O(m\lg{n})\\)
* totaal: \\(O(m^2\lg{n}\lg{C})\\)

### capacity scaling

* vergrotende weg vinden die stroomtoename van minstens \\(c\\) toelaat: \\(O(m)\\)
* stel: geen vergrotende weg meer te  vinden van minstens \\(c\\)
    * minimale snedecapaciteit van restnetwerk < \\(mc\\)
    * ondergrens halveren
        * stroomtoename zoeken van minstens \\( \frac{c}{2}\\)
* totaal: \\(O(m^2\lg{C})\\)

## performantie onafhankelijk van capaciteiten

* Breedte-eerst zoeken: \\(O(m)\\)
* lengte van vergrotende weg zo kort mogelijk
* maximaal \\(O(nm)\\) iteraties
* totaal: \\( O(nm^2)\\)
    * performantie polynomiaal

## Preflow-push

* nadeel van vorige algoritmen voor vergrotende wegen
    * stroomtoename moet langs volledige weg van \\(p\\) naar \\(v\\) gebeuren
    * in slechtste geval \\(O(n)\\)
* stroomtoename langs weg kan opgedeeld worden in stroomtoename langs zijn verbindingen
* maximale stroom vinden door stroomtoename langs individuele verbindingen
    * *push*-operatie
* stroom is tijdens uitvoering van algoritme niet noodzakelijk conservatieef
    * er kan meer stroom binnenkomen in knoop dan er buiten gaat
        * stroom is tijdelijk *preflow*
* knopen met dergelijk positie overschot/excess zijn actief
    * zolang er actieve knopen zijn voldoet oplossing niet
        * moet conservatief zijn
* basisoperatie van methode
    * actieve knoop selecteren
    * overschot trachten weg te werken via de buren
* als er geen actieve knopen meer zijn
    * stroom voldoet aan vereisten en is maximaal
* implementatie
    * eenvoudige implementatie \\(O(n^2m)\\)
    * FIFO preflow-push active knopen selecteren met wachtrij \\(O(n^3)\\)
    * highest-label preflow-push: actieve knoop verst van \\(v\\) nemen \\(O(n^2\sqrt{m})\\)
    * excess-scaling: stroom van actieve knoop met voldoend groot overschot duwen naar knoop met voldoend klein overschot \\(O(nm + n^2\lg{C})\\)
