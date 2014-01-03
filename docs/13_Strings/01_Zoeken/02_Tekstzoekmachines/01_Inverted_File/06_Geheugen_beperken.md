## Wat wordt er in geheugen bewaard?

\\[ 
    S_{q,d} = \sum_{t}{ \frac{w_{d,t}.w_{q,t}}{W_d.W_q} } 
\\]

* Accumulator bijhouden voor elk document \\(d\\): \\(A_d\\)
    * Document kan in elke lijst voorkomen
* Voor elke term \\(t\\) in \\(q\\):
    * \\(w_{q,t}\\)
    * \\(w_{d,t}\\)
* alles delen door \\(W_d\\)

## Accumulator threshholding

* Als er nog geen accumulator \\(A_d\\) gemaakt is voor document
    * eerst kijken of je nog onder grens \\(L\\) zit voor aantal accumulatoren: \\(|A| < L \\) 
* Best termen uit query behandelen volgens dalende \\(w_{q,t}\\) (stijgende \\(f_t\\))
    * meest zeldzame termen eerst nemen (hebben grotere invloed)
* Alternatief
    * als er nog geen accumulator voor dat document is
        * als nieuwe bijdrage groot genoeg is, dan wordt er één aangemaakt voor dat document
* nadelen
    * documenten zijn geordend volgens nummer in lijsten
    * documenten met laagste nummer worden bevoordeeld
        * accumulator wegnemen als die niet groot genoeg zijn

## Datastructuren

* Set van accumulatoren
    * niet noodzakelijk set: ervoor zorgen dat je een geordende structuur hebt
    * zodat bijwerken van \\(A\\) via merge(sort) kan gebeuren
        * overlopen volgens documentnummer
* \\(W_d\\) beperken (documentlengtes)
    * query-onafhankelijk
    * in praktijk: precisie niet belangrijk (benaderingen)
        * beperkt aantal waarden gebruiken
        * waarden dienen als interval/regio waar \\(W_d\\) erin zou voorkomen
* Woordenschat
    * B-tree
