
```
int d = 256; // alfabet
int Q = 997; // priemgetal

int hash(const uchar* str, uint m){
    int h = 0;
    for(uint i = 0; i < m; i++)
        h = d * h + str[i] % Q;
    return h;
}

bool controleer(const uchar* hooiberg, uint pos, const uchar* naald, uint m) {
    for (uint i = 0; i < m; i++)
        if (hooiberg[pos + i] != naald[i])
            return false;
    return true;
}

int search( const uchar* hooiberg, uint n, const uchar * naald, uint m, std::queue<uchar*> & resultaten){
    uint naald_hash = hash(naald,m);
    uint hooiberg_hash = hash(hooiberg, m);

    if( hooiberg_hash == naald_hash && controleer(hooiberg, 0, naald, m) )
        resultaten.push( &hooiberg[0] );

    //d^(m-1) % Q
    int dm = 1;
    for(uint i = 0; i < m; i++)
        dm = ( dm * d ) % Q;

    for(uint i = m; i < n; i++){
        // nieuwe hash:
        //  (1) eerste char eraf trekken
        //  (2) volgend char erbij tellen
        hooiberg_hash = ( hooiberg_hash + Q - ( dm* hooiberg[i-m] ) % Q ) % Q; // (1) 
        hooiberg_hash = ( hooiberg_hash * d + hooiberg[i] ) % Q; // (2) 

        // hashes vergelijken
        if( hooiberg_hash == naald_hash && controleer(hooiberg, i - m + 1, naald, m) )
            resultaten.push( &hooiberg[i - m + 1] );
    }
}
```
