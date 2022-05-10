#include<bits/stdc++.h>

using namespace std;

const int maxn=1024;
int M,N,numbers[maxn];
bool maxheap=true,minheap=true;

struct node{
    int val;
    node*left=nullptr;
    node*right=nullptr;
    node(int x): val(x){}
};

node*root=nullptr;

void treeConstruct(node*p,int rk){
    p->val=numbers[rk];
    if(2*rk+1<N){
        if(numbers[rk]>numbers[2*rk+1]) minheap=false;
        if(numbers[rk]<numbers[2*rk+1]) maxheap=false;
        p->left=new node(numbers[2*rk+1]);
        treeConstruct(p->left,2*rk+1);
    }
    if(2*rk+2<N){
        if(numbers[rk]>numbers[2*rk+2]) minheap=false;
        if(numbers[rk]<numbers[2*rk+2]) maxheap=false;
        p->right=new node(numbers[2*rk+2]);
        treeConstruct(p->right,2*rk+2);
    }
}

void preorder(node*p){
    if(p==nullptr) return;
    
    preorder(p->left);
    preorder(p->right);
    
    cout<<p->val;
    if(p==root) cout<<endl;
    else cout<<' ';
}

int main(){
    cin>>M>>N;
    
    while(M--){
        for(int i=0;i<N;i++) scanf("%d",&numbers[i]);
        maxheap=true;
        minheap=true;
        root=new node(numbers[0]);
        treeConstruct(root,0);
        if(maxheap) cout<<"Max Heap"<<endl;
        else if(minheap) cout<<"Min Heap"<<endl;
        else cout<<"Not Heap"<<endl;
        preorder(root);
    }
    
    return 0;
}
