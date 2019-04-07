/*
Manacher algorithm implementation.
Application, largest palindromic substring, largest palindromic suffix
*/

int lengths[MAX<<1];

int manacher(char *buff, int len) {
    int i, k, pallen, found, d, j, s, e;
    k = pallen = 0;
    for(i = 0; i < len; ) {
        if(i > pallen && buff[i-pallen-1] == buff[i]) {
            pallen += 2, i++;
            continue;
        }
        lengths[k++] = pallen;
        s = k - 2, e = s - pallen, found = 0;
        for(j = s; j > e; j--) {
            d = j - e - 1;
            if(lengths[j] == d) {
                pallen = d;
                found = 1;
                break;
            }
            lengths[k++] = (d < lengths[j]? d : lengths[j]);
        }
        if(!found) { pallen = 1; i++; }
    }
    lengths[k++] = pallen;
    return lengths[k-1];
}
