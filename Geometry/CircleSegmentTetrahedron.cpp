/*
This code assumes the circle center and radius to be integer.
Change this when necessary.
*/

inline double commonArea(const Circle &a, const Circle &b) {
    int dsq = sqDist(a.c, b.c);
    double d = sqrt((double)dsq);
    if(sq(a.r + b.r) <= dsq) return 0;
    if(a.r >= b.r && sq(a.r-b.r) >= dsq) return pi * b.r * b.r;
    if(a.r <= b.r && sq(b.r-a.r) >= dsq) return pi * a.r * a.r;
    double angleA = 2.0 * acos((a.r * a.r + dsq - b.r * b.r) / (2.0 * a.r * d));
    double angleB = 2.0 * acos((b.r * b.r + dsq - a.r * a.r) / (2.0 * b.r * d));
    return 0.5 * (a.r * a.r * (angleA - sin(angleA)) + b.r * b.r * (angleB - sin(angleB)));
}


/*
Segment intersection in 2D integer space.
P1, p2 makes first segment, p3, p4 makes the second segment
*/

inline bool intersect(const Point &p1, const Point &p2, const Point &p3, const Point &p4) {
    i64 d1, d2, d3, d4;
    d1 = direction(p3, p4, p1);
    d2 = direction(p3, p4, p2);
    d3 = direction(p1, p2, p3);
    d4 = direction(p1, p2, p4);
    if(((d1 < 0 && d2 > 0) || (d1 > 0 && d2 < 0)) && ((d3 < 0 && d4 > 0) || (d3 > 0 && d4 < 0))) return true;
    if(!d3 && onsegment(p1, p2, p3)) return true;
    if(!d4 && onsegment(p1, p2, p4)) return true;
    if(!d1 && onsegment(p3, p4, p1)) return true;
    if(!d2 && onsegment(p3, p4, p2)) return true;
    return false;
}


/*
Some tetrahedron formulas
*/

inline double volume(double u, double v, double w, double U, double V, double W) {
    double u1,v1,w1;
    u1 = v * v + w * w - U * U;
    v1 = w * w + u * u - V * V;
    w1 = u * u + v * v - W * W;
    return sqrt(4.0*u*u*v*v*w*w - u*u*u1*u1 - v*v*v1*v1 - w*w*w1*w1 + u1*v1*w1) / 12.0;
}

inline double surface(double a, double b, double c) {
    return sqrt((a + b + c) * (-a + b + c) * (a - b + c) * (a + b - c)) / 4.0;
}

inline double insphere(double WX, double WY, double WZ, double XY, double XZ, double YZ) {
    double sur, rad;
    sur = surface(WX, WY, XY) + surface(WX, XZ, WZ) + surface(WY, YZ, WZ) + surface(XY, XZ, YZ);
    rad = volume(WX, WY, WZ, YZ, XZ, XY) * 3.0 / sur;
    return rad;
}


//1.angle of a regular polygon if is T then total arm n = 360/(180-T) where n is integer.

