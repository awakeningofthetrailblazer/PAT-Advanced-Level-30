#include<bits/stdc++.h>

using namespace std;

struct NODE{
    int v,height;
    NODE*left=nullptr;
    NODE*right=nullptr;
    int cnt=0;
};

class AVL{
private:
    int N;
    bool isComplete=true;
    NODE*root=nullptr;
    
    //创建结点
    NODE* newNode(int v){
        NODE* nd=new NODE;
        nd->v=v;
        nd->height=1;
        nd->left=nd->right=nullptr;
        return nd;
    }
    
    //取height
    int getHeight(NODE*x){
        if(x==nullptr) return 0;
        else return x->height;
    }
    
    //平衡因子
    int getBalanceFactor(NODE*x){
        return getHeight(x->left)-getHeight(x->right);
    }
    
    //更新height
    void updateHeight(NODE* x){
        x->height=max(getHeight(x->left),getHeight(x->right))+1;
    }
    
    //左旋
    void LL(NODE*&x){
        NODE*temp=x->right;
        x->right=temp->left;
        temp->left=x;
        
        updateHeight(x);
        updateHeight(temp);
        
        x=temp;
    }
    
    //右旋
    void RR(NODE*&x){
        NODE*temp=x->left;
        x->left=temp->right;
        temp->right=x;
        
        updateHeight(x);
        updateHeight(temp);
        
        x=temp;
    }
    
    //插入
    void insert(NODE*&x,int v){
        if(x==nullptr){
            x=newNode(v);
            return;
        }
        if(v<x->v) {
            insert(x->left,v);
            updateHeight(x);
            if(getBalanceFactor(x)==2){
                if(getBalanceFactor(x->left)==1) RR(x);
                else if(getBalanceFactor(x->left)==-1){
                    LL(x->left);
                    RR(x);
                }
            }
        }
        else {
            insert(x->right,v);
            updateHeight(x);
            if(getBalanceFactor(x)==-2){
                if(getBalanceFactor(x->right)==-1) LL(x);
                else if(getBalanceFactor(x->right)==1){
                    RR(x->right);
                    LL(x);
                }
            }
        }
    }
public:
    AVL(){
        cin>>N;
        int v;
        for(int i=0;i<N;i++){
            cin>>v;
            insert(root,v);
        }
    }
    
    bool isCom(){
        return isComplete;
    }
    
    vector<int> levelOrder(){
        vector<int> res;
        
        queue<NODE*> temp;
        temp.push(root);
        res.push_back(root->v);
        int cnt=0;
        while(temp.size()){
            NODE*head=temp.front();
            if(head->cnt!=cnt) isComplete=false;
            
            temp.pop();
            cnt++;
            if(head->left!=nullptr){
                temp.push(head->left);
                res.push_back((head->left)->v);
                (head->left)->cnt=head->cnt*2+1;
            }
            if(head->right!=nullptr){
                temp.push(head->right);
                res.push_back((head->right)->v);
                (head->right)->cnt=head->cnt*2+2;
            }
        }
        
        return res;
    }
};

int main(){
    
    AVL avl;
    
    
    vector<int> res=avl.levelOrder();
    for(int i=0;i<res.size();i++){
        cout<<res[i];
        if(i==res.size()-1) cout<<endl;
        else cout<<' ';
    }
    
    if(avl.isCom()) cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
    
    return 0;
}
