
* algemene boom waarvan sleutels voldoen aan heapvoorwaarde
* standaard binaire boomvoorstelling
    * elke knoop bevat wijzer naar linkerkind en zijn rechterbroer
* als verminderen van prioriteit nodig is
    * elke knoop heeft extra wijzer nodig
        * van linkerkind naar ouder
        * van rechterbroer naar linkerbroer

## Operaties

* samenvoegen
    * vergelijkt wortelelementen van beide heaps
    * wortel met grootste element wordt linkerkind van deze met kleinste element
* toevoegen
    * speciaal geval van samenvoegen
* prioriteit van (gelokaliseerde) knoop verminderen
    * nagaan of heapvoorwaarde tegenover ouder nog steeds voldaan is
    * meeste knopen hebben geen ouderwijzer
    * knoop loskoppelen van ouder
    * wordt wortel van nieuwe heap
    * samenvoegen met oorspronkelijke (gewijzigde) heap
* minimum verwijderen
    * wortel verwijderen
        * levert collectie van \\(c\\) heaps op
    * nieuwe heap maken door \\(c-1\\) keer samenvoegen
    * in slechtste geval \\( O(n) \\) ( want \\(c=O(n)\\) )
    * volgorde van samenvoegen zorgvuldig kiezen
        * geamortiseerde performantie wordt \\( O(\lg{n}) \\)
    * standaardmanier gebruikt twee doorgangen
        * eerst heaps in paren samenvoegen, beginnend bij links
        * daarna beginnen bij meest rechtse (nieuwe) heap
            * anderen één voor één aan toevoegen: van rechts naar links
* willekeurige (gelokaliseerde) knoop verwijderen
    * loskoppelen van ouder
    * wordt wortel van nieuwe heap
    * minimum van nieuwe heap verwijderen (wortel)
    * rest van heap samenvoegen met oorspronkelijke (gewijzigde) heap
