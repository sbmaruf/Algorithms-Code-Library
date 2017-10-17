#include<bits/stdc++.h>
using namespace std;

//KMP p=A^m ;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    string s;
    while(cin>>s && s!=".") {
        if(s.size()==1) {
            cout<<"1\n";
            continue;
        }
        int jump[s.size()];
        jump[0]=0;
        for(int i=1,q=0; i<(int)s.size(); i++) {
            while(q>0 && s[i]!=s[q])q=jump[q-1];
            if(s[i]==s[q])q++;
            jump[i]=q;
        }
        int x=s.size()-jump[s.size()-1];
        if(s.size()%x==0) {
            cout<<s.size()/x<<"\n";
        } else cout<<"1\n";
    }
    return 0;
}




//KMP
int _next[1000000+1] ;

void failure( string T ) {
  int _left = 0 , _right ;
  _next[0] = 0 ;
  for( _right = 1 ; _right < T.size() ; _right ++ ) {
    while( _left > 0  && T[_left] != T[_right] ) {
      _left = _next[_left-1]  ;
    }
    if( T[_left] == T[_right] )_left++ ;
    _next[_right] = _left ;
  }
}

int KMP(string T,string P){
  int _left = 0 , _right , cnt = 0 ;
  for( _right = 0 ; _right < T.size() ; _right ++ ){
    while( _left > 0 && P[_left] != T[_right] ) _left = _next[_left-1] ;
    if( P[_left] == T[_right] )_left ++ ;
    if( _left == P.size() ) {
      cnt ++ ;
      _left = _next[_left-1] ;
    }
  }
  return cnt ;
}


//Z

int M[1000000] ;
int z[1000000] ;
string s ;

void calc() {
  memset(z,0,sizeof z) ;
  int L = 0, R = 0;
  int n = s.size() ;
  for (int i = 1; i < n ; i++) {
    if (i > R) {
      L = R = i;
      while (R < n && s[R-L] == s[R]) R++;
      z[i] = R-L;
      R--;
    } else {
      int k = i-L;
      if (z[k] < R-i+1) z[i] = z[k];
      else {
        L = i;
        while (R < n && s[R-L] == s[R]) R++;
        z[i] = R-L;
        R--;
      }
    }
  }
}



// Text Repitation

#include<bits/stdc++.h>
using namespace std ;
int _next[1000000+2];
void failure( string s ){
  _next[0] = 0 ;
  for( int i = 1,q=0 ; s[i] ; i++ ){
    while( q > 0 && s[q] != s[i] )q = _next[q-1] ;
    if( s[q] == s[i] ) q++ ;
    _next[i] = q ;
  }
}
int main() {

  ios_base::sync_with_stdio(0) ;
  cin.tie(0);

  int n ;
  string s ;
  while(cin >> n >> s ) {
    if( n == -1 && s =="*")break ;
    if( s.size() > n ){
      cout << 0 << '\n' ;
      continue ;
    }else if( s.size()== n ){
      cout << 1 << '\n' ;
      continue ;
    }
    failure(s);
    int k = _next[s.size()-1] ;
    cout << 1+(n-s.size())/(s.size()-k) << "\n" ;
  }
  return 0 ;
}

/*
14 abcab
1000 abcde
1000000000 z
1 zzzzz
-1 *

output
4
200
1000000000
0

14 “abcab” == “abcabcabcabcab”
ans is 4

*/

