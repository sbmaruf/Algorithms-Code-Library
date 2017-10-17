pair<double , double> Rotate_Point( pair<double,double> P ,pair<double,double> Ref ,double dist, double cosA ,double sinA ){

    //if only theta comes then sinA= sin(theta) , conA = cos( theta ) ;
    double a = sqrt( (P.first-Ref.first)*(P.first-Ref.first) + (P.second-Ref.second)*(P.second-Ref.second) ) ;

    double x1 = (dist*(Ref.first-P.first))/a ;
    double y1 = (dist*(Ref.second-P.second))/a ;

    pair<double,double> ret ;
    ret.first = x1*cosA-y1*sinA+P.first ;
    ret.second = x1*sinA+y1*cosA+P.second ;

    return ret ;

}
