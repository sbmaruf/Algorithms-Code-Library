#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

 //algorithm of clocest pair, not my algorithm collected from WJMZBMR's code
const int N = int(1e5) + 10;
typedef long long int64;
const int64 INF = 1LL << 60;

struct Point {
	int64 x;
	int64 y;
} point[N];
int n;
int tmpt[N];

bool cmpxy(const Point& a, const Point& b) {
	if (a.x != b.x)
		return a.x < b.x;
	return a.y < b.y;
}

bool cmpy(const int& a, const int& b) {
	return point[a].y < point[b].y;
}

int64 dis2(int i, int j) {
	return (point[i].x - point[j].x) * (point[i].x - point[j].x)
			+ (point[i].y - point[j].y) * (point[i].y - point[j].y);
}

int64 sqr(int64 x) {
	return x * x;
}

int64 Closest_Pair(int left, int right) {
	int64 d = INF;
	if (left == right)
		return d;
	if (left + 1 == right)
		return dis2(left, right);
	int mid = (left + right) >> 1;
	int64 d1 = Closest_Pair(left, mid);
	int64 d2 = Closest_Pair(mid + 1, right);
	d = min(d1, d2);
	int i, j, k = 0;
	for (i = left; i <= right; i++) {
		if (sqr(point[mid].x - point[i].x) <= d)
			tmpt[k++] = i;
	}
	sort(tmpt, tmpt + k, cmpy);
	for (i = 0; i < k; i++) {
		for (j = i + 1; j < k && sqr(point[tmpt[j]].y - point[tmpt[i]].y) < d;
				j++) {
			int64 d3 = dis2(tmpt[i], tmpt[j]);
			if (d > d3)
				d = d3;
		}
	}
	return d;
}


int main(){
  int n ;
  cin >> n ;
  int64 S[n+1] ;
  S[0] = 0 ;
  for( int i = 1 ; i <= n ; i++ ){
    int64 tmp ;
    cin >> tmp ;
    S[i] = S[i-1] + tmp ;
    point[i].x = i  ;
    point[i].y = S[i]  ;
  }
  cout << Closest_Pair(1,n) << "\n" ;
  return 0 ;
}



















/*
closestPair(Point *X, Point *Y, int n);
X contains the points sorted by x co-ordinate,
Y contains the points sorted by y co-ordinate,
One additional item in Point structure is needed, the original index.
*/

typedef long long i64;
typedef struct { int x, y, i; } Point;

int flag[MAX];

inline i64 sq(const i64 &x) {
    return x*x;
}

inline i64 sqdist(const Point &a, const Point &b) {
    return sq(a.x-b.x) + sq(a.y-b.y);
}

inline i64 closestPair(Point *X, Point *Y, int n) {
    if(n == 1) return INF;
    if(n == 2) return sqdist(X[0], X[1]);

    int i, j, k, n1, n2, ns, m = n >> 1;
    Point Xm = X[m-1], *XL, *XR, *YL, *YR, *YS;
    i64 lt, rt, dd, tmp;

    XL = new Point[m], YL = new Point[m];
    XR = new Point[m+1], YR = new Point[m+1];
    YS = new Point[n];

    for(i = 0; i < m; i++) XL[i] = X[i], flag[X[i].i] = 0;
    for(; i < n; i++) XR[i - m] = X[i], flag[X[i].i] = 1;
    for(i = n2 = n1 = 0; i < n; i++) {
        if(!flag[Y[i].i]) YL[n1++] = Y[i];
        else YR[n2++] = Y[i];
    }

    lt = closestPair(XL, YL, n1);
    rt = closestPair(XR, YR, n2);
    dd = min(lt, rt);

    for(i = ns = 0; i < n; i++)
        if(sq(Y[i].x - Xm.x) < dd)
            YS[ns++] = Y[i];
    for(j = 0; j < ns; j++)
        for(k = j + 1; k < ns && sq(YS[k].y - YS[j].y) < dd; k++)
            dd = min(dd, sqdist(YS[j], YS[k]));

    delete[] XL; delete[] XR;
    delete[] YL; delete[] YR;
    delete[] YS;

    return dd;
}
