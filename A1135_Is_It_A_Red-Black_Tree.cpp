#include<bits/stdc++.h>

using namespace std;
const int maxn=32;
int N,K,numbers[maxn],depth_stand;
bool isRed[maxn],is_br_tree;

struct node{
    int val;
    bool is_red;
    node*left=nullptr;
    node*right=nullptr;
    node(int x,bool is_red): val(x),is_red(is_red){}
};

void treeConstruct(node*p,int l,int r);

void dfs(node*p,int d);

int main(){
    cin>>K;
    while(K--){
        cin>>N;
        int x;
        for(int i=0;i<N;i++){
            cin>>x;
            if(x>0) numbers[i]=x,isRed[i]=false;
            if(x<0) numbers[i]=-x,isRed[i]=true;
        }
        
        node*root=new node(numbers[0],isRed[0]);
        treeConstruct(root,1,N);
        is_br_tree=true,depth_stand=-1;
        dfs(root,0);
        if(isRed[0]) is_br_tree=false;
        if(is_br_tree) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }
    return 0;
}

void treeConstruct(node*p,int l,int r){
    if(l==r) return;
    
    int lk=l-1,rk=r;
    if(numbers[l]<p->val){
        p->left=new node(numbers[l],isRed[l]);
        lk=l;
    }
    for(int i=l;i<r;i++){
        if(numbers[i]>p->val){
            p->right=new node(numbers[i],isRed[i]);
            rk=i;
            break;
        }
    }
    if(lk!=l-1) treeConstruct(p->left,l+1,rk);
    if(rk!=r) treeConstruct(p->right,rk+1,r);
}

void dfs(node*p,int d){
    if(p==nullptr){
        if(depth_stand==-1) depth_stand=d;
        else if(d!=depth_stand) is_br_tree=false;
        
        //cout<<d<<' ';
        return;
    }
    if(p->is_red) {
        if((p->left!=nullptr && (p->left)->is_red) || (p->right!=nullptr && (p->right)->is_red)) is_br_tree=false;
        dfs(p->left,d);
        dfs(p->right,d);
    }else{
        dfs(p->left,d+1);
        dfs(p->right,d+1);
    }
}
