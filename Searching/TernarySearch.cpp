#include<bits/stdc++.h>
using namespace std ;
#define x first
#define y second
pair<double,double> p[4] ;

double dist( pair<double,double> a ,pair<double,double> b ){
    return ( (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) ) ;
}
double Dist( pair<double,double> a ,pair<double,double> b ){
    return sqrt( (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) ) ;
}
double ternary_search(){
    pair<double , double > P[4] ;
    for( int i = 0 ; i < 40 ; i++ ){

        P[0].x = (2*p[0].x+p[1].x)/3.0 ;
        P[0].y = (2*p[0].y+p[1].y)/3.0 ;

        P[1].x = (p[0].x+2*p[1].x)/3.0 ;
        P[1].y = (p[0].y+2*p[1].y)/3.0 ;

        P[2].x = (2*p[2].x+p[3].x)/3.0 ;
        P[2].y = (2*p[2].y+p[3].y)/3.0 ;

        P[3].x = (p[2].x+2*p[3].x)/3.0 ;
        P[3].y = (p[2].y+2*p[3].y)/3.0 ;

        //cout << P[0].x << " " << P[0].y <<" " <<  P[1].x << " " << P[1].y  <<" " <<  P[2].x << " " << P[2].y  <<" " << P[3].x << " " << P[3].y  << endl;

        if( dist( P[0] , P[2] ) > dist( P[1] , P[3] ) ){
            p[0] = P[0] ;
            p[2] = P[2] ;
        }else {
            p[1] = P[1] ;
            p[3] = P[3] ;
        }

    }
    return min(Dist(p[0],p[2]),Dist(p[1],p[3])) ;
}

int main(){

    int cases , caseno=1 ;
    scanf("%d",&cases ) ;
    while( cases-- ){
        scanf("%lf%lf%lf%lf%lf%lf%lf%lf",&p[0].x,&p[0].y,&p[1].x,&p[1].y,&p[2].x,&p[2].y,&p[3].x,&p[3].y) ;
        printf("Case %d: %.8f\n",caseno++,ternary_search());
    }

    return 0 ;
}







#include<bits/stdc++.h>

#define x first
#define y second.first
#define z second.second

using namespace std ;

typedef pair<double,pair<double,double> > _3Dpoint ;


double dist( _3Dpoint a , _3Dpoint b )
{
    return sqrt( (a.x-b.x)* (a.x-b.x) + (a.y-b.y)* (a.y-b.y) + (a.z-b.z)* (a.z-b.z) ) ;
}

double TS(_3Dpoint point[])
{

    _3Dpoint lthird , rthird ;
    int tmp = 100 ;

    while( tmp -- ) {

        lthird.x = (2*point[0].x+point[1].x)/3.0 ;
        lthird.y = (2*point[0].y+point[1].y)/3.0 ;
        lthird.z = (2*point[0].z+point[1].z)/3.0 ;
        rthird.x = (point[0].x+2*point[1].x)/3.0 ;
        rthird.y = (point[0].y+2*point[1].y)/3.0 ;
        rthird.z = (point[0].z+2*point[1].z)/3.0 ;

        if( dist( lthird,point[2] ) > dist( rthird , point[2] ) )
            point[0] = lthird ;
        else
            point[1] = rthird ;

    }

    double ret = dist( point[0] , point[2] ) ;
    return ret ;
}

int main()
{

    int T ;
    scanf("%d",&T) ;

    for( int i = 0; i < T ; i++ ) {
        _3Dpoint point[3] ;
        scanf("%lf%lf%lf%lf%lf%lf%lf%lf%lf",&point[0].x,&point[0].y,&point[0].z,&point[1].x,&point[1].y,&point[1].z,&point[2].x,&point[2].y,&point[2].z) ;
        double ans = TS(point) ;
        printf("Case %d: %.10f\n", i+1 , ans );
    }

    return 0 ;
}

