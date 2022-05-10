#include<bits/stdc++.h>

using namespace std;

int N;

struct node{
    int val;
    node*left=nullptr;
    node*right=nullptr;
    node(int x):val(x){}
};

vector<int> seq;

unordered_map<int,int> lvl_record;

int max_lvl=0;

void init();

node* bstConstruct(int rk);

void bstInsert(node*rt,int x);

void dfs(node*p, int lvl);

void display();

int main(){
    init();
    
    node*root=bstConstruct(0);
    
    dfs(root,0);
    
    display();
    
    return 0;
}

void init(){
    cin>>N;
    int x;
    while(N--){
        cin>>x;
        seq.push_back(x);
    }
    N=seq.size();
}

node* bstConstruct(int rk){
    node*root=new node(seq[0]);
    for(int i=1;i<N;i++){
        bstInsert(root,seq[i]);
    }
    return root;
}

void bstInsert(node*rt,int x){
    if(x<=rt->val){
        if(rt->left==nullptr) rt->left=new node(x);
        else bstInsert(rt->left,x);
    }else if(x>rt->val){
        if(rt->right==nullptr) rt->right=new node(x);
        else bstInsert(rt->right,x);
    }
}

void dfs(node*p, int lvl){
    lvl_record[lvl]++;
    max_lvl=max(max_lvl,lvl);
    if(p->left!=nullptr) dfs(p->left,lvl+1);
    if(p->right!=nullptr) dfs(p->right,lvl+1);
}

void display(){
    if(max_lvl>0){
        int sum=lvl_record[max_lvl-1]+lvl_record[max_lvl];
        cout<<lvl_record[max_lvl]<<" + "<<lvl_record[max_lvl-1]<<" = "<<sum<<endl;
    }else cout<<lvl_record[max_lvl]<<" + 0 = "<<lvl_record[max_lvl]<<endl;
}
