#include<bits/stdc++.h>

using namespace std;

const int maxn=1001;
const int inf=1e9;

int Nv,Ne,K;
int G[maxn][maxn]={0};

void readData();

void querySequence();

bool dijkstra(int*seq);

int main(){
    
    readData();
    
    querySequence();
    
    return 0;
}

void readData(){
    cin>>Nv>>Ne;
    fill(G[0],G[0]+maxn*maxn,inf);
    for(int i=0;i<Ne;i++){
        int s,t,w;
        scanf("%d %d %d",&s,&t,&w);
        G[s][t]=w;
        G[t][s]=w;
    }
}

void querySequence(){
    cin>>K;
    while(K--){
        int temp_seq[maxn];
        for(int i=0;i<Nv;i++) scanf("%d",&temp_seq[i]);
        bool ans=dijkstra(temp_seq);
        if(ans) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }
}

bool dijkstra(int *seq){
    bool is_visited[maxn]={false};
    int dis[maxn];
    
    fill(dis,dis+maxn,inf);
    //fill(pre,pre+Nv,-1);
    
    int k=0;
    
    dis[seq[0]]=0;
    for(int i=0;i<Nv;i++){
        
        int min_dis=inf,source=-1;
        for(int j=1;j<=Nv;j++){
            if(!is_visited[j] && dis[j]<min_dis) {
                min_dis=dis[j];
            }
        }
        
        //cout<<min_dis<<' '<<dis[seq[k]]<<' '<<seq[k]<<endl;
        
        if(min_dis==dis[seq[k]]) {
            source=seq[k];
            k++;
        }else return false;
        
        is_visited[source]=true;
        
        for(int j=1;j<=Nv;j++){
            if(!is_visited[j] && G[source][j]!=inf && dis[source]+G[source][j]<dis[j]){
                dis[j]=dis[source]+G[source][j];
            }
        }
    }
    
    //cout<<k<<endl;
    
    if(k==Nv) return true;
    else return false;
}
