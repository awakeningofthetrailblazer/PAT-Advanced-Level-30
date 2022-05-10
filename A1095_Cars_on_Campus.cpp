#include<cstdio>
#include<cstring>
#include<string>
#include<map>
#include<algorithm>
using namespace std;
const int maxn=10010;
struct Car{
	char id[8];
	int time;
	char status[4];
}all[maxn],valid[maxn];//all为所有记录，valid为有效记录 
int num=0;
map<string,int>parkTime; //车牌号->总停留时间
//timeToint将时间转换以s为单位
int timeToInt(int hh,int mm,int ss){
	return hh*3600+mm*60+ss;
} 
//先按车牌号字典序从小到大排序，若车牌号相同，则按时间从小到大排序
bool cmpByIdAndTime(Car a,Car b){
	if(strcmp(a.id,b.id))return strcmp(a.id,b.id)<0;
	else return a.time<b.time;
} 
//按时间从小到大排序
bool cmpByTime(Car a,Car b){
	return a.time<b.time;
} 
int main(){
	int n,k,hh,mm,ss;
	scanf("%d%d",&n,&k); //记录数，查询数
	for(int i=0;i<n;i++){
		scanf("%s %d:%d:%d %s",all[i].id,&hh,&mm,&ss,all[i].status);
		all[i].time=timeToInt(hh,mm,ss);
	} 
	sort(all,all+n,cmpByIdAndTime); //按车牌号和时间排序
	int maxTime=-1; //最长总停留时间
	for(int i=0;i<n-1;i++){//遍历所有记录
		if(!strcmp(all[i].id,all[i+1].id)&&
			!strcmp(all[i].status,"in")&&
			!strcmp(all[i+1].status,"out")){
				valid[num++]=all[i]; //i和i+1是配对的存入valid数组
				valid[num++]=all[i+1];
				int inTime=all[i+1].time-all[i].time;
				if(parkTime.count(all[i].id)==0){
					parkTime[all[i].id]=0;
				} 
				parkTime[all[i].id]+=inTime;
				maxTime=max(maxTime,parkTime[all[i].id]);
			} 
	}
	sort(valid,valid+num,cmpByTime);   //把有效记录按时间从小到大排序
	//now指向不超过当前查询时间的记录，numCar为当前校园内车辆数
	int now=0,numCar=0;
	for(int i=0;i<k;i++){
		scanf("%d:%d:%d",&hh,&mm,&ss);
		int time=timeToInt(hh,mm,ss);
		//让now处理至当前查询时间
		while(now<num&&valid[now].time<=time){
			if(!strcmp(valid[now].status,"in"))numCar++; //车辆进入
			else numCar--; //车辆离开
			now++; //指向下一条记录 
		} 
		printf("%d\n",numCar); // 
	}
	map<string,int>::iterator it;
	for(it=parkTime.begin();it!=parkTime.end();it++){
		if(it->second==maxTime){
			printf("%s ",it->first.c_str());
		}
	} 
	printf("%02d:%02d:%02d\n",maxTime/3600,maxTime%3600/60,maxTime%60);
	return 0;
}
