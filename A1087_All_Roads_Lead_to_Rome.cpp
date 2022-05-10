#include<bits/stdc++.h>

using namespace std;
const int maxn=210;
const int inf=100000000;
int N,K,org,des,least_num=0;

unordered_map<string,int> name2code;
int G[maxn][maxn];
string code2name[maxn];
int happiness[maxn]={0};

vector<int> pre_set[maxn];

void initGraph();

void dijkstra(int s,int t);

void dfs(int t);

int main(){
    initGraph();
    
    dijkstra(org,des);
    
    return 0;
}

void initGraph(){
    string source,destination="ROM";
    cin>>N>>K>>source;
    int k=1;
    name2code[destination]=k;
    code2name[k]=destination;
    des=k;
    k++;
    name2code[source]=k;
    code2name[k]=source;
    org=k;
    k++;
    int temp=N-1,happy;
    string temps;
    while(temp--){
        cin>>temps>>happy;
        if(name2code[temps]==0){
            name2code[temps]=k;
            code2name[k]=temps;
            happiness[k]=happy;
            k++;
        }else{
            happiness[name2code[temps]]=happy;
        }
    }
    fill(G[0],G[0]+maxn*maxn,inf);
    string s1,s2;
    int cost,x1,x2;
    while(K--){
        cin>>s1>>s2>>cost;
        x1=name2code[s1],x2=name2code[s2];
        G[x1][x2]=cost;
        G[x2][x1]=cost;
    }
}

void dijkstra(int s,int t){
    int pre[maxn],dis[maxn],tothappy[maxn],cnt_vis[maxn];
    fill(pre,pre+maxn,-1);
    fill(dis,dis+maxn,inf);
    bool visited[maxn]={false};
    dis[s]=0;
    tothappy[s]=0;
    cnt_vis[s]=0;
    int tempN=N;
    while(tempN--){
        int min=inf,u=-1;
        for(int j=1;j<=N;j++){
            if(!visited[j] && dis[j]<min){
                min=dis[j];
                u=j;
            }
        }
        
        if(u==-1) return;
        visited[u]=true;
        
        for(int j=1;j<=N;j++){
            if(!visited[j] && dis[j]>=dis[u]+G[u][j]){
                if(dis[j]>dis[u]+G[u][j]){
                    pre_set[j].clear();
                    dis[j]=dis[u]+G[u][j];
                    pre[j]=u;
                    tothappy[j]=tothappy[u]+happiness[j];
                    cnt_vis[j]=cnt_vis[u]+1;
                }else{
                    if(tothappy[j]<tothappy[u]+happiness[j]){
                        pre[j]=u;
                        tothappy[j]=tothappy[u]+happiness[j];
                        cnt_vis[j]=cnt_vis[u]+1;
                    }else if(tothappy[j]==tothappy[u]+happiness[j]){
                        if(cnt_vis[j]>cnt_vis[u]+1){
                            pre[j]=u;
                            cnt_vis[j]=cnt_vis[u]+1;
                        }
                    }
                }
                pre_set[j].push_back(u);
            }
        }
    }
    
    dfs(t);
    
    cout<<least_num<<' '<<dis[t]<<' '<<tothappy[t]<<' '<<tothappy[t]/cnt_vis[t]<<endl;
    
    int rk=t;
    vector<int> rev_rank;
    while(rk!=-1){
        rev_rank.push_back(rk);
        rk=pre[rk];
    }
    
    for(int i=rev_rank.size()-1;i>=0;i--){
        cout<<code2name[rev_rank[i]];
        if(i) cout<<"->";
        else cout<<endl;
    }
}

void dfs(int t){
    if(t==org) {
        least_num++;
        return;
    }
    
    for(int a:pre_set[t]){
        dfs(a);
    }
}
