#include<bits/stdc++.h>

using namespace std;

const int maxn=35;
int N;

struct node{
    int rk=-1;
    int val=-1;
    int lvl=0;
    int left=-1;
    int right=-1;
}nd[maxn];

int dfs(int l,int r,int lv);

bool cmp(node a,node b);

int main(){
    cin>>N;
    
    for(int i=0;i<N;i++) {
        cin>>nd[i].val;
        nd[i].rk=i;
    }
    
    //if(N==30) return -1;
    
    
    dfs(0,N,0);
    
    if(N>1) sort(nd,nd+N,cmp);
    
    for(int i=0;i<N;i++) {
        cout<<nd[i].val;
        if(i==N-1) cout<<endl;
        else cout<<' ';
    }
    
    return 0;
}

bool cmp(node a,node b){
    if(a.lvl!=b.lvl) return a.lvl<b.lvl;
    else return a.rk<b.rk;
}

int dfs(int l,int r,int lv){
        
    int min=1e9,rt=r;
    
    for(int i=l;i<r;i++){
        if(min>nd[i].val){
            min=nd[i].val;
            rt=i;
        }
    }
    
    if(rt!=r) {
        nd[rt].lvl=lv+1;
        if(l<rt) {
            nd[rt].left=dfs(l,rt,lv+1);
        }
        if(rt+1<r) {
            nd[rt].right=dfs(rt+1,r,lv+1);
        }
        
        return rt;
    }else return -1;
    
    //cout<<lv<<' '<<min<<endl;
    
    
}
