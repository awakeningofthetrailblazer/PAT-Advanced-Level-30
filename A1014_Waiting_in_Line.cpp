#include<iostream>
#include<vector>
#include<iomanip>

using namespace std;

int N,M,K,Q;//windows,length,customers,queries

const int startPoint=8*60;
const int overPoint=17*60;

vector<int> win[21];

int cusTime[1010];

int beginTime[1010];

int endTime[1010];

int winChose[1010];

bool bye[1010]={false};

void assign(int k){
    if(bye[k]==true){
        bye[k+1]=true;
        return;
    }
    int minLen=M,minWin=-1;
    int earlyWin=-1,earlyTime=overPoint;
    for(int i=0;i<N;i++){
        int len=win[i].size();
        if(len<minLen){
            minLen=len;
            minWin=i;
        }
        if(len>=M){
            int bb=win[i][len-M];
            if(earlyTime>endTime[bb]){
                earlyTime=endTime[bb];
                earlyWin=i;
            }
        }
    }
    if(minWin!=-1){
        winChose[k]=minWin;
        if(minLen>0){
            int lb=win[minWin][minLen-1];
            beginTime[k]=endTime[lb];
        }
        endTime[k]=beginTime[k]+cusTime[k];
        win[minWin].push_back(k);
    }else{
        winChose[k]=earlyWin;
        int ll=win[earlyWin].size();
        int lb=win[earlyWin][ll-1];
        beginTime[k]=endTime[lb];
        endTime[k]=beginTime[k]+cusTime[k];
        win[earlyWin].push_back(k);
    }
    
    if(beginTime[k]>=overPoint) bye[k]=true;
    
    bool stillWait=false;
    for(int i=0;i<N;i++){
        if(win[i].size()!=0){
            int l=win[i].size();
            int butt=win[i][l-1];
            if(bye[butt]==false) stillWait=true;
        }else stillWait=true;
    }
    
    if(stillWait==false) bye[k+1]=true;
}

void showTime(int q){
    int tt=endTime[q];
    int h=tt/60;
    int m=tt%60;
    cout<<setw(2)<<setfill('0')<<h;
    cout<<':';
    cout<<setw(2)<<setfill('0')<<m<<endl;
}

int main(){
    
    cin>>N>>M>>K>>Q;
    
    fill(beginTime,beginTime+N,startPoint);
    fill(endTime,endTime+N,startPoint);
    fill(winChose,winChose+N,-1);
    
    for(int i=0;i<K;i++){
        cin>>cusTime[i];
        assign(i);
    }
    
    for(int i=0;i<Q;i++){
        int q;
        cin>>q;
        if(bye[q-1]==true) cout<<"Sorry"<<endl;
        else showTime(q-1);
    }
    
    return 0;
}
