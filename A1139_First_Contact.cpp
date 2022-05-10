#include<bits/stdc++.h>

using namespace std;

int N,M,K;
const int maxn=1e5;

struct MD{
    int f1=-1,f2=-1;
};

vector<MD> media;

bool isMale[maxn];

unordered_set<int> relations[maxn];

void init();

int setGender(string x);

void queries();

void lookup(int a,int b);

bool cmp(MD a,MD b);

void print(int x);

int main(){
    init();
    
    //if(N==300) return -1;
    
    queries();
    
    return 0;
}

void init(){
    cin>>N>>M;
    int tempM=M,a,b;
    string aa,bb;
    while(tempM--){
        cin>>aa>>bb;
        a=setGender(aa);
        b=setGender(bb);
        //cout<<a<<' '<<b<<endl;
        relations[a].insert(b);
        relations[b].insert(a);
    }
    
    cin>>K;
}

int setGender(string x){
    int k,res=0;
    if(x[0]=='-') k=1;
    else k=0;
    
    for(int i=k;i<x.size();i++){
        res*=10;
        res+=x[i]-'0';
    }
    
    if(x[0]=='-') {
        isMale[res]=false;
    }
    else {
        isMale[res]=true;
    }
    
    return res;
}

void queries(){
    
    int a,b;
    while(K--){
        cin>>a>>b;
        a=a>0?a:-a;
        b=b>0?b:-b;
        lookup(a,b);
    }
}

void lookup(int a,int b){
    media.clear();
    
    for(int f1:relations[a]){
        if(isMale[a]!=isMale[f1] || f1==b) continue;
        for(int f2:relations[b]){
            if(isMale[b]!=isMale[f2] || f2==a) continue;
            if(relations[f1].find(f2)!=relations[f1].end()){
                media.push_back({f1,f2});
            }
        }
    }
    
    cout<<media.size()<<endl;
    
    sort(media.begin(),media.end(),cmp);
    
    for(MD x:media){
        print(x.f1);
        cout<<' ';
        print(x.f2);
        cout<<endl;
    }
}

bool cmp(MD a,MD b){
    if(a.f1!=b.f1) return a.f1<b.f1;
    else return a.f2<b.f2;
}

void print(int x){
    cout<<setw(4)<<setfill('0')<<x;
}
