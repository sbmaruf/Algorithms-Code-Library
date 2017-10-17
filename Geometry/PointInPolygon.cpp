/*
C[] array of points of convex polygon in ccw order,
nc number of points in C, p target points.
returns true if p is inside C (including edge) or false otherwise.
complexity O(lg n)
*/

inline bool inConvexPoly(point *C, int nc, const point &p) {
    int st = 1, en = nc - 1, mid;
    while(en - st > 1) {
        mid = (st + en)>>1;
        if(triArea2(C[0], C[mid], p) < 0) en = mid;
        else st = mid;
    }
    if(triArea2(C[0], C[st], p) < 0) return false;
    if(triArea2(C[st], C[en], p) < 0) return false;
    if(triArea2(C[en], C[0], p) < 0) return false;
    return true;
}




int crossproduct(pair<int,int> a , pair<int,int> b , pair<int,int>p ){
    return ((a.x-p.x)*(b.y-p.y)-(a.y-p.y)*(b.x-p.x)) ;
}

bool isInsidePolygon( pair<int,int> P[] , pair<int,int> sample , int n ){

    int cnt = 0 ;
    bool f = 0 ;
    for( int i = 0 , j = n-1 ; i < n ; j = i++ ){

        int Xmin = min( P[i].x,P[j].x ) ;
        int Xmax = max( P[i].x,P[j].x ) ;

        int Ymin = min( P[i].y,P[j].y ) ;
        int Ymax = ma
        x( P[i].y,P[j].y ) ;

        if( Xmin <= sample.x && sample.x <= Xmax && Ymin <= sample.y && sample.y <= Ymax){
            if( crossproduct( P[i] , P[j] , sample ) == 0 )return true ;
        }
        if( crossproduct( P[i] , P[j] , sample ) < 0 ){
            swap( P[i],P[j] ) ;
            f = 1 ;
        }

        if( P[i].y >= sample.y && P[j].y < sample.y )cnt++ ;
        if( f == 1 ){
            f = 0 ;
            swap( P[i],P[j] ) ;
        }
    }
    return ( cnt & 1 ) ;

}


/*
P[] holds the points, must be either in cw or ccw
function returns double of the area.
*/

inline int dArea(int np) {
    int area = 0;
    for(int i = 0; i < np; i++) {
        area += p[i].x*p[i+1].y - p[i].y*p[i+1].x;
    }
    return abs(area);
}
