#include<bits/stdc++.h>

using namespace std;

map<int,int>M;
map<int,int>::iterator mid;
int beforemid;
stack<int>S;

void adjust_mid(){
    if(beforemid>=(S.size()+1)/2){
        mid--;
        beforemid-=mid->second;
    }else if(beforemid+mid->second<(S.size()+1)/2){
        beforemid+=mid->second;
        mid++;
    }
}

int main(){
    
    int N;
    cin>>N;
    while(N--){
        string command;
        cin>>command;
        
        if(command[1]=='u'){//push
            int key;
            cin>>key;
            S.push(key);
            M[key]++;
            if(S.size()==1){
                mid=M.begin();
                beforemid=0;
            }else{
                if(key<mid->first)beforemid++;
                adjust_mid();
            }
        }else if(command[1]=='o'){
            if(!S.size()){
                cout<<"Invalid"<<endl;
            }else{
                int key=S.top();
                cout<<key<<endl;
                S.pop();
                M[key]--;
                if(key<mid->first)beforemid--;
                adjust_mid();
                if(M[key]==0){
                    if(mid->first==key) mid++;
                    M.erase(key);
                }
            }
        }else{
            if(!S.size()) cout<<"Invalid"<<endl;
            else cout<<mid->first<<endl;
        }
    }
    
    return 0;
}
