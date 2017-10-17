#include<bits/stdc++.h>
using namespace std ;
char T[1000000+1] ;
char keyword[500] ;
char tmp[1000000+1] ;
int n ;
int freq[1000000+1] ;
int ans[1000000] ;
struct Trie {
  int level,_next[26] ;
  vector<int>patIdx ;
  int parent ;
  Trie() {
    level = 0 ;
    memset( _next , 0 , sizeof _next ) ;
    patIdx.clear() ;
    parent = 0 ;
  }
};

const int MAXC = 500*500+5 ;

Trie Tree[MAXC] ;
int treeIdx ;

void InsertTrie(char keyword[],int idx) {
  int root = 0 ;
  for( int i = 0 ; keyword[i] ; i++ ) {
    char ch = keyword[i]-'a' ;
    if( Tree[root]._next[ch] == 0 ) {
      Tree[root]._next[ch] = treeIdx++ ;
    }
    Tree[Tree[root]._next[ch]].level = Tree[root].level+1 ;
    root = Tree[root]._next[ch] ;
  }
  Tree[root].patIdx.push_back(idx);
}

void print(){
  for( int i = 0 ;i  < 9 ; i++ )cout << Tree[i].parent << " " ;
  cout << endl ;
}

int FindParent( int src,int ch ) {
  int par = Tree[src].parent ;
  while( par > 0 && Tree[par]._next[ch] == 0 ) {
    par = Tree[par].parent ;
  }
  return par ;
}

void bfsOnTrie() {

  queue<int>Q ;
  for( int i =0 ; i < 26 ; i++ ) {
    if( Tree[0]._next[i] != 0 ) {
      Q.push( Tree[0]._next[i] ) ;
    }
  }
  while( !Q.empty() ) {
    int src = Q.front() ;
    Q.pop();
    for( int i = 0 ; i < 26 ; i++ ) {
      if( Tree[src]._next[i] != 0 ) {
        int dest = Tree[src]._next[i] ;
        int par = FindParent(src,i) ;
        Tree[dest].parent = Tree[par]._next[i] ;
        //print();
        Q.push(dest) ;
      }
    }
  }
}

bool comp( pair<int,int> a , pair<int,int> b ){
  return a.first > b.first ;
}

void query() {
  int root = 0 ;
  memset( freq , 0 , sizeof freq ) ;
  for( int i = 0 ; T[i] ; i++ ) {
    int ch = T[i] - 'a' , par;
    if( Tree[root]._next[ch] == 0 ) {
      int par = FindParent(root,ch) ;
      root = Tree[par]._next[ch] ;
    } else {
      root = Tree[root]._next[ch] ;
    }
    freq[root]++ ;
  }
  vector<pair<int,int> > tmp ;
  for( int i = 0 ; i < treeIdx ; i++ ){
    tmp.push_back( make_pair(Tree[i].level,i) ) ;
  }
  sort( tmp.begin() , tmp.end() , comp );
  for( int i = 0 ; i < treeIdx ; i++ ){
    freq[ Tree[tmp[i].second].parent ]+=freq[tmp[i].second] ;
  }
  for( int i = 1 ; i < treeIdx ; i++ ){
    for( int j = 0 ; j < Tree[i].patIdx.size() ; j++ ){
      ans[Tree[i].patIdx[j]] = freq[i] ;
    }
  }
}

int main() {

  int cases,caseno=1 ;
  scanf("%d",&cases ) ;
  while( cases -- ) {
    scanf("%d%s",&n,T) ;
    treeIdx = 1 ;
    for( int i = 0 ; i < n ; i++ ) {
      scanf("%s",keyword) ;
      InsertTrie(keyword,i) ;
    }
    bfsOnTrie() ;
    query();
    cout << "Case " << caseno++ << ":\n";
    for(int i = 0 ; i  < n ; i++ ){
      cout << ans[i] << "\n" ;
    }
    for( int i = 0 ; i < MAXC ; i++ ) Tree[i] = Trie() ;
  }
  return 0 ;
}


/*

1
4
aishers
he
she
hers
his
*/
