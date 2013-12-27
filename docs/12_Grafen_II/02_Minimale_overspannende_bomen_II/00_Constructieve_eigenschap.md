
* Minimale Overspannende Boom (MOB)
    * ongerichte gewogen graaf
    * overspannende boom met kleinste gewicht
    * gewicht van boom is som van gewichten van zijn takken
    * niet noodzakelijk uniek
* alle efficiënte algoritmen construeren die *tak per tak*
    * telkens *lokaal optimale* keuze maken
    * bekomt *globaal optimaal* resultaat
    * inhalige/greedy algoritmen
* eigenschap
    * gegeven
        * deelverzameling \\(D\\) van graafverbinding die behoren tot MOB
        * graafverbinding \\(v\\) die niet dot \\(D\\) behoort
    * opdat \\(v\\) samen met verbindingen van \\(D\\) tot MOB zou behoren
        * nodig en voldoende dat er snede \\(S\\) bestaat
            * die geen verbindingen van \\(D\\) bevat
            * waarin \\(v\\) lichtste verbinding is
        * snede verdeelt graafknopen in twee deelverzamelingen
            * bevat alle verbindingen tussen die twee deelverzamelingen
* algoritme van *Prim*
    * snede bestond uit
        * knopen van partiële MOB
        * resterende knopen
    * telkens lichtste verbinding uit snede (en betrokken resterende knoop)
        * aan MOB toevoegen
