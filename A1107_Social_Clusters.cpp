#include<bits/stdc++.h>

using namespace std;
const int maxn=1024;
int N,cnt=0;

unordered_set<int> hobbies[maxn],persons[maxn],temp;
vector<unordered_set<int>> clusters;
bool visited[maxn]={false};
int hobbies_code[maxn]={0};

void init();

void dfs(int x);

bool cmp(unordered_set<int> a,unordered_set<int> b);

int main(){
    init();
    
    for(int i=1;i<=N;i++){
        if(!visited[i]) {
            temp.clear();
            dfs(i);
            clusters.push_back(temp);
        }
    }
    
    cout<<clusters.size()<<endl;
    
    sort(clusters.begin(),clusters.end(),cmp);
    
    for(vector<unordered_set<int>>::iterator it=clusters.begin();it!=clusters.end();it++){
        cout<<it->size();
        if(it==clusters.end()-1) cout<<endl;
        else cout<<' ';
    }
    
    return 0;
}

void init(){
    cin>>N;
    int k,x;
    for(int i=1;i<=N;i++){
        scanf("%d:",&k);
        while(k--){
            cin>>x;
            hobbies[i].insert(x);
            persons[x].insert(i);
        }
    }
}

void dfs(int x){
    visited[x]=true;
    temp.insert(x);
    for(unordered_set<int>::iterator it=hobbies[x].begin();it!=hobbies[x].end();it++){
        for(unordered_set<int>::iterator is=persons[*it].begin();is!=persons[*it].end();is++){
            if(!visited[*is]) dfs(*is);
        }
    }
}

bool cmp(unordered_set<int> a,unordered_set<int> b){
    return a.size()>b.size();
}
