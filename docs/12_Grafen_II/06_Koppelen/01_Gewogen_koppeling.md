
* gegeven: één of twee verzamelingen van elementen
    * elk element heeft gerangschikte voorkeurslijst van andere elementen
    * elementen moeten gekoppeld worden
        * rekening houdend met voorkeuren, zodanig dat koppeling stabiel is
        * onstabiel: als er twee niet met elkaar gekoppelde elementen die liever met elkaar gekoppeld zijn dan in hun huidige toestand te blijven

## Stable marriage

* twee verzamelingen met dezelfde grootte
    * elementen: mannen en vrouwen
* elke man (vrouw) heeft voorkeurslijst die alle vrouwen (mannen) bevat
* elke man moet gekoppeld worden aan vrouw zodat koppeling stabiel is

## Hospitals/residents

* twee verzamelingen
    * elementen: hospitalen en stagiairs
* elk hospitaal biedt aantal stageplaatsen aan
* totaal aantal stageplaatsen moet niet noodzakelijk gelijk zijn aan aantal stagiairs
* elke hospitaal en stagiair heeft voorkeurslijst van alle elementen uit andere verzameling
* hospitaal moet gekoppeld worden aan aantal stagiairs (niet meer dan er plaatsen zijn)
    * zodat koppeling stabiel is

## Stable roommates

* zoekt stabiele koppeling tussen elementen van dezelfde verzameling
    * met even cardinaliteit
* elk element heeft voorkeurslijst die alle andere elementen bevat

## Gale-Shapley

* elk stable marriage probleem: tenminste 1 stabiele koppeling
* mannen krijgen beste partner die ze kunnen hebben
* controle stabiliteit
    * alle paren niet gekoppelde elementen moeten hun eigen partners verkiezen boven elkaar.
    * elk element uit een van de verzamelingen testen met elementen uit andere verzameling die hoger op zijn voorkeurslijst staan dan partner
* performantie \\(\Theta(n^2)\\)
* algoritme
    * reeks *aanzoeken* van mannen aan vrouwen
    * iedereen op elk ogenblik: ofwel vrij ofwel verloofd
        * man: kan afwisselend verloofd of vrij zijn
        * vrouw: eens verloofd, altijd verloofd, maar kan van partner veranderen
    * aanzoek van (vrije) man aan vrouw:
        * als vrouw vrij is: zal zich steeds verloven
        * als vrouw al verloofd is
            * vergelijkt man met partner
            * verwerpt laagst geklasseerde
    * laagst geklasseerde = vrij, moet aanzoek doen
        * volgende op zijn voorkeurslijst gebruiken
    * algo stopt eens iedereen verloofd is
        * gebeurt zeker vóór man einde van lijst bereikt.

### Eigenschappen van Gale-Shapley

#### Algoritme stopt altijd

* geen enkele man wordt afgewezen door alle vrouwen
    * enkel verloofde vrouw kan man afwijzen, eens verloofd, blijft ze verloofd
    * man kan niet afgewezen worden door laatste vrouw op lijst
        * dan zouden alle vrouwen verloofd zijn
    * polygamie is niet toegestaan
* in elke iteratie gebeurt er een aanzoek
    * geen enkele man doet dat tweemaal aan dezelfde vrouw
    * maximaal \\(n^2\\) aanzoeken: algoritme stopt zeker

#### Oplossing is steeds stabiel

* als er man \\(m\\) bestaat die vrouw \\(v\\) verkiest boven zijn partner
    * \\(v\\) moet hem ooit afgewezen hebben
    * omdat ze verloofd was of zich verloofde met man die ze verkoos boven \\(m\\)
    * als ze later een andere partner aanvaardde, stond die nog hoger op haar lijst
* \\(m\\) verkiest andere vrouw \\(v\\) niet omgekeerd
* er bestaat geen ongekoppeld paar dat stabiliteit van koppeling in gevaar brengt

#### Elke mogelijke aanzoekvolgorde van mannen geeft dezelfde oplossing

* elke man krijgt best mogelijke partner die hij kan hebben in stabiele koppeling
* onderstel dat man \\(m\\) niet zijn best mogelijke stabiele partner \\(v\\) krijgt
    * maar vrouw dat lager staat op zijn lijst
    * \\(m\\) werd ooit door \\(v\\) afgewezen
