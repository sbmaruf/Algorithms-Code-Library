#include<bits/stdc++.h>
using namespace std;
inline int readInt() {
  int ip = getchar_unlocked(), ret = 0, flag = 1;
  for(; ip < 48 || ip > 57; ip = getchar_unlocked()) {
    if(ip == 45) {
      flag = -1;
      ip = getchar_unlocked();
      break;
    }
  }
  for(; ip > 47 && ip < 58; ip = getchar_unlocked())
    ret = ret * 10 + ip - 48 ;
  return flag * ret;
}
#define MAX 100000+5
#define LGMAX 18
int ST[MAX][LGMAX];

void rmq( int n ){
  for( int j = 1 ; 1<<j <= n ; j++ ){
    for( int i = 0 ; i+(1<<j)-1 < n ; i++ ){
      ST[i][j] = min( ST[i][j - 1] ,  ST[i+(1<<(j-1))][j - 1] ) ;
    }
  }
}


int main() {

  int cases = readInt() ;
  int caseno = 1 ;
  while( cases -- ){
    int N = readInt() ;
    int Q = readInt() ;
    for( int i = 0 ; i < N ; i++ ){
      ST[i][0] = readInt() ;
    }
    rmq(N) ;
    cout << "Scenario #" << caseno++ << ":\n" ;
    while( Q -- ){
      int x = readInt()-1 ;
      int y = readInt()-1 ;
      int lim = y-x+1 , lg = 0 ;
      while( lim ){
        lim >>= 1 ;
        lg++ ;
      }
      lg-- ;
      cout << min( ST[x][lg] , ST[y-(1<<lg)+1][lg] ) << "\n" ;
    }
  }
  return 0 ;
}
