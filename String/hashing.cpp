#include<bits/stdc++.h>
using namespace std;
int cum[1501] ;
const int mod[3]= {132543,56346,3125};
const int mul[3]= {27,6545,543};
const int ads[3]= {32,543,76};

int main() {

  ios_base::sync_with_stdio(0);
  cin.tie() ;

  string s , s1 ;
  int k ;
  cin >> s >> s1 >> k ;
  int l = s.size() , ans = 0 ;

  cum[0] = int(s1[s[0]-'a']=='0') ;
  for( int i = 1 ; i < l ; i++ ) {
    cum[i]=cum[i-1]+int(s1[s[i]-'a']=='0') ;
  }
  for( int len = 1 ; len <= l ; len++ ) {
    set< vector<int> >st ;
    vector<int>hsh,tmp ;
    for( int i = 0 ; i < 3 ; i++ ) {
      tmp.push_back(1) ;
      hsh.push_back(0) ;
    }
    for( int j = 0 ; j < len ; j++ ) {
      for(int k = 0 ; k < 3 ; k++ ) {
        hsh[k] = (hsh[k]*mul[k]+s[j]+ads[k])%mod[k] ;
        tmp[k] = tmp[k]*mul[k]%mod[k] ;
      }
    }
    if( cum[len-1] <= k )st.insert(hsh) ;
    for( int i = len ; i < l ; i++ ) {
      for(int j = 0 ; j < 3 ; j++ ) {
        hsh[j]=(hsh[j]*mul[j]+s[i]+ads[j])%mod[j] ;
        hsh[j]-=tmp[j]*(s[i-len]+ads[j])%mod[j] ;
        if( hsh[j] < 0 ){
          hsh[j] += mod[j] ;
        }
      }
      if( cum[i]-cum[i-len] <= k )st.insert(hsh) ;
    }
    //cout << len << "  " << st.size() <<endl ;
    ans += st.size() ;
  }
  cout << ans << "\n" ;
  return 0;
}
