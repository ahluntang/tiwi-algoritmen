
* voor elke mogelijke stroomverdeling: overeenkomstig **restnetwerk**:
    * met dezelfde knopen
    * met enkel verbindingen die meer stroom toelaten
* meer stroom van knoop \\(i\\) naar knoop \\(j\\)
    * als capaciteit van verbinding \\((i,j)\\) nog niet volledig gebruikt werd:
        * \\(s(i,j) \lt c(i,j)\\) en/of: er loopt stroom over \\((j,i)\\) die kleiner kan gemaakt worden
* in restnetwerk
    * verbinding \\((i,j)\\) krijgt restcapaciteit: \\( c_r(i,j) = c(i,j) - s(i,j) + s(j,i) \\)
        * = positief
    * restcapaciteit: kan groter zijn dan originele capaciteit
        * als \\( s(i,j) \lt s(j,i) \\)
        * als er geen verbinding \\((i,j)\\) is, maar wel \\((j,i)\\)
            * restnetwerk heeft toch verbinding \\((i,j)\\)
    * verbindingen vormen niet noodzakelijkdeelverzameling van originele verbindingen
* vergortende weg = enkelvoudige weg (zonder lus) van *producent* naar *verbruiker*

## performantie afhankelijk van capaciteiten

\\[
 pseudopolynomiaal \Rightarrow
\begin{cases}
\text{complexiteit van graaf ($n \times m$)} \\
\text{grootte van capaciteiten}  \\
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
