void precalc() {
  arr[0] = 0 ;
  arr[1] = 1 ;
  for( int i = 2 ; i < 1000000 ; i++ ) {
    arr[i] = arr[i-1]+ (1/double(i)) ;
  }
}
#define gamma 0.57721566490153286060651209008240243104215933593992
double Hn( double N ) {
  if( N < 1000000 ) {
    return arr[int(N)];
  } else return (log(double(N))+log(double(N+1)))/2 + gamma ; ;
}


---------------------------------
long long H( int n ) {
    long long res = 0;
    for( int i = 1; i <= n; i++ )
        res = res + n / i;
    return res;
}


long long a ;
scanf("%lld",&a ) ;
long long ans = 0 ;
long long LIM = sqrt( a ) ;
for( int i = 1 ; i <= LIM ; i++ ) {
  ans += a/i ;
}
printf("Case %d: %lld\n",caseno++ , (ans<<1) - LIM*LIM ) ;
