
#include<bits/stdc++.h>
#define rep(i,n) for( int i = 0 ; i < n ; i++ )
#define x first
#define y second
#define eps 1e-9
using namespace std ;


#define MAXD 2
#define FOR(i,b,c) for(int i = b ; i < c ; i++ )
#define eps 1e-9
#define pi acos(-1.0)
double mx = numeric_limits<double>::max()-1 ;
struct Vec {

  int d; //Dimension
  double val[MAXD];//Contains value of each component
  Vec() {
    d=2;
  }
  Vec( double a , double b ,double c ) {
    val[0] = a ;
    val[1] = b ;
    val[2] = c ;
    d = 3 ;
  }
  Vec( double a , double b ) {
    val[0] = a ;
    val[1] = b ;
    d = 2 ;
  }
  Vec add ( Vec b ) {
    Vec res;
    FOR(i,0,d) res.val[i] = val[i] + b.val[i];
    return res;
  }
  Vec sub ( Vec b ) {
    Vec res;
    FOR(i,0,d) res.val[i] = val[i] - b.val[i];
    return res;
  }
  Vec mul ( double t ) {
    Vec res;
    FOR(i,0,d)res.val[i] = val[i] * t;
    return res;
  }
  Vec div ( double t ) {
    Vec res;
    FOR(i,0,d) res.val[i] = val[i] / t;
    return res;
  }
  bool operator == ( Vec b ) {
    FOR(i,0,d) if ( fabs ( val[i] - b.val[i] ) > eps ) return false;
    return true;
  }
  Vec perp2D() {
    Vec res = (*this);
    swap ( res.val[0], res.val[1] );
    res.val[0] *= -1;
    return res;
  }
  double dot ( Vec v ) { //Finds *this (dot) v
    double res = 0;
    d = 2 ;
    for ( int i = 0; i < d; i++ ) res += val[i] * v.val[i];
    return res;
  }
  double length () { //Finds length of current Vec
    return sqrt ( this->dot( *this ) );
  }
  Vec unitVec () {
    return (*this).div ( length() ); // v / ||v||
  }
  double angleBetween ( Vec b ) { //Angle between two Vecs
    double res = dot( b ) / ( length() * b.length() );
    if ( res > 1 ) res = 1;
    if ( res < -1 ) res = -1;
    return acos (res);
  }
  double polarAngle2D() { //Angle from x-axis
    double res = atan2 ( val[1], val[0] );
    if ( res + eps < 0 ) res += 2 * pi;
    return res;
  }
  double dist( Vec a ) {
    if( a.d != d )cout << "Wrong dimension to calculate in sqdist function\n" ;
    double ret = 0 ;
    for( int i = 0 ; i < d ; i++ ) {
      ret += ( val[i] - a.val[i] )*( val[i] - a.val[i] ) ;
    }
    return sqrt(ret) ;
  }
  double sqdist( Vec a ) {
    if( a.d != d )cout << "Wrong dimension to calculate in sqdist function\n" ;
    double ret = 0 ;
    for( int i = 0 ; i < d ; i++ ) {
      ret += ( val[i] - a.val[i] )*( val[i] - a.val[i] ) ;
    }
    return (ret) ;
  }
  double cross2D ( Vec v ) { //Cross the two values. Only for 2D. Z compo 0.
    return val[0]*v.val[1] - val[1]*v.val[0];
  }
  double isLeft( Vec st , Vec en ) {
    return ( (en.val[0] - st.val[0])*(val[1] - st.val[1])
             - (val[0] - st.val[0])*(en.val[1] - st.val[1]) ) ; ;
  }
};

