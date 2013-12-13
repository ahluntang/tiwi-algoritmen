## Zoeken

* kleur  van knopen speelt geen rol
* zoals bij gewone binaire zoekboom
* hoogte steeds \\(O(\lg{n})\\)
    * bij binaire boom zoeken: \\(O(h)\\)
    * bij rood-zwarte boom: zoeken gegarandeerd \\(O(\lg{n})\\)

## Toevoegen en verwijderen

* Zonder rekening houden met kleur: \\(O(\lg{n})\\)
    * niet zeker of boom na toevoegen/verwijderen nog steeds rood-zwarte boom is
* operaties die rekening houden met regels rood-zwarte boom kunnen ook efficiënt gebeuren
* twee manieren
    * bottom-up
        * eerst toevoegen zonder op kleur te letten (zoals bij gewone binaire zoekboom)
        * blad wordt vervangen door nieuwe knoop
        * nadien rood-zwarte boom herstellen vanaf nieuwe knoop
            * desnoods tot bij wortel
        * afdalen om nadien terug te stijgen
            * ouderwijzers of stapel nodig
    * top-down
        * boom reeds aanpassen langs dalende zoekweg
        * in praktijk efficiënter
* structuurwijzigingen gebeuren via rotaties

## Rotaties

* wijzigen vorm van boom
    * behouden **inorder** volgorde van sleutels
    * kleur van knopen blijft onveranderd
* lokale operatie waarbij twee inwendige knopen betrokken zijn
    * draait rond de ouder-kind verbinding
* rotatie naar links (voor rechterkind)
* rotatie naar rechts (voor linkerkind)

![](/assets/rzboom_rotatie.png)
