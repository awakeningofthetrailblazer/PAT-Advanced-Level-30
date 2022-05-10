#include<bits/stdc++.h>

using namespace std;

const int maxn=101;

long long N,M,S;
long long weight[maxn];
vector<int> nd[maxn];

vector<int> temp_child_res;
vector<vector<int>> res;

void dfs(int id, long long w);

bool cmp(vector<int> a,vector<int> b);

int main(){
    cin>>N>>M>>S;
    for(int i=0;i<N;i++) cin>>weight[i];
    int id,K,x;
    while(M--){
        cin>>id>>K;
        while(K--){
            cin>>x;
            nd[id].push_back(x);
        }
    }
    
    dfs(0, weight[0]);
    
    sort(res.begin(),res.end(),cmp);
    
    for(vector<int> res_child:res){
        for(int i=0;i<res_child.size();i++){
            cout<<res_child[i];
            if(i==res_child.size()-1) cout<<endl;
            else cout<<' ';
        }
    }
    
    return 0;
}

void dfs(int id, long long w){
    temp_child_res.push_back(weight[id]);
    if(w>=S){
        if(w==S && nd[id].size()==0) res.push_back(temp_child_res);
        temp_child_res.pop_back();
        return;
    }
    for(int x:nd[id]){
        dfs(x,w+weight[x]);
    }
    if(temp_child_res.size())temp_child_res.pop_back();
}

bool cmp(vector<int> a,vector<int> b){
    for(int i=0;i<a.size() && i<b.size();i++){
        if(a[i]==b[i]) continue;
        else return a[i]>b[i];
    }
    return false;
}
