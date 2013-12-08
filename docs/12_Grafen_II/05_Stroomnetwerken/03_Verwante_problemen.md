
## meerdere producenten en verbruikers

* gezamenlijke nettostroom van alle producenten maximaliseren
* fictieve **totaalproducent** en **totaalverbruiker** invoeren
* vanuit **totaalproducent**
    * verbindingen met onbeperkte capaciteit naar alle producenten
* vanuit alle verbruikers
    * verbindingen met onbeperkte capaciteit naar **totaalverbruiker**

## capaciteitsbeperkingen in netwerkknopen

* elke knoop **ontdubbelen**
* tussen **originele** knoop en **dubbelganger**
    * verbinding met capaciteit van knoop
* oorspronkelijke uitgaande verbinding van **originele** knoop
    * wordt uitgaande verbinding bij **dubbelganger**

## ongericht stroomnetwerk

* stroom inverbinding kan in ene of andere richting lopen
    * mag capaciteit niet overschrijden
* **elke** verbinding vervangen door een **paar gerichte** verbindingen
    * één in elke richting
    * elk krijgt originele capaciteit

## ondergrenzen (naast bovengrenzen)

* in twee fasen oplossen
    * onderzoeken of netwerkstroom wel mogelijk is
    * transformeren in maximale stroom
* beide fasen vereisen oplossing van gewoon stroomnetwerk
    * met enkel bovengrenzen voor de stromen

## meerdere soorten materiaal (multicommodity network)

* voor elke soort één producent en één verbruiker
* in elke knoop (behalve producenten en verbruikers)
    * stroom is voor elke soort **apart** conservatief
    * gezamenlijke stroom van alle materialen door verbinding mag haar capaciteit niet overschrijden.

## kost per stroomeenheid (minimale kostprobleem)

* speciaal geval van maximaal stroomprobleem
    * met minimale kost
