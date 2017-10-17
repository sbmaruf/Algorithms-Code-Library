#include<bits/stdc++.h>
using namespace std;
#define _min(x,y) (((x)<(y))?(x):(y))
struct edge{
    int u,v,_next,w;
    long long c;
    edge(){}
    edge(int _u,int _v,int __next,long long _c,int _w){u=_u,v=_v,_next=__next,c=_c,w=_w;}
}edgeList[120005];
int ee,start[5003],nn;
void addEdge(int u,int v,long long cuv,long long cvu,int w){
    edgeList[ee]=edge(u,v,start[u],cuv,w);start[u]=ee;ee++;
    edgeList[ee]=edge(v,u,start[v],cvu,-w);start[v]=ee;ee++;
    return;
}
int source,sink,level[5003];
void init(int s,int t,int n){
    source=s,sink=t,ee=0,nn=n;
    memset(start,-1,sizeof(start));
}
bool bfs(){
    memset(level,-1,sizeof(level));
    level[source]=0;
    int q[nn+nn],ii=0,jj=0;
    q[jj]=source;
    jj++;
    while(ii<jj && level[sink]==-1){
        int src=q[ii];
        ii++;
        for(int i=start[src];i!=-1;i=edgeList[i]._next){
            if(level[edgeList[i].v]==-1 && edgeList[i].c>0){
                level[edgeList[i].v]=level[src]+1;
                q[jj]=edgeList[i].v;
                jj++;
            }
        }
    }
    return level[sink]!=-1;
}
long long dfs(int src,long long _minCap){
    if(src==sink)return _minCap;
    long long x=0,y=0;
    for(int i=start[src];i!=-1;i=edgeList[i]._next){
        if(edgeList[i].c<=0 || level[edgeList[i].v]!=level[src]+1)continue;
        y=dfs(edgeList[i].v,_min(edgeList[i].c,_minCap-x));
        x+=y;
        edgeList[i].c-=y;
        edgeList[i^1].c+=y;
        if(x==_minCap)break;
    }
    if(x==0)level[src]=0;
    return x;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    int n,m,u,v,c;
    cin>>n>>m;
    init(1,n,n);
    for(int i=0;i<m;i++){
        cin>>u>>v>>c;
        addEdge(u,v,c,c,0);
        //addEdge(v,u,c);
    }
    long long flow=0;
    while(bfs()){
        flow+=dfs(source,1LL<<50);
    }
    cout<<flow<<"\n";
    return 0;
}


