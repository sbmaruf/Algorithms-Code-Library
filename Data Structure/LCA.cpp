//LCA using sparse table
//Complexity: O(NlgN,lgN)
#define EX 100002
int L[EX]; 
int P[EX][22];
int T[EX]; 
vector<int>g[EX];
void dfs(int from,int u,int dep)
{
    T[u]=from;
    L[u]=dep;
    for(int i=0;i<(int)g[u].size();i++)
    {
        int v=g[u][i];
        if(v==from) continue;
        dfs(u,v,dep+1);
    }
}

int lca_query(int N, int p, int q) 
  {
      int tmp, log, i;

      if (L[p] < L[q])
          tmp = p, p = q, q = tmp;

        log=1;
      while(1) {
        int next=log+1;
        if((1<<next)>L[p])break;
        log++;

      }

        for (i = log; i >= 0; i--)
          if (L[p] - (1 << i) >= L[q])
              p = P[p][i];

      if (p == q)
          return p;

        for (i = log; i >= 0; i--)
          if (P[p][i] != -1 && P[p][i] != P[q][i])
              p = P[p][i], q = P[q][i];

      return T[p];
  }

void lca_init(int N)
  {
      memset (P,-1,sizeof(P)); 
      int i, j;
       for (i = 0; i < N; i++)
          P[i][0] = T[i];

      for (j = 1; 1 << j < N; j++)
         for (i = 0; i < N; i++)
             if (P[i][j - 1] != -1)
                 P[i][j] = P[P[i][j - 1]][j - 1];
 }

int main(void) {
	g[0].pb(1);
	g[0].pb(2);
	g[2].pb(3);
	g[2].pb(4);
	dfs(0, 0, 0);
	lca_init(5);
	printf( "%d\n", lca_query(5,3,4) );
	return 0;
}





























//EX extra node
int EX[NODES][LGNODES] , ST[NODES][LGNODES] ;
int L[NODES] ;
void dfs(int u , int bc , int level , int EX ) {
  EX[u][0] = EX , ST[u][0]=bc , L[u] = level;
  for( int i = (int)G[u].size()-1 ; i >= 0 ; i-- ) {
    int v = G[u][i].u ;
    if( v == bc ) continue ;
    dfs( v , u , level+1 , G[u][i].w ) ;
  }
}
void preProcessLCA() {
  memset( ST , -1 , sizeof ST ) ;
  memset( EX , 0 , sizeof EX ) ;
  dfs(1,-1,0,0) ;
  for( int j = 1 ; (1<<j) <= N ; j++ ) {
    for( int i = 1 ; i <= N ; i++ ) {
      if( ST[i][j - 1] != -1 ) {
        EX[i][j] = max( EX[i][j - 1] , EX[ST[i][j - 1]][j - 1] ) ;
        ST[i][j] = ST[ST[i][j - 1]][j - 1] ;
      }
    }
  }
}

int queryLCA(int s , int t) {
  if( L[s] < L[t] ) swap( s , t ) ;
  int ret = -1 ;
  for( int i = 19 ; i >= 0 ; i-- ) {
    if( (L[s] - (1<<i)) >= L[t] ) {
      ret = max( ret , EX[s][i] ) ;
      s = ST[s][i] ;
    }
  }

  if( s == t ) return ret ;
  for( int i = 19 ; i >= 0 ; i-- ) {
    if( ST[s][i] != -1 ) {
      if( ST[s][i] != ST[t][i] ) {
        ret = max( ret , EX[s][i] );
        s = ST[s][i] ;
        ret = max( ret , EX[t][i] );
        t = ST[t][i] ;
      }
    }
  }
  ret = max( ret , EX[s][0] ) ;
  ret = max( ret , EX[t][0] ) ;
  return ret ;
}
