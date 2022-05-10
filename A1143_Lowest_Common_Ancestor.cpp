#include<bits/stdc++.h>

using namespace std;

const int maxn=10002;

int M,N;
unordered_map<int,int> prerank;
int preorder[maxn]={0};

struct node{
    int val;
    int lvl;
    int father;
    //int left;
    //int right;
}nd[maxn];//inorder

void queryAncestor(int u,int v);

void treeConstruct(int l,int r,int ftr,int lv);

int main(){
    cin>>M>>N;
    
    //if(M==1000) return -1;
    
    for(int i=1;i<=N;i++) {
        //cin>>nd[i].val;
        scanf("%d",&nd[i].val);
        prerank[nd[i].val]=i;
    }
    
    treeConstruct(1,N+1,0,0);
    
    //for(int i=1;i<=N;i++) cout<<nd[i].lvl<<endl;
    
    while(M--){
        int uu,vv;
        //cin>>uu>>vv;
        scanf("%d %d",&uu,&vv);
        //cout<<"val:"<<u<<' '<<v<<endl;
        queryAncestor(uu,vv);
    }
    
    return 0;
}

void treeConstruct(int l,int r,int ftr,int lv){
    int rnk=l;
    
    /*
    int rnk,min_prernk=maxn;
    
    for(int i=l;i<r;i++){
        if(min_prernk>prerank[nd[i].val]){
            min_prernk=prerank[nd[i].val];
            rnk=i;
        }
    }*/
    
    nd[rnk].father=ftr;
    nd[rnk].lvl=lv;
    
    int rtl=-1,rtr=-1;
    for(int i=l+1;i<r;i++){
        if(rtl==-1 && nd[i].val<nd[l].val) rtl=i;
        if(nd[i].val>nd[l].val) {rtr=i;break;}
    }
    
    if(rtl!=-1 && rtr!=-1) {
        treeConstruct(l+1,rtr,l,lv+1);
        treeConstruct(rtr,r,l,lv+1);
    }else if(rtl!=-1 || rtr!=-1) treeConstruct(l+1,r,l,lv+1);
    
    //return rnk;
}

void queryAncestor(int u,int v){
    //cout<<u<<' '<<v<<endl;
    int uid=prerank[u];
    int vid=prerank[v];
    
    if(vid==0 || uid==0){
        
        if(uid+vid==0){
            //cout<<"id:"<<uid<<" "<<vid<<endl;
            //cout<<"ERROR: "<<u<<" and "<<v<<" are not found."<<endl;
            printf("ERROR: %d and %d are not found.\n",u,v);
        }else{
            int temp;
            if(uid) temp=v;
            else temp=u;
            //cout<<"ERROR: "<<temp<<" is not found."<<endl;
            printf("ERROR: %d is not found.\n",temp);
        }
        
        return;
    }
    
    //cout<<"test"<<endl;
    int ancestor;
    
    if(nd[uid].lvl==nd[vid].lvl){
        if(u==v){
            //cout<<v<<" is an ancestor of "<<u<<"."<<endl;
            printf("%d is an ancestor of %d.\n",v,u);
            return;
        }
        
        int temp_uid=uid,temp_vid=vid;
        while(true){
            if(nd[temp_uid].father!=nd[temp_vid].father || temp_uid==uid){
                temp_uid=nd[temp_uid].father;
                temp_vid=nd[temp_vid].father;
            }else break;
        }
        ancestor=nd[temp_uid].val;
        //cout<<"LCA of "<<u<<" and "<<v<<" is "<<ancestor<<"."<<endl;
        printf("LCA of %d and %d is %d.\n",u,v,ancestor);
    }else if(nd[uid].lvl>nd[vid].lvl){
        
        int temp=uid;
        while(nd[temp].lvl!=nd[vid].lvl){
            temp=nd[temp].father;
        }
        if(temp==vid){
            //cout<<v<<" is an ancestor of "<<u<<"."<<endl;
            printf("%d is an ancestor of %d.\n",v,u);
            return;
        }
        int temp_uid=temp,temp_vid=vid;
        while(temp_uid!=temp_vid){
            temp_uid=nd[temp_uid].father;
            temp_vid=nd[temp_vid].father;
        }
        ancestor=nd[temp_uid].val;
        //cout<<"LCA of "<<u<<" and "<<v<<" is "<<ancestor<<"."<<endl;
        printf("LCA of %d and %d is %d.\n",u,v,ancestor);
    }else if(nd[uid].lvl<nd[vid].lvl){
        //cout<<"lvl:"<<nd[uid].val<<' '<<nd[uid].lvl<<endl;
        
        int temp=vid;
        while(nd[temp].lvl!=nd[uid].lvl){
            //cout<<nd[temp].val<<"temp"<<nd[nd[temp].father].val<<endl;
            
            temp=nd[temp].father;
            
        }
        if(temp==uid){
            //cout<<u<<" is an ancestor of "<<v<<"."<<endl;
            printf("%d is an ancestor of %d.\n",u,v);
            return;
        }
        int temp_uid=uid,temp_vid=temp;
        while(temp_uid!=temp_vid){
            temp_uid=nd[temp_uid].father;
            temp_vid=nd[temp_vid].father;
        }
        ancestor=nd[temp_vid].val;
        //cout<<"LCA of "<<u<<" and "<<v<<" is "<<ancestor<<"."<<endl;
        printf("LCA of %d and %d is %d.\n",u,v,ancestor);
    }
}
