* *iterative improvement*: elke keuze wordt enkel gedaan als de resulterende oplossing beter is dan de huidige oplossing
* **keuze**: kiezen van oplossing \\(s'\\) in de buurt \\(\mathcal{N}(s)\\) van oplossing \\(s\\)
* algoritme stopt als het een lokaal minimum vindt

## Pseudocode
```
s ← GenerateInitialSolution()
repeat
    s ← Improve(N(s))
until no improvement is possible
```

* beginnen met bepaalde "oplossing"
* in de buurt zoeken naar verbeteringen: \\(\mathcal{N}(s)\\) (neighbourhood)
* tot er geen verbeteringen meer zijn
* probleem: lokale putten

### Improve(\\(\mathcal{N}(s)\\))

* **first improvement** of **best improvement** (of tussenliggend)
* first improvement
    * onderzoekt de buurt \\(\mathcal{N}(s)\\) en kiest de eerste oplossing dat beter is dan \\(s\\)
* best improvement
    * onderzoekt de buurt volledig en geeft de oplossingen terug met de *lowest objective function* waarde
* beide stoppen bij lokale minima's
* uitkomst sterk afhankelijk van de definitie van \\(S\\), \\(f\\) en \\(\mathcal{N}(s)\\)

### Stop criterium/ terminating condition

* moeten complexere criteria gebruiken dan enkel oplossing (om lokale putten te vermijden)
* kan combinatie zijn van
    * maximum CPU tijd
    * maximum aantal iteraties (waarbij geen verbeteringen zijn)
    * oplossing is met \\(f(s)\\) kleiner dan voorgedefinieerde drempelwaarde

