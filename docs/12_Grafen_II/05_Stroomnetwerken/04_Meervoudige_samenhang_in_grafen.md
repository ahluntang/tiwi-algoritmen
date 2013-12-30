
* \\(k\\)-connected: \\(k\\)-voudig samenhangend
    * tussen elk paar knopen van graaf
        * \\(k\\) onafhankelijke wegen zonder gemeenschappelijke knopen en verbindingen
* \\(k\\)-edge-connected: \\(k\\)-voudig lijnsamenhangend
    * tussen elk paar knopen van graaf
        * \\(k\\) onafhankelijke wegen zonder gemeenschappelijke verbindingen
* enkel-, dubbel-, drievoudig samenhangend: via diepte-eerst
* meervoudig: via `stroomnetwerken`
    * `max-flow min-cut` stelling

## Meervoudige samenhang vinden

* eenvoudige vormen: via diepte-eerst zoeken
* meervoudige vormen: stroomnetwerken
    * nauw verband tussen maximale netwerkstromen en minimale snede
        * als men maximale netwerkstroom vindt, heeft men meteen minimale snede
    * als alle capaciteiten één zijn: capaciteit van snede \\((P,V)\\) gelijk aan aantal verbindingen van knopen in \\(P\\) naar knopen in \\(V\\)
    * elke vergrotende weg laat stroomtoename van één toe
        * weg van \\(p\\) naar \\(v\\) in stroomnetwerk
        * gebruikt één voorwaartse verbinding over minimale snede
    * maximale netwerkstroom loopt over (gerichte) wegen zonder gemeenschappelijke verbindingen
    * aantal onafhankelijke wegen
      = minimale snedecapaciteit
      = maximale netwerkstroom \\(f\\)
    * kan gevonden worden in \\(O(nm)\\) (als capaciteit \\(C = 1\\))

## Fundamentele eigenschap van samenhang in graaf: stelling van Menger

* in 4 versies
    * zowel voor gerichte als ongerichte grafen
    * zowel voor meervoudige samenhang als meervoudige lijnsamenhang
* voor meervoudig lijnsamenhangende gerichte graaf
    * minimum aantal verbindingen dat moet verwijderd worden om knoop \\(v\\) van gerichte graaf onbereikbaar te maken vanuit andere knoop \\(p\\)
      = aantal maximaal lijnonafhankelijke wegen (zonder gemeenschappelijke verbindingen) van \\(p\\) naar \\(v\\)
      \\(v\\) mag geen buur zijn van \\(p\\)
* stelling volgt uit eigenschappen van stroomnetwerk met eenheidscapaciteiten
    * beide aantallen zijn gelijk aan capaciteit van minimale snede tussen \\(p\\) en \\(v\\)
        * maximale stroom loopt over maximaal aantal lijnonafhankelijke wegen van \\(p\\) naar \\(v\\)
            * aantal is gelijk aan maximale stroom en ook gelijk aan capaciteit van minimale snede
        * minimale verzameling verbindingen \\(M\\) die \\(v\\) onberekbaar maakt vanuit \\(p\\) vormt snede \\((P,V)\\)
            * definieer
                * \\(P\\) als verzameling van alle knopen bereikbaar vanuit \\(p\\) via wegen die geen verbinding uit \\(M\\) bevatten (dus ook \\(p\\))
                * \\(V\\) als verzameling van alle andere knopen (ook \\(v\\))
            * alle verbindingen van snede behoren tot \\(M\\)
            * \\(M\\) kan geen andere verbindingen bevatten, want \\(M\\) is minimaal
            * \\(M\\) is minimale snede, capaciteit is gelijk aan aantal verbindingen in \\(M\\)
* verband tussen
    * onafhankelijke wegen zonder gemeenschappelijke knopen
    * vergrotende wegen
* alle knopen ontdubbelen   
    * nieuwe verbinding van capaciteit één tussen elke knoop en dubbelganger
    * inkomende verbindingen blijven bij originele knoop
    * uitgaande verbindingen bij dubbelganger
* slechts één vergrotende weg kan gebruikmaken van elke knoop
* knopen vinden die \\(v\\) onbereikbaar maken vanuit \\(p\\) wanneer men ze wegneemt
    * enkel eenheidscapaciteiten toewijzen aan verbindingen tussen knopen en dubbelgangers
    * capaciteit van alle andere verbindingen onbeperkt groot maken
* ongerichte grafen naar stroomnetwerk omvormen
    * ongerichte verbinding vervangen door twee tegengesteld gerichte verbindingen
    * beide met eenheidscapaciteit
    * elke collectie onafhankelijke wegen in ongerichte graaf komt zeker overeen met collectie onafhankelijke gerichte wegen in gerichte graaf
        * ook omgekeerd
* als originele graaf \\(n\\) knopen en \\(m\\) verbindingen had
    * getransformeerde graaf: \\(O(n)\\) knopen en \\(O(m)\\) verbindingen

### Stelling van Whitney

* eigenschap toepassen op elk paar knopen van graaf
    * graaf (al dan niet gericht) is \\(k\\)-voudig samenhangend (\\(k\\)-voudig lijnsamenhangend)
      als er tenminste \\(k\\) knopen (verbindingen) moeten verwijderd worden om hem te doen uiteenvallen
* maximaal stroomprobleem oplossen voor elk knopenpaar
    * minimum van die oplossingen nemen
    * \\(\Theta(n^2)\\) knopenparen: performantie \\(\Theta(n^3m)\\)
* \\(\Theta(n)\\) stroomproblemen volstaan
    * stel dat \\(r\\) en \\(s\\) producent en verbruiker zijn van stroomnetwerk met kleinste minimale snede \\(R,S\\) onder alle \\(\Theta(n^2)\\) knopenparen
    * hetzelfde resultaat kan gevonden worden door stroomnetwerk met willekeurige knoop \\(x\\) uit \\(R\\) als producent en willekeurige knoop \\(y\\) uit \\(S\\) als verbruiker
        * \\((R,S)\\) was bij veronderstelling kleinste minimale snede
    * probleem \\((R,S)\\) niet gekend, dus ook \\(x\\) en \\(y\\) niet
        * alle knopen cyclisch in willekeurige volgorde zetten: \\( x_1, x_2, ..., x_n \\)
        * altijd twee opeenvolgende knopen \\(x_i\\) en \\(x_{i+1}\\) zodat \\(x_i\\) in \\(R\\) ligt en \\(x_{i+1}\\) in \\(S\\)
    * slechts \\(n\\) stroomnetwerken oplossen
        * voor alle paren opeenvolgende knopen
        * minimum van alle oplossingen bijhouden


