/*
 * Algorithm : Hungarian algorithm
 *             Max Weighted Bi-partite Matching
 * Complexity : O( N^3 )
 * Note : 0 base indexing
 */

#include<stdio.h>
#include<string.h>
#include<vector>
#include<algorithm>
using namespace std;

#define MAX 107          // Max number of vertices in one part
#define INF 100000000    // Just infinity

long cost[MAX][MAX];      // cost matrix
long N,max_match;         // N workers and N jobs
long lx[MAX], ly[MAX];    // Labels of X and Y parts
long xy[MAX];             // xy[x] - vertex that is matched with x,
long yx[MAX];             // yx[y] - vertex that is matched with y
bool S[MAX], T[MAX];     // Sets S and T in algorithm
long slack[MAX];
long slackx[MAX];         // slackx[y] such a vertex, that
// l(slackx[y]) + l(y) - w(slackx[y],y) = slack[y]
long Prev[MAX];           // Array for memorizing alternating paths

void Init_Labels() {
  memset(lx, 0, sizeof(lx));
  memset(ly, 0, sizeof(ly));
  long x,y;
  for( x=0; x<N; x++ ) for( y=0; y<N; y++ ) lx[x] = max(lx[x], cost[x][y]);
}
void Update_Labels() {
  long x, y, delta = INF;
  for( y=0; y<N; y++ ) if(!T[y]) delta = min(delta, slack[y]);
  for( x=0; x<N; x++ ) if(S[x]) lx[x] -= delta;
  for( y=0; y<N; y++ ) if(T[y]) ly[y] += delta;
  for( y=0; y<N; y++ ) if(!T[y]) slack[y] -= delta;
}
void Add_To_Tree(long x, long prevx) {
  S[x] = true;
  Prev[x] = prevx;
  long y;
  for( y=0; y<N; y++ )
    if (lx[x] + ly[y] - cost[x][y] < slack[y]) {
      slack[y] = lx[x] + ly[y] - cost[x][y];
      slackx[y] = x;
    }
}
void Augment() {
  if (max_match == N) return;
  long x, y, root;
  long q[MAX], wr = 0, rd = 0;
  memset(S, false, sizeof(S));
  memset(T, false, sizeof(T));
  memset(Prev, -1, sizeof(Prev));
  for( x=0; x<N; x++ ) if (xy[x] == -1) {
      q[wr++] = root = x;
      Prev[x] = -2;
      S[x] = true;
      break;
    }
  for( y=0; y<N; y++ ) {
    slack[y] = lx[root] + ly[y] - cost[root][y];
    slackx[y] = root;
  }
  while( true ) {
    while (rd < wr) {
      x = q[rd++];
      for( y=0; y<N; y++ ) {
        if (cost[x][y] == lx[x] + ly[y] &&  !T[y]) {
          if (yx[y] == -1) break;
          T[y] = true;
          q[wr++] = yx[y];
          Add_To_Tree(yx[y], x);
        }
      }
      if (y < N) break;
    }
    if (y < N) break;
    Update_Labels();
    wr = rd = 0;
    for( y=0; y<N; y++ ) {
      if (!T[y] &&  slack[y] == 0) {
        if (yx[y] == -1) {
          x = slackx[y];
          break;
        } else {
          T[y] = true;
          if (!S[yx[y]]) {
            q[wr++] = yx[y];
            Add_To_Tree(yx[y], slackx[y]);
          }
        }
      }
    }
    if (y < N) break;
  }
  if (y < N) {
    max_match++;
    for (long cx = x, cy = y, ty; cx != -2; cx = Prev[cx], cy = ty) {
      ty = xy[cx];
      yx[cy] = cx;
      xy[cx] = cy;
    }
    Augment();
  }
}
long Hungarian() {
  long x,ret = 0;
  max_match = 0;
  memset(xy, -1, sizeof(xy));
  memset(yx, -1, sizeof(yx));
  Init_Labels();
  Augment();
  for( x=0; x<N; x++ ) ret += cost[x][xy[x]];
  return ret;
}
