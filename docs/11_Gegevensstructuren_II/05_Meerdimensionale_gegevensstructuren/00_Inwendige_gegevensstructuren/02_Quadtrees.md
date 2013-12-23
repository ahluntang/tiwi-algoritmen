
* verdelen zoekruimte (of gedeelte ervan) telkens in \\(2^k\\) (hyper)rechthoeken
    * waarvan zijden evenwijdig zijn met assenstelsel
* hiërarchische verdeling wordt opgeslagen in \\(2^k\\)-wegsboom
    * elke knoop staat voor gebied dat onderverdeeld wordt in de \\(2^k\\) deelgebieden van zijn kinderen
* aantal knopen neemt zeer snel toe met hoogte
    * niet geschikt voor veel dimensies
* verschil tussen point quadtrees en point region quadtrees
    * bij opdeling van zoekruimte houdt point quadtree rekening met opgeslagen punten

## Point quadtrees

* originele quadtree is meerdimensionale uitbreiding van binaire zoekboom
    * elke inwendige knoop bevat punt
        * coördinaten (deel)zoekruimte opdelen in vier rechthoeken (niet noodzakelijk even groot)
    * elk kind is wortel van deelboom die alle punten in overeenkomstig rechthoek bevat
        * als deelboom ledig is
            * is blad
* zoeken van punt 
    * weg volgen vanuit wortel
    * telkens zoekpunt vergelijken met punten bij opeenvolgende knopen
    * eventueel afdalen naar kind met gepaste deelgebied
    * als punt niet aanwezig blijkt: leeg deelgebied
        * toevoegen als nieuw inwendig punt
* vorm afhankelijk van toevoegvolgorde
    * als elke toevoegvolgorde even waarschijnlijk is: zoeken en toevoegen \\(O(\lg{n})\\)
    * in slechtste geval: \\(O(n)\\)
* als punten op voorhand gekend zijn
    * ervoor zorgen dat geen enkel deelboom meer dan helft van punten dna die van zijn ouder bevat
    * punten lexicografisch rangschikken (op \\(x\\), bij gelijke \\(x\\) op \\(y\\))
    * mediaan wordt wortel
    * alle punten vóór mediaan
        * in eerste twee deelbomen
    * alle punten na mediaan
        * in laatste twee deelbomen
    * hetzelfde bij kinderen
        * punten zijn reeds gerangschikt
    * hoogte wordt \\(O(\lg{n})\\)
    * constructie: \\(O(n\lg{n})\\)
        * rangschikken  \\(O(n\lg{n})\\)
        * werk op elk niveau:  \\(O(n)\\)
        * mediaan vinden \\(O(1)\\)
        * punten verdelen over deelbomen zodat ze gerangschikt blijven: \\(O(n)\\)
* zoeken naar punten in zoekrechthoek
    * recursief
    * bij knoop testne of punt in rechthoek ligt
    * deelbomen onderzoeken die rechthoek overlappen
* verwijderen
    * moeilijk
    * deelboom onder overeenkomstige knoop herstructureren
    * eenvoudigst: alle punten van deelboom opnieuw toevoegen

## Point region quadtrees

* gegevensstructuur voor ruimtelijke objectne (*gebieden* in twee dimensies)
* vereist dat zoekruimte rechthoek is (in tegenstelling to quadtree)
    * is ofwel gegeven of moet eerst bepaald worden
        * als kleinste rechthoek die alle punten bevat
* elke knoop verdeelt deel van ruimte in vier gelijke rechthoeken
    * opdeling gaat door tot deelgebied nog één punt bevat
    * inwendige knopen bevatten geen punten
    * niet nodig dat ze coördinaten bevatten (plaatsbesparing)
        * kan op zoekweg berekend worden
* punt zoeken
    * opeenvolgende knopen vanuit wortel gebruiken
        * rechthoek vinden waarin punt zou moeten liggen (als rechthoek 1 punt bevat)
    * als zoekpunt verschilt van enig punt
        * bij toevoegen
            * gebied opsplitsen tot elk van punten in eigen gebied ligt
        * bij verwijderen
            * onderverdelingen (en knopen) verwijderen
* vorm onafhankelijk van toevoegvolgorde
    * opsplitsen van deelgebied wilt niet zeggen dat punten erin onderverdeeld worden
        * kan onevenwichtig uitvallen
        * onmogelijk om grootte en hoogte uit te drukken in functie van aantal opgeslagen punten \\(n\\)
    * verband tussen hoogte en kleinste afstand \\(a\\) tussen twee punten
        * als \\(z\\) grootste zijde van zoekruimte is
            * grootste zijde van gebied op diepte \\(d\\): \\( \frac{z}{2^d} \\)
            * maximale afstand tussen twee punten in gebied: \\( z\frac{\sqrt{k}}{2^d} \\)
            * gebied van elke inwendigek noop bevat minstens twee punten
                * onderlinge afstand is tenminsta \\(a\\)
            * op elke diepte \\(d\\) : \\( z\frac{\sqrt{k}}{2^d} \ge a \\) of \\( \lg{\left( \frac{z}{a} \right)} + \frac{\lg{k}}{2} \\)
            * hoogte \\(h\\) = maximale diepte van inwendige knoop + 1
              voor tweedimensionale quadtree: \\( h \le \lg{\left( \frac{z}{a} \right)} + \frac{3}{2} \\)
* op elk niveau
    * gebieden van inwendige knopen bedekken zoekruimte
    * al deze gebieden bevatten punten
    * per niveau: aantal inwendige knopen \\(O(n)\\)
    * totaal aantal inwendige knopen \\(i\\) in boom met hoogte \\(h\\) is \\(O(hn)\\)
    * elke inwendige knoop heeft vier kinderen
        * aantal bladeren \\(3i+1\\)
        * aantal knopen van boom \\( O(hn) \\)
* bij constructie van boom
    * meeste werk gaat naar verdelen van punten over deelgebieden van elke knoop
    * evenredig met aantal te verdelen punten
        * op elk niveau \\(O(n)\\)
    * constructietijd: \\(O(hn)\\)
