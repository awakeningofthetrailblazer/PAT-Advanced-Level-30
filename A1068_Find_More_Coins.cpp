#include<bits/stdc++.h>

using namespace std;

int N,M;
vector<int> coins,res;

void init();

void display();

bool cmp(int a,int b);

void calRes();

int main(){
    init();
    
    calRes();
    
    display();
    
    return 0;
}

void init(){
    cin>>N>>M;
    int x;
    for(int i=0;i<N;i++){
        cin>>x;
        if(x<=M) coins.push_back(x);
    }
    sort(coins.begin(),coins.end(), cmp);
    
    N=coins.size();
}

void display(){
    //cout<<"No Solution"<<endl;
    //return;
    if(res.size()){
        for(int a:res){
            cout<<a;
            if(a==*(res.end()-1)) cout<<endl;
            else cout<<' ';
        }
    }else{
        cout<<"No Solution"<<endl;
    }
}

bool cmp(int a,int b){
    return a>b;
}

void calRes(){
    unordered_map<int,int> dp;
    for(int i=-1;i<N;i++) dp[i]=0;
    int sum=0;
    vector<int> tempres[101];
    for(int i=0;i<N;i++){
        for(int v=M;v>=coins[i];v--){
            if(dp[v]<=dp[v-coins[i]]+coins[i]){
                dp[v]=dp[v-coins[i]]+coins[i];
                tempres[v]=tempres[v-coins[i]];
                tempres[v].push_back(coins[i]);
                //cout<<i<<' '<<v<<endl;
            }
        }
    }
    
    if(dp[M]==M) res=tempres[M];
    //cout<<res.size()<<endl;
    sort(res.begin(),res.end());
}
