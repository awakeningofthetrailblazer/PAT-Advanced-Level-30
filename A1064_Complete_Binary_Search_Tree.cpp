#include<bits/stdc++.h>

using namespace std;

const int maxn=1024;

vector<int> seq;

int level_order[maxn];

void init();

int dfs(int ln,int k);

int main(){
    init();
    
    int cnt=dfs(0,0);
    
    for(int i=0;i<seq.size();i++) {
        cout<<level_order[i];
        if(i==seq.size()-1) cout<<endl;
        else cout<<' ';
    }
    
    return 0;
}

void init(){
    int N,x;
    cin>>N;
    while(N--) {
        cin>>x;
        seq.push_back(x);
    }
    
    sort(seq.begin(),seq.end());
}

int dfs(int ln,int k){
    
    int left_num=k*2+1<seq.size()?dfs(ln,k*2+1):0;
    
    level_order[k]=seq[ln+left_num];
    
    int right_num=k*2+2<seq.size()?dfs(ln+left_num+1,k*2+2):0;
    
    return 1+left_num+right_num;
}
