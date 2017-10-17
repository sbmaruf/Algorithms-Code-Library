void precalc() {
    for(int i = 1 ; i <= 1000 ; i++) {
        nCr[i][0]=1;
        nCr[i][1]=i;
        for(int j = 2 ; j <= i ; j++ ) {
            nCr[i][j] = ( nCr[i-1][j-1] + nCr[i-1][j] ) % MOD;
        }
    }
}
long long Pow(long long n , long long k) {
    long long ret = 1;
    while( k ) {
        if( k&1 ) {
            ret *= n;
            ret %= MOD;
        }
        n *= n;
        n %= MOD;
        k >>= 1;
    }
    return ret;
}
