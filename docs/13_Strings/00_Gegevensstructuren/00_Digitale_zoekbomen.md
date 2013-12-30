
## Digitale zoekboom

* sleutels opslaan in knopen
* niet in juiste volgorde (in-order) eruit te halen
* zoeken en toevoegen
    * beginnend bij wortel
    * zoeksleutel vergelijken met sleutel in huidige knoop
    * als ze verschillen
        * verderzoeken in één van de deelbomen
        * bij ledige deelboom: eventueel toevoegen
* verschil met gewone zoekbomen
    * juiste deelboom wordt bepaald door telkens volgend element van zoeksleutel te vergelijken met sleutel in knoop
        * bij wortel eerste sleutelelement
        * niveau dieper: volgend sleutelelement
* toepasbaar op willekeurige sleutelelementen
    * bv. bits: binaire digitale zoekbomen

### Binaire digitale zoekbomen

![](/assets/digitalezoekboom.png)

* volgens diepte juiste bit gebruiken
* in knoop op diepte \\(i\\)  wordt bit \\(i+1\\) van zoeksleutel gebruikt
    * om te beslissen of we afdalen naar linker- of naar rechterkind
* in-order overlopen van (binaire) digitale zoekboom levert niet noodzakelijk opgeslagen sleutels in volgorde
    * alle sleutels in linkerdeelboom van knoop op diepte \\(i\\) zijn kleiner dan deze in zijn rechterdeelboom
    * \\(i\\) beginbits van al deze sleutels zijn gelijk
    * onderscheid werd gemaakt op grond van bit \\(i+1\\)
    * sleutel in knoop zelf heeft dezelfde \\(i\\) beginbits
        * kan toch om het even waar vallen tussen sleutels van beide deelbomen
* elke sleutel in digitale zoekboom bevindt zich ergens op weg vanuit wortel bepaald door opeenvolgende bits van sleutel
    * langste weg in boom (hoogte) wordt beperkt door aantal bits van langst opgeslagen sleutel
* voor groot aantal sleutels met relatief kleine bitlengte
    * performantie in slechtste geval veel beter dan gewone binaire zoekboom
    * vergelijkbaar met rood-zwarte boom
* gelijkmatig verdeelde sleutels
    * kans op volgend \\(0\\) of \\(1\\) bit steeds gelijk
    * gemiddeld evenveel sleutels aan beide zijden van elke knoop
    * gemiddelde weglengte tot elke knoop \\(O(\lg{n})\\)
    * zoeken of toevoegen vereist gemiddeld \\(O(\lg{n})\\) sleutelvergelijkingen
* aantal vergelijkingen is nooit meer dan aantal bits van zoeksleutel
* performantie vergelijkbaar met die van rood-zwarte bomen
    * implementatie even eenvoudig als die van gewone zoekbomen
* beperkende voorwaarde
    * vereist efficiënte toegang tot bits van sleutels
    * enkel woordenboekoperaties mogelijk
