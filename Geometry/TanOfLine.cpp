pair<int,int> TanOfLine( pair<int,int> a , pair<int,int> b )
{

    const int INF = 1<<30 ;
    pair<int,int> M ;

    if( a.y == b.y ) {
        M.x = INF ;
        M.y = INF ;
    } else {
        M.x = a.x-b.x ;
        M.y = a.y-b.y ;
        int tmp = __gcd( (M.x),(M.y) ) ;
        M.x = M.x/tmp ;
        M.y = M.y/tmp ;
    }
    return M ;
}
