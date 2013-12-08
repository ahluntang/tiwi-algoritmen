
* sluiting = algemene methode om 1 of meerdere verzamelingen op te bouwen
    * herhaaldelijk één of meerdere regels toepassen
        > als verzameling deze gegevens bevat,  
        > dan moet ze ook de volgende gegevens bevatten
    * tot er niets meer aan verzameling toegevoegd kan worden  
    = `fixed-point`-bepaling: verdere toepassing van regels verandert niets meer
* regels bepalen
    * wat er in verzameling moet komen
    * niet wat er niet in mag
* bijkomende regel
    * er mag niets anders in dan wat regels vermelden  
    = `least fixed-point` bepaling
* speciaal geval: `transitieve sluiting`
    * regels van vorm
        > als \\((a,b)\\) en \\((b,c)\\) aanwezig zijn,  
        > dan moet ook \\((a,c)\\) aanwezig zijn.
* `transitieve sluiting` van gerichte graaf  
= nieuwe gerichte graaf
    * met dezelfde knopen
    * verbinding van knoop \\(i\\) naar knoop \\(j\\) als er een weg bestaat van \\(i\\) naar \\(j\\) in oorspronkelijke graaf.

## Opbouwen transitieve sluiting

### diepte-eerst of breedte-eerst zoeken

* alle knopen opsporen die vanuit startknoop bereikbaar zijn
* herhalen met elke knoop als startknoop
* ijle grafen: \\( \Theta( n(n+m) ) \\)
* dichte grafen: \\( O(n^3) \\)

### componentengraaf

* als graaf dicht is
* bevat gering aantal sterk samenhangende componenten (alle knopen onderling bereikbaar)
    * in \\( \Theta(n+m) \\) te bepalen
* componentengraaf is veel kleiner dan originele graaf
* transitieve sluiting bepalen van (lusloze) componentengraaf
    * als component \\(j\\) bereikbaar is vanuit component \\(i\\)
        * alle knopen uit component \\(j\\) zijn bereikbaar door alle knopen uit component \\(i\\)

### Warshall

* dichte grafen
* analoog met `Floyd-Warshall`
* reeks opeenvolgende \\(n \times n\\) matrices: \\( T^{(0)}, T^{(1)}, ... T^{(n)} \\)
    * matrices bevatten logische waarden
* element \\( t_{ij}^{(k)} \\) duidt aan of er weg bestaat tussen \\(i\\) en \\(j\\)  
met als "mogelijke" intermediaire knopen \\( 1, 2, ..., k \\)
* verbinding \\((i,j)\\) behoort tot transitieve sluiting als \\( t_{ij}^{(n)} \\) waar is
    * \\( T = T^{(n)} \\) is gezochte burenmatrix
* eerste matrix bepalen:
\\[
 t_{ij}^{(0)} =
\begin{cases}
false,  & \text{als $i \ne j$ en $g_{ij} = \infty$} \\
true, & \text{als $i=j$ of $g_{ij} < \infty$}  \\
\end{cases}
\\]
* volgende matrices (voor \\(1 \le k \le n\\) ):
\\[
t_{ij}^{(k)} = t_{ij}^{(k-1)} \lor ( t_{ik}^{(k-1)} \land t_{kj}^{(k-1)} ) 
\\]
* berekening kan ter plaatse: vereist slechts 1 matrix
* efficiëntie: \\( \Theta(n^3) \\)
    * kleinere verborgen constante dan Floyd-Warshall
    * logische waarden vereisen minder plaats dan getallen
