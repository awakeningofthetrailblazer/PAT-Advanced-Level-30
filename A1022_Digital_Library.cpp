#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>

using namespace std;

int N,M;

struct BOOK{
    char id[8];
    char title[81];
    char author[81];
    char keywords[60];
    char publisher[81];
    char publishedyear[5];
};

vector<BOOK> lby;

void readMessage(){
    BOOK temp;
    cin.getline(temp.id,8);
    cin.getline(temp.title,81);
    cin.getline(temp.author,81);
    cin.getline(temp.keywords,60);
    cin.getline(temp.publisher,81);
    cin.getline(temp.publishedyear,5);
    lby.push_back(temp);
    
    //cout<<temp.id<<endl;
}

bool cmpMessage(char*a,char*b){
    int k=0;
    bool cc=false;
    while(a[k]==b[k] && b[k]!='\0'&& a[k]!='\0' ){
        k++;
    }
    if(a[k]=='\0' && (b[k]=='\0' || b[k]==' ')) cc=true;
    return cc;
}

bool cmpKeywords(char*a,char*b){
    int k=0;
    bool cc=false;
    while(b[k]!='\0'){
        if(k==0 || b[k-1]==' '){
            if(cmpMessage(a,b+k)) cc=true;
        }
        k++;
    }
    return cc;
}

bool cmp(BOOK a,BOOK b){
    if(strcmp(a.id,b.id)<0) return true;
    else return false;
}

void searchMessage(char* msg){
    bool therethere=false;
    for(vector<BOOK>::iterator it=lby.begin();it!=lby.end();it++){
        if(cmpMessage(msg,it->id)){
            cout<<it->id<<endl;
            therethere=true;
            continue;
        }
        if(cmpMessage(msg,it->title)){
            cout<<it->id<<endl;
            therethere=true;
            continue;
        }
        if(cmpMessage(msg,it->author)){
            cout<<it->id<<endl;
            therethere=true;
            continue;
        }
        if(cmpKeywords(msg,it->keywords)){
            cout<<it->id<<endl;
            therethere=true;
            continue;
        }
        if(cmpMessage(msg,it->publisher)){
            cout<<it->id<<endl;
            therethere=true;
            continue;
        }
        if(cmpMessage(msg,it->publishedyear)){
            cout<<it->id<<endl;
            therethere=true;
            continue;
        }
    }
    if(therethere==false) cout<<"Not Found"<<endl;
}

int main(){
    scanf("%d\n",&N);
    
    while(N--){readMessage();}
    
    sort(lby.begin(),lby.end(),cmp);
    
    scanf("%d\n",&M);
    
    while(M--){
        int rk;
        char msg[1000];
        scanf("%d: ",&rk);
        cin.getline(msg,1000);
        cout<<rk<<": "<<msg<<endl;
        searchMessage(msg);
    }
    
    return 0;
}
