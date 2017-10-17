/*
 * Algorithm : Stoer Wagner all pair Min Cut
 * Complextity : O( n^3 )
 * Note : All vertex is 1 based indexing
 */
#include<stdio.h>
#include<algorithm>
using namespace std;
#define MAX_V 1007
#define INF 777777777
long nV,nE;
long Cap[MAX_V+7][MAX_V+7];
long Dist[MAX_V+7],Done[MAX_V+7];
long Best,Ind;

long AllPairMinCut( void ) {
  long i,j,u,v,Ans = INF,N = nV;
  while( N > 1 ) {
    memset( Dist,0,sizeof(Dist));
    memset( Done,0,sizeof(Done));
    for( i=1; i<=N; i++) {
      Best = Ind = -1;
      for( j=1; j<=N; j++ ) {
        if(!Done[j] && Dist[j] > Best) {
          Best = Dist[j];
          Ind = j;
        }
      }
      if( i+1==N ) u = Ind;
      if( i==N ) {
        v = Ind;
        Ans = min( Ans,Best );
      }
      Done[Ind] = 1;
      for( j=1; j<=N; j++) {
        Dist[j] += Cap[Ind][j];
      }
    }
    if( u > v) swap( u,v);
    for( i=1; i<=N; i++ ) {
      Cap[u][i] += Cap[v][i];
      Cap[i][u] += Cap[i][v];
    }
    for( i=1; i<=N; i++) {
      Cap[v][i] = Cap[N][i];
      Cap[i][v] = Cap[i][N];
    }
    N--;
  }
  return Ans;
}

int main( void) {
  memset(Cap,0,sizeof(Cap));
  return 0;
}
