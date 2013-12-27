
*overspannende boom met kleinste gewicht ( in ongerichte gewogen graaf )*

## Kruskal

* MOB opbouwen uit afzonderlijke deelbomen
    * geleidelijk verbonden tot er maar 1 boom overblijft
    * oorspronkelijke (triviale) deelbomen zijn knopen van graaf
    * lichtste graafverbinding die 2 deelbomen verbindt:  
    lichtste verbinding uit snede (gevormd door knopen van deelbomen en alle andere knopen)
        * snede bevat geen enkele tak van deelbomen.
        * verbinding behoort tot MOB: mag toegevoegd worden.
    * graafverbinding volgens stijgend gewicht onderzoeken: rangschikken of via `priority_queue`
* hoe weten of eindknopen tot verschillende deelbomen behoren?
    * elk stuk is deelverzameling van verzameling knopen
    * stukken hebben geen gemeenschappelijke knopen
    * zijn disjuncte deelverzamelingen: delen samen verzameling knopen op
    * elke nieuwe verbinding duidt 2 equivalente knopen aan
        * nagaan of ze reeds tot hetzelfde stuk behoren
        * anders samenvoegen
        * twee `finds`, eventueel gevolgd door 1 `union`
    * stoppen nadat er \\( n-1 \\) geschikte verbindingen toegevoegd werden

### Efficiëntie

* Opbouw `heap`: \\( O(n) \\)
* Slechtste geval
    * elke verbinding uit `heap` halen: max \\( O(m\lg(n)) \\)
    * elke verbinding: 2 `find` operaties en hoogstens 1 `union`
        * samen \\( O(m+n) \\)
    * totaal: \\( O(n + m + m\lg(m)) \\)
        * \\( O(m\lg(m)) \\) ( want \\( n = O(m) \\))
* In praktijk komen niet alle verbindingen aan bod.

## Clustering

* collecties objecten indelen in clusters van gelijkaardige objecten.
* criterium: afstand tussen objecten, grotere afstand = minder gelijkenis
* objecten in dezelfde cluster liggen *dicht* bij elkaar.
* objecten in verschillende clusters liggen *ver* van elkaar.
* eenvoudige methode: via `MOB`
* verzameling van \\( n \\) objecten: \\( S=\{p_1, p_2, ..., p_n\} \\)
    * verdelen in \\( k \\) clusters: \\( C=\{C_1, C_2, ..., C_k\} \\)
    * afstandsfunctie `d()`, als \\( p_i \\) en \\( p_j \\) objecten zijn:
        * \\( d(p_i,p_i) = 0 \\)
        * \\( d(p_i,p_j) > 0 \\) als \\( i \neq j \\)
        * \\( d(p_i,p_j) = d(p_j,p_i) \\)
    * *spreiding/spacing* van cluster: kleinste afstand tussen 2 objecten uit verschillende clusters.
* aantal clusteringen groeit exponentieel met \\( n \\) en \\( k \\).

### Constructie

*Construeren van ongerichte graaf, met objecten als knopen.*

* clusters = samenhangende componenten
* dichtbijgelegen objecten: in dezelfde cluster
    * vermijden dat ze in andere cluster terechtkomen
* verbinding liggen tussen paren objecten
    * volgens stijgende onderlinge afstand
    zonder lussen: verzameling wortelloze bomen
* elk toegevoegde verbinding voegt 2 clusters samen
    * `single link clustering`
* \\( \Rightarrow \\) `Kruskal`: stoppen wanneer er \\( k \\) samenhangende componenten zijn
    * laatste \\( k-1 \\) verbindingen worden niet toegevoegd

### Is spreiding van clustering maximaal?

* spreiding = lengte \\( d^* \\) van verbinding die algoritme van Kruskal zou toegevoegd hebben indien we die niet onderbroken hadden.
* bestaat er andere clustering \\( C'=\{C_1', C_2', ..., C_k'\} \\) met grotere spriding?
* \\( C' \neq C \\) :
    * cluster van \\( C \\) moet 2 elementen bevatten die tot verschillende clusters van \\( C' \\)
    * beide elementen behoren tot dezelfde cluster
        * verbonden via weg waarvan alle verbindingen door Kruskal tgoegevoegd werden.
        * gewicht van al die verbindingen hoogstens \\( d^* \\).
* in \\( C' \\) : beide elementen behoren tot verschillende clusters
    * weg tussen beide moet twee opeenvolgende knopen \\( p \\) en \\( p' \\) bevatten die ook tot verschillende clusters van \\( C' \\) behoren.
    * \\( \Rightarrow d(p,p') \le d^* \\)
        * = afstand tussen twee knopen uit verschillende clusters van \\( C' \\) niet groter dan \\( d^* \\).

### Implementatie

```
// Kruskal en clustering
// We stellen een MOB op
// Als we de laatste k verbindingen van de MOB niet toevoegen zullen we k clusters hebben.
// Kruskal werkt door het samenvoegen van bomen.
// Dat samenvoegen gebeurt door telkens de verbinding met het kleinste gewicht tussen 2 bomen te kiezen.
unsigned int k = 200;
unsigned int merges = 0;
while (!verbindingen.empty() && merges < (graaf.aantalKnopen() - k)) {
    verbinding v = verbindingen.top();
    
    // Zoek de vertegenwoordiger van de uiteinden van deze verbinding.
    int vertegenw1 = findMethod(v.van, vertegenwoordiger);
    int vertegenw2 = findMethod(v.naar, vertegenwoordiger);
    
    // Als de vertegenwoordigers verschillen, dan zijn dit 2 verschillende bomen.
    if (vertegenw1 != vertegenw2) {
        // We doen een union operatie op deze 2 bomen.
        // merge=union omdat union een reserved keyword is.
        unionMethod(verzameling, vertegenw1, vertegenw2, vertegenwoordiger);
        merges++;
    }
    
    // Deze verbinding hebben we verder niet nodig.
    verbindingen.pop();
}
```
