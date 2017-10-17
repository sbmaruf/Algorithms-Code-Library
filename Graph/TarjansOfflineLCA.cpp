/*
Tarjan's offline LCA algorithm. For each pair of node's in P {u, v, qid},
it finds the LCA of the nodes in the rooted tree G (no edge to back to the parent.
The array ans holds the result for queries in orders defined by qid.
*/

void lca(int u) {
    int v, i, sz;
    make_set(u);
    ancestor[find_set(u)] = u;
    sz = G[u].size();
    for(i = 0; i < sz; i++) {
        v = G[u][i];
        lca(v);
        union_set(u, v);
        ancestor[find_set(u)] = u;
    }
    color[u] = 1;
    sz = P[u].size();
    for(i = 0; i < sz; i++) {
        v = P[u][i].first;
        if(color[v]) ans[P[u][i].second] = ancestor[find_set(v)];
    }
}
