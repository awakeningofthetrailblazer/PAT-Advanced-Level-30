#include<bits/stdc++.h>

using namespace std;

const int maxn=1024;
int N;
vector<int> numbers;
vector<int> seq;

bool max_heap=true,min_heap=true;

void readData();

void treeConstruct(int x);

void showResult();

int main(){
    
    readData();
    
    treeConstruct(0);
    
    showResult();
    
    return 0;
}

void readData(){
    cin>>N;
    while(N--) {
        int x; cin>>x;
        numbers.push_back(x);
    }
    N=numbers.size();
}

void treeConstruct(int x){
    seq.push_back(numbers[x]);
    
    if(2*x+2<N) {
        treeConstruct(2*x+2);
        if(numbers[2*x+2]<numbers[x]) min_heap=false;
        if(numbers[2*x+2]>numbers[x]) max_heap=false;
    }
    if(2*x+1<N) {
        treeConstruct(2*x+1);
        if(numbers[2*x+1]<numbers[x]) min_heap=false;
        if(numbers[2*x+1]>numbers[x]) max_heap=false;
    }
    else{
        for(int a:seq){
            cout<<a;
            if(a!=*(seq.end()-1)) cout<<' ';
            else cout<<endl;
        }
    }
    
    seq.pop_back();
}

void showResult(){
    if(max_heap) cout<<"Max Heap"<<endl;
    else if(min_heap) cout<<"Min Heap"<<endl;
    else cout<<"Not Heap"<<endl;
}
