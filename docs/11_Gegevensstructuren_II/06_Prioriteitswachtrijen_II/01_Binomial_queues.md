
## Structuur

* bestaat uit bos van binomiaalbomen, elk met heapvoorwaarde
* gekenmerkt door hoogte
    * slechts 1 binomiaalboom \\(B_n\\) met hoogte \\(h\\) mogelijk
* definitie is recursief
    * \\(B_0\\) bestaat uit 1 knoop
    * \\(B_h\\) uit twee \\(B_{h-1}\\) bomen
        * tweede is meest rechtse deelboom van wortel van eerste 
        * kinderen: \\( B_0, B_1, ..., B_{h-1} \\)
        * op diepte \\(d\\) zijn er \\( \binom{h}{d} \\) knopen
            * volledige boom heeft \\(2^h\\) knopen
* bos van binomiaalbomen
    * bevat hoogstens één boom van elke hoogte
    * er zijn evenveel bomen als er enen zijn in binaire voorstelling van aantal elementen
        * met \\(2^i\\) komt \\(B_i\\) overeen

## Operaties

* minimum vinden
    * alle wortels van bomen overlopen
    * hoogstens \\(\lg{n}\\) bomen: \\(O(\lg{n})\\)
    * als plaats van minimum bijgehouden wordt: \\(O(1)\\)
* samenvoegen
    * telt bomen met dezelfde hoogte bij elkaar op
    * twee \\(B_h\\) bomen optellen
        * wortel met grootste sleutel kind maken van wortel met kleinste
        * resultaat \\(B_{h+1}\\)
    * binomiaalbomen samenvoegen \\(O(1)\\)
        * \\(O(\lg{n})\\) bomen: samenvoegen binomial queues \\(O(\lg{n})\\)
    * bijhouden van binomiaalbomen gerangschikt op hoogte
* toevoegen
    * speciaal geval van samenvoegen
    * knoop met toe te voegen element is triviale binomial queue
    * performantie \\(O(\lg{n})\\)
    * \\(n\\) toevoegoperaties op ledige binomial heap
        * slechtste geval \\(O(n)\\)
        * geamortiseerd \\(O(1)\\)
* minimum verwijderen
    * binomiaalboom \\(B_k\\) met kleinste wortelelement zoeken
    * verwijderen uit bos
        * levert nieuwe binomial queue
    * wortel verwijderen uit \\(B_k\\)
        * levert \\(k\\) binomiaalbomen op: \\( B_0, B_1, ..., B_{k-1} \\)
        * vormen samen tweede binomial queue
        * beide binomial queues samenvoegen
        * performantie \\(O(\lg{n})\\)
            * \\(B_k\\) zoeken, beide binomial queues creëren/samenvoegen 
                * elk \\(O(\lg{n})\\)

## Implementatie

* binomial queue voorgesteld als tabel van binomiaalbomen
* voor binomiaalbomen
    * standaard binaire boomvoorstelling van algemene boom
    * elke knoop bevat wijzer naar linkerkind en naar zijn rechterbroer
* gelinkte lijst van kinderen van knoop
    * gerangschikt volgens dalend aantal knopen
    * vergemakkelijkt samenvoegen van binomiaalbomen

