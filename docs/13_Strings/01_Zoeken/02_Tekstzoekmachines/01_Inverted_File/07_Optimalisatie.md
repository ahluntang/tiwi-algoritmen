\\[ 
    S_{q,d} = \sum_{t}{ \frac{w_{d,t}.w_{q,t}}{W_d.W_q} } 
\\]

## Frequency-Ordered Inverted Lists

* Lijsten sorteren op \\(f_d\\) in plaats van documentnummer
    * zodat de meest belangrijke documenten eerst behandeld worden
    * hoe kleiner \\(w_{d,t}\\), hoe minder van belang
* Oorspronkelijke lijsten gesorteerd op documentnummer
    * \\( \langle 12,2 \rangle \\) \\( \langle 17,2 \rangle \\) \\( \langle 19,1 \rangle \\) \\( \langle 31,1 \rangle \\) \\( \langle 40,6 \rangle \\) \\( \langle 78,1 \rangle \\) \\( \langle 101,3 \rangle \\) \\( \langle 106,1 \rangle \\)
* Sorteren op \\(f_t\\) (aantal termen)
    * \\( \langle 40,6 \rangle \\) \\( \langle 101,3 \rangle \\) \\( \langle 12,2 \rangle \\) \\( \langle 17,2 \rangle \\) \\( \langle 29,1 \rangle \\) \\( \langle 32,1 \rangle \\) \\( \langle 78,1 \rangle \\) \\( \langle 106,1 \rangle \\)
* Documenten waarbij term evenveel voorkomen: prefix-component met aantal keer, gevolgd door aantal documenten en opsomming van documentnummers
    * \\( \langle 6:1:40 \rangle \\) \\( \langle 3:1:101 \rangle \\) \\( \langle 2:2:12,17 \rangle \\) \\( \langle 1:4:29,32,78,106 \rangle \\)
* Compressie: gaps tussen documentnummers gebruiken in plaats van documentnummers
    * \\( \langle 6:1:40 \rangle \\) \\( \langle 3:1:101 \rangle \\) \\( \langle 2:2:12,5 \rangle \\) \\( \langle 1:4:29,3,46,28 \rangle \\)
* Maakt het mogelijk om enkel stukjes van lijsten op te halen
    * niet meer voor elke term volledige lijst ophalen
    * stoppen als bijdrage niet groot genoeg wordt
* Nadeel
    * als er nieuw document toekomt
    * updaten van systeem wat ingewikkelder (in plaats van achteraan lijst toevoegen)


## Impact-Ordered Inverted Lists

* nadat alle termen overlopen zijn: er moet gedeeld worden door \\(W_d\\)
* beter om te sorteren op \\( \frac{w_{d,t}}{W_d}\\) in plaats van \\(w_{d,t}\\)
* complicatie
    * \\(f_{d,t}\\) zijn gehele getallen
    * \\( \frac{w_{d,t}}{W_d}\\) kunnen reële getallen opleveren: moeilijker om gelijke getallen te krijgen
        * bij gelijke frequentie kon je meerdere documenten opslaan
    * oplossing: minder precisie gebruiken (benaderend systeem)
        * gehele getallen gebruiken
* Opnieuw enkel stukjes van lijsten ophalen
    * eerste blok van elke inverted list die we nodig hebben
    * behandel die met hoogste impact
        * op einde volgend blok ophalen van die lijst
    * volgend te behandelen blok: die met hoogste impact
    * er kan dus gesprongen worden van ene inverted list naar andere inverted list.
    
