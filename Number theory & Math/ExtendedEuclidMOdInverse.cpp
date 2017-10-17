/*
Implementation of extended euclid algorithm.
Modular inverse requires gcd(a, n) = 1.
*/

class Euclid {
public:
    i64 x, y, d;
    Euclid() {}
    Euclid(i64 _x, i64 _y, i64 _d) : x(_x), y(_y), d(_d) {}
};

Euclid egcd(i64 a, i64 b) {
    if(!b) return Euclid(1, 0, a);
    Euclid r = egcd(b, a % b);
    return Euclid(r.y, r.x - a / b * r.y, r.d);
}

i64 modinv(i64 a, i64 n) {
    Euclid t = egcd(a, n);
    if(t.d > 1) return 0;
    i64 r = t.x % n;
    return (r < 0 ? r + n : r);
}
