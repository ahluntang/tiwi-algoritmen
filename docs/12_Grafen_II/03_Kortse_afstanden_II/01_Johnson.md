

## Kortste afstanden tussen alle knopenparen

* `Floyd-Warshall`: \\( \Theta(n^3) \\) voor dichte grafen
* `Johnson`: \\( O(nm\lg(n)) \\) voor ijle grafen

* `Johnson` maakt gebruik van `Bellman-Ford` en `Dijkstra`
* om `Dijkstra` vanuit elke knoop te gebruiken
    * alle verbindingen krijgen nieuw (positief) gewicht.
* graaf uitbreiden
    * nieuwe knoop \\(s\\)
    * knoop \\(s\\) krijgt verbindingen naar alle andere knopen
        * met gewicht \\(0\\).
* als oorspronkelijke graaf geen negatieve lussen had
    * geldt eveneens voor nieuwe graaf (knoop \\(s\\) heeft enkel **uitgaande** verbindingen)
* vanuit \\(s\\) kortste afstand \\(d_i\\) bepalen tot elke knoop \\(i\\)
    *  via `Bellman-Ford`
* afstanden gebruiken om nieuwe gewichten te bepalen
    * oorspronkelijk gewicht = \\(g_{ij}\\) van verbinding \\((i,j)\\)
    * nieuwe gewicht = \\( \hat{g_{ij}} = g_{ij} + d_i - d_j \\)
        * \\(d_i\\) en \\(d_j\\) zijn kortste afstanden: \\(d_j \le d_i + g_{ij}\\)
            * \\(\hat{g_{ij}} \\) nooit negatief
* `Dijkstra` gebruiken om correcte kortste wegen te weten
* kortste afstanden: opnieuw originele gewichten gebruiken en toepassen op reeds gevonden kortste wegen

### Zijn kortste wegen met nieuwe gewichten dezelfde als de wegen met originele gewicht?

* stel: 
    * \\(w_{ij}\\) = origineel gewicht van kortste weg tussen knopen \\(i\\) en \\(j\\)
    * \\(\hat{w_{ij}} \\) = nieuw gewicht van diezelfde weg
* als: met nieuwe gewichten kortere weg tussen \\(i\\) en \\(j\\) zou zijn
    * met (nieuw) gewicht \\(\hat{w_{ij}}' \\) en origineel gewicht \\(w_{ij}' \\)
        * dan zou \\(w_{ij}' \lt \hat{w_{ij}}' \\) zijn
    * zodat \\( w_{ij}' +d_i - d_j \lt w_{ij} + d_i - d_j \\) en dus \\( w_{ij}' \lt w_{ij} \\)
        * eerste weg was toch niet kortste

## Performantie

* graaf uitbreiden: \\( \Theta(n) \\)
* `Bellman-Ford`: \\( O(nm) \\)
* gewichten aanpassen: \\( \Theta(m) \\)
* n keer `Dijkstra`: \\( O( n(n+m)\lg(n) ) \\) (belangrijkste term)
* totaal:  \\( O( nm\lg(n) ) \\)
