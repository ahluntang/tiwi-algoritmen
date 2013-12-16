
## Potentiaal

* vorm van bomen verandert voortdurend
* geamortiseerde efficiëntie \\(O(\lg{n})\\) per operatie via potentiaalfunctie \\( \Phi \\)
* elke mogelijke vorm van boom krijgt reëel getal toegewezen: zijn potentiaal
* operaties op boom kunnen vorm en dus potentiaal wijzigen
    * efficiënte operaties verhogen potentiaal (maar verbruiken minder tijd)
    * inefficiënte operaties verbruiken meer tijd (maar verlagen potentiaal)
        * spreken reserve aan

## Geamortiseerde tijd

* geamortiseerde tijd van individuele operatie wordt gedefinieerd als som van haar werkelijke tijd en toename van potentiaal
* geamortiseerde tijd van \\(i^\text{de}\\) operatie: \\(a^i\\)
    * \\(a^i = t_i + \Phi_i - \Phi_{i-1} \\) 
    * \\(t_i\\): tijd van \\(i^\text{de}\\) operatie
    * \\(\Phi_i \\): potentiaal na \\(i^\text{de}\\) operatie
    * \\(\Phi_{i-1}\\): potentiaal voor \\(i^\text{de}\\) operatie
* geamortiseerde tijd van reeks van \\(m\\) operaties
    * som van individuele geamortiseerde tijden
    \\[
        \sum_{i=1}^{m}{a_i} = \sum_{i=1}^{m}{ t_i + \Phi_i - \Phi_{i-1} }
    \\]
    * meeste potentialen komen met tegengestelde tekens voor:
    \\[
        \sum_{i=1}^{m}{a_i} = \sum_{i=1}^{m}{ t_i + \Phi_m - \Phi_0 } \\\
        \Phi_0 \text{ is beginpotentiaal} \\\
        \Phi_m \text{ is eindpotentiaal}
    \\]

## Keuze potentiaalfunctie en rang van knoop

* potentiaalfunctie zo kiezen dat eindpotentiaal niet kleiner is dan beginpotentiaal
    * totaal geamortiseerde tijd is dan bovengrens voor wekelijke tijd van reeks operaties
* eenvoudigste keuze: geef elke knoop \\(i\\) gewicht \\(s_i\\)
* \\(s_i\\) is gelijk aan aantal knopen in deelboom waarvan het de wortel is
* som van logaritmen van al de gewichten 
  \\[
    \Phi = \sum_{i=1}^n{\lg{s_i}}
  \\]
  * \\( \lg{s_i} = r_i \\): rang van knoop \\(i\\)
* potentiaal van ledige boom: 0
* performantie analyse van topdown en bottom-up is volledig analoog

## Performantie-analyse van bottom-up splay tree

* performantie van splay-operatie op knoop is evenredig met diepte van knoop
    * dus met aantal uitgevoerde (enkelvoudige) rotaties
    * zig: één rotatie
    * zig-zag en zig-zig: twee rotaties
* geamortiseerde tijd voor zoeken naar knoop \\(c\\) gevolgd door splay-operatie op die knoop: \\( O(1+3(r_w-r_c)) \\)
    * \\(r_w\\): rang van wortel in originele boom
    * \\(r_c\\): rang van knoop \\(c\\) in originele boom
    * in uiteindelijke boom: rang van \\(c\\) is gelijk aan rang van \\(w\\) (wortel)

### Gezochte knoop is wortel

* als \\(c\\) wortel is: niet nodig om af te dalen in boom en geen rotaties nodig
* werkelijke tijd \\(O(1)\\)
* potentiaal blijft gelijk

### Afdalen

* diepte van knoop = aantal enkelvoudige rotaties dat splay-operatie zal uitvoeren
* werkelijke tijd om één niveau te dalen en later overeenkomstige (enkelvoudige) rotatie uit te voeren: \\(O(1)\\)
* onbekend aantal zig-zags en/of zig-zigs, eventueel gevolgd door één zig
    * eerst geamortiseerde tijd \\(a\\) voor de drie gevallen apart bepalen
    * dezelfde knoop \\(c\\) stijgt telkens één of twee niveau's
        * resultaten trachten te bekomen waarin enkel rang van c vóór en na de operatie voorkomt
        * geamortiseerde tijd van volledige splay-operatie is som van afzonderlijke tijden
            * rang van \\(c\\) na operatie is gelijk an rang van \\(c\\) vóór volgende operatie
                * meeste terme nin som vallen weg
            * \\(s_i\\) en \\(r_i\\): gewicht en rang van knoop vóór operatie \\(i\\)
            * \\(s_i'\\) en \\(r_i'\\): gewicht en rang van knoop na operatie \\(i\\)
            * vóór operatie: 
                * \\(p\\) is ouder van \\(c\\)
                * \\(g\\) eventuele grootouder

#### Zig

