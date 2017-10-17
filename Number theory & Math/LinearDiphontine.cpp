typedef long long Long;

void Egcd( Long a, Long b, Long &x, Long &y, Long &g ){
    if( !b ) x = 1,y = 0,g = a;
    else{
        Long x1,y1;
        Egcd( b,a%b,x1,y1,g );
        x = y1;
        y = x1 - a/b*y1;
    }
}

Long MyFloor( Long a, Long b ) {
        Long c = a / b;
        if( (a%b) and a<0 ) c--;
        return c;
}

Long Solve( Long a, Long b, Long c, Long x1, Long x2, Long y1, Long y2 ){
    Long x,y,g;

        if( a < 0 ) a *= -1, x1 *= -1, x2 *= -1, swap(x1, x2);
        if( b < 0 ) b *= -1, y1 *= -1, y2 *= -1, swap(y1, y2);

        if( !a and !b ) return !c ? ( x2-x1+1 )*( y2-y1+1 ) : 0;
        if( b==0 ){
                if( c%a ) return 0;
                x = c/a;
                return ( x>=x1 and x<=x2)*( y2-y1+1 );
        }
        if( a==0 ) {
                if( c%b ) return 0;
                y = c/b;
                return ( y>=y1 and y<=y2 )*( x2-x1+1 );
        }

        Egcd( a,b,x,y,g );
        if( c%g ) return 0;

        a /= g; b /= g; c /= g; g = 1;
        x = x*c; y = y*c;

        Long n2 = min( MyFloor( x-x1, b ), MyFloor( y2-y, a ) );
        Long n1 = -min( MyFloor( y-y1, a ), MyFloor( x2-x, b ) );
        return ( n2<n1 ) ? 0 : n2-n1+1;
}
