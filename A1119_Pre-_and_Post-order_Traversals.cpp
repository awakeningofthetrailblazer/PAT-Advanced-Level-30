#include<bits/stdc++.h>

using namespace std;

const int maxn=31;

int N,preorder[maxn],postorder[maxn];
unordered_map<int,int> prerank,postrank;
bool multi=false;

struct node{
    int val;
    node*left=nullptr;
    node*right=nullptr;
    node(int x): val(x){}
};

void treeConstruct(node*p,int l,int r){
    if(l>=r) return;
    //p=new node(preorder[l]);
    //if(p==root) cout<<"root"<<endl;
    int pork=postrank[p->val];
    
    if(l+1<r && preorder[l+1]!=postorder[pork-1]){
        int rk=prerank[postorder[pork-1]];
        p->left=new node(preorder[l+1]);
        p->right=new node(preorder[rk]);
        treeConstruct(p->left,l+1,rk);
        treeConstruct(p->right,rk,r);
    }else if(l+1<r){
        multi=true;
        p->left=new node(preorder[l+1]);
        treeConstruct(p->left,l+1,r);
    }
    
    //cout<<p->val<<endl;
}

void inorder(node*p){
    if(p==nullptr) return;
    
    inorder(p->left);
    
    if(p->val!=postorder[0]) cout<<' ';
    cout<<p->val;
    
    inorder(p->right);
}

int main(){
    cin>>N;
    for(int i=0;i<N;i++){
        cin>>preorder[i];
        prerank[preorder[i]]=i;
    }
    for(int i=0;i<N;i++){
        cin>>postorder[i];
        postrank[postorder[i]]=i;  
    }
    
    node*root=new node(preorder[0]);
    
    treeConstruct(root,0,N);
    
    if(multi) {cout<<"No"<<endl;}
    else {cout<<"Yes"<<endl;}
    
    //cout<<root->val;
    
    inorder(root);
    cout<<endl;
    
    return 0;
}
