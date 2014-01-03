
* eenvoudiger alternatief voor suffixboom
* ondersteunt dezelfde operaties met dezelfde performantie
    * vereist **minder geheugen**
* is tabel met alfabetisch gerangschikte suffixen van tekst \\(T\\)
* suffixen zelf worden niet opgeslagen
    * tabel bevat enkel beginindices (zoals bladeren van suffixboom)
    * bevat geen informatie over gebruikte alfabet
        * suffixboom wel
        * voordeel voor zeer grote alfabetten

## constructie

* eenvoudig
* efficiënte constructie is complex
    * te rangschikken suffixen bevatten \\( O(n^2) \\) karakters
* klassieke oplossing
    * eerst suffixboom construeren (als er tijdelijk voldoende plaats voor is)
    * nadien gerangschikte suffixen bekomen door suffixboom inorder te overlopen
    * beide deeloperaties: \\(O(n)\\)
* rechtstreekse constructies efficiënter en vereisen minder plaats

### rechtstreekse constructie

* patroon (prefix) \\(P\\) opzoeken in suffixtabel: met binair zoeken
    * \\(O(\lg{n})\\) stringvergelijkingen nodig
    * \\(O(m\lg{n})\\) karaktervergelijkingen
* met extra voorbereidend werk: patroon kan gevonden worden in \\(O(m+\lg{n})\\) karaktervergelijkingen
    * binair zoeken gebruikt  in suffixtabel \\(A\\):
        * linkerindex \\(l\\)
        * rechterindex \\(r\\)
        * middelste index \\(c\\) ( \\(\lfloor \frac{l+r}{2} \rfloor\\) ) 
          ![](/assets/suffixtabel_binairzoeken.png)
            * \\(p_l\\) is lengte van langst gemeenschappelijke prefix \\(P\\) en suffix \\(A[l]\\)
            * \\(p_r\\) is lengte van langst gemeenschappelijke prefix \\(P\\) en suffix \\(A[r]\\)
            * \\(p_{min}\\) is minimum van \\(p_l\\) en \\(p_r\\)
        * \\(P\\) heeft prefix met lengte \\(p_{min}\\) gemeen met alle suffixen tuusen \\(l\\) en \\(r\\)
            * volgende stringvergelijking tussen P en middelste suffix \\(A[c]\\) kan beginnen bij karakter op positie \\(p_{min}+1\\) (in plaats van herbeginnen vooraan)  
              ![](/assets/suffixtabel_pminplus1.png)
        * lengten bepalen vergt weinig extra werk en vermijdt talrijke nutteloze testen
        * gewoonlijk slechtst \\(O(m+\lg{n})\\) karakters worden vergeleken
        * in slechtste geval nog steeds \\(O(m\lg{n})\\)
    * in slechtste geval \\(O(m+\lg{n})\\) halen
        * voorbereidend werk:\\(O(n)\\) bijkomenende gegevens bepalen
        * elke iteratie van binair zoeken test hooguit één karakter van \\(P\\) dat vroeger reeds getest werd
        * \\(P\\) bestaat uit \\(m\\) karakters en er zijn \\(O(\lg{n})\\) iteraties

#### \\(p_l\\) en \\(p_r\\) bepalen

* \\(p_l\\) en \\(p_r\\) bepalen: karakters van \\(P\\) testen tot één positie voorbij maximum van die twee waarden: \\(p_{max}\\)
* volgende test op \\(P\\) gebeurt op dezelfde positie (\\(p_{max}\\))
    * één redudante test per herhaling van binair zoeken
    * elke iteratie gebruikt de lengte 
        * \\(p_{l,c}\\) van langste gemeenschappelijk prefix van suffix \\(A[l]\\) en middelste suffix \\(A[c]\\)
        * of \\(p_{l,r}\\) van langste gemeenschappelijk prefix van middelste suffix \\(A[c]\\) en suffix \\(A[r]\\)  
          ![](/assets/suffixtabel_redundantetest.png)
    * indices die gebruikt worden door binair zoeken hangen enkel af van \\(n\\) (en niet van \\(P\\))  
      voorbeeld: tekst met lengte 13: te indexeren van positie 1 tot en met 13:  
      ![](/assets/suffixtabel_indices.png)
        * waarden kunnen op voorhand bepaald worden (tijdens constructie van suffixtabel)
        * slechts \\(O(n)\\) waarden
            * geheugenvereisten nemen slechts met (kleine) constante factor toe
        * kunnen na constructie ook bepaald worden (in \\(O(n)\\))

#### \\(p_l\\) en \\(p_r\\) gebruiken

* als \\(p_l = p_r \\)
    * \\(p_{min} = p_{max}\\): slechts één redundante test
* als \\(p_l \ne p_r \\): 6 mogelijkheden, verdeeld in twee analoge groepen van 3
    * \\(p_l > p_r \\)
        * \\(p_{l,c} > p_l \\): eerste \\(p_l\\) karakters van \\(P\\) en \\(A[c]\\) gelijk
            * \\(P\\) ligt rechts van \\(l\\): 
                * patroonkarakter op positie \\(p_l+1\\) groter dan karakter van \\(A[l]\\) op dezelfde positie.
                * karakter op positie \\(p_l+1\\) van \\(A[l]\\) is gelijk aan overeenkomstig karakter van \\(A[c]\\)
            * \\(P\\) ligt rechts van \\(c\\)
                *  \\(c\\) wordt nieuwe \\(l\\) (\\(p_l\\) verandert niet)
        * \\(p_{l,c} < p_l \\):
            * karakter op positie \\(p_{l,c}+1\\) van \\(A[c]\\) is groter dan overeenkomstig karakter van \\(A[l]\\)
            * karakter op positie \\(p_{l,c}+1\\) van \\(A[l]\\) is gelijk aan overeenkomstig karakter van \\(P\\)
            * \\(c\\) wordt nieuwe \\(r\\) (\\(p_r\\) wordt \\(p_{l,c}\\))
        * \\(p_{l,c} = p_l \\):
            * eerste \\(p_l\\) karakters van \\(P\\) en \\(A[c]\\) komen reeds overeen
            * verder vergelijken vanaf positie \\(p_l+1 = p_{max}+1\\)
                * om te beslissen of \\(P\\) links of rechts van \\(c\\) ligt
                * enkel eerste test is redundant
                * bij meer testen wordt \\(p_{max}\\) navenant verhoogd
                    * laatst geteste karakter van \\(P\\) heeft steeds positie \\(p_{max}+1\\)

