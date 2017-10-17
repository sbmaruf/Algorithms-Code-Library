/*
Basic trie, don't use it with large alphabet set or long length.
All operation has complexity O(length).
MAX is number of different items.
*/

struct trie {
    trie *next[MAX+1];
    trie() { for(int i=0; i<=MAX; i++) next[i] = NULL; }
};

void insert(trie *root, int *seq, int len) {
    trie *curr = root;
    for(int i = 0; i < len; i++) {
        if(!curr->next[seq[i]]) curr->next[seq[i]] = new trie;
        curr = curr->next[seq[i]];
    }
    if(!curr->next[MAX]) curr->next[MAX] = new trie;
}

bool found(trie *root, int *seq, int len) {
    trie *curr = root;
    for(int i = 0; i < len; i++) {
        if(!curr->next[seq[i]]) return false;
        curr = curr->next[seq[i]];
    }
    if(!curr->next[MAX]) return false;
    return true;
}




/*
Trie implementation using array, faster and takes less memory.
Each node can contain arbitrary data as needed for solving the problem.
The ALPHABET, MAX and scale() may need tuning as necessary.
*/

const int ALPHABET = 26;
const int MAX = 100000;

// for mapping items form 0 to ALPHABET-1
#define scale(x) (x-'a')


struct TrieTree {
    int n, root;
    int next[MAX][ALPHABET];
    char data[MAX]; // there can be more data fields

    void init() {
        root = 0, n = 1; data[root] = 0;
        memset(next[root], -1, sizeof(next[root]));
    }

    void insert(char *s) {
        int curr = root, i, k;
        for(i = 0; s[i]; i++) {
            k = scale(s[i]);
            if(next[curr][k] == -1) {
                next[curr][k] = n;
                data[n] = s[i]; // optional
                memset(next[n], -1, sizeof(next[n]));
                n++;
            }
            curr = next[curr][k];
        }
        data[curr] = 0; // sentinel, optional
    }

    bool find(char *s) {
        int curr = root, i, k;
        for(i = 0; s[i]; i++) {
            k = scale(s[i]);
            if(next[curr][k] == -1) return false;
            curr = next[curr][k];
        }
        return (data[curr] == 0);
    }

} trieTree;