struct Line {
  Vec a, b; //a is displacement, b is direction.
  //Builds a Line from two points
  Line() {}
  Line( Vec x, Vec y ) {
    a = x;
    b = y.sub ( x );
  }
  Line( Vec x, Vec y , bool p ) {
    a = x;
    b = y;
    //assign a direction vector
  }
  Line LineFromPoints ( Vec x, Vec y ) {
    Line m;
    m.a = x;
    m.b = y.sub ( x );
    return m;
  }
  //Finds point on Line, given t.
  double length() {
    return b.length();
  }
  Vec atPos ( double t ) {
    return a.add ( b.mul ( t ) ); // a + tb;
  }
  double calT( Vec pt ) {
    double d1 = a.dist( pt ) ;
    double d2 = sqrt(b.val[0]*b.val[0]+b.val[1]*b.val[1]) ;
    Vec q = Vec(a.val[0]+b.val[0],a.val[1]+b.val[1]) ;

    double s1 = q.isLeft( Vec(0,0) , a );
    double s2 = pt.isLeft(Vec(0,0) , a ) ;
    double mul = 1 ;
    if( s1 >= 0 && s2 < 0 )mul = -1 ;
    if( s1 < 0 && s2 >= 0 )mul = -1 ;

    return mul*d1/d2 ;
  }
  double LineToPointDistance ( Vec p, double t ) {
    p = p.sub ( a ); //Take it to origin
    t = b.dot ( p ) / ( b.length() * b.length() ); //point of intersection
    Vec x = b.mul ( t ); //tb
    return ( p.sub(x).length() ); //xp length()
  }
  double segmentToPointDistance ( Vec p, double &t ) {
    p = p.sub ( a ); //Take it to origin
    t = b.dot ( p ) / ( b.length() * b.length() );
    if ( t + eps < 0 || t > 1 + eps ) { //Not on segment
      return min ( p.length(), p.sub(b).length() );
    }
    Vec x = b.mul ( t ); //tb
    return ( p.sub(x).length() ); //xp length()
  }
  bool overlapParallel ( Line l ) {
    double p, q, r, s;
    if ( b.val[0] == 0 ) {
      p = a.val[1];
      q = atPos(1).val[1];
      r = l.a.val[1];
      s = l.atPos ( 1 ).val[1];
      if ( min ( r, s ) > max ( p, q ) ) return false;
      if ( max ( r, s ) < min ( p, q ) ) return false;
      return true;
    } else {
      p = a.val[0];
      q = atPos(1).val[0];
      r = l.a.val[0];
      s = l.atPos ( 1 ).val[0];
      if ( min ( r, s ) > max ( p, q ) ) return false;
      if ( max ( r, s ) < min ( p, q ) ) return false;
      return true;
    }
  }
  char LineAndLineIntersection2D ( Line l, double &t, double &s ) {
    if ( b.cross2D ( l.b) == 0 ) {
      if ( l.a.sub(a).cross2D(l.b) == 0 ) {
        if ( overlapParallel ( l ) ) return 'o'; //overlaps
        else return 'p'; //parallel
      } else return 'd'; //disjoint and parallel
    }
    Vec w = a.sub ( l.a );
    Vec p = l.b.perp2D(), z = b.perp2D();
    t = -(w.dot(p))/p.dot(b); //for current Line
    s = w.dot(z)/z.dot(l.b); //for Line l
    return 'i';
  }
  double LineAndLineDistance2D ( Line l ) {
    double t, s; //First check if the intersect
    char r = LineAndLineIntersection2D ( l, t, s );
    if ( r == 'i' ) return 0; //Intersects. 0 distance.
    //Parallel Lines
    return LineToPointDistance ( l.a, t );
  }
  double LineAndSegmentDistance2D ( Line l ) {
    double t, s;
    char r = LineAndLineIntersection2D ( l, t, s );
    if ( r == 'i' && s + eps > 0 && s < 1 + eps ) {
      return 0; //Valid intersection
    }
    double res = LineToPointDistance ( l.a, t );
    res = min ( res, LineToPointDistance ( l.a.add(l.b), t ) );
    return res;
  }
  double segmentAndSegmentDistance2D ( Line l ) {
    double t, s;
    char r = LineAndLineIntersection2D ( l, t, s );
    if ( r =='i' && t+eps > 0 && t < 1 + eps && s + eps > 0 && s < 1 + eps ) {
      return 0; //Valid intersection
    }
    double res = segmentToPointDistance ( l.a, t );
    res = min ( res, segmentToPointDistance ( l.a.add(l.b), t ) );
    res = min ( res, l.segmentToPointDistance ( a, t ) );
    res = min ( res, l.segmentToPointDistance ( a.add ( b ), t ) );
    return res;
  }
  Line reflect ( Vec p, Vec norm ) {
    Vec ap = p.sub ( a ); //Starting to Point of Reflection
    norm = norm.unitVec();

    double d = fabs ( ap.dot ( norm ) );

    Vec m = p.add ( norm.mul ( d ) );
    Vec h = m.sub ( a ).mul ( 2 );
    m = a.add ( h );

    Line ray = ray.LineFromPoints ( p, m );
    return ray;
  }
};

vector< Vec > V ;

pair<Vec,Vec> getcenter( Vec V1 , Vec V2 , double R ) {
  if( (V1.dist(V2)/2.0) > (R+eps)) return {Vec(mx,mx),Vec(mx,mx)} ;
  Vec dr = V2.sub(V1) ;
  dr = dr.unitVec() ;
  swap( dr.val[0] , dr.val[1] ) ;
  dr.val[0] = -dr.val[0] ;
  Vec pt = V1.add(V2).div(2) ;
  double t = sqrt(R*R-V1.sqdist(V2)/4) ;
  Vec ret1 = pt.add(dr.mul(t)) ;
  Vec ret2 = pt.sub(dr.mul(t)) ;
  return {ret1,ret2} ;

}
