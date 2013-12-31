
## Deelsequentie (LGD) van string

* door nul of meer stringelementen weg te laten
* elke deelstring is deelsequentie
* bv: *lente* is LGD van *dee**l**s**e**que**nt**i**e***

## Waarom LGD van twee strings zoeken?

* om teksten te vergelijken
* gelijkaardige maar niet gelijke DNA-strings te identificeren

## LGD probleem heeft optimale deelstructuur

* optimale oplossing maakt gebruik van optimale oplossingen voor deelproblemen
* deelproblemen zijn paren prefixen van twee strings
* Gegeven: twee strings
    * \\(X = \langle x_1, x_2, ... x_n \rangle \\)
        * \\( X_i \\) is prefix van \\(X\\) met lengte \\(i\\)
        * \\(X_0\\) is ledige prefix
        * \\(n\\) is lengte van string \\(X\\)
    * \\(Y = \langle y_1, y_2, ... y_m \rangle \\)
        * \\(m\\) is lengte van string \\(Y\\)
* Langste gemeenschappelijke deelsequentie: \\( LGD(X,Y) = Z = \langle z_1, z_2, ... z_k \rangle \\) 
    * als \\( x_n = y_m \\)
        * \\( z_k = x_n = y_m \\)
            * \\(Z\\) is \\(LGD\\) van \\(X_{n-1}\\) en \\(Y_{m-1}\\)
    * als \\( x_n \ne y_m \\)
        * \\( z_k \ne x_n \\)
            * \\(Z\\) is \\(LGD\\) van \\(X_{n-1}\\) en \\(Y\\)
        * \\( z_k \ne y_m \\)
            * \\(Z\\) is \\(LGD\\) van \\(X\\) en \\(Y_{m-1}\\)
* Deelproblemen zijn onafhankelijk en kunnen overlappen
    * worden door meer dan één (hoger) deelprobleem gebruikt
    * om \\(LGD\\) van \\(X\\) en \\(Y\\) te vinden:
        * \\(LGD\\) nodig van 
            * zowel: \\(X\\) en \\(Y_{m-1}\\)
            * als: \\(X_{n-1}\\) en \\(Y\\)
    * beide deelproblemen gebruiken als deel-deelprobleem \\(LGD(X_{n-1},Y_{m-1})\\)

## Lengte van \\(LGD\\) berekenen

* \\(c[i,j]\\) is lengte van \\(LGD(X_i,Y_j)\\):
\\[
c[i,j] = 
\begin{cases}
    0 & \text{als} & i = 0 & \text{of} & j = 0 \\\
    c[i-1,j-1]+1 & \text{als} & i > 0 & \text{en} & j > 0 & \text{en} & x_i = y_j \\\
    \max{( c[i,j-1], c[i-1,j] )} & \text{als} & i > 0 & \text{en} & j > 0 & \text{en} & x_i \ne y_j  \\\
\end{cases}
\\]


* Recursief?
    * Performantie om \\(c[n,m]\\) vinden is exponentieel
    * Er zijn maar \\( \Theta(nm) \\) verschillende deelproblemen: **dynamisch programmeren**
        * voorwaarden zijn voldaan
* Dynamisch programmeren
    * waarden van \\(c[i,j]\\) opslaan in tweedimensionale \\( (n+1)\times(m+1)\\) tabel \\(c\\)
    * rij per rij van links naar rechts berekenen
    * eerste rij en eerste kolom initialiseren met nullen

### Voorbeeld

\\[
\begin{array}{c|c|cccccc}
  &   & B & D & C & A & B & A \\\
\\hline
  & 0 & 0 & 0 & 0 & 0 & 0 & 0 \\\
\\hline
A & 0 & 0 & 0 & 0 & 1 & 1 & 1 \\\
B & 0 & 1 & 1 & 1 & 1 & 2 & 2 \\\
C & 0 & 1 & 1 & 2 & 2 & 2 & 2 \\\
B & 0 & 1 & 1 & 2 & 2 & 3 & 3 \\\
D & 0 & 1 & 2 & 2 & 2 & 3 & 3 \\\
A & 0 & 1 & 2 & 2 & 2 & 3 & 4 \\\
B & 0 & 1 & 2 & 2 & 2 & 4 & 4 \\\
\end{array}
\\]

* 3 deelsequenties van lengte 4
    * BCBA
    * BDAB
    * BCAB

## Juiste deelsequentie vinden

* naast tabel voor lengte: extra tweedimensionale \\( n \times m\\) tabel \\(b\\)
* in element \\(b[i,j]\\) plaats bijhouden van \\(c\\)-waarde die gebruikt werd om \\(c[i,j]\\) te bepalen
* vanuit \\(b[n,m]\\) langste deelsequentie te vinden in omgekeerde volgorde
    * telkens wanneer \\(c[i,j]\\) gebruikmaakt van \\(c[i-1,j-1]\\)
        * \\(x_i = y_j\\)

## Performantie

* bepaald door invullen van tabellen
    * reconstructie van \\(LGD\\) zelf: \\( O(n+m)\\)
        * bij elke iteratie: tenminste één van indices \\(i\\) of \\(j\\) gedecrementeerd
    * totale performnantie: \\( \Theta(nm) \\) (ook voor vereiste plaats)
* als men enkel lengte van \\(LGD\\) wenst: tabel \\(c\\) volstaat
    * elke rij gebruikt enkel waarden van vorige rij: twee rijen volstaan
        * vereiste plaats wordt \\( \Theta(\min(n,m)) \\)
    * niet voldoende om \\(LGD\\) te reconstrueren

