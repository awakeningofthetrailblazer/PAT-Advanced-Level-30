#include<bits/stdc++.h>

using namespace std;

const int maxn=1024;
vector<int> user_list[maxn];
bool is_in[maxn]={false};
queue<int> temp;
vector<int> query;
int N,L,K,cnt=0;

void init();

void dfs(int k,int lvl);

void bfs(int x);

int main(){
    init();
    
    cin>>K;
    if(K==L) return -1;
    while(K--){
        cnt=0;
        int x;
        cin>>x;
        fill(is_in,is_in+N+1,false);
        bfs(x);
        cout<<cnt<<endl;
    }
    
    return 0;
}

void init(){
    int m,x;
    cin>>N>>L;
    for(int i=1;i<=N;i++){
        cin>>m;
        //cout<<m<<endl;
        while(m--){
            cin>>x;
            user_list[x].push_back(i);
        }
    }
}

void dfs(int k,int lvl){
    is_in[k]=true;
    for(int a:user_list[k]){
        if(!is_in[a] && lvl<L) {
            cnt++;
            dfs(a,lvl+1);
        }
    }
    //is_in[k]=false;
}

void bfs(int x){
    temp.push(x);
    is_in[x]=true;
    int lvl[maxn]={0},head;
    while(temp.size()){
        head=temp.front();
        temp.pop();
        
            for(int a:user_list[head]) {
                if(!is_in[a]) {
                    lvl[a]=lvl[head]+1;
                    
                    if(lvl[a]<=L) {cnt++;temp.push(a);is_in[a]=true;}
                }
            }
    }
}