* onderstel verder dat \\(m\\) eerste man is die door stabiele partner wordt afgewezen tijdens uitvoering van algoritme
    * impliceert dat \\(v\\) best mogelijke partner van \\(m\\) is
    * \\(m\\) wordt door \\(v\\) afgewezen als ze andere man \\(m'\\) verkiest
    * \\(m'\\) was reeds partner, of wordt nieuwe partner
    * wanneer \\(m'\\) partner van \\(v\\) wordt, werd hij nog door stabiele partner afgewezen
    * we onderstelden dat dit eerste keer gebeurt bij \\(m\\)
    * alle mogelijke stabiele partners van \\(m'\\) staan lager op zijn lijst dan \\(v\\)
    * \\(v\\) is stabiele partner van \\(m\\)
        * er bestaat een andere stabiele koppeling \\(K\\) waarin \\(m\\) en \\(v\\) partners zijn
        * waarin \\(v'\\) partner van \\(m'\\) is
    * \\(v'\\) staat ook lager dan \\(v\\) op lijst van \\(m'\\)
    * koppels \\((m,v)\\) en \\((m',v')\\) uit \\(K\\) zijn dus niet stabiel
        * zowel \\(v\\) als \\(m'\\) verkiezen elkaar boven hun partners
    * koppeling \\(K\\) blijft dus toch niet stabiel
        * veronderstelling klopt niet
    * niet vanzelfsprekend dat mannen een stabiele koppeling bekomen die gelijktijdig optimaal is voor hen allemaal
        * man-geörienteerde versie = man-optimaal
        * mogelijk dat beide oplossingen identiek zijn, maar niet noodzakelijk

 #### In man-geörienteerde versie krijgt elke vrouw de slechtst mogelijke partner die ze kan hebben in stabiele koppeling

* onderstel: vrouw \\(v\\) krijgt niet haar slechts mogelijke stabiele partner \\(m\\), maar man \\(m'\\) hoger op haar lijst
* \\(m\\) is stabiele partner van \\(v\\)
    * er bestaat andere stabiele koppeling \\(K\\) waarin
        * \\(m\\) en \\(v\\) partners zijn
        * partner van \\(m'\\) bijvoorbeeld \\(v'\\) is
    * zowel \\(v\\) als \\(v'\\) zijn stabiele partners van \\(m'\\)
        * Gale-Shapley wijst aan elke man best mogelijke stabiele partner toe
        * \\(v\\) staat hoger dan \\(v'\\) op lijst van \\(m'\\)
        * \\(m'\\) staat hoger dan \\(m\\) op lijst van \\(v\\)
        * koppels \\((m,v)\\) en \\((m',v')\\) uit \\(K\\) zijn niet stabiel
            * zowel \\(v\\) als \\(m'\\) verkiezen elkaar boven hun partners

### implementatie

* voorkeurslijsten van alle deelnemers
    * volstaan niet om snel te weten te komen aan welke van twee mannen een vrouw voorkeur geeft
* ranglijsten voor elke vrouw opstellen
    * geven volgorde van elke man aan in haar voorkeurslijst
    * lijsten opstellen: \\( \Theta(n^2) \\) 
* lijst van vrije mannen
    * om vrije man efficiënt te vinden
    * enkel verwijderen: afgewezen man kan meteen nieuw aanzoek doen.
* stopt als laatste vrouw haar eerste aanzoek krijgt.
* aantal aanzoeken: \\( O(n^2) \\)
* \\(n-1\\) vrouwen kunnen elk maximaal \\(n\\) aanzoeken krijgen
    * plus \\(1\\) aanzoek aan laatste vrouw
* Gale-Shapley: \\( \Theta(n^2) \\) 

### Uitbreidingen

#### verzamelingen van ongelijke grootte

* aantal mannen \\(n_m\\) is verschillend van aantal vrouwen \\(n_v\\)
* meeste resultaten voor gelijke aantallen blijven echter behouden, in licht gewijzigde vorm
* koppeling \\(M(m,v)\\) onstabiel als
    * man \\(m\\) en vrouw \\(v\\) geen partners zijn.
    * man \\(m\\) ofwel ongekoppeld blijft, ofwel vrouw \\(v\\) verkiest boven zijn partner.
    * vrouw \\(v\\) ofwel ongekoppeld blijft, ofwel man \\(m\\) verkiest boven haar partner.
* iemand wordt liever gekoppeld dan alleen te moeten blijven
    * elke stabiele koppeling bestaat uit \\( \min{\lbrace n_m, n_v \rbrace} \\) koppels
        * de rest van grootste groep blijft ongekoppeld
    * voor kleinste groep vindt Gale-Shapley een stabiele koppeling
        * is optimaal voor iedereen uit die groep
    * slechts mogelijke koppeling voor iedereen uit grootste groep die partner krijgt

#### Onaanvaardbare partners

* voorkeurslijsten moeten niet volledige andere groep bevatten
    * onaanvaardbare partners weglaten.
* koppeling \\(M(m,v)\\) onstabiel als
    * man \\(m\\) en vrouw \\(v\\) geen partners zijn, maar wel aanvaardbaar voor elkaar.
    * man \\(m\\) ofwel ongekoppeld blijft, ofwel vrouw \\(v\\) verkiest boven zijn partner.
    * vrouw \\(v\\) ofwel ongekoppeld blijft, ofwel man \\(m\\) verkiest boven haar partner.
* twee groepen
    * zij die partners krijgen in alle stabiele koppelingen
    * zij die nooit partners krijgen.

#### gelijke voorkeuren

* voorkeurslijsten mogen ex-aequo's bevatten
* **super stabiliteit**
    * koppeling onstabiel als er een man en een vrouw bestaan die geen partners zijn en elkaar minstens evenzeer verkiezen als hun partners.
    * er zijn gevallen waarbij geen (super)stabiele koppeling mogelijk is
* **sterke stabiliteit**
    * koppeling onstabiel als er een man en een vrouw bestaan die geen partners zijn waarvan
        * ene de andere strikt verkiest boven de partner
        * andere de eerste minstens even graag heeft als de partner
    * er is niet altijd een (sterk) stabiele koppeling
* **zwakke stabiliteit**
    * koppeling onstabiel als er een man en een vrouw bestaan die geen partners zijn en elkaar strikt verkiezen boven hun eigen partner.
    * kan getransformeerd worden tot standaardprobleem
        * door gelijke voorkeuren arbitrair ordenen
        * stabiele oplossing is ook (zwak) stabiel voor origineel probleem
    * zal steeds oplossing vinden, niet noodzakelijk uniek
        * hangt af van arbitraire ordening

### Hospitals/Residents

* asymmetrische veralgemening van stable marriage probleem
    * enerzijds stagiairs
    * anderzijders hospitalen die elk een of meer stageplaatsen aanbieden
* elk hospitaal moet stabiel gekoppeld worden aan aantal stagiairs
* aantal plaatsen moet niet noodzakelijk gelijk zijn aan aantal stagiairs
* voorkeurslijsten mogen onvolledig zijn (van zowel hospitalen als stagiairs)
* gelijke voorkeuren worden niet toegelaten
* koppeling is onstabiel wanneer er hospitaal \\(h\\) en stagiair \\(s\\) zijn zodat
    * hospitaal \\(h\\) en stagiair \\(s\\) geen partners zijn, maar wel aanvaardbaar zijn
    * stagiair \\(s\\) ofwel ongekoppeld blijft ofwel hospitaal \\(h\\) verkiest boven zijn toegewezen hospitaal
    * hospitaal \\(h\\) ofwel onbezette stageplaatsen overhoudt, ofwel stagiair \\(s\\) verkiest boven tenminste een van zijn toegewezen stagiairs
* koppeling van meerdere stagiairs aan één hospitaal
  transformeren in één-één-duidige koppeling
    * elke hospitaal \\(h\\) met \\(p\\) plaatsen
        * vervangen door \\(p\\) identieke hospitalen \\(h_1, h_2, ..., h_p\\) met elk één stageplaats
        * allemaal met dezelfde voorkeurslijst als \\(h\\)
    * als \\(h\\) voorkomt in lijst van stagiair
        * vervangen door reeks
    * stabiele koppeling voor dit probleem komt overeen met stabiele koppeling voor origineel probleen
* versie voor paren stagiairs
    * verkiezen meestal dezelfde hospitalen
    * elk stagiairpaar mag gezamenlijke voorkeurslijst van hospitalen indienen
        * geordende paren hospitalen
    * niet langer zeker dat er stabiele oplossingen bestaan

### Stable roommates

* veralgemening van stable marriage probleem
    * slechts één groep met \\(n\\) personen (\\(n\\) is even)
    * elk maken voorkeurslijst op van al de anderen als potentiële kamergenoten
* koppeling verdeelt groep in paren
    * is onstabiel wanneer er twee elkaar verkiezen boven hun toegewezen kamergenoten
* niet altijd stabiele koppeling nodig
* performantie \\(O(n^2)\\)
