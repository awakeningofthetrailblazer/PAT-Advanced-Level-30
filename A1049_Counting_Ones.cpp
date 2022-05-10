#include<iostream>
#include<cmath>

using namespace std;

int n,ans=0;

int main(){
    cin>>n;
    
    int left=n/10,cur=n%10,right=0;
    
    for (int i = 1; right != n; i *= 10){
        if(cur==0) ans+=left*i;
        else if(cur==1) ans+=left*i+right+1;
        else ans+=(left+1)*i;
        
        right += cur * i;
        cur = left % 10;
        left /= 10;
    }
    
    cout<<ans<<endl;
    return 0;
}
