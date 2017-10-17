/*
1. Assign hull.n
2. Take input in hull.point
3. Call convexSort()
4. Call findHull()
5. Convex Hull is ready in hull.convex with hull.m points in it.
*/

pll g;

vlong triArea  ( pll a, pll b, pll c ) {
    vlong area = a.ff * b.ss + b.ff * c.ss + c.ff * a.ss;
    area -= a.ff * c.ss + b.ff * a.ss + c.ff * b.ss;
    return area;
}

vlong sqDist ( pll a, pll b ) {
    return ( SQ(a.ff-b.ff) + SQ(a.ss-b.ss ) );
}

bool convexCompare ( const pll &a, const pll &b ) {
    vlong area = triArea ( g, a, b );
    if ( area > 0 ) return true;
    else if ( area == 0 && sqDist ( g, a ) < sqDist ( g, b ) ) return true;
    else return false;
}

struct ConvexHull {
    int n, m;
    pll point[PPP], convex[PPP];

    void convexSort() {
        g = point[0];
        FOR(i,0,n-1) {
            if ( point[i].ff < g.ff ) g = point[i];
            else if ( point[i].ff == g.ff && point[i].ss < g.ss ) g = point[i];
        }
        sort ( point, point + n, convexCompare );
    }
    void findHull() {
        if ( n == 1 ) {
            convex[0] = convex[1] = point[0];
            m = 1;
            return;
        }
        convex[0] = point[n-1]; convex[1] = point[0]; convex[2] = point[1];
        int cur = 3;
        for ( int i = 2; i < n; i++ ) {
            vlong area = triArea ( convex[cur-2], convex[cur-1], point[i] );
            if ( area > 0 ) {
                convex[cur] = point[i];
                cur++;
            }
            else if ( area == 0 ) { ///Take action depending on what is required
                /*Left Vertical Line gets omitted. Manually handle it*/
                /*convex[cur] = point[i];
                cur++;*/
                ///If extra point needs to be removed
                convex[cur-1] = point[i];
            }
            else {
                cur--;
                i--;
            }
        }
        m = cur - 1;
    }

}hull;

