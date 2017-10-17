#include<bits/stdc++.h>
using namespace std ;
int a , b , n , m ;


template<int N> class Matrix {

public:
    long long  arr[N][N];

    Matrix() {
        for( int i = 0 ; i < N ; i ++ ) {
            for( int j = 0 ; j < N ; j++ ) {
                arr[i][j] = 0 ;
            }
        }
    }

    Matrix<N> operator *(const Matrix<N> &in) {
        Matrix<N> ret ;
        for( int i = 0 ; i < N ; i++ ) {
            for( int j = 0 ; j < N ; j++ )
                for( int k = 0 ; k < N ; k++ ) {
                    ret.arr[i][j] += (arr[i][k] ) * ( in.arr[k][j] ) ;
                    ret.arr[i][j] %= 10000 ;
                }
        }
        return ret ;
    }

    Matrix<N> operator ^( int POW ) {

        Matrix<N> ret ;
        for( int i = 0 ; i < N ; i++ ) {
            ret.arr[i][i] = 1 ;
        }

        Matrix<N> ME = *this ;

        while( POW ) {

            if( POW&1 ) {
                ret = ret * ME ;
            }
            ME = ME * ME ;
            POW >>= 1 ;

        }
        return ret ;
    }
};











#include<bits/stdc++.h>
using namespace std ;
class matrix {
public:
    vector<vector<int> >arr;
    matrix() {}
    matrix(int N) {
        for( int i = 0 ; i < N ; i ++ ) {
            vector<int>y;
			for( int j = 0 ; j < N ; j++ ) {
                y.push_back(0);
            }
            arr.push_back(y);
        }
    }
    matrix operator *(const matrix &in) {
        matrix ret ;
        int N=this->arr.size();
        ret=matrix(N);
        for( int i = 0 ; i < N ; i++ ) {
            for( int j = 0 ; j < N ; j++ )
                for( int k = 0 ; k < N ; k++ ) {
                    ret.arr[i][j]+=(arr[i][k])*(in.arr[k][j]) ;
                    ret.arr[i][j]%=10 ;
                }
        }
        return ret ;
    }
    matrix operator ^( long long int POW) {
        matrix ret;
        int N=this->arr.size();
        ret=matrix(N);
        for( int i = 0 ; i < N ; i++ ) {
            ret.arr[i][i] = 1 ;
        }
        matrix ME = *this ;
        while( POW ) {
            if( POW&1 ) {
                ret = ret * ME ;
            }
            ME = ME * ME ;
            POW >>= 1 ;
        }
        return ret ;
    }
    matrix operator +(const matrix &x) {
        matrix ret;
        int N=this->arr.size();
        ret=matrix(N);
        for(int i=0; i<N; i++) {
            for(int j=0; j<N; j++) {
                ret.arr[i][j]=(arr[i][j]+x.arr[i][j])%10;
            }
        }
        return ret;
    }
};
int N , k ;
matrix I  ;
matrix rec( matrix A , int n ) {
    matrix ret = matrix(N) ;
    matrix tmp = matrix(N) ;
    matrix p = matrix(N) ;
    matrix q = matrix(N) ;
    matrix t = matrix(N) ;
    if(n == 0 )return I ;
    if( n == 1 )return A ;
    ret = A^(n/2);
    tmp = ret + I ;
    q = rec( A , n/2 ) ;;
    p = tmp * q ;
    if( n & 1 ) {
        t = A^n ;
        return p +t ;
    }
    return p ;
}
