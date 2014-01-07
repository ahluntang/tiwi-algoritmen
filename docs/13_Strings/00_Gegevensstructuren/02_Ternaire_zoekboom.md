
* alternatieve voorstelling van meerwegstrie
* snelste implementatie van \\(m\\)-wegstrie gebruikt tabel met \\(m\\) kindwijzers in elke knoop
    * vereist onnodig veel geheugen
* geheugenverbruik vermijden
    * elke knoop bevat sleutelelement
    ![](/assets/ternairezoekboom.png)
* zoeken vergelijkt zoeksleutelelement met element in huidige knoop
    * als zoeksleutelelement **kleiner** is dan element in huidige knoop
        * verderzoeken in linkse deelboom, met **hetzelfde** zoeksleutelelement.
    * als zoeksleutelelement **groter** is dan element in huidige knoop
        * verderzoeken in rechtse deelboom, met **hetzelfde** zoeksleutelelement.
    * als zoeksleutelelement **gelijk** is aan element in huidige knoop
        * verderzoeken in middelste deelboom, met **volgende** zoeksleutelelement (als het bestaat)
    * te testen sleutelelement wordt niet bepaald door diepte van knoop
        * opeenvolgende elementen van zoeksleutels te vinden als je middelste wijzers volgt
* prefix: geschikt afsluitelement gebruiken
* zoeksleutel gevonden
    * als we met afsluitelement bij knoop met datzelfde element terechtkomen
* boom bevat zoeksleutel niet als
    * we bij nullwijzer terechtkomen
    * einde van zoeksleutel bereikt is vooraleer afsluitelement in boom gevonden werd
* toevoegen
    * eerst zoeken
    * maken van reeks opeenvolgende knopen voor alle volgende elementen van sleutel
* tijd vereist: evenredig met sleutellengte
* aantal knopen hangt af van opgeslagen sleutels
    * onafhankelijk van toevoegvolgorde
        * met elke sleutelprefix komt één knoop overeen
* in-order overlopen geeft volgorde van opgeslagen sleutels

## Voordelen

* past goed aan bij onregelmatig verdeelde zoeksleutels
    * soms aantal sleutelelementen groot
        * gebruik van elementen niet helemaal uniform
        * bij standaard meerwegstries met tabellen: teveel plaats
        * niet nodig om af te vragen welk deel van alfabet gebruikt wordt
    * praktijk: gestructureerd formaat
        * verschilt naargelang toepassing
        * bv: deel van sleutel letters, ander deel cijfers
            * ternaire zoekbomen gaan zich automatisch gedragen als zoekbomen met 26 knopen voor letters of met 10 knopen voor cijfers
* zoeken naar afwezige sleutels: meestal zeer efficiënt, zelfs voor lange sleutels
    * hashtabel heeft alle sleutelelementen nodig voor hashfunctie
    * zoekboom met \\(n\\) sleutels heeft \\(\Omega(\lg{n})\\) sleutelvergelijkingen nodig
    * patricia tries vereisen \\(\Omega(\lg{n})\\) bitoperaties voor willekeurige afwezige sleutel
    * ternaire zoekbomen vergelijken dikwijls slechts enkele sleutelelementen
        * volgen slechts enkele wijzers
* laten meer complexere zoekoperaties toe
    * zoeken naar sleutels waarvan bepaalde elementen niet gespecificeerd zijn
        * *don't care* karakters
    * alle sleutels opsporen die niet meer dan één element verschillen van zoeksleutel

## Verbeteringen

* aantal knopen beperken
    * sleutels in bladeren opslaan zodra men ze kan onderscheiden
    * inwendige knopen met slechts één kind elimineren via sleutelelementindex
        * zoektijd wordt onafhankelijk van sleutellengte
* wortel vervangen door meerwegstrieknoop
    * tabel van ternaire zoekbomen
    * als aantal mogelijke sleutelelementen \\(m\\) niet groot is
        * tabel van \\(m^2\\) ternaire zoekbomen gebruiken
        * er komt zoekboom overeen met elk eerste paar sleutelelementen
        * enkel zin als eerste sleutelelement gelijkmatig verdeeld zijn
* ternaire zoekbomen met verbeteringen
    * efficiëntste woordenboekstructuren voor strings
    * laten nog andere operaties toe

## Implementatie

```
void TernaireBoom::voegtoe(const string& sl) {
    // afsluitkarakter toevoegen
    stringstream ss;
    string naam;
    ss << sl << afsluiter;
    ss >> naam;
    
    Tknoop** h = &k;
    int index = 0;
    while(*h != 0 && index < naam.length()) {
        if(naam[index] < (*h)->c) {
            h = &(*h)->kind[0].k;
        } else if(naam[index] > (*h)->c) {
            h = &(*h)->kind[2].k;
        } else {
            h = &(*h)->kind[1].k;
            index++;
        }
    }
    
    for(int i=index; i<naam.length(); i++) {
        char karakter = naam[i];
        *h = new Tknoop();
        (*h)->c = karakter;
        h = &((*h)->kind[1].k);
    }
}
```
