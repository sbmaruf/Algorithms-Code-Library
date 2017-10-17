#include<bits/stdc++.h>
using namespace std ;

int N , R , P ;
int U[9900+1] , V[9900+1] , C[9900+1] , D[101] ;

int main() {

    int cases , caseno = 1 ;
    //scanf("%d",&cases ) ;
    cases = readInt() ;

    while( cases -- ) {

        //scanf("%d%d%d",&N,&R,&P) ;
        N = readInt() ;
        R = readInt() ;
        P = readInt() ;
        for( int i = 0 ;i < R ; i++ ){
            int e ;
            //scanf("%d%d%d%d" , &U[i],&V[i],&C[i],&e) ;
            U[i] = readInt() ;
            V[i] = readInt() ;
            C[i] = readInt() ;
            e = readInt() ;
            C[i] = P*e-C[i] ;
        }
        memset( D , (1<<30) , sizeof D ) ;
        D[0] = 0 ;
        bool isCycle = 0 ;
        for( int i = 0 ; i < N ; i++ ){
            bool brk = 0 ;
            for( int j = 0 ; j < R ; j++ ){
                int u = U[j] ;
                int v = V[j] ;
                if( D[u] + C[j] < D[v] ){
                    brk = 1 ;
                    if( i == (N-1) )isCycle =1 ;
                    else D[v] = D[u] + C[j] ;
                }
            }
            if( !brk ) break ;
        }

        if( isCycle )cout << "Case " << caseno++ << ": YES\n" ;
        else cout << "Case " << caseno++ << ": NO\n" ;
    }

    return 0;
}
