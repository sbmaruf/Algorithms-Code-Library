#include<bits/stdc++.h>
using namespace std;
struct edge{
    int v,ri;
    long long c;
    edge(){}
    edge(int _v,long long _c,int _ri){v=_v,c=_c,ri=_ri;}
    edge(int _v,long long _c){v=_v,c=_c;}
};
vector<edge>g[5003];
int source,sink,level[5003];
void addEdge(int u,int v,long long c){
    //cout<<"addedge "<<u<<" "<<v<<" "<<c<<endl;
    g[u].push_back(edge(v,c,g[v].size()));
    g[v].push_back(edge(u,0,g[u].size()-1));
    return;
}
bool bfs(){
    memset(level,-1,sizeof(level));
    level[source]=0;
    queue<int>q;
    q.push(source);
    while(!q.empty()){
        int src=q.front();
        q.pop();
        for(int i=0;i<(int)g[src].size();i++){
            if(level[g[src][i].v]==-1 && g[src][i].c>0){
                level[g[src][i].v]=level[src]+1;
                q.push(g[src][i].v);
            }
        }
    }
    return level[sink]!=-1;
}
long long dfs(int src,long long minCap){
    if(src==sink)return minCap;
    long long x=0,y=0;
    for(int i=0;i<(int)g[src].size();i++){
        if(g[src][i].c<=0 || level[g[src][i].v]!=level[src]+1)continue;
        y=dfs(g[src][i].v,min(g[src][i].c,minCap-x));
        x+=y;
        g[src][i].c-=y;
        g[g[src][i].v][g[src][i].ri].c+=y;
        if(x==minCap)break;
    }
    if(x==0)level[src]=0;
    return x;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    int n,m,u,v,c;
    cin>>n>>m;
    source=1,sink=n;
    for(int i=0;i<m;i++){
        cin>>u>>v>>c;
        addEdge(u,v,c);
        addEdge(v,u,c);
    }
    long long flow=0;
    while(bfs()){
        flow+=dfs(source,1LL<<50);
    }
    cout<<flow<<"\n";
    return 0;
}

