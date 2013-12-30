
## Definities

* equivalentierelatie
* deelverzamelingen van equivalente elementen: equivalentieklassen
* doorsnede ledig: disjunct
* **reflexieve eigenschap**
    * elk element behoort tot zijn eigen deelverzameling
* **transitieve eigenschap**
    * als twee equivalente elementen opgegeven worden en als die tot verschillende deelverzamelingen behoren
    * beide deelverzamelingen zijn equivalent
* `find`-operatie
    * vertegenwoordiger vinden op element  van deelverzameling waartoe het behoort
* `union`-operatie
    * samenvoegen van elementen uit deelverzameling

## Efficiënte find

* voor elk element vertegenwoordiger  van deelverzameling waartoe het behoort in tabel bijhouden
* find: \\(O(1)\\)
* union zo efficiënt mogelijk maken
    * tabel moet aangepast worden voor elk element uit 1 van beide verzamelingen
    * tabel overlopen indien elementen niet gekend
    * gelinkte lijst bijhouden voor elke verzameling: met  de elementen
        * in tabel bijhouden met als index vertegenwoordiger van deelverzameling
    * union:
        * samenvoegen lijsten
        * 1 van lijsten gebruiken om vertegenwoordigers aan te passen
* `union-by-size` heuristiek
    * kortste lijst toevoegen aan langste
        * lengte van lijsten bijhouden
    * elk element kan hoogstens \\( \lceil\lg{n}\rceil \\) keer van verzameling veranderen
        * \\( n - 1 \\) union operaties: \\(O(n\lg{n})\\) bewerkingen
    * reeks van \\(m\\) operaties: \\( O(m + n\lg{n}) \\) in slechtste geval


```
/* efficiënte find
 * @param knoopnr
 * @param vertegenwoordigers
 */
int findMethod(int knoopnr, vector<int> & vertegenwoordigers){
    return vertegenwoordigers[knoopnr];
}

/* Union/merge
 * @param verzameling
 * @param lijst1
 * @param lijst2
 * @param vertegenwoordigers
 */
void unionMethod(vector< list<int> > & verzameling,int lijst1, int lijst2, vector<int> & vertegenwoordigers) {
    list<int> * kortste = &verzameling[lijst1];
    list<int> * langste = &verzameling[lijst2];
    if (kortste->size() > langste->size()) {
        swap(kortste, langste);
        int temp = lijst1;
        lijst1 = lijst2;
        lijst2 = temp;
    }
    
    //Vertegenwoordigers aanpassen
    int vertegenwoordiger = vertegenwoordigers[lijst2];
    for (list<int>::const_iterator it = kortste->begin(); it != kortste->end(); it++) {
        vertegenwoordigers[*it]=vertegenwoordiger;
    }
    
    //Voeg lijst 1 bij lijst 2
    langste->merge(*kortste);
}
```
## Efficiënte union

* union-operatie efficiënt maken
    * deelverzamelingen voorstellen als bomen van bos
    * wortel is vertegenwoordiger
    * boomknoop wijst naar ouder (niet omgekeerd)
* union
    * wortel van ene boom wordt kind van wortel van andere
    * \\(O(1)\\)
* find
    * volgen van ouderwijzers van bij knoop tot aan wortel
    * vereiste tijd afhankelijk van lengte van weg
    * hoogte zo klein mogelijk houden
* \\(n-1\\) union operaties
    * kan resulteren in 1 boom die gelinkte lijst is met hoogte \\(n-1\\)
    * find wordt \\(O(n)\\)
    * \\(m\\) operaties: \\(O(mn)\\)
* twee heuristieken
    * `union-by-size`
        * boom met minder elementen samenvoegen met deze met meer elementen
        * hoogte beperken tot \\( \lceil\lg{n}\rceil \\)
        * find wordt \\( O(\lg{n}) \\)
        * \\(m\\) operaties: \\( O(m\lg{n}) \\)
        * gemiddeld \\( O(m) \\)
            * geamortiseerd: \\(O(1)\\)
    * `path compression`
        * optimale find
            * elke knoop wijst rechtstreeks naar wortel van boom
            * maakt union-operatie inefficiënt: alle knopen van één boom moet aangepast worden
        * benaderen
            * bij elke find alle knopen op gevolgde weg naar wortel laten wijzen
            * volgende find op één van die knopen zal optimaal zijn
            * hoe meer find-operaties, hoe kleiner hoogte
* performantie in slechtste geval
    * sterk verbeterd als beide heuristieken gebruikt worden
    * geamortiseerde performantie per operatie \\(O(1)\\) 
