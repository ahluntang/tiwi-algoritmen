
## ~ boek

* boek bevat woordenlijst met verwijzing naar bladzijde = inverted file
* in plaats van : bladzijde waar woorden voorkomen dat je wilt indexeren

## document-level inverted file


| term \\(t\\)  | \\(f_t\\) | Inverted list voor \\(t\\) |
|---------------|-----------|----------------------------|
| and           | 1         | \\( \langle 6,2 \rangle \\) 
| big           | 2         | \\( \langle 2,2 \rangle \\) \\( \langle 3,1 \rangle \\) 
| dark          | 1         | \\( \langle 6,1 \rangle \\) 
| did           | 1         | \\( \langle 4,1 \rangle \\) 
| gown          | 1         | \\( \langle 2,1 \rangle \\) 
| had           | 1         | \\( \langle 3,1 \rangle \\) 
| house         | 2         | \\( \langle 2,1 \rangle \\) \\( \langle 3,1 \rangle \\) 
| in            | 5         | \\( \langle 1,1 \rangle \\) \\( \langle 2,2 \rangle \\) \\( \langle 3,1 \rangle \\) \\( \langle 5,1 \rangle \\) \\( \langle 6,2 \rangle \\) 
| keep          | 3         | \\( \langle 1,1 \rangle \\) \\( \langle 3,1 \rangle \\) \\( \langle 5,1 \rangle \\)
| keeper        | 3         | \\( \langle 1,1 \rangle \\) \\( \langle 4,1 \rangle \\) \\( \langle 5,1 \rangle \\) 
| keeps         | 3         | \\( \langle 1,1 \rangle \\) \\( \langle 5,1 \rangle \\) \\( \langle 6,1 \rangle \\) 
| light         | 1         | \\( \langle 6,1 \rangle \\) 
| never         | 1         | \\( \langle 4,1 \rangle \\) 
| night         | 3         | \\( \langle 1,1 \rangle \\) \\( \langle 4,1 \rangle \\) \\( \langle 5,2 \rangle \\) 
| old           | 4         | \\( \langle 1,1 \rangle \\) \\( \langle 2,2 \rangle \\) \\( \langle 3,1 \rangle \\) \\( \langle 4,1 \rangle \\) 
| sleep         | 1         | \\( \langle 4,1 \rangle \\) 
| sleeps        | 1         | \\( \langle 6,1 \rangle \\) 
| the           | 6         | \\( \langle 1,3 \rangle \\) \\( \langle 2,2 \rangle \\) \\( \langle 3,3 \rangle \\) \\( \langle 4,1 \rangle \\) \\( \langle 5,3 \rangle \\) \\( \langle 6,2 \rangle \\) 
| town          | 2         | \\( \langle 1,1 \rangle \\) \\( \langle 3,1 \rangle \\) 
| where         | 1         | \\( \langle 4,1 \rangle \\) 

* kolommen
    * term \\(t\\): woordenschat
        *  bevat alle zoektermen
        * in praktijk: B-tree (met verwijzingen naar de inverted files)
    * \\(f_t\\): aantal keer dat term \\(t\\) voorkomt ( = lengte van inverted list)
    * inverted list: lijst met tuples/pairs \\( \langle d, f_{d,t} \rangle \\)
        * tuple/pair verwijst naar document en geeft aan hoe vaak term erin voorkomt

* lijsten
    * te reserveren blokken?
    * dezelfde lijst moet opeenvolgende blokken krijgen
    * zo weinig mogelijk schijfoperaties
    * grootte beperken
        * gaps gebruiken naar volgend document (kleinere waarden, beter te comprimeren)  
| Documentnr| 7 | 18 | 19 | 22 | 23 | 25 | 63 | ... |
|-----------|---|----|----|----|----|----|----|-----|
| Gaps      | 7 | 11 | 1  | 3  | 1  | 2  | 38 | ... |


