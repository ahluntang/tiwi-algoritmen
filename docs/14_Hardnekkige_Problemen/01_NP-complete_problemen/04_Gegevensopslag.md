## Bin packing

* gegeven
    * verzameling van \\(n\\) objecten met afmetingen \\(s_1, ..., s_n \\)
    * verzameling van \\(m\\) bakken met capaciteiten \\(c_1, ..., c_m \\)
* alle objecten opslaan in zo weinig mogelijk bakken
* er kunnen beperkingen opgelegd worden aan oriëntatie en plaatsing van objecten
* bij verpakkings- en fabricatieproblemen
* heuristische methoden
* eendimensionaal geval: *first-fit, decreasing*
    * \\(O(n\lg{n})\\)
    * gebruikt nooit meer dan 22% bakken teveel

## Knapsack

* gegeven
    * verzameling van \\(n\\) objecten met elk een afmeting en een waarde
    * knapzak met zekere capaciteit
* objecten in knapzak stoppen, zonder zijn capaciteit overschrijden
    * totale waarde zo groot mogelijk
* bij financiële beperkingen
    * zoveel mogelijk waarde verkrijgen voor beperkt budget
* *0/1 knapsack problem*
    * objecten mogen niet opgedeeld worden
* als objecten opgedeeld mogen worden
    * inhalig algoritme dat optimale oplossing vind
* als afmetingen relatief kleine gehele getallen zijn
    * optimale oplossing zoeken met dynamisch programmeren

