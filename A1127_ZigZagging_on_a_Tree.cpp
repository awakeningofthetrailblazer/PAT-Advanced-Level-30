#include<bits/stdc++.h>

using namespace std;

struct node{
    int val;
    int lvl;
    node*left=nullptr;
    node*right=nullptr;
    node(int x,int l):val(x),lvl(l){}
};

const int maxn=31;
int N,postorder[maxn];
unordered_map<int,int> inorderrk,postorderrk;

void treeConstruct(node*nd,int lb,int ub,int lvl);

void zigzag(node*x);

int main(){
    
    cin>>N;
    int x;
    for(int i=0;i<N;i++) {
        cin>>x;
        inorderrk[x]=i;
    }
    for(int i=0;i<N;i++) {
        cin>>x;
        postorder[i]=x;
        postorderrk[x]=i;
    }
    
    node*root=nullptr;
    root=new node(postorder[N-1],0);
    treeConstruct(root,0,N,0);
    
    zigzag(root);
    
    return 0;
}

void treeConstruct(node*nd,int lb,int ub,int lvl){
    //cout<<nd->val<<endl;
    if(lb>=ub) return;
    
    int irk=inorderrk[nd->val],pork=postorderrk[nd->val];
    int leftnum=irk-lb,rightnum=ub-irk-1;
    if(leftnum){
        nd->left=new node(postorder[pork-rightnum-1],lvl+1);
        treeConstruct(nd->left,lb,irk,lvl+1);
    }
    if(rightnum){
        nd->right=new node(postorder[pork-1], lvl+1);
        treeConstruct(nd->right,irk+1,ub,lvl+1);
    }
    
    
}

void zigzag(node*x){
    queue<node*> seq;
    
    seq.push(x);
    
    vector<int> que[maxn];
    int maxl=0;
    while(seq.size()){
        node *temp=seq.front();
        que[temp->lvl].push_back(temp->val);
        if(maxl<temp->lvl) maxl=temp->lvl;
        seq.pop();
        if(temp->left!=nullptr) seq.push(temp->left);
        if(temp->right!=nullptr) seq.push(temp->right);
    }
    
    for(int i=0;i<=maxl;i++){
        if(i%2){
            for(int x:que[i]) {
                cout<<x;
                if(i==maxl && x==*(que[i].end()-1)) cout<<endl;
                else cout<<' ';
            }
        }else{
            for(vector<int>::iterator it=que[i].end();it!=que[i].begin();it--) {
                cout<<*(it-1);
                if(i==maxl && it==que[i].begin()+1) cout<<endl;
                else cout<<' ';
            }
        }
    }
}
