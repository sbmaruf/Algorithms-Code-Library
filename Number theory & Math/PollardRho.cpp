#include<bits/stdc++.h>
using namespace std;
#define LL long long
/*
This is not my code . I collect It from net. use it. save it as
a pollard rho in my library. Use as a API for problem solving.
http://www.csie.ntnu.edu.tw/~u91029/Prime.html
*/

int p[5500], pt = 0;
void sieve() {
    int mark[46340] = {};
    int i, j;
    for(i = 2; i < 46340; i++) {
        if(mark[i] == 0) {
            p[pt++] = i;
            for(j = i+i; j < 46340; j += i)
                mark[j] = 1;
        }
    }
}
LL modmultiply(LL a,LL b,LL c) {
    LL x = 0,y = a%c;
    while(b > 0) {
        if(b%2 == 1) {
            x = (x+y)%c;
        }
        y = (y*2)%c;
        b /= 2;
    }
    return x%c;
}
LL modpow(LL x, LL y, LL mod) {
    LL ret = 1;// ret = x^y%mod;
    while(y) {
        if(y&1)
            //ret = (ret*x)%mod;
            ret = modmultiply(ret, x, mod);
        //x = (x*x)%mod;
        x = modmultiply(x, x, mod);
        y >>= 1;
    }
    return ret;
}
int isprime(LL n) {
    if(n == 2 || n == 3)
        return 1;
    if(n < 2 || (n&1) == 0)
        return 0;
    int i, a;
    for(i = 0; i < 5; i++) {
        a = rand()%(n-4)+2;
        if(modpow(a, n-1, n) != 1)
            return 0;
    }
    return 1;
}
LL gcd(LL x, LL y)  {
    if(!x)    return y;
    if(!y)    return x;
    if(x < 0)    x = -x;
    if(y < 0)    y = -y;
    LL t;
    while(x%y)
        t = x, x = y, y = t%y;
    return y;
}
vector<LL> ret;
LL pollard_rho(LL n, LL c) {
    long long x = 2, y = 2;
    do {
        //x = (x*x+c)%n;
        x = (modmultiply(x, x, n)+c)%n;
        //y = (y*y+c)%n, y = (y*y+c)%n;
        y = (modmultiply(y, y, n)+c)%n;
        y = (modmultiply(y, y, n)+c)%n;
        LL d = gcd(x-y, n);
        if(d > 1)    return d;
    } while(true);
    return n;
}
void small_factorize(LL n) {
    int i;
    for(i = 0; i < pt && p[i]*p[i] <= n; i++) {
        if(n%p[i] == 0) {
            while(n%p[i] == 0)
                ret.push_back(p[i]), n /= p[i];
        }
    }
    if(n != 1)
        ret.push_back(n);
}
void factorize(LL n) {
    if(n == 1)    return;
    if(isprime(n)) {
        ret.push_back(n);
        return;
    }
    if(n < 1000000000) {
        small_factorize(n);
        return;
    }
    int c;
    LL d = n;
    for(c = 2; d == n; c++) {
        d = pollard_rho(n, c);
    }
    factorize(d);
    factorize(n/d);
}
int main() {
    sieve();
    int cases ;
    scanf("%d",&cases ) ;
    while( cases-- ) {
        long long n ;
        scanf("%lld", &n);
        ret.clear();
        factorize(n);
        sort(ret.begin(), ret.end());
        cout << n << " = " ;
      /*
        for( int i = 0 ; i < ret.size() ; i++ )cout << ret[i] << " " ;
        cout << "\n" ;
      */
      int cnt = 1  ;
      for( int i = 1 ; i < ret.size() ; i++ ){
        if( ret[i] == ret[i-1] )cnt ++ ;
        else {
          cout << ret[i-1] ;
          if( cnt > 1 ){
            cout << "^" << cnt ;
          }
          cout << " * " ;
          cnt = 1 ;
        }
      }
      cout << ret[ret.size()-1] ;
      if( cnt > 1 )cout << "^" << cnt ;
      cout << "\n" ;

    }
    return 0;
}
