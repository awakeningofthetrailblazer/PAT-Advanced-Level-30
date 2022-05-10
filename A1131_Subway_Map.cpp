#include<bits/stdc++.h>

using namespace std;

//unordered_map<int,unordered_map<int,int>> subwaynet;
const int maxn=1e5;

int N,M,K;

unordered_set<int> subwaynet[maxn];

unordered_map<int,unordered_map<int,int>> line_of_node;

bool visited[maxn]={false};

int temp_stops;
int stops;
vector<int> temp_transfer_stops;
vector<int> transfer_stops;
vector<int> temp_line_code;
vector<int> line_code;

void init();

void query();

void get_route(int s,int t);

void dfs(int s,int t,int ln);

void fourdigits(int x);

int main(){
    init();
    
    query();
    
    return 0;
}

void init(){
    int nd;
    cin>>N;
    for(int i=1;i<=N;i++){
        cin>>M;
        int pren=-1;
        while(M--){
            cin>>nd;
            if(pren>=0){
                subwaynet[pren].insert(nd);
                subwaynet[nd].insert(pren);
                line_of_node[nd][pren]=i;
                line_of_node[pren][nd]=i;
            }
            pren=nd;
        }
    }
}

void query(){
    int s, t;
    cin>>K;
    while(K--){
        cin>>s>>t;
        get_route(s,t);
    }
}

void get_route(int s, int t){
    //fill(visited,visited+maxn,false);
    temp_stops=0;
    temp_transfer_stops.clear();
    temp_line_code.clear();
    stops=0;
    transfer_stops.clear();
    line_code.clear();
    dfs(s,t,0);
    int stop_num=stops;
    
    int k=0;
    
    if(line_code.size()) {
        cout<<stop_num<<endl;
        cout<<"Take Line#"<<line_code[0]<<" from ";
    }
    else cout<<'0'<<endl<<"Take Line#"<<0<<" from ";
    fourdigits(s);
    cout<<" to ";
    
    for(int a:transfer_stops){
        k++;
        fourdigits(a);
        cout<<".\nTake Line#"<<line_code[k]<<" from ";
        fourdigits(a);
        cout<<" to ";
    }
    fourdigits(t);
    cout<<".\n";
}

void dfs(int s,int t,int ln){
    //if(stops.size() && s!=t && stops.size()<temp_stops.size()) return;
    
    visited[s]=true;
    if(s == t){
        if(ln) temp_line_code.push_back(ln);
        if(stops==0 || stops > temp_stops ||
          (stops == temp_stops && 
                 temp_transfer_stops.size() < transfer_stops.size())){
            stops=temp_stops;
            transfer_stops=temp_transfer_stops;
            line_code=temp_line_code;
        }
        if(ln) temp_line_code.pop_back();
    }else{
        for(int nxt:subwaynet[s]){
            if(!visited[nxt]){
                int newln=line_of_node[s][nxt];
                
                if(ln && newln!=ln) {
                    temp_transfer_stops.push_back(s);
                    temp_line_code.push_back(ln);
                }
                
                temp_stops++;
                dfs(nxt,t,newln);
                temp_stops--;
                
                if(ln && newln!=ln) {
                    temp_transfer_stops.pop_back();
                    temp_line_code.pop_back();
                }
            }
        }
    }
    
    visited[s]=false;
}

void fourdigits(int x){
    cout<<setw(4)<<setfill('0')<<x;
}
