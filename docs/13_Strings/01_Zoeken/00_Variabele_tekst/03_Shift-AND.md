

```
//constructor
ShiftAnd(const uchar* naald, int _naaldlengte) : naaldlengte(_naaldlengte){
    for(uint i = 0; i < naaldlengte; i++)
        letterpatroon[ naald[i] ] |= Bitpatroon::eenbit(i); // letterpatroon = S-tabel
}

//zoek
zoek(std::queue<const uchar*> & resultaten, const uchar * hooiberg, uint hooiberglengte){
    Bitpatroon oplossing = Bitpatroon::eenbit( naaldlengte - 1 );
    Bitpatroon R(0);
    for(uint i = 0; i < hooiberglengte; i++){
        R  = R.shiftrechts(1); // shift
        R |= Bitpatroon::eenbit(0); // bit 1 inschuiven op positie 0
        R &= letterpatroon[ hooiberg[i] ];
        if( oplossing.en(R) )
            resultaten.push( &hooiberg[ i - naaldlengte + 1 ] );
    }
}
```
