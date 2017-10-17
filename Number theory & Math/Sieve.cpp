#define MAX 10000000
unsigned flag[MAX/64];
vector<long long>prime ;

#define chkC(n) (flag[n>>6]&(1<<((n>>1)&31)))
#define setC(n) (flag[n>>6]|=(1<<((n>>1)&31)))
int lim;
void sieve() {
    unsigned i, j, k;
    flag[0]|=0;
    int sqrtN = sqrt(MAX) ;
    for(i=3; i<= sqrtN ; i+=2)
        if(!chkC(i))
            for(j=i*i,k=i<<1; j<MAX; j+=k)
                setC(j);
    prime.push_back(2);

    for(i=3; i<MAX; i+=2)
        if(!chkC(i))
            prime.push_back(i) ;
    lim = prime.size() ;
}
