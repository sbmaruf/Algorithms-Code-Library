/*
Generates primes within interval [a, b] when b - a <= 100000
and 1 <= a <= b <= 2147483647
*/
int base[MAX>>6], segment[RNG>>6], primes[LEN], prlen;

#define chkC(x,n) (x[n>>6]&(1<<((n>>1)&31)))
#define setC(x,n) (x[n>>6]|=(1<<((n>>1)&31)))

void sieve() {
    int i, j, k;
    for(i=3; i<LMT; i+=2) if(!chkC(base, i)) for(j=i*i, k=i<<1; j<MAX; j+=k) setC(base, j);
    for(i=3, prlen=0; i<MAX; i+=2) if(!chkC(base, i)) primes[prlen++] = i;
}

int segmented_sieve(int a, int b) {
    int rt, i, k, cnt = (a<=2 && 2<=b)? 1 : 0;
    if(b<2) return 0;
    if(a<3) a = 3;
    if(a%2==0) a++;
    memset(segment, 0, sizeof segment);
    for(i=0, rt=(int)sqrt((double)b); i < prlen && primes[i] <= rt; i++) {
        unsigned j = primes[i] * ( (a+primes[i]-1) / primes[i] );
        if(j%2==0) j += primes[i];
        for(k=primes[i]<<1; j<=b; j+=k) if(j!=primes[i]) setC(segment, (j-a));
    }
    for(i=0; i<=b-a; i+=2) if(!chkC(segment, i)) cnt++;
    return cnt;
}
