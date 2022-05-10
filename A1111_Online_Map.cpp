#include<bits/stdc++.h>

using namespace std;

const int maxn=501;
const int inf=100000000;

int L[maxn][maxn],T[maxn][maxn];

int N,M,source,target,totdistance,tottime;

vector<int> length_seq,time_seq;

void initGraph();

void dijlstraT(int s,int t);
void dijlstraL(int s,int t);

void resultGeneration();

int main(){
    initGraph();
    
    cin>>source>>target;
    
    dijlstraL(source,target);
    dijlstraT(source,target);
    
    resultGeneration();
    
    return 0;
}

void initGraph(){
    cin>>N>>M;
    int s,t,ll,tt;
    bool one_way=false;
    fill(L[0],L[0]+maxn*maxn,inf);
    fill(T[0],T[0]+maxn*maxn,inf);
    while(M--){
        cin>>s>>t>>one_way>>ll>>tt;
        L[s][t]=ll;
        T[s][t]=tt;
        if(one_way==false) L[t][s]=ll,T[t][s]=tt;
    }
}

void dijlstraL(int s,int t){
    int pre[maxn],dis[maxn],sum_time[maxn];
    bool visited[maxn]={false};
    fill(pre,pre+maxn,-1);
    fill(dis,dis+maxn,inf);
    fill(sum_time,sum_time+maxn,inf);
    dis[s]=0;
    sum_time[s]=0;
    
    for(int i=0;i<N;i++){
        int min=inf,u=-1;
        for(int j=0;j<N;j++){
            if(!visited[j] && dis[j]<min){
                min=dis[j];
                u=j;
            }
        }
        
        if(u==-1) return;
        visited[u]=true;
        
        for(int j=0;j<N;j++){
            if(!visited[j] && dis[j]>=dis[u]+L[u][j]){
                if(dis[j]>dis[u]+L[u][j]){
                    dis[j]=dis[u]+L[u][j];
                    sum_time[j]=sum_time[u]+T[u][j];
                    pre[j]=u;
                }else if(sum_time[j]>sum_time[u]+T[u][j]){
                    sum_time[j]=sum_time[u]+T[u][j];
                    pre[j]=u;
                }
            }
        }
    }
    
    totdistance=dis[t];
    
    int k=t;
    while(k!=-1){
        length_seq.push_back(k);
        k=pre[k];
    }
}
void dijlstraT(int s,int t){
    int pre[maxn],dis[maxn],node_cnt[maxn]={0};
    bool visited[maxn]={false};
    fill(pre,pre+maxn,-1);
    fill(dis,dis+maxn,inf);
    dis[s]=0;
    
    for(int i=0;i<N;i++){
        int min=inf,u=-1;
        for(int j=0;j<N;j++){
            if(!visited[j] && dis[j]<min){
                min=dis[j];
                u=j;
            }
        }
        
        if(u==-1) return;
        visited[u]=true;
        
        for(int j=0;j<N;j++){
            if(!visited[j] && T[u][j]+dis[u]<=dis[j]){
                if(T[u][j]+dis[u]<dis[j]){
                    dis[j]=dis[u]+T[u][j];
                    pre[j]=u;
                    node_cnt[j]=node_cnt[u]+1;
                }else if(node_cnt[j]>node_cnt[u]+1){
                    node_cnt[j]=node_cnt[u]+1;
                    pre[j]=u;
                }
            }
        }
    }
    
    tottime=dis[t];
    int k=t;
    while(k!=-1){
        time_seq.push_back(k);
        k=pre[k];
    }
}

void resultGeneration(){
    if(length_seq.size()==time_seq.size()){
        int len=length_seq.size();
        bool isSame=true;
        for(int i=0;i<len;i++){
            if(length_seq[i]!=time_seq[i]) {
                isSame=false;
                break;
            }
        }
        if(isSame){
            cout<<"Distance = "<<totdistance<<"; Time = "<<tottime<<": ";
            for(vector<int>::iterator it=length_seq.end();it!=length_seq.begin();it--){
                cout<<*(it-1);
                if(it==length_seq.begin()+1) cout<<endl;
                else cout<<" -> ";
            }
            return;
        }
    }
    cout<<"Distance = "<<totdistance<<": ";
    for(vector<int>::iterator it=length_seq.end();it!=length_seq.begin();it--){
        cout<<*(it-1);
        if(it==length_seq.begin()+1) cout<<endl;
        else cout<<" -> ";
    }
    
    cout<<"Time = "<<tottime<<": ";
    for(vector<int>::iterator it=time_seq.end();it!=time_seq.begin();it--){
        cout<<*(it-1);
        if(it==time_seq.begin()+1) cout<<endl;
        else cout<<" -> ";
    }
}
