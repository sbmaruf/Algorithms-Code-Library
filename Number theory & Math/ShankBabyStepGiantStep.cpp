/*
Shanks baby step giant step - discrete logarithm algorithm
for the equation: b = a^x % p where a, b, p known, finds x
works only when p is an odd prime
*/

int shank(int a, int b, int p) {
    int i, j, m;
    long long c, aj, ami;
    map< long long, int > M;
    map< long long, int > :: iterator it;
    m = (int)ceil(sqrt((double)(p)));
    M.insert(make_pair(1, 0));
    for(j = 1, aj = 1; j < m; j++) {
        aj = (aj * a) % p;
        M.insert(make_pair(aj, j));
    }
    ami = modexp(modinv(a, p), m, p);
    for(c = b, i = 0; i < m; i++) {
        it = M.find(c);
        if(it != M.end()) return i * m + it->second;
        c = (c * ami) % p;
    }
    return 0;
}