* kan enkel rang van \\(c\\) en \\(p\\) wijzigen
\\( a = 1 + r_c' + r_p' - r_c - r_p \\)
\\( a < 1 + r_c' - r_c\\)

#### Zig-zag

* dubbele rotatie van zig-zag kan enkel rang van \\(c\\), \\(p\\) en \\(g\\) wijzigen
\\( a = 2 + r_c' + r_p' + r_g' - r_c - r_p - r_g \\)
\\( a = 2 + r_p' + r_g' - r_c - r_p \\) want \\(r_c' = r_g \\)
* om \\(r_p' + r_g' \\) kwijt te spelen
    * \\( s_c' > s_p' + s_g' \Rightarrow r_c' > \lg{( s_p' + s_g' )} \\) 
    * logaritmische functie is concaaf, voor positieve \\(a\\) en \\(b\\):  
      \\( \lg{ \left( \frac{a+b}{2} \right) } \ge \frac{ \lg{a} + \lg{b} }{2} \\) 
    * \\( \lg{ \left( \frac{s_p' + s_g'}{2} \right) } \ge \frac{ \lg{s_p'} + \lg{s_g'} }{2}  =  \frac{r_p'+r_g'}{2} \\) 
    * zodat
        * \\( r_c' > 1 + \frac{r_p'+r_g'}{2}  \\) 
        * of \\( r_p' + r_g' < 2r_c' - 2 \\)
    * zodat
        * \\( a < 2r_c' - r_c - r_p \\)
    * omdat \\( r_p > r_c \\)
        * \\( a < 2(r_c'-r_c) \\)

#### Zig-zig

* dubbele rotatie van zig-zig kan enkel rang van \\(c\\), \\(p\\) en \\(g\\) wijzigen
\\( a = 2 + r_c' + r_p' + r_g' - r_c - r_p - r_g \\)
\\( a = 2 + r_p' + r_g' - r_c - r_p \\) want \\(r_c' = r_g \\)
* \\( s_c' > s_g' + s_c \\) en logaritme is concaaf
    * \\( r_c' > \lg{(s_g'+s_c)} \ge 1 + \frac{r_g'- r_c}{2} \\)
        * zodat: \\( r_g' < 2r_c' - r_c - 2 \\)
    * \\( a < r_p' + 2r_c' -2r_c -r_p \\)
* met \\(r_c' > r_p'\\) en \\( r_p > r_c\\)
    * \\( a < 3(r_c' - r_c) \\)


#### Bovengrenzen

* bovengrenzen voor de drie soorten operatie bevateen dezelfde positieve term \\(r_c'-r_c\\) (want \\(r_c' > r_c\\) )
    * maar met verschillende coëfficiënten
* totale geamortiseerde tijd: som van dergelijke tijden
    * kunnen maar vereenvoudigd worden als coëfficiënten gelijk zijn
* we zoeken bovengrenzen, dus: alle coëfficiënten gelijkstellen aan grootste waarde, die van zig-zig
* in som: meeste termen vallen nu weg
    * behalve rang van \\(c\\) vóór en na volledige splay-operatie
* op einde is \\(c\\) wortel, met als rang \\(r_w\\)


## Geamortiseerde tijden van woordenboekoperaties

* geamortiseerde tijden van woordenboekoperaties op (bottom-up) splay tree met \\(n\\) knopen bepalen

### Zoeken

* zoeken gevolgd door splay-operatie  
  \\( O(1+3\lg{n}) \\)

* want 
    * \\(s_w\\) is gelijk aan \\(n\\)
    * \\(s_c\\) voor blad = 1

### Toevoegen

* eerst afdalen net als zoeken, wijzigt met nieuwe knoop enkel rang van knopen \\(p_1, p_2, ...p_k\\) op zoekweg
    * als \\(s_{p_i}\\) gewicht van knoop \\(p_i\\) vóór toevoegen van nieuwe knoop voorstelt en \\(s_{p_i}'\\) gewicht erna, dan is potentiaaltoename  
      \\[
        \lg{ \left( \frac{s_{p_1}'}{s_{p_1}} \right) } + 
        \lg{ \left( \frac{s_{p_2}'}{s_{p_2}} \right) } + 
        ... +
        \lg{ \left( \frac{s_{p_k}'}{s_{p_k}} \right) } =
        \lg{ \left( \frac{s_{p_1}'}{s_{p_1}} \times \frac{s_{p_2}'}{s_{p_2}} \times ... \times \frac{s_{p_k}'}{s_{p_k}} \right) } 
      \\]
    * zodat \\( s_{p_{i-1}} > s_{p_i} + 1 \\) en \\( s_{p_i}' = s_{p_i} + 1 \\) en dus:
        * \\( s_{p_{i-1}} \ge s_{p_i}' \\)
        * zodat potentiaaltoename niet groter is dan  
          \\[
            \lg{\left( \frac{s_{p_1}'}{s_{p_k}} \right)}
            \le
            \lg{(n+1)}
          \\]
* geamortiseerde tijd van toevoegen  
  \\( O(1+4\lg{n}) \\)

### Verwijderen

* knoop fysisch verwijderen doet rang van knopen op zoekweg dalen
* effect is nooit positief

### Reeks van \\(m\\) woordenboekoperaties

\\( O(1+4\lg{n}) \\)

* geamortiseerde tijd voor reeks van \\(m\\) woordenboekoperaties
    * is som van geamortiseerde tijden voor individuele operaties
    * tijd wordt  
      \\[
        O\left( m + 4 \sum_{i=1}^m{\lg{n_i}} \right) \\\
        \text{met }n_i \text{ aantal knopen bij } i^\text{de} \text{operatie}
      \\]  
* als boom max \\(n\\) knopen bevat
    * resultaat is zeker  
      \\(
        O\left( m + 4 m \lg{n} \right) \Rightarrow O\left( m \lg{n} \right)
      \\)




