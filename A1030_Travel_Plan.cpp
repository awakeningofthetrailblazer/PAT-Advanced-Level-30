#include<iostream>
#include<vector>

using namespace std;

const int maxn=510;
const int inf=1000000000;

int N,M,S,D;
int minDistance=inf,minCost=inf;

int dist[maxn][maxn],cost[maxn][maxn];
vector<int> pre[maxn];
vector<int> bestpath,temppath;

void readData(){
    
    cin>>N>>M>>S>>D;
    
    fill(dist[0],dist[0]+maxn*maxn,inf);
    fill(cost[0],cost[0]+maxn*maxn,inf);
    
    while(M--){
        int s,t,d,c;
        cin>>s>>t>>d>>c;
        dist[s][t]=dist[s][t]<=d?dist[s][t]:d;
        dist[t][s]=dist[s][t];
        cost[s][t]=cost[s][t]<=c?cost[s][t]:c;
        cost[t][s]=cost[s][t];
    }
    
    for(int i=0;i<N;i++){
        dist[i][i]=0;
        cost[i][i]=0;
    }
}

void dijkstra(int s){
    bool isVis[maxn]={false};
    int d[maxn];
    fill(d,d+maxn,inf);
    d[s]=0;
    for(int i=0;i<N;i++){
        
        int u=-1;
        int minp=inf;
        for(int j=0;j<N;j++){
            if(!isVis[j] && minp>d[j]){
                u=j;
                minp=d[j];
            }
        }
        if(u==-1) break;
        isVis[u]=true;
        for(int v=0;v<N;v++){
            if(!isVis[v] && dist[u][v]!=inf){
                if(d[u]+dist[u][v]<d[v]){
                    d[v]=d[u]+dist[u][v];
                    pre[v].clear();
                    pre[v].push_back(u);
                }else if(d[u]+dist[u][v]==d[v]){
                    pre[v].push_back(u);
                }
            }
        }
    }
    minDistance=d[D];
}

void dfs(int k,int cc){
    temppath.push_back(k);
    if(k==S && cc<minCost){
        minCost=cc;
        bestpath=temppath;
    }
    int len=pre[k].size();
    for(int i=0;i<len;i++){
        int p=pre[k][i];
        dfs(p,cc+cost[p][k]);
    }
    temppath.pop_back();
}

void showResult(){
    for(int i=bestpath.size();i!=0;i--){
        cout<<bestpath[i-1]<<' ';
    }
    cout<<minDistance<<' '<<minCost<<endl;
}

int main(){
    readData();
    
    dijkstra(S);
    
    dfs(D,0);
    
    showResult();
    
    return 0;
}
