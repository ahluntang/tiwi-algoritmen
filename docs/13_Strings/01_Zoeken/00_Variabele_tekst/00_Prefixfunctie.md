
* prefixfunctie \\(p(i)\\) van string \\(P\\) bepaalt voor elke stringpositie \\(i\\)
    * lengte van langste prefix van \\(P\\) die overeenkomst met (deelstring van) diezelfde \\(P\\), eindigend bij \\(i\\).

```
std::string hooiberg;
std::string naald;
int begin = naald.size();

std::vector<int> prefix(naald.length());
int j = prefix[0] = 0;
for(int i = 1; i < naald.length(); i++){
    while( j > 0 && naald[i] != naald[j] )
        j = prefix[j-1];
    if( naald[i] == naald[j] )
        j++;
    prefix[i] = j;
}

j = 0;
for(int i = begin; i < hooiberg.length(); i++){
    while( j > 0 && naald[j] != hooiberg[i] )
        j = prefix[j-1];
    if( hooiberg[i] == naald[j] )
        j++;
    if( j == naald.length() )
        resultaat.push( &hooiberg[ i - 2 * m ] );
}
```
