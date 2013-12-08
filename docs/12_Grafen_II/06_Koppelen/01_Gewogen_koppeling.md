

## Gale Shapley

* elk stable marriage probleem: tenminste 1 stabiele koppeling
* mannen krijgen beste partner die ze kunnen hebben
* controle stabiliteit
    * alle paren niet gekoppelde elementen moeten hun eigen partners verkiezen boven elkaar.
* algoritme
    * reeks 'aanzoeken' van mannen aan vrouwen
    * iedereen op elk ogenblik: ofwel vrij ofwel verloofd
        * man: kan afwisselend verloofd of vrij zijn
        * vrouw: eens verloofd, altijd verloofd, maar kan van partner veranderen
    * aanzoek van man aan vrouw:
        * als vrouw vrij is: zal zich steeds verloven
        * als vrouw al verloofd is
            * vergelijkt man met partner
            * verwerpt laagst geklasseerde
    * laagst geklasseerde = vrij, moet aanzoek doen
        * volgende op zijn voorkeurslijst gebruiken
    * algo stopt eens iedereen verloofd is
        * gebeurt zeker vóór man einde van lijst bereikt.

### implementatie

* voorkeurslijsten van alle deelnemers
* ranglijsten voor elke vrouw opstellen
    * geven volgorde van elke man aan in haar voorkeurslijst
    * lijsten opstellen: \\( \Theta(n^2) \\) 
* lijst van vrije mannen
    * om vrije man efficiënt te vinden
    * enkel verwijderen: afgewezen ma nkan meteen nieuw aanzoek doen.
* stopt als laatste vrouw haar eerste aanzoek krijgt.
* aantal aanzoeken: \\( O(n^2) \\)

### Uitbreidingen

#### verzamelingen van ongelijke grootte

* koppeling \\(M(man,vrouw)\\) onstabiel als
    * man en vrouw geen partners zijn.
    * man ofwel ongekoppeld blijft, ofwel vrouw verkiest boven zijn partner.
    * vrouw ofwel ongekoppeld blijft, ofwel man verkiest boven haar partner.
* iemand wordt liever gekoppeld dan alleen te moeten blijven

#### Onaanvaardbare partners

* voorkeurslijsten moeten niet volledige andere groep bevatten
    * onaanvaardbare partners weglaten.
* koppeling \\(M(man,vrouw)\\) onstabiel als
    * man en vrouw geen partners zijn, maar wel aanvaardbaar voor elkaar.
    * man ofwe longekoppeld blijft, ofwel vrouw verkiest boven zijn partner.
    * vrouw ofwel ongekoppeld blijft, ofwel man verkiest boven haar partner.
* twee groepen
    * zij die partners krijgen in alle stebiele koppelingen
    * zij die nooit partners krijgen.

#### gelijke voorkeuren

* voorkeurslijsten mogen ex aequo's bevatten
* **super stabiliteit**
    * koppeling onstabiel als man en vrouw bestaan die geen partners zijn en elkaar minstens evenzeer verkiezen als hun partners.
* **sterke stabiliteit**
    * koppeling onstabiel als er man en vrouw bestaat die geen partners zijn waarvan
        * ene de andere strikt erkiest boven de partner
        * andere de eerste minstens even graag heeft als de partner
* **zwakke stabiliteit**
    * koppeling onstabiel als er man en vrouw bestaat die geen partner zijn en elkaar strikt verkiezen boven hun eigen partner.
    * gelijke voorkeuren arbitrair ordenen.
