#include<bits/stdc++.h>

using namespace std;

int N,maxlen=0;
vector<int> stripe;
unordered_map<int,int> evaorder;

void init();

void pickMaxLen();

int main(){
    
    init();
    
    pickMaxLen();
    
    cout<<maxlen<<endl;
    
    return 0;
}

void init(){
    cin>>N;
    int M,L,x;
    cin>>M;
    for(int i=1;i<=M;i++){
        cin>>x;
        evaorder[x]=i;
    }
    cin>>L;
    while(L--){
        cin>>x;
        if(evaorder[x]) stripe.push_back(evaorder[x]);
    }
}

void pickMaxLen(){
    vector<int> len_num;
    for(int i=0;i<stripe.size();i++) len_num.push_back(1);
    for(int i=1;i<len_num.size();i++){
        for(int j=0;j<i;j++){
            if(stripe[j]<=stripe[i]) len_num[i]=len_num[j]+1;
        }
    }
    
    for(int a:len_num){
        if(a>maxlen) maxlen=a;
    }
}
