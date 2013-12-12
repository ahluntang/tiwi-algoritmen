## Up-to-date houden van indexen

### Rebuild

* van scratch opnieuw opbouwen
* enkel haalbaar voor kleinere collecties

### Intermittent Merge

* belangrijkste methode
* bestaand systeem intact houden
* in geheugen tijdelijke run opbouwen voor alle nieuwe documenten
* bij zoeken samen gebruiken (dus ook in geheugen zoeken)
* als geheugen vol is
    * run op schijf wegschrijven (mergen met bestaand systeem)
* volgende documenten opnieuw in run in geheugen opbouwen.

### Incrementele Update

* af en toe, via achtergrondproces of met bepaalde trigger updaten
* deels updaten, bv enkel voor bepaalde term
* probleem bij crash
    * na herstellen backup
    * niet gekend wat laatst bijgewerkt werd
    * bij intermittent merge werd het bestaand systeem intact gehouden.
