## ongerichte graaf

### samenhangende componenten

* wanneer er weg bestaat tussen elk paar knopen
* niet samenhangende ongerichte graaf
    * bestaat uit zo groot mogelijke samenhangende componenten
* `diepte-eerst` zoeken
    * vindt alle knopen die met wortel van diepte-eerst boom verbonden zijn
    * graaf is samenhangend als boom alle knopen bevat
    * bij meerdere bomen: elke boom vormt samenhangende component
* alternatief: `breedte-eerst` zoeken
* performantie
    * ijle graaf: \\( \Theta(n+m) \\)
    * dichte graaf: \\( \Theta(n^2) \\)

## gerichte graaf

### sterk samenhangende componenten

* wanneer er een weg in beide richtingen bestaat tussen elk paar knopen
* niet in beide richting: zwak samenhangend
* gerichte graaf die niet sterk samenhangend is
    * bestaat uit zo groot mogelijk sterk samenhangende componenten
* componentengraaf
    * heeft knoop voor elke sterk samenhangende component
    * verbinding van knoop \\(a\\) naar knoop \\(b\\) 
        * als er in originele graaf een verbinding bestaat vanuit
            * 1 van de knopen uit \\(a\\)
            * naar één van de knopen uit \\(b\\)
    * heeft geen lussen
    * verschillende componenten behandelen
        * verbindingen componentengraaf volgen
* methode
    * `diepte-eerst` zoeken
    * 2 keer `diepte-eerst` zoeken: constante trager

#### methode

* omgekeerde graaf opstellen
    * richting van verbindingen omkeren
* op omgekeerde graaf `diepte-eerst` zoeken
    * knopen postorder nummeren
* `diepte-eerst` zoeken op oorspronkelijke graaf
    * telkens als startknoop resterende knoop met hoogste postordernummer nemen
* resultaat
    * diepte-eerst bos, waarvan bomen sterk samenhangende componenten zijn
* bewijs
    * knopen uit verschillende bomen van bos kunnen niet tot dezelfde sterk samenhangende componenten behoren
        * verbinding van linkse boom naar rechtse boom onmogelijk
    * elke knoop in beide richtingen verbonden
        * wortel is in beide richtingen verbonden met elk van zijn knopen
            * elk paar knopen van boom is in beide richtingen verbonden (via wortel)
                * via boomtakken: zeker weg van wortel \\(w\\) naar elk van knopen \\(u\\) in boom
                    * er is weg van \\(u\\) naar \\(w\\) in omgekeerde graaf
                * \\(w\\) is steeds voorouder van \\(u\\) in `diepte-eerst` boom van omgekeerde graaf
                    * ze kunnen niet tot tweeverschillende bomen behoren
                        * door postordernummer zou \\(w\\) in rechtse deelboom moeten liggen
                            * onmogelijk: er bestaat een weg van \\(u\\) naar \\(w\\)
                            * kunnen ook niet tot nevendeelbomen behoren
                    * ene knoop moet dus voorouder zijn van andere
                        = \\(w\\) (door hoger postordernummer)
                    * er bestaat een weg van \\(w\\) naar \\(u\\) in omgekeerde graaf (via boomtakken)
                        * er is dus weg van \\(u\\) naar \\(w\\) in oorspronkelijke graaf
                        * knopen zijn in beide richtingen verbonden

## performantie

* twee maal `diepte eerst` zoeken
    * ijle graaf: \\( \Theta(n+m) \\)
    * dichte graaf: \\( \Theta(n^2) \\)
* omkeren graaf
    * ijle graaf: \\( \Theta(n+m) \\)
    * dichte graaf: \\( \Theta(n^2) \\)

## implementatie

```
enum Kleur {
    WIT, GRIJS, ZWART
};

template<RichtType RT>
std::stack<int> Graaf<RT>::diepte_eerst_zoeken(
        int begin_knoop) {
    // We doen DEZ op de begin_knoop
    // en postorderen de knopen.
    // Alles wit.
    std::vector<Kleur> kleuren(aantalKnopen(), WIT);
    // Behandel de begin knoop.
    std::stack<int> post_order;
    this->behandel(begin_knoop, kleuren, post_order);
    return post_order;
}

template<RichtType RT>
void Graaf<RT>::behandel(int knoop_id,
        std::vector<Kleur>& kleuren, std::stack<int>& pad) {
    kleuren[knoop_id] = GRIJS;
    // Alle buren ophalen en over lopen
    std::map<int, int> buren = knopen[knoop_id];
    std::map<int, int>::iterator buren_it = buren.begin();
    while (buren_it != buren.end()) {
        // We behandelen enkel een knoop als we hem nog niet gezien hebben
        if (kleuren[buren_it->first] == WIT) {
            // Als we een knoop nog nooit gezien hebben, dan wordt hij grijs.
            behandel(buren_it->first, kleuren, pad);
            // We hebben een knoop volledig afgewerkt.
            kleuren[buren_it->first] = ZWART;
            // POST ORDER tellen!
            // Dus na de behandel plaatsen
            pad.push(buren_it->first);
        }
        buren_it++;
    }
}

template<RichtType RT, class Knoopdata, class Takdata>
GraafMetKnoopEnTakdata<RT, Knoopdata, Takdata> GraafMetKnoopEnTakdata<RT, Knoopdata, Takdata>::keerom() {
    std::cout << "Omkeren van de graaf" << std::endl;
    GraafMetKnoopEnTakdata<RT, Knoopdata, Takdata> omgekeerde_graaf;
    // Knopen kopieren.
    int totaal = this->aantalKnopen();
    for (int i = 0; i < totaal; i++) {
        Knoopdata woord = *this->geefKnoopdata(i);
        omgekeerde_graaf.voegKnoopToe(woord);
    }
    // Verbindingen kopieren in omgekeerde volgorde.
    for (int i = 0; i < totaal; i++) {
        std::map<int, int> buren = this->knopen[i];
        std::map<int, int>::iterator buren_it = buren.begin();
        while (buren_it != buren.end()) {
            Takdata woord = *this->geefTakdata(i, buren_it->first);
            try {
                omgekeerde_graaf.voegVerbindingToe(buren_it->first, i, woord);
            } catch (GraafExceptie e) {
                std::cerr << e.what() << std::endl;
            }
            buren_it++;
        }
    }
    return omgekeerde_graaf;
}

std::vector<std::stack<int> > componenten(const GraafMetKnoopEnTakdata<GERICHT, std::string, std::string> & graaf, const std::string & begin_woord) {

    std::map<std::string, int> knopen;
    int begin_knoop = knopen[begin_woord];

    // 1. Graaf omkeren
    GraafMetKnoopEnTakdata<GERICHT, std::string, std::string> omgekeerde_graaf;
    omgekeerde_graaf = graaf.keerom();

    // 2. DEZ in de omgekeerde graaf beginnende bij de begin knoop.
    std::stack<int> s = omgekeerde_graaf.diepte_eerst_zoeken(begin_knoop);

    // 3. Diepte eerst zoeken op de post order nummers in de gewone graaf.
    std::vector<Kleur> kleuren(graaf.aantalKnopen(), WIT);
    std::vector<std::stack<int> > componenten;

    while (!s.empty()) {
        int knoop_id = s.top();
        if (kleuren[knoop_id] == WIT) {
            std::stack<int> pad;
            graaf.behandel(knoop_id, kleuren, pad);
            componenten.push_back(pad);
        }
        s.pop();
    }
    std::cout << "Er zijn " << componenten.size() << " componenten gevonden." << std::endl;
    return componenten;
}
```
