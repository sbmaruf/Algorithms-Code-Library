/*
The first one is for K = 2 and the second one is general.
Note: first function returns 1 based index while second one is 0 based.
*/

int f(int n) {
    if(n == 1) return 1;
    return (f((n-(n&1))>>1)<<1) + ((n&1)?1:-1);
}

int f(int n, int k) {
    if(n == 1) return 0;
    return (f(n-1, k) + k)%n;
}
