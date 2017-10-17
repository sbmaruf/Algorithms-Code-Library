#include<bits/stdc++.h>
using namespace std ;
#define rep(i,n) for( int i = 0 ;i < n ; i++ )
int Temp[101] ;
int n , p;
inline int readInt()
{
    int ip = getchar_unlocked(), ret = 0, flag = 1;

    for(; ip < 48 || ip > 57; ip = getchar_unlocked())
    {
        if(ip == 45)
        {
            flag = -1;
            ip = getchar_unlocked();
            break;
        }
    }

    for(; ip > 47 && ip < 58; ip = getchar_unlocked())
        ret = ret * 10 + ip - 48 ;
    return flag * ret;
}

int main() {

    int cases , caseno = 1;
    scanf("%d",&cases ) ;

    while( cases -- ) {

        //scanf("%d",&n) ;
        n = readInt() ;
        vector<deque<int> > Can ;
        int Com[n][n] ;
        for( int i = 1 ; i <= n ; i++ ) {
            deque<int>d ;
            for( int j = 1; j <= n ; j++ ) {
                //scanf("%d",&p) ;
                p = readInt() ;
                d.push_back(p-n-1) ;
            }
            Can.push_back(d) ;
        }
        for( int i = 0 ; i  < n ; i++ ) {
            for( int j = 0; j < n ; j++ ) {
                //scanf("%d",&p) ;
                p = readInt() ;
                Com[i][p-1] = j ;
            }
        }
        int cnt = 0 ;

        do {
            memset( Temp , -1 , sizeof Temp ) ;
            cnt = 0  ;
            for( int i = 0 ; i < n ; i++ ) {
                int q = Can[i][0] ;
                if( Temp[q] == -1 )Temp[q] = i,cnt++ ;
                else {
                    int p = Temp[q] ;
                    if( Com[q][i] < Com[q][p] ) {
                        Temp[q] = i ;
                        Can[p].pop_front() ;
                    } else {
                        Temp[q] = p ;
                        Can[i].pop_front() ;
                    }
                }
            }
        } while( cnt != n ) ;
        cout << "Case " << caseno++ << ":" ;
        for(int i = 0 ; i  < n ; i++ ) {
            cout << " (" << Temp[i]+1 << " " << i+n+1 << ")" ;
        }
        cout << "\n";
    }

}
