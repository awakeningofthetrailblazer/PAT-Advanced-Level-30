#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int N,K,P,maxFacSum=0;
vector<int> fac,ans,temp;

int power(int x){
    int as=1;
    for(int i=0;i<P;i++){as*=x;}
    return as;
}

void init(){
    int i=0,t=0;
    while(t<=N){
        fac.push_back(t);
        t=power(++i);
    }
}

void DFS(int index,int nowK,int sum,int facSum){
    if(sum==N && nowK==K){
        if(facSum>maxFacSum){
            ans=temp;
            maxFacSum=facSum;
        }
        return;
    }
    if(sum>N || nowK>K) return;
    if(index-1>=0){
        temp.push_back(index);
        DFS(index,nowK+1,sum+fac[index],facSum+index);
        temp.pop_back();
        DFS(index-1,nowK,sum,facSum);
    }
}

int main(){
    cin>>N>>K>>P;
    init();
    DFS(fac.size()-1,0,0,0);
    if(maxFacSum==0) cout<<"Impossible"<<endl;
    else{
        cout<<N<<" = ";
        for(int i=0;i<ans.size();i++){
            if(i!=0) cout<<" + ";
            cout<<ans[i]<<'^'<<P;
        }
        cout<<endl;
    }
    return 0;
}
