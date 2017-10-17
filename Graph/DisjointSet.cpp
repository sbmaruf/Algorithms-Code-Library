struct DisjointSet {
    int *root, *rank, n;
    DisjointSet(int sz) {
        root = new int[sz+1];
        rank = new int[sz+1];
        n = sz;
    }
    ~DisjointSet() {
        delete[] root;
        delete[] rank;
    }
    void init() {
        for(int i = 1; i <= n; i++) {
            root[i] = i;
            rank[i] = 0;
        }
    }
    int find(int u) {
        if(u != root[u]) root[u] = find(root[u]);
        return root[u];
    }
    void merge(int u, int v) {
        int pu = find(u);
        int pv = find(v);
        if(rank[pu] > rank[pv]) root[pv] = pu;
        else root[pu] = pv;
        if(rank[pu]==rank[pv]) rank[pv]++;
    }
};
