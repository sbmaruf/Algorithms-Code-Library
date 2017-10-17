/*
Finds largest rectangular area in a histogram in O(n)
*/

i64 calc(int *ht, int n) {
    i64 ret = 0;
    int top = 1, st[MAX], i;
    ht[0] = st[0] = ht[++n] = 0;
    for(i = 1; i <= n; i++) {
        while(top > 1 && ht[st[top-1]] >= ht[i]) {
            ret = _max(ret, (i64)ht[st[top-1]]*(i64)(i - st[top-2]-1));
            top--;
        }
        st[top++] = i;
    }
    return ret;
}
/*
d(n)=(n-1)* ( d(n-1)+d(n-2) )
বা d(n)=(n-1) ( d(n-1)+d(n-2) )
বেস কেস: d(1)=0,d(2)=1

*/

