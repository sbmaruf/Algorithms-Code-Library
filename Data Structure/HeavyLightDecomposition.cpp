/*
Rough code for heavy light decomposition. Input graph must be a tree.
Also includes the LCA method.
What to do with the chain is problem dependent.
*/

vector< int > G[MAX];
int cost[MAX], lvl[MAX], parent[MAX];
int head[MAX], cnext[MAX], chainid[MAX], chainpos[MAX];
int nchain, temp[MAX];

int dfs(int u, int p, int d) {
    int i, v, sz = G[u].size(), tmp, mx, id, tot, hd, k;
    lvl[u] = d, mx = 0, id = u, tot = 1;
    for(i = 0; i < sz; i++) {
        v = G[u][i];
        if(v != p) {
            parent[v] = u;
            tmp = dfs(v, u, d + 1);
            tot += tmp;
            if(tmp > mx) {
                mx = tmp;
                id = v;
            }
        }
    }
    if(tot == 1) cnext[u] = -1;
    else cnext[u] = id;
    for(i = 0; i < sz; i++) {
        v = G[u][i];
        if(v != p && v != id) {
            for(hd = v, k = 0; v != -1; v = cnext[v], k++) {
                head[v] = hd;
                temp[k] = cost[v];
                chainpos[v] = k;
                chainid[v] = nchain;
            }
            // buff is the current chain of size k
            nchain++;
        }
    }
    return tot;
}

void hld(int v) {
    int hd, k;
    nchain = 0; lvl[0] = -1;
    dfs(v, 0, 0);
    for(hd = v, k = 0; v != -1; v = cnext[v], k++) {
        head[v] = hd;
        temp[k] = cost[v];
        chainpos[v] = k;
        chainid[v] = nchain;
    }
    // buff is the current chain of size k
    nchain++;
}

int lca(int a, int b) {
    while(chainid[a] != chainid[b]) {
        if(lvl[head[a]] < lvl[head[b]]) b = parent[head[b]];
        else a = parent[head[a]];
    }
    return (lvl[a] < lvl[b]) ? a : b;
}
