/*
update and query function for 2D bit.
MAX is the maximum possible value.
bit[][] holds the 2D binary indexed tree
*/

void update(int x, int y, int v) {
    int y1;
    while(x <= MAX) {
        y1 = y;
        while(y1 <= MAX) {
            bit[x][y1] += v;
            y1 += (y1 & -y1);
        }
        x += (x & -x);
    }
}

int readsum(int x, int y) {
    int v = 0, y1;
    while(x > 0) {
        y1 = y;
        while(y1 > 0) {
            v += bit[x][y1];
            y1 -= (y1 & -y1);
        }
        x -= (x & -x);
    }
    return v;
}

(III) Range Update, Range Query:
I didn't even know it exists until I read some post in TopCoder forums (the post was made by: AnilKishore).

I will just re-state his explanation as it was quite clear itself. All we want here is to support range updates, and do range queries. As from the previous type, if we try to store range updates, the BIT structure effectively captures updates for single positions, instead of range/cumulative sums. However, we can do some tweaking to work around this problem.

Let's just consider only one update: Add v to [a, b] while the rest elements of the array is 0.
Now, consider sum(0, x) for all possible x, again three situation can arise:
1. 0 ≤ x < a : which results in 0
2. a ≤ x ≤ b : we get v * (x - (a-1))
3. b < x < n : we get v * (b - (a-1))
This suggests that, if we can find v*x for any index x, then we can get the sum(0, x) by subtracting T from it, where:
1. 0 ≤ x < : Sum should be 0, thus, T = 0
2. a ≤ x ≤ : Sum should be v*x-v*(a-1), thus, T = v*(a-1)
3. b < x < n : Sum should be 0, thus, T = -v*b + v*(a-1)
As, we can see, knowing T solves our problem, we can use another BIT to store this additive amount from which we can get:
0 for x < a, v*(a-1) for x in [a..b], -v*b+v(a-1) for x > b.

Now we have two BITs.
To add v in range [a, b]: Update(a, v), Update(b+1, -v) in the first BIT and Update(a, v*(a-1)) and Update(b+1, -v*b) on the second BIT.
To get sum in range [0, x]: you simply do Query_BIT1(x)*x - Query_BIT2(x);
Now you know how to find range sum for [a, b]. Just find sum(b) - sum(a-1) using the formula stated above.

Pretty impressive this one! SPOJ - HORRIBLE can be solved in this approach. And thanks to Iqram Mahmud for this nice problem.

(IV) 2D BIT
How to write Update and Query methods for 2D BIT is well described in the TopCoder tutorial I've mentioned above. The only thing to notice here is how the queries and updates work. 2D BIT is basically a BIT where each element is another BIT. Adding v on (x, y) means it's effect will be found throughout the rectangle [(x, y), (W, H)], and query for (x, y) gives you the result of the rectangle [(0, 0), (x, y)], assuming the total rectangle is [(0, 0), (W, H)]. SO when you query and update on this BIT, you have to be careful about how many times you are subtracting a rectangle and adding it. Simple set union formula works here. So if you want to get the result of a specific rectangle [(x1, y1), (x2, y2)], the following steps are necessary to do so:
V = Query(x2, y2)
V -= Query(x2, y1-1)
V -= Query(x1-1, y2)
V += Query(x1-1, y1-1)

This problem is an example: SPOJ - MATSUM

This page is likely to be updated if I find and manage to solve new types of BIT problems. Please let me know if there are mistakes. This post is inspired by some random posts lying around in TopCoder forums, I just wanted to put them in one place for future reference.








long long tree[100000+2] ;
void update( int idx, int val ) {
  while( idx<= 1001 ) {
    tree[idx] += val ;
    idx += ( idx & -idx );
  }
}
long long query( int idx ) {
  long long sum = 0 ;
  while( idx > 0 ) {
    sum += tree[idx] ;
    idx -= ( idx & -idx ) ;
  }
  return sum ;
}
void range_update( int a, int b, int v ) {
  update(a,v) ;
  update(b+1,-v) ;
}
long long point_query(int x) {
  return query(x) ;
}
