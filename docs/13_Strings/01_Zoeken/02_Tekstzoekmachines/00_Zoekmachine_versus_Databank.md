## 4 grote verschillen tussen zoekmachine en databank

* **query**
    * databank: kan zo ingewikkeld zijn als men wilt maken
    * zoekmachine: *bag of words* (hoogstens een zin)
* resultaten
    * databank

|   |             |  Databank                                                       | Zoekmachine                                                                        |
|---|-------------|-----------------------------------------------------------------|------------------------------------------------------------------------------------|
| 1 |  **Query**  | kan zo ingewikkeld zijn als je wilt                             | *bag of words* (hoogstens een zin)                                                 |
| 2 |  Resultaten | document is pas **match** als het precies overeenkomt met query | statistische heuristieken (soms krijg je documenten waar zoekterm niet in voorkomt) |
| 3 |  Filtering  | alle documenten die voldoen worden teruggegeven                 | niet alles wordt gegeven (niet te doen met miljoenen documenten)                   |
| 4 |  Opslag     | databank slaat enkel documenten op                              | bevat ook nog metadata over documenten                                             |

* match: als het relevant zou zijn voor de aanvrager
    * relevantie is niet exact (in tegenstelling tot een match bij SQL query)

## Zoekmachine maken 

* effectiviteit van systeem
    * **precision**: percentage relevante documenten dat je terugkrijgt
    * **recall**: van de documenten die je krijgt, hoeveel zijn er voor de gebruiker relevant?

### Vereisten en/of problemen bij het maken van zoekmachines

* queries juist interpreteren
* eigenschappen van tekst gebruiken
    * woorden die dicht bij elkaar staan zijn relevanter
* hyperlinks (relevanter)
* snelheid queries
* schaalbaarheid en minimaal gebruik van resources
* veranderingen bijwerken
* logische operatoren ondersteunen
* zoeken naar zinnen

### Termen uit tekst halen

* hoe tekst parsen en termen eruithalen?
* **casefold**: rekening houden met hoofdletters of kleine letters?
* **stem**: varianten van woorden (meervoud, verkleinwoord, ...)
* **stopping**: lidwoorden en stopwoorden negeren.

### Hoe bepalen of document relevant is voor query?

* query = *bag of words*
* statistische gegevens gebruiken
    * \\(f_{d,t}\\): aantal keer dat term \\(t\\) voorkomt in document \\(d\\)
    * \\(f_{q,t}\\): aantal keer dat term \\(t\\) voorkomt in query \\(q\\)
    * \\(f_t\\): aantal documenten dat term \\(t\\) bevat
    * \\(F_t\\): aantal keer term voorkomt in volledige collectie (in alle documenten)
    * \\(N\\): aantal documenten
    * \\(n\\): aantal toegestane termen dat er op gezocht kan worden
* 3 observaties (*monotonicity*)
    * minder gewicht aan termen die voorkomen in veel documenten
    * meer gewicht voor documenten als een term veel in voorkomt
    * minder gewicht als document veel algemene termen heeft

#### Meten van relevantie document voor query

* via vector: stelt query of document voor in \\(n\\)-dimensionale ruimte
    * vector bevat \\(n\\) gegevens/elementen/coördinaten
    ![vector q en vector d](/assets/tekstzoekmachines_vectoren.png)
    * voor elk document is er een vector
* relevantie document voor query kan gemeten worden door de hoek met de query-vector te berekenen
    * document met vector dat kleinste hoek maakt met query-vector is het meest relevant  
    ![vector q en vectoren d](/assets/tekstzoekmachines_vector_hoek.png)
* hoek berekenen
    * wiskunde: via inwendig product (cosinus)
      \\[ \vec{a}.\vec{b} = \cos\alpha = \frac{x_ax_b + y_ay_b}{|a|.|b|} \\]
    * in n-dimensionale ruimte: *similarity* tussen q en d: 
      \\[ S_{q,d} = \sum_{t}{ \frac{w_{d,t}.w_{q,t}}{W_d.W_q} } \\]
        * \\(w_{d,t}\\) : elementen van vector d (TF: term frequency)  
          \\[ w_{d,t} = 1 + ln(f_{d,t}) \\]
        * \\(w_{q,t}\\) : elementen van vector q (IDF: inverse document frequenty)
          \\[ w_{q,t} = \ln\left({1+ \frac{1}{ \frac{f_t}{N} } }\right) \\]
            * termen die minder frequent zijn worden belangrijker
        * \\(W_{d}\\) : lengte van vector d (wiskunde: \\(|a| = \sqrt{ x_a^2 + y_a^2 } \\))  
          \\[ W_d = \sqrt{ \sum_{t}{w_{d,t}^2} } \\]
        * \\(W_{q}\\) : lengte van vector q  
          \\[ W_q = \sqrt{ \sum_{t}{w_{q,t}^2} } \\]
* relevantie berekenen
    * eens je formules hebt: IDF berekenen voor query
    * door alle documenten lopen
        * TF berekenen of ophalen
        * \\(S_{q,d}\\) berekenen

Nadeel: zeer inefficiënt

* oplossing: inverted file 

