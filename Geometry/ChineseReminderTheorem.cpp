#include<stdio.h>
#include <utility>
using namespace std ;

long long Extendex_GCD( long long a , long long b ) {
    long long x = 0 , y = 1 , g = b ;
    long long  m, n, q, r;
    for (long long  u=1, v=0; a != 0; g=a, a=r) {
        q = g / a;
        r = g % a;
        m = x-u*q;
        n = y-v*q;
        x=u;
        y=v;
        u=m;
        v=n;
    }
    return y;

}


long long CRT(pair<long long int,long long int> arr[] , int n ) {
    long long int N = 1  ;
    for( int i = 0 ;  i < n ; i++ ) {
        N*=arr[i].first ;
    }
    long long ans = 0 ;
    for( int i = 0 ; i < n ; i++ ) {
        long long b = Extendex_GCD( arr[i].first , N/arr[i].first );
        ans+=arr[i].second*b*(N/arr[i].first) ;
        ans%=N ;
    }
    if( ans < 0 )ans += N ;
    return ans ;

}

int main() {

   // freopen( "in" , "r" , stdin ) ;
    int cases , caseno = 1 ;
    scanf("%d",&cases )  ;

    while( cases -- ) {

        int n ;
        scanf("%d" , &n) ;
        pair<long long int,long long int> arr[n] ;

        for( int i = 0 ; i < n ; i++ ) {
            scanf("%lld%lld",&arr[i].first , &arr[i].second ) ;
        }

        printf("Case %d: %lld\n",caseno++,CRT(arr , n )) ;

    }

}
