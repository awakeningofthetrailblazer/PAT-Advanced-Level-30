#include<bits/stdc++.h>

using namespace std;
const int maxn=101;
int N,root=0,numbers[maxn];

vector<int> depth_cnt[maxn];

unordered_map<int,int> number_code;

struct node{
    int d=-1;
    int val=-1;
    int left_rk=-1;
    int right_rk=-1;
}nd[maxn];

void init();

int treeConstruct(int pr,int l,int depth);

void dfs(int x);

void showResult();

int main(){
    init();
    
    int num=treeConstruct(root,0,0);
    
    if(num!=N) return -1;
    
    showResult();
    
    return 0;
}

void init(){
    cin>>N;
    int a,b;
    for(int i=0;i<N;i++){
        cin>>a>>b;
        nd[i].left_rk=a;
        nd[i].right_rk=b;
    }
    
    for(int i=0;i<N;i++) cin>>numbers[i];
    
    sort(numbers,numbers+N);
    
    for(int i=0;i<N;i++) number_code[numbers[i]]=i;
}

int treeConstruct(int pr,int l,int depth){
    nd[pr].d=depth;
    
    int left_num=(nd[pr].left_rk==-1)?0:treeConstruct(nd[pr].left_rk,l,depth+1);
    
    nd[pr].val=numbers[l+left_num];
    
    depth_cnt[depth].push_back(nd[pr].val);
    
    int right_num=(nd[pr].right_rk==-1)?0:treeConstruct(nd[pr].right_rk,number_code[nd[pr].val]+1,depth+1);
    
    return left_num+right_num+1;
    
}

void showResult(){
    for(int i=0;depth_cnt[i].size()!=0;i++){
        for(int a:depth_cnt[i]){
            cout<<a;
            if(depth_cnt[i+1].size()==0 && a==depth_cnt[i][depth_cnt[i].size()-1]) cout<<endl;
            else cout<<' ';
        }
    }
}
