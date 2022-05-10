#include<iostream>
#include<vector>
#include<algorithm>
#include<iomanip>
#include<cmath>

using namespace std;

int N,K,M,watch;
bool vipStand=false;
int waitingTable=-1;

const int openTime=8*3600;
const int closeTime=21*3600;

struct RCD{
    int arrivingTime=0;//seconds
    int playingMinutes=0;
    bool isVIP=false;
    int rank=1010;
    bool isAssigned=false;
    int startTime=closeTime;
    int tableNumber=-1;
};
vector<RCD> cstmr;

struct TBL{
    int serveNumber=0;
    bool isVIP=false;
    int changeTime=openTime;
};
vector<TBL> table;

bool cmp(RCD a,RCD b){
    return a.arrivingTime<b.arrivingTime;
}
bool cmp2(RCD a,RCD b){
    return a.rank<b.rank;
}

int getEndPoint(){
    int ee=closeTime+7201;
    for(vector<TBL>::iterator it=table.begin();it!=table.end();it++){
        if(ee>it->changeTime) {
            ee=it->changeTime;
            vipStand=it->isVIP;
            waitingTable=it-table.begin();
        }
    }
    return ee;
}

void readMessage(){
    cin>>N;
    watch=N;
    while(N--){
        RCD temp;
        int hh,mm,ss;
        double plm;
        bool vip;
        scanf("%d:%d:%d %lf",&hh,&mm,&ss,&plm);
        cin>>vip;
        if(plm>120) plm=120;
        if(hh>=21) continue;
        temp={hh*3600+mm*60+ss,plm,vip,watch};
        cstmr.push_back(temp);
    }
    
    watch=0;
    
    if(cstmr.size()!=0) sort(cstmr.begin(),cstmr.end(),cmp);
    
    cin>>K>>M;
    
    while(K--){
        TBL temp;
        table.push_back(temp);
    }
    
    while(M--){
        int tg;
        cin>>tg;
        table[tg-1].isVIP=true;
    }
}

void refresh(RCD& a,int rk){
    a.isAssigned=true;
    table[rk].serveNumber++;
    a.startTime=table[rk].changeTime>a.arrivingTime?
        table[rk].changeTime:a.arrivingTime;
    table[rk].changeTime=a.startTime+a.playingMinutes*60;
    a.tableNumber=rk;
    a.rank=watch++;
}

void dispatch(){    
    for(vector<RCD>::iterator it=cstmr.begin();it!=cstmr.end();it++){
        
        if(getEndPoint()==closeTime || it->arrivingTime>=closeTime) break;
        
        if(it->isAssigned) continue;
        
        if(it->isVIP){
            for(vector<TBL>::iterator is=table.begin();is!=table.end();is++){
                if(it->arrivingTime>=is->changeTime && is->isVIP==true){
                    refresh(*it,is-table.begin());
                    break;
                }
            }
            if(it->isAssigned) continue;
            for(vector<TBL>::iterator is=table.begin();is!=table.end();is++){
                if(it->arrivingTime>=is->changeTime){
                    refresh(*it,is-table.begin());
                    break;
                }
            }
        }else{
            for(vector<TBL>::iterator is=table.begin();is!=table.end();is++){
                if(it->arrivingTime>=is->changeTime){
                    refresh(*it,is-table.begin());
                    break;
                }
            }
        }
        
        if(it->isAssigned) continue;
        {
            bool len=true;
            while(len){
                len=false;
                int earlyEnd=getEndPoint();
                if(earlyEnd>=closeTime) break;
                if(vipStand){
                    for(vector<RCD>::iterator ip=it;ip!=cstmr.end() && ip->arrivingTime<=earlyEnd;ip++){
                        if(ip->isAssigned || ip->isVIP==false) continue;
                        len=true;
                        refresh(*ip,waitingTable);
                        break;
                    }
                    if(len) continue;
                    for(vector<RCD>::iterator ip=it;ip!=cstmr.end() && ip->arrivingTime<=earlyEnd;ip++){
                        if(ip->isAssigned) continue;
                        len=true;
                        refresh(*ip,waitingTable);
                        break;
                    }
                }else{
                    for(vector<RCD>::iterator ip=it;ip!=cstmr.end() && ip->arrivingTime<=earlyEnd;ip++){
                        if(ip->isAssigned) continue;
                        len=true;
                        refresh(*ip,waitingTable);
                        break;
                    }
                }
            }
        }
    }
}

void timeTransfer(int tt){
    int hh=tt/3600;
    hh%=24;
    int mm=(tt%3600)/60;
    int ss=tt%60;
    cout<<setw(2)<<setfill('0')<<hh;
    cout<<':';
    cout<<setw(2)<<setfill('0')<<mm;
    cout<<':';
    cout<<setw(2)<<setfill('0')<<ss;
}

void printMessage(){
    if(cstmr.size()) sort(cstmr.begin(),cstmr.end(),cmp2);
    
    for(vector<RCD>::iterator it=cstmr.begin();it!=cstmr.end();it++){
        if(!it->isAssigned) continue;
        timeTransfer(it->arrivingTime);
        cout<<' ';
        timeTransfer(it->startTime);
        int dt=round((it->startTime-it->arrivingTime)/60.0);
        //cout<<' '<<it->tableNumber<<' '<<it->playingMinutes<<' '<<it->isVIP<<' ';
        cout<<' '<<dt<<endl;
    }
    
    for(vector<TBL>::iterator it=table.begin();it!=table.end();it++){
        cout<<it->serveNumber;
        if(it==table.end()-1) cout<<endl;
        else cout<<' ';
    }
}

int main(){
    readMessage();
    
    dispatch();
    
    printMessage();
    
    return 0;
}
