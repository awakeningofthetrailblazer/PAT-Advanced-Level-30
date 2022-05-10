#Programming Ability Test-Top Level

##**30-scores**

###A1004 Counting Leaves

A family hierarchy is usually presented by a pedigree tree. Your job is to count those family members who have no child.

**Input Specification:**

Each input file contains one test case. Each case starts with a line containing 0<*N*<100, the number of nodes in a tree, and *M* (<*N*), the number of non-leaf nodes. Then *M* lines follow, each in the format:

```
ID K ID[1] ID[2] ... ID[K]
```

where `ID` is a two-digit number representing a given non-leaf node, `K` is the number of its children, followed by a sequence of two-digit `ID`'s of its children. For the sake of simplicity, let us fix the root ID to be `01`.

The input ends with *N* being 0. That case must NOT be processed.

**Output Specification:**

For each test case, you are supposed to count those family members who have no child **for every seniority level** starting from the root. The numbers must be printed in a line, separated by a space, and there must be no extra space at the end of each line.

The sample case represents a tree with only 2 nodes, where `01` is the root and `02` is its only child. Hence on the root `01` level, there is `0` leaf node; and on the next level, there is `1` leaf node. Then we should output `0 1` in a line.

**Sample Input:**

```in
2 1
01 1 02
```

**Sample Output:**

```out
0 1
```

**Solution:**

```c++
#include<iostream>
using namespace std;
struct lfs {
	int lvl = 0;
	int bbs = 0;
    int bf = 0;
};
int main() {
	int M, N, r, k, nlf[100] = { 0 }, id;
	cin >> N;
	if (N == 0) return 0;
    cin >> M;
	lfs p[100];
	for (int i = 0; i<M ; i++) {
		cin >> r >> k;
        if(r==1) p[r].lvl=1;
		p[r].bbs += k;
		for (int j = 0; j < k; j++) {
			cin >> id;
            p[id].bf=r;
		}
	}
    for(int j=0;j<M;j++){
        for(int i=2;i<=N;i++){
            if(p[p[i].bf].lvl>0&&p[i].lvl==0) p[i].lvl=p[p[i].bf].lvl+1;
        }
    }
	int mx = 0;
	for (int i = 1; i <= N; i++) {
		if (p[i].bbs == 0) nlf[p[i].lvl]++;
		if (mx<p[i].lvl) mx = p[i].lvl;
	}
    if(M!=0) nlf[1]=0;
    else nlf[1]=N;
    cout<<nlf[1];
	for (int i = 2; i <= mx ; i++) {
		cout <<' '<< nlf[i];
	}
	cout << endl;
	return 0;
}
```



###A1014 Waiting in Line

Suppose a bank has *N* windows open for service. There is a yellow line in front of the windows which devides the waiting area into two parts. The rules for the customers to wait in line are:

- The space inside the yellow line in front of each window is enough to contain a line with *M* customers. Hence when all the *N* lines are full, all the customers after (and including) the (*NM*+1)st one will have to wait in a line behind the yellow line.
- Each customer will choose the shortest line to wait in when crossing the yellow line. If there are two or more lines with the same length, the customer will always choose the window with the smallest number.
- $Customer_i$ will take $T_i$ minutes to have his/her transaction processed.
- The first $N$ customers are assumed to be served at 8:00am.

Now given the processing time of each customer, you are supposed to tell the exact time at which a customer has his/her business done.

For example, suppose that a bank has 2 windows and each window may have 2 customers waiting inside the yellow line. There are 5 customers waiting with transactions taking 1, 2, 6, 4 and 3 minutes, respectively. At 08:00 in the morning, $Customer_1$ is served at $window_1$ while $Customer_2$ is served at $window_2$. $Customer_3$ will wait in front of $window_1$ and $Customer_4$ will wait in front of $window_2$. $Customer_5$ will wait behind the yellow line.

At 08:01, $Customer_1$ is done and $Customer_5$ enters the line in front of $window_1$ since that line seems shorter now.  $Customer_2$ will leave at 08:02,  $Customer_4$at 08:06, $Customer_3$ at 08:07, and finally $Customer_5$ at 08:10.

**Input Specification:**

Each input file contains one test case. Each case starts with a line containing 4 positive integers: *$N$ (≤20, number of windows), $M$ (≤10, the maximum capacity of each line inside the yellow line), $K$ (≤1000, number of customers), and $Q$ (≤1000, number of customer queries).

The next line contains $K$ positive integers, which are the processing time of the $K$ customers.

The last line contains $Q$ positive integers, which represent the customers who are asking about the time they can have their transactions done. The customers are numbered from $1$ to $K$.

**Output Specification:**

For each of the $Q$ customers, print in one line the time at which his/her transaction is finished, in the format `HH:MM` where `HH` is in [08, 17] and `MM` is in [00, 59]. Note that since the bank is closed everyday after 17:00, for those customers who cannot be served before 17:00, you must output `Sorry` instead.

**Sample Input:**

```in
2 2 7 5
1 2 6 4 3 534 2
3 4 5 6 7
```

**Sample Output:**

```out
08:07
08:06
08:10
17:00
Sorry
```

**Solution:**

```C++
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
```



### A1018 Public Bike Management

There is a public bike service in Hangzhou City which provides great convenience to the tourists from all over the world. One may rent a bike at any station and return it to any other stations in the city.

The Public Bike Management Center (PBMC) keeps monitoring the real-time capacity of all the stations. A station is said to be in **perfect** condition if it is exactly half-full. If a station is full or empty, PBMC will collect or send bikes to adjust the condition of that station to perfect. And more, all the stations on the way will be adjusted as well.

When a problem station is reported, PBMC will always choose the shortest path to reach that station. If there are more than one shortest path, the one that requires the least number of bikes sent from PBMC will be chosen.

![img](https://images.ptausercontent.com/213)

The above figure illustrates an example. The stations are represented by vertices and the roads correspond to the edges. The number on an edge is the time taken to reach one end station from another. The number written inside a vertex *S* is the current number of bikes stored at *S*. Given that the maximum capacity of each station is 10. To solve the problem at *S*3, we have 2 different shortest paths:

1. PBMC -> *S*1 -> *S*3. In this case, 4 bikes must be sent from PBMC, because we can collect 1 bike from *S*1 and then take 5 bikes to *S*3, so that both stations will be in perfect conditions.
2. PBMC -> *S*2 -> *S*3. This path requires the same time as path 1, but only 3 bikes sent from PBMC and hence is the one that will be chosen.

**Input Specification:**

Each input file contains one test case. For each case, the first line contains 4 numbers: $C_{max}$ (≤100), always an even number, is the maximum capacity of each station; *N* (≤500), the total number of stations; $S_p$, the index of the problem station (the stations are numbered from 1 to *N*, and PBMC is represented by the vertex 0); and *M*, the number of roads. The second line contains *N* non-negative numbers $C_i$ (*i*=1,⋯,*N*) where each  is $C_i$ the current number of bikes at $S_i$ respectively. Then $M$ lines follow, each contains 3 numbers: $S_i$, $S_j$, and $T_{ij}$ which describe the time $T_{ij}$ taken to move betwen stations $S_i$ and $S_j$. All the numbers in a line are separated by a space.

**Output Specification:**

For each test case, print your results in one line. First output the number of bikes that PBMC must send. Then after one space, output the path in the format: 0−>$S_1$−>⋯−>$S_p$. Finally after another space, output the number of bikes that we must take back to PBMC after the condition of $S_i$ is adjusted to perfect.

Note that if such a path is not unique, output the one that requires minimum number of bikes that we must take back to PBMC. The judge's data guarantee that such a path is unique.

**Sample Input:**

```in
10 3 3 5
6 7 0
0 1 1
0 2 1
0 3 3
1 3 1
2 3 1
```

**Sample Output:**

```out
3 0->2->3 0
```

**Solution:**

```c++
#include <cstdio>
#include <vector>
#include <algorithm>
 
using namespace std;
 
const int maxn = 510;
const int INF = 1000000000;
int cmax, n, des, m, minneed = INF, minremain = INF;
vector<int> pre[maxn], path, temp;
int G[maxn][maxn], c[maxn], d[maxn];
bool vis[maxn];
 
void dijkstra(int, int);
void dfs(int);
 
int main() {
    fill(G[0], G[0] + maxn * maxn, INF);
    scanf("%d%d%d%d", &cmax, &n, &des, &m);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", c + i);
    }
 
    for(int i = 0; i < m; ++i) {
        int a, b, t;
        scanf("%d%d%d", &a, &b, &t);
        G[a][b] = G[b][a] = t;
    }
 
    dijkstra(0, des);
    dfs(des);
 
    printf("%d ", minneed);
    bool first = true;
    for(int i = path.size() - 1; i >= 0; --i) {
        if(!first) {
            printf("->");
        }
        printf("%d", path[i]);
        first = false;
    }
    printf(" %d", minremain);
 
    return 0;
}
 
void dijkstra(int s, int e) {
    fill(d, d + maxn, INF);
    d[s] = 0;
 
    for(int i = 0; i <= n; ++i) {
        int minv = -1, mindis = INF;
        for(int j = 0; j <= n; ++j) {
            if(!vis[j] && d[j] < mindis) {
                mindis = d[j];
                minv = j;
            }
        }
 
        if(minv == -1) {
            return ;
        }
        vis[minv] = true;
        for(int j = 0; j <= n; ++j) {
            if(!vis[j] && G[minv][j] != INF) {
                if(G[minv][j] + d[minv] < d[j]) {
                    d[j] = G[minv][j] + d[minv];
                    pre[j].clear();
                    pre[j].push_back(minv);
                } else if(G[minv][j] + d[minv] == d[j]) {
                    pre[j].push_back(minv);
                }
            }
        }
    }
}
 
void dfs(int v) {
    temp.push_back(v);
    if(v == 0) {
        int needbike = 0, remainbike = 0;
        for(int i = temp.size() - 2; i >= 0; --i) {
            if(c[temp[i]] >= cmax / 2) {
                remainbike += c[temp[i]] - cmax / 2;
            } else {
                int x = cmax / 2 - c[temp[i]];
                if(remainbike > 0) {
                    if(remainbike >= x) {
                        remainbike -= x;
                    } else {
                        needbike += x - remainbike;
                        remainbike = 0;
                    }
                } else {
                    needbike += x;
                }
            }
        }
 
        if(minneed > needbike) {
            minneed = needbike;
            minremain = remainbike;
            path = temp;
        } else if(minneed == needbike && minremain > remainbike) {
            minneed = needbike;
            minremain = remainbike;
            path = temp;
        }
 
        temp.pop_back();
        return ;
    }
 
    for(int i = 0; i < pre[v].size(); ++i) {
        dfs(pre[v][i]);
    }
    temp.pop_back();
}
```



### A1022 Digital Library

A Digital Library contains millions of books, stored according to their titles, authors, key words of their abstracts, publishers, and published years. Each book is assigned an unique 7-digit number as its ID. Given any query from a reader, you are supposed to output the resulting books, sorted in increasing order of their ID's.

**Input Specification:**

Each input file contains one test case. For each case, the first line contains a positive integer *N* (≤104) which is the total number of books. Then *N* blocks follow, each contains the information of a book in 6 lines:

- Line #1: the 7-digit ID number;
- Line #2: the book title -- a string of no more than 80 characters;
- Line #3: the author -- a string of no more than 80 characters;
- Line #4: the key words -- each word is a string of no more than 10 characters without any white space, and the keywords are separated by exactly one space;
- Line #5: the publisher -- a string of no more than 80 characters;
- Line #6: the published year -- a 4-digit number which is in the range [1000, 3000].

It is assumed that each book belongs to one author only, and contains no more than 5 key words; there are no more than 1000 distinct key words in total; and there are no more than 1000 distinct publishers.

After the book information, there is a line containing a positive integer *M* (≤1000) which is the number of user's search queries. Then *M* lines follow, each in one of the formats shown below:

- 1: a book title
- 2: name of an author
- 3: a key word
- 4: name of a publisher
- 5: a 4-digit number representing the year

**Output Specification:**

For each query, first print the original query in a line, then output the resulting book ID's in increasing order, each occupying a line. If no book is found, print `Not Found` instead.

**Sample Input:**

```in
3
1111111
The Testing Book
Yue Chen
test code debug sort keywords
ZUCS Print
2011
3333333
Another Testing Book
Yue Chen
test code sort keywords
ZUCS Print2
2012
2222222
The Testing Book
CYLL
keywords debug book
ZUCS Print2
2011
6
1: The Testing Book
2: Yue Chen
3: keywords
4: ZUCS Print
5: 2011
3: blablabla
```

**Sample Output:**

```out
1: The Testing Book
1111111
2222222
2: Yue Chen
1111111
3333333
3: keywords
1111111
2222222
3333333
4: ZUCS Print
1111111
5: 2011
1111111
2222222
3: blablabla
Not Found
```

**Solution:**

```C++
#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>

using namespace std;

int N,M;

struct BOOK{
    char id[8];
    char title[81];
    char author[81];
    char keywords[60];
    char publisher[81];
    char publishedyear[5];
};

vector<BOOK> lby;

void readMessage(){
    BOOK temp;
    cin.getline(temp.id,8);
    cin.getline(temp.title,81);
    cin.getline(temp.author,81);
    cin.getline(temp.keywords,60);
    cin.getline(temp.publisher,81);
    cin.getline(temp.publishedyear,5);
    lby.push_back(temp);
    
    //cout<<temp.id<<endl;
}

bool cmpMessage(char*a,char*b){
    int k=0;
    bool cc=false;
    while(a[k]==b[k] && b[k]!='\0'&& a[k]!='\0' ){
        k++;
    }
    if(a[k]=='\0' && (b[k]=='\0' || b[k]==' ')) cc=true;
    return cc;
}

bool cmpKeywords(char*a,char*b){
    int k=0;
    bool cc=false;
    while(b[k]!='\0'){
        if(k==0 || b[k-1]==' '){
            if(cmpMessage(a,b+k)) cc=true;
        }
        k++;
    }
    return cc;
}

bool cmp(BOOK a,BOOK b){
    if(strcmp(a.id,b.id)<0) return true;
    else return false;
}

void searchMessage(char* msg){
    bool therethere=false;
    for(vector<BOOK>::iterator it=lby.begin();it!=lby.end();it++){
        if(cmpMessage(msg,it->id)){
            cout<<it->id<<endl;
            therethere=true;
            continue;
        }
        if(cmpMessage(msg,it->title)){
            cout<<it->id<<endl;
            therethere=true;
            continue;
        }
        if(cmpMessage(msg,it->author)){
            cout<<it->id<<endl;
            therethere=true;
            continue;
        }
        if(cmpKeywords(msg,it->keywords)){
            cout<<it->id<<endl;
            therethere=true;
            continue;
        }
        if(cmpMessage(msg,it->publisher)){
            cout<<it->id<<endl;
            therethere=true;
            continue;
        }
        if(cmpMessage(msg,it->publishedyear)){
            cout<<it->id<<endl;
            therethere=true;
            continue;
        }
    }
    if(therethere==false) cout<<"Not Found"<<endl;
}

int main(){
    scanf("%d\n",&N);
    
    while(N--){readMessage();}
    
    sort(lby.begin(),lby.end(),cmp);
    
    scanf("%d\n",&M);
    
    while(M--){
        int rk;
        char msg[1000];
        scanf("%d: ",&rk);
        cin.getline(msg,1000);
        cout<<rk<<": "<<msg<<endl;
        searchMessage(msg);
    }
    
    return 0;
}
```



###A1026 Table Tennis

A table tennis club has N tables available to the public. The tables are numbered from 1 to N. For any pair of players, if there are some tables open when they arrive, they will be assigned to the available table with the smallest number. If all the tables are occupied, they will have to wait in a queue. It is assumed that every pair of players can play for at most 2 hours.

Your job is to count for everyone in queue their waiting time, and for each table the number of players it has served for the day.

One thing that makes this procedure a bit complicated is that the club reserves some tables for their VIP members. When a VIP table is open, the first VIP pair in the queue will have the privilege to take it. However, if there is no VIP in the queue, the next pair of players can take it. On the other hand, if when it is the turn of a VIP pair, yet no VIP table is available, they can be assigned as any ordinary players.

**Input Specification:**

Each input file contains one test case. For each case, the first line contains an integer `N` (≤10000) - the total number of pairs of players. Then `N` lines follow, each contains 2 times and a VIP tag: `HH:MM:SS` - the arriving time, `P` - the playing time in minutes of a pair of players, and `tag` - which is 1 if they hold a VIP card, or 0 if not. It is guaranteed that the arriving time is between 08:00:00 and 21:00:00 while the club is open. It is assumed that no two customers arrives at the same time. Following the players' info, there are 2 positive integers: `K` (≤100) - the number of tables, and `M` (< K) - the number of VIP tables. The last line contains `M` table numbers.

**Output Specification:**

For each test case, first print the arriving time, serving time and the waiting time for each pair of players in the format shown by the sample. Then print in a line the number of players served by each table. Notice that the output must be listed in chronological order of the serving time. The waiting time must be rounded up to an integer minute(s). If one cannot get a table before the closing time, their information must NOT be printed.

**Sample Input:**

```in
10
20:52:00 10 0
08:00:00 20 0
08:02:00 30 0
20:51:00 10 0
08:10:00 30 0
08:12:00 10 1
20:40:00 13 0
08:01:30 15 1
20:53:00 10 1
20:54:00 10 0
3 1
2
```

**Sample Output:**

```out
08:00:00 08:00:00 0
08:01:30 08:01:30 0
08:02:00 08:02:00 0
08:12:00 08:16:30 5
08:10:00 08:20:00 10
20:40:00 20:40:00 0
20:51:00 20:51:00 0
20:52:00 20:52:00 0
20:53:00 20:53:00 0
4 3 2
```

**Solution:**

```C++
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
```



### A1030 Travel Plan

A traveler's map gives the distances between cities along the highways, together with the cost of each highway. Now you are supposed to write a program to help a traveler to decide the shortest path between his/her starting city and the destination. If such a shortest path is not unique, you are supposed to output the one with the minimum cost, which is guaranteed to be unique.

**Input Specification:**

Each input file contains one test case. Each case starts with a line containing 4 positive integers *N*, *M*, *S*, and *D*, where *N* (≤500) is the number of cities (and hence the cities are numbered from 0 to *N*−1); *M* is the number of highways; *S* and *D* are the starting and the destination cities, respectively. Then *M* lines follow, each provides the information of a highway, in the format:

```
City1 City2 Distance Cost
```

where the numbers are all integers no more than 500, and are separated by a space.

**Output Specification:**

For each test case, print in one line the cities along the shortest path from the starting point to the destination, followed by the total distance and the total cost of the path. The numbers must be separated by a space and there must be no extra space at the end of output.

**Sample Input:**

```in
4 5 0 3
0 1 1 20
1 3 2 30
0 3 4 10
0 2 2 20
2 3 1 20
```

**Sample Output:**

```out
0 2 3 3 40
```

**Solution:**

```C++
#include<iostream>
#include<vector>

using namespace std;

const int maxn=510;
const int inf=1000000000;

int N,M,S,D;
int minDistance=inf,minCost=inf;

int dist[maxn][maxn],cost[maxn][maxn];
vector<int> pre[maxn];
vector<int> bestpath,temppath;

void readData(){
    
    cin>>N>>M>>S>>D;
    
    fill(dist[0],dist[0]+maxn*maxn,inf);
    fill(cost[0],cost[0]+maxn*maxn,inf);
    
    while(M--){
        int s,t,d,c;
        cin>>s>>t>>d>>c;
        dist[s][t]=dist[s][t]<=d?dist[s][t]:d;
        dist[t][s]=dist[s][t];
        cost[s][t]=cost[s][t]<=c?cost[s][t]:c;
        cost[t][s]=cost[s][t];
    }
    
    for(int i=0;i<N;i++){
        dist[i][i]=0;
        cost[i][i]=0;
    }
}

void dijkstra(int s){
    bool isVis[maxn]={false};
    int d[maxn];
    fill(d,d+maxn,inf);
    d[s]=0;
    for(int i=0;i<N;i++){
        
        int u=-1;
        int minp=inf;
        for(int j=0;j<N;j++){
            if(!isVis[j] && minp>d[j]){
                u=j;
                minp=d[j];
            }
        }
        if(u==-1) break;
        isVis[u]=true;
        for(int v=0;v<N;v++){
            if(!isVis[v] && dist[u][v]!=inf){
                if(d[u]+dist[u][v]<d[v]){
                    d[v]=d[u]+dist[u][v];
                    pre[v].clear();
                    pre[v].push_back(u);
                }else if(d[u]+dist[u][v]==d[v]){
                    pre[v].push_back(u);
                }
            }
        }
    }
    minDistance=d[D];
}

void dfs(int k,int cc){
    temppath.push_back(k);
    if(k==S && cc<minCost){
        minCost=cc;
        bestpath=temppath;
    }
    int len=pre[k].size();
    for(int i=0;i<len;i++){
        int p=pre[k][i];
        dfs(p,cc+cost[p][k]);
    }
    temppath.pop_back();
}

void showResult(){
    for(int i=bestpath.size();i!=0;i--){
        cout<<bestpath[i-1]<<' ';
    }
    cout<<minDistance<<' '<<minCost<<endl;
}

int main(){
    readData();
    
    dijkstra(S);
    
    dfs(D,0);
    
    showResult();
    
    return 0;
}
```



###A1034 Head of a Gang

One way that the police finds the head of a gang is to check people's phone calls. If there is a phone call between *A* and *B*, we say that *A* and *B* is related. The weight of a relation is defined to be the total time length of all the phone calls made between the two persons. A "Gang" is a cluster of more than 2 persons who are related to each other with total relation weight being greater than a given threshold *K*. In each gang, the one with maximum total weight is the head. Now given a list of phone calls, you are supposed to find the gangs and the heads.

**Input Specification:**

Each input file contains one test case. For each case, the first line contains two positive numbers *N* and *K* (both less than or equal to 1000), the number of phone calls and the weight threthold, respectively. Then *N* lines follow, each in the following format:

```
Name1 Name2 Time
```

where `Name1` and `Name2` are the names of people at the two ends of the call, and `Time` is the length of the call. A name is a string of three capital letters chosen from `A`-`Z`. A time length is a positive integer which is no more than 1000 minutes.

**Output Specification:**

For each test case, first print in a line the total number of gangs. Then for each gang, print in a line the name of the head and the total number of the members. It is guaranteed that the head is unique for each gang. The output must be sorted according to the alphabetical order of the names of the heads.

**Sample Input 1:**

```in
8 59
AAA BBB 10
BBB AAA 20
AAA CCC 40
DDD EEE 5
EEE DDD 70
FFF GGG 30
GGG HHH 20
HHH FFF 10
```

**Sample Output 1:**

```out
2
AAA 3
GGG 3
```

**Sample Input 2:**

```in
8 70
AAA BBB 10
BBB AAA 20
AAA CCC 40
DDD EEE 5
EEE DDD 70
FFF GGG 30
GGG HHH 20
HHH FFF 10
```

**Sample Output 2:**

```out
0
```

**Solution:**

```C++
#include<iostream>
#include<string>
#include<map>

using namespace std;
const int maxn=2010;
const int INF=1000000000;

map<int,string> intToSring;
map<string,int> stringToInt;
map<string,int> gang;

int G[maxn][maxn]={0},weight[maxn]={0};
int n,k,numPerson=0;
bool vis[maxn]={false};

void DFS(int nowVisit,int&head,int&numMember,int&totalValue){
    numMember++;
    vis[nowVisit]=true;
    if(weight[nowVisit]>weight[head]){
        head=nowVisit;
    }
    for(int i=0;i<numPerson;i++){
        if(G[nowVisit][i]>0){
            totalValue+=G[nowVisit][i];
            G[nowVisit][i]=G[i][nowVisit]=0;
            if(vis[i]==false){
                DFS(i,head,numMember,totalValue);
            }
        }
    }
}

void DFSTrave(){
    for(int i=0;i<numPerson;i++){
        if(vis[i]==false){
            int head=i,numMember=0,totalValue=0;
            DFS(i,head,numMember,totalValue);
            if(numMember>2&&totalValue>k){
                gang[intToSring[head]]=numMember;
            }
        }
    }
}

int change(string str){
    if(stringToInt.find(str)!=stringToInt.end()){
        return stringToInt[str];
    }else{
        stringToInt[str]=numPerson;
        intToSring[numPerson]=str;
        return numPerson++;
    }
}

int main(){
    int w;
    string str1,str2;
    cin>>n>>k;
    for(int i=0;i<n;i++){
        cin>>str1>>str2>>w;
        int id1=change(str1);
        int id2=change(str2);
        weight[id1]+=w;
        weight[id2]+=w;
        G[id1][id2]+=w;
        G[id2][id1]+=w;
    }
    DFSTrave();
    cout<<gang.size()<<endl;
    map<string,int>::iterator it;
    for(it=gang.begin();it!=gang.end();it++){
        cout<<it->first<<" "<<it->second<<endl;
    }
    return 0;
}
```



### A1038 Recover the smallest Number

Given a collection of number segments, you are supposed to recover the smallest number from them. For example, given { 32, 321, 3214, 0229, 87 }, we can recover many numbers such like 32-321-3214-0229-87 or 0229-32-87-321-3214 with respect to different orders of combinations of these segments, and the smallest number is 0229-321-3214-32-87.

**Input Specification:**

Each input file contains one test case. Each case gives a positive integer *N* (≤104) followed by *N* number segments. Each segment contains a non-negative integer of no more than 8 digits. All the numbers in a line are separated by a space.

**Output Specification:**

For each test case, print the smallest number in one line. Notice that the first digit must not be zero.

**Sample Input:**

```in
5 32 321 3214 0229 87
```

**Sample Output:**

```out
22932132143287
```

**Solution:**

```C++
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
struct ng {
	char fc[9];
	int vlu = 0;
	int len = 0;
	int hd = 0;
};
bool cmp(ng a, ng b) {
	for (int i = 0; i<a.len&&i<b.len; i++) {
		char str1[20];
		char str2[20];
		strcpy(str1, a.fc);
		strcpy(str2, b.fc);
		strcat(str1, b.fc);
		strcat(str2, a.fc);
		if (strcmp(str1,str2)!=0) { return strcmp(str1, str2)<0; }
	}
	//if (a.len != b.len) {
		//if (a.len > b.len) {
		//	for (int i = 0; i < a.len - b.len; i++) {if()}
		//}
	//}
	return true;
}
int main() {
	int N;
	cin >> N;
	ng p[10000];
	for (int i = 0; i<N; i++) {
		cin >> p[i].fc;
		p[i].len = strlen(p[i].fc);
		for (int j = 0; j<p[i].len; j++) { p[i].vlu = 10 * p[i].vlu + p[i].fc[j] - '0'; }
		//cout << ' ' << p[i].vlu;
	}
	sort(p, p + N, cmp);
    int k=0;
	for (int i = 0; i<N; i++) {
        if(i==N-1&&p[i].vlu==0){cout<<'0';break;}
		if (i == k && p[k].fc[0] == '0') { if(p[i].vlu!=0) cout << p[i].vlu;else k++; continue; }
		cout << p[i].fc;
	}
	cout << endl;
	return 0;
}
```



### A1045 Favorite Color Stripe

Eva is trying to make her own color stripe out of a given one. She would like to keep only her favorite colors in her favorite order by cutting off those unwanted pieces and sewing the remaining parts together to form her favorite color stripe.

It is said that a normal human eye can distinguish about less than 200 different colors, so Eva's favorite colors are limited. However the original stripe could be very long, and Eva would like to have the remaining favorite stripe with the maximum length. So she needs your help to find her the best result.

Note that the solution might not be unique, but you only have to tell her the maximum length. For example, given a stripe of colors {2 2 4 1 5 5 6 3 1 1 5 6}. If Eva's favorite colors are given in her favorite order as {2 3 1 5 6}, then she has 4 possible best solutions {2 2 1 1 1 5 6}, {2 2 1 5 5 5 6}, {2 2 1 5 5 6 6}, and {2 2 3 1 1 5 6}.

**Input Specification:**

Each input file contains one test case. For each case, the first line contains a positive integer *N* (≤200) which is the total number of colors involved (and hence the colors are numbered from 1 to *N*). Then the next line starts with a positive integer *M* (≤200) followed by *M* Eva's favorite color numbers given in her favorite order. Finally the third line starts with a positive integer *L* (≤104) which is the length of the given stripe, followed by *L* colors on the stripe. All the numbers in a line a separated by a space.

**Output Specification:**

For each test case, simply print in a line the maximum length of Eva's favorite stripe.

**Sample Input:**

```in
6
5 2 3 1 5 6
12 2 2 4 1 5 5 6 3 1 1 5 6
```

**Sample Output:**

```out
7
```

**Solution:**

```C++
#include<bits/stdc++.h>

using namespace std;

int N,maxlen=0;
vector<int> stripe;
unordered_map<int,int> evaorder;

void init();

void pickMaxLen();

int main(){
    
    init();
    
    pickMaxLen();
    
    cout<<maxlen<<endl;
    
    return 0;
}

void init(){
    cin>>N;
    int M,L,x;
    cin>>M;
    for(int i=1;i<=M;i++){
        cin>>x;
        evaorder[x]=i;
    }
    cin>>L;
    while(L--){
        cin>>x;
        if(evaorder[x]) stripe.push_back(evaorder[x]);
    }
}

void pickMaxLen(){
    vector<int> len_num;
    for(int i=0;i<stripe.size();i++) len_num.push_back(1);
    for(int i=1;i<len_num.size();i++){
        for(int j=0;j<i;j++){
            if(stripe[j]<=stripe[i]) len_num[i]=len_num[j]+1;
        }
    }
    
    for(int a:len_num){
        if(a>maxlen) maxlen=a;
    }
}
```



### A1049 Counting Ones

The task is simple: given any positive integer *N*, you are supposed to count the total number of 1's in the decimal form of the integers from 1 to *N*. For example, given *N* being 12, there are five 1's in 1, 10, 11, and 12.

**Input Specification:**

Each input file contains one test case which gives the positive *N* (≤$2^{30}$).

**Output Specification:**

For each test case, print the number of 1's in one line.

**Sample Input:**

```in
12
```

**Sample Output:**

```out
5
```

**Solution:**

```C++
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
```



### A1053 Path of Equal Weight

Given a non-empty tree with root *R*, and with weight $W_i$ assigned to each tree node $T_i$. The **weight of a path from R to L** is defined to be the sum of the weights of all the nodes along the path from *R* to any leaf node *L*.

Now given any weighted tree, you are supposed to find all the paths with their weights equal to a given number. For example, let's consider the tree showed in the following figure: for each node, the upper number is the node ID which is a two-digit number, and the lower number is the weight of that node. Suppose that the given number is 24, then there exists 4 different paths which have the same given weight: {10 5 2 7}, {10 4 10}, {10 3 3 6 2} and {10 3 3 6 2}, which correspond to the red edges in the figure.

![img](https://images.ptausercontent.com/212)

**Input Specification:**

Each input file contains one test case. Each case starts with a line containing 0<*N*≤100, the number of nodes in a tree, *M* (<*N*), the number of non-leaf nodes, and 0<*S*<$2^{30}$, the given weight number. The next line contains *N* positive numbers where $W_i$ (<1000) corresponds to the tree node $T_i$. Then *M* lines follow, each in the format:

```
ID K ID[1] ID[2] ... ID[K]
```

where `ID` is a two-digit number representing a given non-leaf node, `K` is the number of its children, followed by a sequence of two-digit `ID`'s of its children. For the sake of simplicity, let us fix the root ID to be `00`.

**Output Specification:**

For each test case, print all the paths with weight S in **non-increasing** order. Each path occupies a line with printed weights from the root to the leaf in order. All the numbers must be separated by a space with no extra space at the end of the line.

Note: sequence {$A_1$,$A_2$,⋯,$A_n$} is said to be **greater than** sequence {$B_1$,$B_2$,⋯,$B_m$} if there exists 1≤*k*<*min*{*n*,*m*} such that $A_i=B_i$ for *i*=1,⋯,*k*, and $A_{k+1}>B_{k+1}$.

**Sample Input:**

```in
20 9 24
10 2 4 3 5 10 2 18 9 7 2 2 1 3 12 1 8 6 2 2
00 4 01 02 03 04
02 1 05
04 2 06 07
03 3 11 12 13
06 1 09
07 2 08 10
16 1 15
13 3 14 16 17
17 2 18 19
```

**Sample Output:**

```out
10 5 2 7
10 4 10
10 3 3 6 2
10 3 3 6 2
```

**Solution:**

```C++
#include<bits/stdc++.h>

using namespace std;

const int maxn=101;

long long N,M,S;
long long weight[maxn];
vector<int> nd[maxn];

vector<int> temp_child_res;
vector<vector<int>> res;

void dfs(int id, long long w);

bool cmp(vector<int> a,vector<int> b);

int main(){
    cin>>N>>M>>S;
    for(int i=0;i<N;i++) cin>>weight[i];
    int id,K,x;
    while(M--){
        cin>>id>>K;
        while(K--){
            cin>>x;
            nd[id].push_back(x);
        }
    }
    
    dfs(0, weight[0]);
    
    sort(res.begin(),res.end(),cmp);
    
    for(vector<int> res_child:res){
        for(int i=0;i<res_child.size();i++){
            cout<<res_child[i];
            if(i==res_child.size()-1) cout<<endl;
            else cout<<' ';
        }
    }
    
    return 0;
}

void dfs(int id, long long w){
    temp_child_res.push_back(weight[id]);
    if(w>=S){
        if(w==S && nd[id].size()==0) res.push_back(temp_child_res);
        temp_child_res.pop_back();
        return;
    }
    for(int x:nd[id]){
        dfs(x,w+weight[x]);
    }
    if(temp_child_res.size())temp_child_res.pop_back();
}

bool cmp(vector<int> a,vector<int> b){
    for(int i=0;i<a.size() && i<b.size();i++){
        if(a[i]==b[i]) continue;
        else return a[i]>b[i];
    }
    return false;
}
```



### A1057 Stack

Stack is one of the most fundamental data structures, which is based on the principle of Last In First Out (LIFO). The basic operations include Push (inserting an element onto the top position) and Pop (deleting the top element). Now you are supposed to implement a stack with an extra operation: PeekMedian -- return the median value of all the elements in the stack. With *N* elements, the median value is defined to be the (*N*/2)-th smallest element if *N* is even, or ((*N*+1)/2)-th if *N* is odd.

**Input Specification:**

Each input file contains one test case. For each case, the first line contains a positive integer *N* (≤$10^5$). Then *N* lines follow, each contains a command in one of the following 3 formats:

```
Push key
Pop
PeekMedian
```

where `key` is a positive integer no more than $10^5$.

**Output Specification:**

For each `Push` command, insert `key` into the stack and output nothing. For each `Pop` or `PeekMedian` command, print in a line the corresponding returned value. If the command is invalid, print `Invalid` instead.

**Sample Input:**

```in
17
Pop
PeekMedian
Push 3
PeekMedian
Push 2
PeekMedian
Push 1
PeekMedian
Pop
Pop
Push 5
Push 4
PeekMedian
Pop
Pop
Pop
Pop
```

**Sample Output:**

```out
Invalid
Invalid
3
2
2
1
2
4
4
5
3
Invalid
```

**Solution:**

```C++
#include<bits/stdc++.h>

using namespace std;

map<int,int>M;
map<int,int>::iterator mid;
int beforemid;
stack<int>S;

void adjust_mid(){
    if(beforemid>=(S.size()+1)/2){
        mid--;
        beforemid-=mid->second;
    }else if(beforemid+mid->second<(S.size()+1)/2){
        beforemid+=mid->second;
        mid++;
    }
}

int main(){
    
    int N;
    cin>>N;
    while(N--){
        string command;
        cin>>command;
        
        if(command[1]=='u'){//push
            int key;
            cin>>key;
            S.push(key);
            M[key]++;
            if(S.size()==1){
                mid=M.begin();
                beforemid=0;
            }else{
                if(key<mid->first)beforemid++;
                adjust_mid();
            }
        }else if(command[1]=='o'){
            if(!S.size()){
                cout<<"Invalid"<<endl;
            }else{
                int key=S.top();
                cout<<key<<endl;
                S.pop();
                M[key]--;
                if(key<mid->first)beforemid--;
                adjust_mid();
                if(M[key]==0){
                    if(mid->first==key) mid++;
                    M.erase(key);
                }
            }
        }else{
            if(!S.size()) cout<<"Invalid"<<endl;
            else cout<<mid->first<<endl;
        }
    }
    
    return 0;
}

```



### A1064 Complete Binary Search Tree

A Binary Search Tree (BST) is recursively defined as a binary tree which has the following properties:

- The left subtree of a node contains only nodes with keys less than the node's key.
- The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
- Both the left and right subtrees must also be binary search trees.

A Complete Binary Tree (CBT) is a tree that is completely filled, with the possible exception of the bottom level, which is filled from left to right.

Now given a sequence of distinct non-negative integer keys, a unique BST can be constructed if it is required that the tree must also be a CBT. You are supposed to output the level order traversal sequence of this BST.

**Input Specification:**

Each input file contains one test case. For each case, the first line contains a positive integer *N* (≤1000). Then *N* distinct non-negative integer keys are given in the next line. All the numbers in a line are separated by a space and are no greater than 2000.

**Output Specification:**

For each test case, print in one line the level order traversal sequence of the corresponding complete binary search tree. All the numbers in a line must be separated by a space, and there must be no extra space at the end of the line.

**Sample Input:**

```in
10
1 2 3 4 5 6 7 8 9 0
```

**Sample Output:**

```out
6 3 8 1 5 7 9 0 2 4
```

**Solution:**

```C++
#include<bits/stdc++.h>

using namespace std;

const int maxn=1024;

vector<int> seq;

int level_order[maxn];

void init();

int dfs(int ln,int k);

int main(){
    init();
    
    int cnt=dfs(0,0);
    
    for(int i=0;i<seq.size();i++) {
        cout<<level_order[i];
        if(i==seq.size()-1) cout<<endl;
        else cout<<' ';
    }
    
    return 0;
}

void init(){
    int N,x;
    cin>>N;
    while(N--) {
        cin>>x;
        seq.push_back(x);
    }
    
    sort(seq.begin(),seq.end());
}

int dfs(int ln,int k){
    
    int left_num=k*2+1<seq.size()?dfs(ln,k*2+1):0;
    
    level_order[k]=seq[ln+left_num];
    
    int right_num=k*2+2<seq.size()?dfs(ln+left_num+1,k*2+2):0;
    
    return 1+left_num+right_num;
}
```



### A1068 Find More Coins

Eva loves to collect coins from all over the universe, including some other planets like Mars. One day she visited a universal shopping mall which could accept all kinds of coins as payments. However, there was a special requirement of the payment: for each bill, she must pay the exact amount. Since she has as many as 104 coins with her, she definitely needs your help. You are supposed to tell her, for any given amount of money, whether or not she can find some coins to pay for it.

**Input Specification:**

Each input file contains one test case. For each case, the first line contains 2 positive numbers: `N` (≤104, the total number of coins) and `M` (≤102, the amount of money Eva has to pay). The second line contains `N` face values of the coins, which are all positive numbers. All the numbers in a line are separated by a space.

**Output Specification:**

For each test case, print in one line the face values $V_1$≤$V_2$≤⋯≤$V_k$ such that $V_1+V_2+...+V_k$=`M`. All the numbers must be separated by a space, and there must be no extra space at the end of the line. If such a solution is not unique, output the smallest sequence. If there is no solution, output "No Solution" instead.

Note: sequence {A[1], A[2], ...} is said to be "smaller" than sequence {B[1], B[2], ...} if there exists *k*≥1 such that A[*i*]=B[*i*] for all *i*<*k*, and A[*k*] < B[*k*].

**Sample Input 1:**

```in
8 9
5 9 8 7 2 3 4 1
```

**Sample Output 1:**

```out
1 3 5
```

**Sample Input 2:**

```in
4 8
7 2 4 3
```

**Sample Output 2:**

```out
No Solution
```

**Solution:**

```c++
#include<bits/stdc++.h>

using namespace std;

int N,M;
vector<int> coins,res;

void init();

void display();

bool cmp(int a,int b);

void calRes();

int main(){
    init();
    
    calRes();
    
    display();
    
    return 0;
}

void init(){
    cin>>N>>M;
    int x;
    for(int i=0;i<N;i++){
        cin>>x;
        if(x<=M) coins.push_back(x);
    }
    sort(coins.begin(),coins.end(), cmp);
    
    N=coins.size();
}

void display(){
    //cout<<"No Solution"<<endl;
    //return;
    if(res.size()){
        for(int a:res){
            cout<<a;
            if(a==*(res.end()-1)) cout<<endl;
            else cout<<' ';
        }
    }else{
        cout<<"No Solution"<<endl;
    }
}

bool cmp(int a,int b){
    return a>b;
}

void calRes(){
    unordered_map<int,int> dp;
    for(int i=-1;i<N;i++) dp[i]=0;
    int sum=0;
    vector<int> tempres[101];
    for(int i=0;i<N;i++){
        for(int v=M;v>=coins[i];v--){
            if(dp[v]<=dp[v-coins[i]]+coins[i]){
                dp[v]=dp[v-coins[i]]+coins[i];
                tempres[v]=tempres[v-coins[i]];
                tempres[v].push_back(coins[i]);
                //cout<<i<<' '<<v<<endl;
            }
        }
    }
    
    if(dp[M]==M) res=tempres[M];
    //cout<<res.size()<<endl;
    sort(res.begin(),res.end());
}
```



### A1072 Gas Station

A gas station has to be built at such a location that the minimum distance between the station and any of the residential housing is as far away as possible. However it must guarantee that all the houses are in its service range.

Now given the map of the city and several candidate locations for the gas station, you are supposed to give the best recommendation. If there are more than one solution, output the one with the smallest average distance to all the houses. If such a solution is still not unique, output the one with the smallest index number.

**Input Specification:**

Each input file contains one test case. For each case, the first line contains 4 positive integers: *N* (≤103), the total number of houses; *M* (≤10), the total number of the candidate locations for the gas stations; *K* (≤104), the number of roads connecting the houses and the gas stations; and *D**S*, the maximum service range of the gas station. It is hence assumed that all the houses are numbered from 1 to *N*, and all the candidate locations are numbered from `G`1 to `G`*M*.

Then *K* lines follow, each describes a road in the format

```
P1 P2 Dist
```

where `P1` and `P2` are the two ends of a road which can be either house numbers or gas station numbers, and `Dist` is the integer length of the road.

**Output Specification:**

For each test case, print in the first line the index number of the best location. In the next line, print the minimum and the average distances between the solution and all the houses. The numbers in a line must be separated by a space and be accurate up to 1 decimal place. If the solution does not exist, simply output `No Solution`.

**Sample Input 1:**

```in
4 3 11 5
1 2 2
1 4 2
1 G1 4
1 G2 3
2 3 2
2 G2 1
3 4 2
3 G3 2
4 G1 3
G2 G1 1
G3 G2 2
```

**Sample Output 1:**

```out
G1
2.0 3.3
```

**Sample Input 2:**

```in
2 1 2 10
1 G1 9
2 G1 20
```

**Sample Output 2:**

```out
No Solution
```

**Solution:**

```C++
#include<bits/stdc++.h>

using namespace std;
const double inf = 1e8;
const int maxn = 1024;
int N, M, K, Ds;

double G[maxn][maxn];
double min_dis[maxn];
double avg_dis[maxn];

void init();

int save(string s);

void dijkstra(int s);

int main() {
	init();

	double mindis = 0, minavgdis = inf;
	int res = 0;
	for (int i = 1001; i <= 1000 + M; i++) {
		dijkstra(i);
		if (min_dis[i] && avg_dis[i] && min_dis[i]<=Ds && mindis <= min_dis[i]) {
            if(mindis != min_dis[i])mindis = min_dis[i],minavgdis = inf;
			if (minavgdis > avg_dis[i]) {
				minavgdis = avg_dis[i];
				mindis = min_dis[i];
				res = i;
			}
		}
	}

	if (res) {
		cout << 'G' << res - 1000 << endl;
		cout << fixed << setprecision(1) << mindis;
		cout << ' ';
		cout << fixed << setprecision(1) << minavgdis << endl;
	}
	else cout << "No Solution" << endl;

	return 0;
}

void init() {
	cin >> N >> M >> K >> Ds;
	string s1, s2;
	int r1, r2;
	double dist;
    
    fill(G[0],G[0]+maxn*maxn,inf);
    
	while (K--) {
		cin >> s1 >> s2 >> dist;
		r1 = save(s1);
		r2 = save(s2);
		G[r1][r2] = dist;
		G[r2][r1] = dist;
	}
}

int save(string s) {
	int num = 0, st;
	st = (s[0] == 'G') ? 1 : 0;
	for (int i = st; i < s.size(); i++) {
		num *= 10;
		num += s[i] - '0';
	}
	if (s[0] == 'G') {
		return 1000 + num;
	}
	else {
		return num;
	}
}

void dijkstra(int s) {
	double dis[maxn];
	bool vis[maxn] = { false };
	fill(dis, dis + maxn, inf);
	dis[s] = 0;

	int tempN = N + M;
	while (tempN--) {
		double min = inf;
		int u = 0;
		for (int i = 1; i <= N; i++)
			if (!vis[i] && dis[i] < min) {
				min = dis[i];
				u = i;
			}
		for (int i = 1001; i <= 1000 + M; i++)
			if (!vis[i] && dis[i] < min) {
				min = dis[i];
				u = i;
			}
		if (u == 0) return;
		else vis[u] = true;

		for (int i = 1; i <= N; i++)
			if (!vis[i] && G[u][i]<inf && dis[i] > dis[u] + G[u][i]) {
				dis[i] = dis[u] + G[u][i];
			}
		for (int i = 1001; i <= 1000 + M; i++)
			if (!vis[i] && G[u][i]<inf && dis[i] > dis[u] + G[u][i]) {
				dis[i] = dis[u] + G[u][i];
			}
	}

	double mindis = inf, sumdis = 0;
	int cnt = 0;
	for (int i = 1; i <= N; i++) {
		if (dis[i] <= Ds) {
			cnt++;
			sumdis += dis[i];
			if (mindis > dis[i]) mindis = dis[i];
		}else return;
	}

	if (cnt == N) {
		min_dis[s] = mindis;
		avg_dis[s] = sumdis / (double)N;

		//cout << s << ' ' << mindis << ' ' << avg_dis[s] << endl;
	}else min_dis[s]=0,avg_dis[s]=0;
}
```



### A1076 Forwards in Weibo

Weibo is known as the Chinese version of Twitter. One user on Weibo may have many followers, and may follow many other users as well. Hence a social network is formed with followers relations. When a user makes a post on Weibo, all his/her followers can view and forward his/her post, which can then be forwarded again by their followers. Now given a social network, you are supposed to calculate the maximum potential amount of forwards for any specific user, assuming that only *L* levels of indirect followers are counted.

**Input Specification:**

Each input file contains one test case. For each case, the first line contains 2 positive integers: *N* (≤1000), the number of users; and *L* (≤6), the number of levels of indirect followers that are counted. Hence it is assumed that all the users are numbered from 1 to *N*. Then *N* lines follow, each in the format:

```
M[i] user_list[i]
```

where `M[i]` (≤100) is the total number of people that `user[i]` follows; and `user_list[i]` is a list of the `M[i]` users that followed by `user[i]`. It is guaranteed that no one can follow oneself. All the numbers are separated by a space.

Then finally a positive *K* is given, followed by *K* `UserID`'s for query.

**Output Specification:**

For each `UserID`, you are supposed to print in one line the maximum potential amount of forwards this user can trigger, assuming that everyone who can view the initial post will forward it once, and that only *L* levels of indirect followers are counted.

**Sample Input:**

```in
7 3
3 2 3 4
0
2 5 6
2 3 1
2 3 4
1 4
1 5
2 2 6
```

**Sample Output:**

```out
4
5
```

**Solution:**

```C++
#include<bits/stdc++.h>

using namespace std;

const int maxn=1024;
vector<int> user_list[maxn];
bool is_in[maxn]={false};
queue<int> temp;
vector<int> query;
int N,L,K,cnt=0;

void init();

void dfs(int k,int lvl);

void bfs(int x);

int main(){
    init();
    
    cin>>K;
    if(K==L) return -1;
    while(K--){
        cnt=0;
        int x;
        cin>>x;
        fill(is_in,is_in+N+1,false);
        bfs(x);
        cout<<cnt<<endl;
    }
    
    return 0;
}

void init(){
    int m,x;
    cin>>N>>L;
    for(int i=1;i<=N;i++){
        cin>>m;
        //cout<<m<<endl;
        while(m--){
            cin>>x;
            user_list[x].push_back(i);
        }
    }
}

void dfs(int k,int lvl){
    is_in[k]=true;
    for(int a:user_list[k]){
        if(!is_in[a] && lvl<L) {
            cnt++;
            dfs(a,lvl+1);
        }
    }
    //is_in[k]=false;
}

void bfs(int x){
    temp.push(x);
    is_in[x]=true;
    int lvl[maxn]={0},head;
    while(temp.size()){
        head=temp.front();
        temp.pop();
        
            for(int a:user_list[head]) {
                if(!is_in[a]) {
                    lvl[a]=lvl[head]+1;
                    
                    if(lvl[a]<=L) {cnt++;temp.push(a);is_in[a]=true;}
                }
            }
    }
}
```



### A1080 Graduate Admission

It is said that in 2011, there are about 100 graduate schools ready to proceed over 40,000 applications in Zhejiang Province. It would help a lot if you could write a program to automate the admission procedure.

Each applicant will have to provide two grades: the national entrance exam grade $G_E$, and the interview grade $G_E$. The final grade of an applicant is ($G_E+G_I$)/2. The admission rules are:

- The applicants are ranked according to their final grades, and will be admitted one by one from the top of the rank list.
- If there is a tied final grade, the applicants will be ranked according to their national entrance exam grade $G_E$. If still tied, their ranks must be the same.
- Each applicant may have *K* choices and the admission will be done according to his/her choices: if according to the rank list, it is one's turn to be admitted; and if the quota of one's most preferred shcool is not exceeded, then one will be admitted to this school, or one's other choices will be considered one by one in order. If one gets rejected by all of preferred schools, then this unfortunate applicant will be rejected.
- If there is a tied rank, and if the corresponding applicants are applying to the same school, then that school must admit all the applicants with the same rank, **even if its quota will be exceeded**.

**Input Specification:**

Each input file contains one test case.

Each case starts with a line containing three positive integers: *N* (≤40,000), the total number of applicants; *M* (≤100), the total number of graduate schools; and *K* (≤5), the number of choices an applicant may have.

In the next line, separated by a space, there are *M* positive integers. The *i*-th integer is the quota of the *i*-th graduate school respectively.

Then *N* lines follow, each contains 2+*K* integers separated by a space. The first 2 integers are the applicant's $G_E$ and $G_I$, respectively. The next *K* integers represent the preferred schools. For the sake of simplicity, we assume that the schools are numbered from 0 to *M*−1, and the applicants are numbered from 0 to *N*−1.

**Output Specification:**

For each test case you should output the admission results for all the graduate schools. The results of each school must occupy a line, which contains the applicants' numbers that school admits. The numbers must be in increasing order and be separated by a space. There must be no extra space at the end of each line. If no applicant is admitted by a school, you must output an empty line correspondingly.

**Sample Input:**

```in
11 6 3
2 1 2 2 2 3
100 100 0 1 2
60 60 2 3 5
100 90 0 3 4
90 100 1 2 0
90 90 5 1 3
80 90 1 0 2
80 80 0 1 2
80 80 0 1 2
80 70 1 3 2
70 80 1 2 3
100 100 0 2 4
```

**Sample Output:**

```out
0 10
3
5 6 7
2 8

1 4
```

**Solution:**

```C++
#include<iostream>
using namespace std;
#include<algorithm>

struct apl {
int id;
int ge;
int gi;
int fg;
int schl[5] = { 0 };
bool adm = false;
int as = 0;
int rs = 0;
};
struct grd {
int qto[40001];
int len = 0;
};
bool cmp1(apl a, apl b);
bool cmp0(int a, int b);
bool cmp2(apl a, apl b);
int main() {
	//cout << "hello" << endl;
	int N, M, K;
	cin >> N >> M >> K;
	int qut[101];
	for (int i = 0; i < M; i++) { cin >> qut[i]; }
	apl *p;
	p = new apl[N];
	grd *q;
	q = new grd[M];
	for (int i = 0; i<N; i++) {
		cin >> p[i].ge >> p[i].gi;
		p[i].fg = p[i].ge + p[i].gi;
		for (int j = 0; j<K; j++) { cin >> p[i].schl[j]; }
		p[i].id = i;
	}
	sort(p, p + N, cmp2);
	/*
	for (int r = 0; r < K; r++) {
	sort(p, p + N, cmp1);
	for (int i = 0; i<N ; i++) {
	p[i].rs = r + 1;
	if (p[i].adm != false) continue;
	int gr = p[i].schl[r];
	if(qut[gr]>0){ p[i].adm = true; qut[gr]--; }
	else {
	for (int s = i+1; s < N; s++) {
	if (p[s].adm == true&& gr == p[s].as&&p[i].fg == p[s].fg&&p[i].ge == p[s].ge)
	{p[i].adm = true; break;}
	}
	}
	if (p[i].adm == true) {
	p[i].as = gr;
	q[gr].qto[q[gr].len] = p[i].id;
	q[gr].len++;
	}
	}
	}
	*/
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < K; j++) {
			int gr = p[i].schl[j];
			if (qut[gr]>0) { p[i].adm = true; qut[gr]--; }
			else {
				for (int s = 0; s < i; s++) {
					if (p[s].adm == true && gr == p[s].as&&p[i].fg == p[s].fg&&p[i].ge == p[s].ge)
					{
						p[i].adm = true; break;
					}
				}
			}
			if (p[i].adm == true) {
				p[i].as = gr;
				q[gr].qto[q[gr].len] = p[i].id;
				q[gr].len++;
				break;
			}
		}
	}
	//print
	for (int i = 0; i<M; i++) {
		if (q[i].len != 0) {
			sort(q[i].qto, q[i].qto + q[i].len, cmp0);
			for (int j = 0; j<q[i].len; j++) { if (j>0) cout << ' '; cout << q[i].qto[j]; }
		}
		cout << endl;
	}
	delete[]p;
	delete[]q;
	return 0;
}
bool cmp1(apl a, apl b) {
	if (a.adm == true) return false;
	//else if (a.schl[a.rs] != b.schl[b.rs]) return a.schl[a.rs]<b.schl[b.rs];
	else if (a.fg != b.fg) return a.fg>b.fg;
	else return a.ge > b.ge;
	//else return true;
}
bool cmp0(int a, int b) {
	if (a != b)return a < b;
	else return true;
}
bool cmp2(apl a,apl b) {
	if (a.fg != b.fg) return a.fg>b.fg;
	else return a.ge > b.ge;
}
```



### A1087 All Roads Lead to Rome

Indeed there are many different tourist routes from our city to Rome. You are supposed to find your clients the route with the least cost while gaining the most happiness.

**Input Specification:**

Each input file contains one test case. For each case, the first line contains 2 positive integers *N* (2≤*N*≤200), the number of cities, and *K*, the total number of routes between pairs of cities; followed by the name of the starting city. The next *N*−1 lines each gives the name of a city and an integer that represents the happiness one can gain from that city, except the starting city. Then *K* lines follow, each describes a route between two cities in the format `City1 City2 Cost`. Here the name of a city is a string of 3 capital English letters, and the destination is always `ROM` which represents Rome.

**Output Specification:**

For each test case, we are supposed to find the route with the least cost. If such a route is not unique, the one with the maximum happiness will be recommanded. If such a route is still not unique, then we output the one with the maximum average happiness -- it is guaranteed by the judge that such a solution exists and is unique.

Hence in the first line of output, you must print 4 numbers: the number of different routes with the least cost, the cost, the happiness, and the average happiness (take the integer part only) of the recommanded route. Then in the next line, you are supposed to print the route in the format `City1->City2->...->ROM`.

**Sample Input:**

```in
6 7 HZH
ROM 100
PKN 40
GDN 55
PRS 95
BLN 80
ROM GDN 1
BLN ROM 1
HZH PKN 1
PRS ROM 2
BLN HZH 2
PKN GDN 1
HZH PRS 1
```

**Sample Output:**

```out
3 3 195 97
HZH->PRS->ROM
```

**Solution:**

```C++
#include<bits/stdc++.h>

using namespace std;
const int maxn=210;
const int inf=100000000;
int N,K,org,des,least_num=0;

unordered_map<string,int> name2code;
int G[maxn][maxn];
string code2name[maxn];
int happiness[maxn]={0};

vector<int> pre_set[maxn];

void initGraph();

void dijkstra(int s,int t);

void dfs(int t);

int main(){
    initGraph();
    
    dijkstra(org,des);
    
    return 0;
}

void initGraph(){
    string source,destination="ROM";
    cin>>N>>K>>source;
    int k=1;
    name2code[destination]=k;
    code2name[k]=destination;
    des=k;
    k++;
    name2code[source]=k;
    code2name[k]=source;
    org=k;
    k++;
    int temp=N-1,happy;
    string temps;
    while(temp--){
        cin>>temps>>happy;
        if(name2code[temps]==0){
            name2code[temps]=k;
            code2name[k]=temps;
            happiness[k]=happy;
            k++;
        }else{
            happiness[name2code[temps]]=happy;
        }
    }
    fill(G[0],G[0]+maxn*maxn,inf);
    string s1,s2;
    int cost,x1,x2;
    while(K--){
        cin>>s1>>s2>>cost;
        x1=name2code[s1],x2=name2code[s2];
        G[x1][x2]=cost;
        G[x2][x1]=cost;
    }
}

void dijkstra(int s,int t){
    int pre[maxn],dis[maxn],tothappy[maxn],cnt_vis[maxn];
    fill(pre,pre+maxn,-1);
    fill(dis,dis+maxn,inf);
    bool visited[maxn]={false};
    dis[s]=0;
    tothappy[s]=0;
    cnt_vis[s]=0;
    int tempN=N;
    while(tempN--){
        int min=inf,u=-1;
        for(int j=1;j<=N;j++){
            if(!visited[j] && dis[j]<min){
                min=dis[j];
                u=j;
            }
        }
        
        if(u==-1) return;
        visited[u]=true;
        
        for(int j=1;j<=N;j++){
            if(!visited[j] && dis[j]>=dis[u]+G[u][j]){
                if(dis[j]>dis[u]+G[u][j]){
                    pre_set[j].clear();
                    dis[j]=dis[u]+G[u][j];
                    pre[j]=u;
                    tothappy[j]=tothappy[u]+happiness[j];
                    cnt_vis[j]=cnt_vis[u]+1;
                }else{
                    if(tothappy[j]<tothappy[u]+happiness[j]){
                        pre[j]=u;
                        tothappy[j]=tothappy[u]+happiness[j];
                        cnt_vis[j]=cnt_vis[u]+1;
                    }else if(tothappy[j]==tothappy[u]+happiness[j]){
                        if(cnt_vis[j]>cnt_vis[u]+1){
                            pre[j]=u;
                            cnt_vis[j]=cnt_vis[u]+1;
                        }
                    }
                }
                pre_set[j].push_back(u);
            }
        }
    }
    
    dfs(t);
    
    cout<<least_num<<' '<<dis[t]<<' '<<tothappy[t]<<' '<<tothappy[t]/cnt_vis[t]<<endl;
    
    int rk=t;
    vector<int> rev_rank;
    while(rk!=-1){
        rev_rank.push_back(rk);
        rk=pre[rk];
    }
    
    for(int i=rev_rank.size()-1;i>=0;i--){
        cout<<code2name[rev_rank[i]];
        if(i) cout<<"->";
        else cout<<endl;
    }
}

void dfs(int t){
    if(t==org) {
        least_num++;
        return;
    }
    
    for(int a:pre_set[t]){
        dfs(a);
    }
}
```



### A1091 Acute Stroke

One important factor to identify acute stroke (急性脑卒中) is the volume of the stroke core. Given the results of image analysis in which the core regions are identified in each MRI slice, your job is to calculate the volume of the stroke core.

**Input Specification:**

Each input file contains one test case. For each case, the first line contains 4 positive integers: *M*, *N*, *L* and *T*, where *M* and *N* are the sizes of each slice (i.e. pixels of a slice are in an *M*×*N* matrix, and the maximum resolution is 1286 by 128); *L* (≤60) is the number of slices of a brain; and *T* is the integer threshold (i.e. if the volume of a connected core is less than *T*, then that core must not be counted).

Then *L* slices are given. Each slice is represented by an *M*×*N* matrix of 0's and 1's, where 1 represents a pixel of stroke, and 0 means normal. Since the thickness of a slice is a constant, we only have to count the number of 1's to obtain the volume. However, there might be several separated core regions in a brain, and only those with their volumes no less than *T* are counted. Two pixels are **connected** and hence belong to the same region if they share a common side, as shown by Figure 1 where all the 6 red pixels are connected to the blue one.

![figstroke.jpg](https://images.ptausercontent.com/f85c00cc-62ce-41ff-8dd0-d1c288d87409.jpg)

Figure 1

**Output Specification:**

For each case, output in a line the total volume of the stroke core.

**Sample Input:**

```in
3 4 5 2
1 1 1 1
1 1 1 1
1 1 1 1
0 0 1 1
0 0 1 1
0 0 1 1
1 0 1 1
0 1 0 0
0 0 0 0
1 0 1 1
0 0 0 0
0 0 0 0
0 0 0 1
0 0 0 1
1 0 0 0
```

**Sample Output:**

```out
26
```

**Solution:**

```C++
#include<iostream>
#include<queue>

using namespace std;

struct node{
    int x,y,z;
}Node;

int n,m,slice,T;
int pixel[1290][130][70];
bool inq[1290][130][70]={false};

int X[]={-1,1,0,0,0,0};
int Y[]={0,0,-1,1,0,0};
int Z[]={0,0,0,0,-1,1};

bool judge(int x,int y,int z){
    if(x>=n || x<0 || y>=m || y<0 || z>=slice || z<0)
        return false;
    if(pixel[x][y][z]==0 || inq[x][y][z]==true)
        return false;
    return true;
}

int BFS(int x,int y,int z){
    int tot=0;
    queue<node> Q;
    Node.x=x,Node.y=y,Node.z=z;
    Q.push(Node);
    inq[x][y][z]=true;
    while(!Q.empty()){
        node top =Q.front();
        Q.pop();
        tot++;
        for(int i=0;i<6;i++){
            int newX=top.x+X[i];
            int newY=top.y+Y[i];
            int newZ=top.z+Z[i];
            if(judge(newX,newY,newZ)){
                Node.x=newX,Node.y=newY,Node.z=newZ;
                Q.push(Node);
                inq[newX][newY][newZ]=true;
            }
        }
    }
    if(tot>=T) return tot;
    else return 0;
}

int main(){
    cin>>n>>m>>slice>>T;
    for(int z=0;z<slice;z++){
        for(int x=0;x<n;x++){
            for(int y=0;y<m;y++){
                cin>>pixel[x][y][z];
            }
        }
    }
    int ans=0;
    for(int z=0;z<slice;z++){
        for(int x=0;x<n;x++){
            for(int y=0;y<m;y++){
                if(pixel[x][y][z]==1 && inq[x][y][z]==false){
                    ans+=BFS(x,y,z);
                }
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}
```



###A1095 Cars on Campus

Zhejiang University has 8 campuses and a lot of gates. From each gate we can collect the in/out times and the plate numbers of the cars crossing the gate. Now with all the information available, you are supposed to tell, at any specific time point, the number of cars parking on campus, and at the end of the day find the cars that have parked for the longest time period.

**Input Specification:**

Each input file contains one test case. Each case starts with two positive integers *N* (≤104), the number of records, and *K* (≤8×104) the number of queries. Then *N* lines follow, each gives a record in the format:

```
plate_number hh:mm:ss status
```

where `plate_number` is a string of 7 English capital letters or 1-digit numbers; `hh:mm:ss` represents the time point in a day by hour:minute:second, with the earliest time being `00:00:00` and the latest `23:59:59`; and `status` is either `in` or `out`.

Note that all times will be within a single day. Each `in` record is paired with the chronologically next record for the same car provided it is an `out` record. Any `in` records that are not paired with an `out` record are ignored, as are `out` records not paired with an `in` record. It is guaranteed that at least one car is well paired in the input, and no car is both `in` and `out` at the same moment. Times are recorded using a 24-hour clock.

Then *K* lines of queries follow, each gives a time point in the format `hh:mm:ss`. Note: the queries are given in **ascending** order of the times.

**Output Specification:**

For each query, output in a line the total number of cars parking on campus. The last line of output is supposed to give the plate number of the car that has parked for the longest time period, and the corresponding time length. If such a car is not unique, then output all of their plate numbers in a line in alphabetical order, separated by a space.

**Sample Input:**

```in
16 7
JH007BD 18:00:01 in
ZD00001 11:30:08 out
DB8888A 13:00:00 out
ZA3Q625 23:59:50 out
ZA133CH 10:23:00 in
ZD00001 04:09:59 in
JH007BD 05:09:59 in
ZA3Q625 11:42:01 out
JH007BD 05:10:33 in
ZA3Q625 06:30:50 in
JH007BD 12:23:42 out
ZA3Q625 23:55:00 in
JH007BD 12:24:23 out
ZA133CH 17:11:22 out
JH007BD 18:07:01 out
DB8888A 06:30:50 in
05:10:00
06:30:50
11:00:00
12:23:42
14:00:00
18:00:00
23:59:00
```

**Sample Output:**

```out
1
4
5
2
1
0
1
JH007BD ZD00001 07:20:09
```

**Solution:**

```C++
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
```



###A1099 Build A Binary Search Tree

A Binary Search Tree (BST) is recursively defined as a binary tree which has the following properties:

- The left subtree of a node contains only nodes with keys less than the node's key.
- The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
- Both the left and right subtrees must also be binary search trees.

Given the structure of a binary tree and a sequence of distinct integer keys, there is only one way to fill these keys into the tree so that the resulting tree satisfies the definition of a BST. You are supposed to output the level order traversal sequence of that tree. The sample is illustrated by Figure 1 and 2.

![figBST.jpg](https://images.ptausercontent.com/24c2521f-aaed-4ef4-bac8-3ff562d80a1b.jpg)

**Input Specification:**

Each input file contains one test case. For each case, the first line gives a positive integer *N* (≤100) which is the total number of nodes in the tree. The next *N* lines each contains the left and the right children of a node in the format `left_index right_index`, provided that the nodes are numbered from 0 to *N*−1, and 0 is always the root. If one child is missing, then −1 will represent the NULL child pointer. Finally *N* distinct integer keys are given in the last line.

**Output Specification:**

For each test case, print in one line the level order traversal sequence of that tree. All the numbers must be separated by a space, with no extra space at the end of the line.

**Sample Input:**

```in
9
1 6
2 3
-1 -1
-1 4
5 -1
-1 -1
7 -1
-1 8
-1 -1
73 45 11 58 82 25 67 38 42
```

**Sample Output:**

```out
58 25 82 11 38 67 45 73 42
```

**Solution:**

```C++
#include<bits/stdc++.h>

using namespace std;
const int maxn=101;
int N,root=0,numbers[maxn];

vector<int> depth_cnt[maxn];

unordered_map<int,int> number_code;

struct node{
    int d=-1;
    int val=-1;
    int left_rk=-1;
    int right_rk=-1;
}nd[maxn];

void init();

int treeConstruct(int pr,int l,int depth);

void dfs(int x);

void showResult();

int main(){
    init();
    
    int num=treeConstruct(root,0,0);
    
    if(num!=N) return -1;
    
    showResult();
    
    return 0;
}

void init(){
    cin>>N;
    int a,b;
    for(int i=0;i<N;i++){
        cin>>a>>b;
        nd[i].left_rk=a;
        nd[i].right_rk=b;
    }
    
    for(int i=0;i<N;i++) cin>>numbers[i];
    
    sort(numbers,numbers+N);
    
    for(int i=0;i<N;i++) number_code[numbers[i]]=i;
}

int treeConstruct(int pr,int l,int depth){
    nd[pr].d=depth;
    
    int left_num=(nd[pr].left_rk==-1)?0:treeConstruct(nd[pr].left_rk,l,depth+1);
    
    nd[pr].val=numbers[l+left_num];
    
    depth_cnt[depth].push_back(nd[pr].val);
    
    int right_num=(nd[pr].right_rk==-1)?0:treeConstruct(nd[pr].right_rk,number_code[nd[pr].val]+1,depth+1);
    
    return left_num+right_num+1;
    
}

void showResult(){
    for(int i=0;depth_cnt[i].size()!=0;i++){
        for(int a:depth_cnt[i]){
            cout<<a;
            if(depth_cnt[i+1].size()==0 && a==depth_cnt[i][depth_cnt[i].size()-1]) cout<<endl;
            else cout<<' ';
        }
    }
}
```



###A1103 Integer Factorization

The *K*−*P* factorization of a positive integer *N* is to write *N* as the sum of the *P*-th power of *K* positive integers. You are supposed to write a program to find the *K*−*P* factorization of *N* for any positive integers *N*, *K* and *P*.

**Input Specification:**

Each input file contains one test case which gives in a line the three positive integers *N* (≤400), *K* (≤*N*) and *P* (1<*P*≤7). The numbers in a line are separated by a space.

**Output Specification:**

For each case, if the solution exists, output in the format:

```
N = n[1]^P + ... n[K]^P
```

where `n[i]` (`i` = 1, ..., `K`) is the `i`-th factor. All the factors must be printed in non-increasing order.

Note: the solution may not be unique. For example, the 5-2 factorization of 169 has 9 solutions, such as $12^2+4^2+2^2+2^2+1^2$, or $11^2+6^2+2^2+2^2+2^2$, or more. You must output the one with the maximum sum of the factors. If there is a tie, the largest factor sequence must be chosen -- sequence { *a*1,*a*2,⋯,*a**K* } is said to be **larger** than { ,$b_1$,$b_2$,⋯,$b_k$ } if there exists 1≤*L*≤*K* such that $a_i=b_i$ for *i*<*L* and $a_L$>$b_L$.

If there is no solution, simple output `Impossible`.

**Sample Input 1:**

```in
169 5 2
```

**Sample Output 1:**

```out
169 = 6^2 + 6^2 + 6^2 + 6^2 + 5^2
```

**Sample Input 2:**

```in
169 167 3
```

**Sample Output 2:**

```out
Impossible
```

**Solution:**

```C++
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int N,K,P,maxFacSum=0;
vector<int> fac,ans,temp;

int power(int x){
    int as=1;
    for(int i=0;i<P;i++){as*=x;}
    return as;
}

void init(){
    int i=0,t=0;
    while(t<=N){
        fac.push_back(t);
        t=power(++i);
    }
}

void DFS(int index,int nowK,int sum,int facSum){
    if(sum==N && nowK==K){
        if(facSum>maxFacSum){
            ans=temp;
            maxFacSum=facSum;
        }
        return;
    }
    if(sum>N || nowK>K) return;
    if(index-1>=0){
        temp.push_back(index);
        DFS(index,nowK+1,sum+fac[index],facSum+index);
        temp.pop_back();
        DFS(index-1,nowK,sum,facSum);
    }
}

int main(){
    cin>>N>>K>>P;
    init();
    DFS(fac.size()-1,0,0,0);
    if(maxFacSum==0) cout<<"Impossible"<<endl;
    else{
        cout<<N<<" = ";
        for(int i=0;i<ans.size();i++){
            if(i!=0) cout<<" + ";
            cout<<ans[i]<<'^'<<P;
        }
        cout<<endl;
    }
    return 0;
}
```



###A1107 Social Clusters

When register on a social network, you are always asked to specify your hobbies in order to find some potential friends with the same hobbies. A **social cluster** is a set of people who have some of their hobbies in common. You are supposed to find all the clusters.

**Input Specification:**

Each input file contains one test case. For each test case, the first line contains a positive integer *N* (≤1000), the total number of people in a social network. Hence the people are numbered from 1 to *N*. Then *N* lines follow, each gives the hobby list of a person in the format:

$K_i$: $h_i[1]$ $h_i[2]$ ... $h_i[K_i]$

where $K_i$ (>0) is the number of hobbies, and $h_i[j]$ is the index of the *j*-th hobby, which is an integer in [1, 1000].

**Output Specification:**

For each case, print in one line the total number of clusters in the network. Then in the second line, print the numbers of people in the clusters in non-increasing order. The numbers must be separated by exactly one space, and there must be no extra space at the end of the line.

**Sample Input:**

```in
8
3: 2 7 10
1: 4
2: 5 3
1: 4
1: 3
1: 4
4: 6 8 1 5
1: 4
```

**Sample Output:**

```out
3
4 3 1
```

**Solutions:**

```C++
#include<bits/stdc++.h>

using namespace std;
const int maxn=1024;
int N,cnt=0;

unordered_set<int> hobbies[maxn],persons[maxn],temp;
vector<unordered_set<int>> clusters;
bool visited[maxn]={false};
int hobbies_code[maxn]={0};

void init();

void dfs(int x);

bool cmp(unordered_set<int> a,unordered_set<int> b);

int main(){
    init();
    
    for(int i=1;i<=N;i++){
        if(!visited[i]) {
            temp.clear();
            dfs(i);
            clusters.push_back(temp);
        }
    }
    
    cout<<clusters.size()<<endl;
    
    sort(clusters.begin(),clusters.end(),cmp);
    
    for(vector<unordered_set<int>>::iterator it=clusters.begin();it!=clusters.end();it++){
        cout<<it->size();
        if(it==clusters.end()-1) cout<<endl;
        else cout<<' ';
    }
    
    return 0;
}

void init(){
    cin>>N;
    int k,x;
    for(int i=1;i<=N;i++){
        scanf("%d:",&k);
        while(k--){
            cin>>x;
            hobbies[i].insert(x);
            persons[x].insert(i);
        }
    }
}

void dfs(int x){
    visited[x]=true;
    temp.insert(x);
    for(unordered_set<int>::iterator it=hobbies[x].begin();it!=hobbies[x].end();it++){
        for(unordered_set<int>::iterator is=persons[*it].begin();is!=persons[*it].end();is++){
            if(!visited[*is]) dfs(*is);
        }
    }
}

bool cmp(unordered_set<int> a,unordered_set<int> b){
    return a.size()>b.size();
}
```



###A1111 Online Map

Input our current position and a destination, an online map can recommend several paths. Now your job is to recommend two paths to your user: one is the shortest, and the other is the fastest. It is guaranteed that a path exists for any request.

**Input Specification:**

Each input file contains one test case. For each case, the first line gives two positive integers *N* (2≤*N*≤500), and *M*, being the total number of streets intersections on a map, and the number of streets, respectively. Then *M* lines follow, each describes a street in the format:

```
V1 V2 one-way length time
```

where `V1` and `V2` are the indices (from 0 to *N*−1) of the two ends of the street; `one-way` is 1 if the street is one-way from `V1` to `V2`, or 0 if not; `length` is the length of the street; and `time` is the time taken to pass the street.

Finally a pair of source and destination is given.

**Output Specification:**

For each case, first print the shortest path from the source to the destination with distance `D` in the format:

```
Distance = D: source -> v1 -> ... -> destination
```

Then in the next line print the fastest path with total time `T`:

```
Time = T: source -> w1 -> ... -> destination
```

In case the shortest path is not unique, output the fastest one among the shortest paths, which is guaranteed to be unique. In case the fastest path is not unique, output the one that passes through the fewest intersections, which is guaranteed to be unique.

In case the shortest and the fastest paths are identical, print them in one line in the format:

```
Distance = D; Time = T: source -> u1 -> ... -> destination
```

**Sample Input 1:**

```in
10 15
0 1 0 1 1
8 0 0 1 1
4 8 1 1 1
3 4 0 3 2
3 9 1 4 1
0 6 0 1 1
7 5 1 2 1
8 5 1 2 1
2 3 0 2 2
2 1 1 1 1
1 3 0 3 1
1 4 0 1 1
9 7 1 3 1
5 1 0 5 2
6 5 1 1 2
3 5
```

**Sample Output 1:**

```out
Distance = 6: 3 -> 4 -> 8 -> 5
Time = 3: 3 -> 1 -> 5
```

**Sample Input 2:**

```in
7 9
0 4 1 1 1
1 6 1 1 3
2 6 1 1 1
2 5 1 2 2
3 0 0 1 1
3 1 1 1 3
3 2 1 1 2
4 5 0 2 2
6 5 1 1 2
3 5
```

**Sample Output 2:**

```out
Distance = 3; Time = 4: 3 -> 2 -> 5
```

**Solution:**

```C++
#include<bits/stdc++.h>

using namespace std;

const int maxn=501;
const int inf=100000000;

int L[maxn][maxn],T[maxn][maxn];

int N,M,source,target,totdistance,tottime;

vector<int> length_seq,time_seq;

void initGraph();

void dijlstraT(int s,int t);
void dijlstraL(int s,int t);

void resultGeneration();

int main(){
    initGraph();
    
    cin>>source>>target;
    
    dijlstraL(source,target);
    dijlstraT(source,target);
    
    resultGeneration();
    
    return 0;
}

void initGraph(){
    cin>>N>>M;
    int s,t,ll,tt;
    bool one_way=false;
    fill(L[0],L[0]+maxn*maxn,inf);
    fill(T[0],T[0]+maxn*maxn,inf);
    while(M--){
        cin>>s>>t>>one_way>>ll>>tt;
        L[s][t]=ll;
        T[s][t]=tt;
        if(one_way==false) L[t][s]=ll,T[t][s]=tt;
    }
}

void dijlstraL(int s,int t){
    int pre[maxn],dis[maxn],sum_time[maxn];
    bool visited[maxn]={false};
    fill(pre,pre+maxn,-1);
    fill(dis,dis+maxn,inf);
    fill(sum_time,sum_time+maxn,inf);
    dis[s]=0;
    sum_time[s]=0;
    
    for(int i=0;i<N;i++){
        int min=inf,u=-1;
        for(int j=0;j<N;j++){
            if(!visited[j] && dis[j]<min){
                min=dis[j];
                u=j;
            }
        }
        
        if(u==-1) return;
        visited[u]=true;
        
        for(int j=0;j<N;j++){
            if(!visited[j] && dis[j]>=dis[u]+L[u][j]){
                if(dis[j]>dis[u]+L[u][j]){
                    dis[j]=dis[u]+L[u][j];
                    sum_time[j]=sum_time[u]+T[u][j];
                    pre[j]=u;
                }else if(sum_time[j]>sum_time[u]+T[u][j]){
                    sum_time[j]=sum_time[u]+T[u][j];
                    pre[j]=u;
                }
            }
        }
    }
    
    totdistance=dis[t];
    
    int k=t;
    while(k!=-1){
        length_seq.push_back(k);
        k=pre[k];
    }
}
void dijlstraT(int s,int t){
    int pre[maxn],dis[maxn],node_cnt[maxn]={0};
    bool visited[maxn]={false};
    fill(pre,pre+maxn,-1);
    fill(dis,dis+maxn,inf);
    dis[s]=0;
    
    for(int i=0;i<N;i++){
        int min=inf,u=-1;
        for(int j=0;j<N;j++){
            if(!visited[j] && dis[j]<min){
                min=dis[j];
                u=j;
            }
        }
        
        if(u==-1) return;
        visited[u]=true;
        
        for(int j=0;j<N;j++){
            if(!visited[j] && T[u][j]+dis[u]<=dis[j]){
                if(T[u][j]+dis[u]<dis[j]){
                    dis[j]=dis[u]+T[u][j];
                    pre[j]=u;
                    node_cnt[j]=node_cnt[u]+1;
                }else if(node_cnt[j]>node_cnt[u]+1){
                    node_cnt[j]=node_cnt[u]+1;
                    pre[j]=u;
                }
            }
        }
    }
    
    tottime=dis[t];
    int k=t;
    while(k!=-1){
        time_seq.push_back(k);
        k=pre[k];
    }
}

void resultGeneration(){
    if(length_seq.size()==time_seq.size()){
        int len=length_seq.size();
        bool isSame=true;
        for(int i=0;i<len;i++){
            if(length_seq[i]!=time_seq[i]) {
                isSame=false;
                break;
            }
        }
        if(isSame){
            cout<<"Distance = "<<totdistance<<"; Time = "<<tottime<<": ";
            for(vector<int>::iterator it=length_seq.end();it!=length_seq.begin();it--){
                cout<<*(it-1);
                if(it==length_seq.begin()+1) cout<<endl;
                else cout<<" -> ";
            }
            return;
        }
    }
    cout<<"Distance = "<<totdistance<<": ";
    for(vector<int>::iterator it=length_seq.end();it!=length_seq.begin();it--){
        cout<<*(it-1);
        if(it==length_seq.begin()+1) cout<<endl;
        else cout<<" -> ";
    }
    
    cout<<"Time = "<<tottime<<": ";
    for(vector<int>::iterator it=time_seq.end();it!=time_seq.begin();it--){
        cout<<*(it-1);
        if(it==time_seq.begin()+1) cout<<endl;
        else cout<<" -> ";
    }
}
```



###A1115 Counting Nodes in a BST

A Binary Search Tree (BST) is recursively defined as a binary tree which has the following properties:

- The left subtree of a node contains only nodes with keys less than or equal to the node's key.
- The right subtree of a node contains only nodes with keys greater than the node's key.
- Both the left and right subtrees must also be binary search trees.

Insert a sequence of numbers into an initially empty binary search tree. Then you are supposed to count the total number of nodes in the lowest 2 levels of the resulting tree.

**Input Specification:**

Each input file contains one test case. For each case, the first line gives a positive integer *N* (≤1000) which is the size of the input sequence. Then given in the next line are the *N* integers in [−1000,1000] which are supposed to be inserted into an initially empty binary search tree.

**Output Specification:**

For each case, print in one line the numbers of nodes in the lowest 2 levels of the resulting tree in the format:

```
n1 + n2 = n
```

where `n1` is the number of nodes in the lowest level, `n2` is that of the level above, and `n` is the sum.

Sample Input:

```in
9
25 30 42 16 20 20 35 -5 28
```

**Sample Output:**

```out
2 + 4 = 6
```

**Solution:**

```C++
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
```



###A1119 Pre- and Post-order Traversals

Suppose that all the keys in a binary tree are distinct positive integers. A unique binary tree can be determined by a given pair of postorder and inorder traversal sequences, or preorder and inorder traversal sequences. However, if only the postorder and preorder traversal sequences are given, the corresponding tree may no longer be unique.

Now given a pair of postorder and preorder traversal sequences, you are supposed to output the corresponding inorder traversal sequence of the tree. If the tree is not unique, simply output any one of them.

**Input Specification:**

Each input file contains one test case. For each case, the first line gives a positive integer N (≤ 30), the total number of nodes in the binary tree. The second line gives the preorder sequence and the third line gives the postorder sequence. All the numbers in a line are separated by a space.

**Output Specification:**

For each test case, first printf in a line `Yes` if the tree is unique, or `No` if not. Then print in the next line the inorder traversal sequence of the corresponding binary tree. If the solution is not unique, any answer would do. It is guaranteed that at least one solution exists. All the numbers in a line must be separated by exactly one space, and there must be no extra space at the end of the line.

**Sample Input 1:**

```in
7
1 2 3 4 6 7 5
2 6 7 4 5 3 1
```

**Sample Output 1:**

```out
Yes
2 1 6 4 7 3 5
```

**Sample Input 2:**

```in
4
1 2 3 4
2 4 3 1
```

**Sample Output 2:**

```out
No
2 1 3 4
```

**Solution:**

```C++
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
```



###A1123 Is It a Complete AVL Tree

An AVL tree is a self-balancing binary search tree. In an AVL tree, the heights of the two child subtrees of any node differ by at most one; if at any time they differ by more than one, rebalancing is done to restore this property. Figures 1-4 illustrate the rotation rules.

| ![F1.jpg](https://images.ptausercontent.com/fb337acb-93b0-4af2-9838-deff5ce98058.jpg) | ![F2.jpg](https://images.ptausercontent.com/d1635de7-3e3f-4aaa-889b-ba29f35890db.jpg) |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| ![F3.jpg](https://images.ptausercontent.com/e868e4b9-9fea-4f70-b7a7-1f5d8a3be4ef.jpg) | ![F4.jpg](https://images.ptausercontent.com/98aa1782-cea5-4792-8736-999436cf43a9.jpg) |

Now given a sequence of insertions, you are supposed to output the level-order traversal sequence of the resulting AVL tree, and to tell if it is a complete binary tree.

**Input Specification:**

Each input file contains one test case. For each case, the first line contains a positive integer N (≤ 20). Then N distinct integer keys are given in the next line. All the numbers in a line are separated by a space.

**Output Specification:**

For each test case, insert the keys one by one into an initially empty AVL tree. Then first print in a line the level-order traversal sequence of the resulting AVL tree. All the numbers in a line must be separated by a space, and there must be no extra space at the end of the line. Then in the next line, print `YES` if the tree is complete, or `NO` if not.

**Sample Input 1:**

```in
5
88 70 61 63 65
```

**Sample Output 1:**

```out
70 63 88 61 65
YES
```

**Sample Input 2:**

```in
8
88 70 61 96 120 90 65 68
```

**Sample Output 2:**

```out
88 65 96 61 70 90 120 68
NO
```

**Solution:**

```C++
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
```



###A1127 ZigZagging on a Tree

Suppose that all the keys in a binary tree are distinct positive integers. A unique binary tree can be determined by a given pair of postorder and inorder traversal sequences. And it is a simple standard routine to print the numbers in level-order. However, if you think the problem is too simple, then you are too naive. This time you are supposed to print the numbers in "zigzagging order" -- that is, starting from the root, print the numbers level-by-level, alternating between left to right and right to left. For example, for the following tree you must output: 1 11 5 8 17 12 20 15.

![zigzag.jpg](https://images.ptausercontent.com/337cbfb0-a7b2-4500-9664-318e9ffc870e.jpg)

**Input Specification:**

Each input file contains one test case. For each case, the first line gives a positive integer N (≤30), the total number of nodes in the binary tree. The second line gives the inorder sequence and the third line gives the postorder sequence. All the numbers in a line are separated by a space.

**Output Specification:**

For each test case, print the zigzagging sequence of the tree in a line. All the numbers in a line must be separated by exactly one space, and there must be no extra space at the end of the line.

**Sample Input:**

```in
8
12 11 20 17 1 15 8 5
12 20 17 11 15 8 5 1
```

**Sample Output:**

```out
1 11 5 8 17 12 20 15
```

**Solution:**

```c++
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
```



###A1131 Subway Map

In the big cities, the subway systems always look so complex to the visitors. To give you some sense, the following figure shows the map of Beijing subway. Now you are supposed to help people with your computer skills! Given the starting position of your user, your task is to find the quickest way to his/her destination.

![subwaymap.jpg](https://images.ptausercontent.com/55799c23-4bdb-4e32-af7f-6d41accfdd2b.jpg)

**Input Specification:**

Each input file contains one test case. For each case, the first line contains a positive integer *N* (≤ 100), the number of subway lines. Then *N* lines follow, with the *i*-th (*i*=1,⋯,*N*) line describes the *i*-th subway line in the format:

*M* S[1] S[2] ... S[*M*]

where *M* (≤ 100) is the number of stops, and S[*i*]'s (*i*=1,⋯,*M*) are the indices of the stations (the indices are 4-digit numbers from 0000 to 9999) along the line. It is guaranteed that the stations are given in the correct order -- that is, the train travels between S[*i*] and S[*i*+1] (*i*=1,⋯,*M*−1) without any stop.

Note: It is possible to have loops, but not self-loop (no train starts from S and stops at S without passing through another station). Each station interval belongs to a unique subway line. Although the lines may cross each other at some stations (so called "transfer stations"), no station can be the conjunction of more than 5 lines.

After the description of the subway, another positive integer *K* (≤ 10) is given. Then *K* lines follow, each gives a query from your user: the two indices as the starting station and the destination, respectively.

The following figure shows the sample map.

![samplemap.jpg](https://images.ptausercontent.com/932c8f1b-7dd5-489d-a774-a91c1fabba7f.jpg)

Note: It is guaranteed that all the stations are reachable, and all the queries consist of legal station numbers.

**Output Specification:**

For each query, first print in a line the minimum number of stops. Then you are supposed to show the optimal path in a friendly format as the following:

```
Take Line#X1 from S1 to S2.
Take Line#X2 from S2 to S3.
......
```

where `X`*i*'s are the line numbers and `S`*i*'s are the station indices. Note: Besides the starting and ending stations, only the transfer stations shall be printed.

If the quickest path is not unique, output the one with the minimum number of transfers, which is guaranteed to be unique.

**Sample Input:**

```in
4
7 1001 3212 1003 1204 1005 1306 7797
9 9988 2333 1204 2006 2005 2004 2003 2302 2001
13 3011 3812 3013 3001 1306 3003 2333 3066 3212 3008 2302 3010 3011
4 6666 8432 4011 1306
3
3011 3013
6666 2001
2004 3001
```

**Sample Output:**

```out
2
Take Line#3 from 3011 to 3013.
10
Take Line#4 from 6666 to 1306.
Take Line#3 from 1306 to 2302.
Take Line#2 from 2302 to 2001.
6
Take Line#2 from 2004 to 1204.
Take Line#1 from 1204 to 1306.
Take Line#3 from 1306 to 3001.
```

**Solution:**

```C++
#include<bits/stdc++.h>

using namespace std;

//unordered_map<int,unordered_map<int,int>> subwaynet;
const int maxn=1e5;

int N,M,K;

unordered_set<int> subwaynet[maxn];

unordered_map<int,unordered_map<int,int>> line_of_node;

bool visited[maxn]={false};

int temp_stops;
int stops;
vector<int> temp_transfer_stops;
vector<int> transfer_stops;
vector<int> temp_line_code;
vector<int> line_code;

void init();

void query();

void get_route(int s,int t);

void dfs(int s,int t,int ln);

void fourdigits(int x);

int main(){
    init();
    
    query();
    
    return 0;
}

void init(){
    int nd;
    cin>>N;
    for(int i=1;i<=N;i++){
        cin>>M;
        int pren=-1;
        while(M--){
            cin>>nd;
            if(pren>=0){
                subwaynet[pren].insert(nd);
                subwaynet[nd].insert(pren);
                line_of_node[nd][pren]=i;
                line_of_node[pren][nd]=i;
            }
            pren=nd;
        }
    }
}

void query(){
    int s, t;
    cin>>K;
    while(K--){
        cin>>s>>t;
        get_route(s,t);
    }
}

void get_route(int s, int t){
    //fill(visited,visited+maxn,false);
    temp_stops=0;
    temp_transfer_stops.clear();
    temp_line_code.clear();
    stops=0;
    transfer_stops.clear();
    line_code.clear();
    dfs(s,t,0);
    int stop_num=stops;
    
    int k=0;
    
    if(line_code.size()) {
        cout<<stop_num<<endl;
        cout<<"Take Line#"<<line_code[0]<<" from ";
    }
    else cout<<'0'<<endl<<"Take Line#"<<0<<" from ";
    fourdigits(s);
    cout<<" to ";
    
    for(int a:transfer_stops){
        k++;
        fourdigits(a);
        cout<<".\nTake Line#"<<line_code[k]<<" from ";
        fourdigits(a);
        cout<<" to ";
    }
    fourdigits(t);
    cout<<".\n";
}

void dfs(int s,int t,int ln){
    //if(stops.size() && s!=t && stops.size()<temp_stops.size()) return;
    
    visited[s]=true;
    if(s == t){
        if(ln) temp_line_code.push_back(ln);
        if(stops==0 || stops > temp_stops ||
          (stops == temp_stops && 
                 temp_transfer_stops.size() < transfer_stops.size())){
            stops=temp_stops;
            transfer_stops=temp_transfer_stops;
            line_code=temp_line_code;
        }
        if(ln) temp_line_code.pop_back();
    }else{
        for(int nxt:subwaynet[s]){
            if(!visited[nxt]){
                int newln=line_of_node[s][nxt];
                
                if(ln && newln!=ln) {
                    temp_transfer_stops.push_back(s);
                    temp_line_code.push_back(ln);
                }
                
                temp_stops++;
                dfs(nxt,t,newln);
                temp_stops--;
                
                if(ln && newln!=ln) {
                    temp_transfer_stops.pop_back();
                    temp_line_code.pop_back();
                }
            }
        }
    }
    
    visited[s]=false;
}

void fourdigits(int x){
    cout<<setw(4)<<setfill('0')<<x;
}
```



###A1135 Is It A Red-Black Tree

There is a kind of balanced binary search tree named **red-black tree** in the data structure. It has the following 5 properties:

- (1) Every node is either red or black.
- (2) The root is black.
- (3) Every leaf (NULL) is black.
- (4) If a node is red, then both its children are black.
- (5) For each node, all simple paths from the node to descendant leaves contain the same number of black nodes.

For example, the tree in Figure 1 is a red-black tree, while the ones in Figure 2 and 3 are not.

| ![rbf1.jpg](https://images.ptausercontent.com/eff80bd4-c833-4818-9786-81680d1b304a.jpg) | ![rbf2.jpg](https://images.ptausercontent.com/b11184df-eaab-451c-b7d4-7fc1dc82b028.jpg) | ![rbf3.jpg](https://images.ptausercontent.com/625c532b-22fc-47b9-80ea-0537cf00d922.jpg) |
| ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| Figure 1                                                     | Figure 2                                                     | Figure 3                                                     |

For each given binary search tree, you are supposed to tell if it is a legal red-black tree.

**Input Specification:**

Each input file contains several test cases. The first line gives a positive integer K (≤30) which is the total number of cases. For each case, the first line gives a positive integer N (≤30), the total number of nodes in the binary tree. The second line gives the preorder traversal sequence of the tree. While all the keys in a tree are positive integers, we use negative signs to represent red nodes. All the numbers in a line are separated by a space. The sample input cases correspond to the trees shown in Figure 1, 2 and 3.

**Output Specification:**

For each test case, print in a line "Yes" if the given tree is a red-black tree, or "No" if not.

**Sample Input:**

```in
3
9
7 -2 1 5 -4 -11 8 14 -15
9
11 -2 1 -7 5 -4 8 14 -15
8
10 -7 5 -6 8 15 -11 17
```

**Sample Output:**

```out
Yes
No
No
```

**Solution:**

```C++
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
```



###A1139 First Contact

Unlike in nowadays, the way that boys and girls expressing their feelings of love was quite subtle in the early years. When a boy A had a crush on a girl B, he would usually not contact her directly in the first place. Instead, he might ask another boy C, one of his close friends, to ask another girl D, who was a friend of both B and C, to send a message to B -- quite a long shot, isn't it? Girls would do analogously.

Here given a network of friendship relations, you are supposed to help a boy or a girl to list all their friends who can possibly help them making the first contact.

**Input Specification:**

Each input file contains one test case. For each case, the first line gives two positive integers N (1 < N ≤ 300) and M, being the total number of people and the number of friendship relations, respectively. Then M lines follow, each gives a pair of friends. Here a person is represented by a 4-digit ID. To tell their genders, we use a negative sign to represent girls.

After the relations, a positive integer K (≤ 100) is given, which is the number of queries. Then K lines of queries follow, each gives a pair of lovers, separated by a space. It is assumed that the first one is having a crush on the second one.

**Output Specification:**

For each query, first print in a line the number of different pairs of friends they can find to help them, then in each line print the IDs of a pair of friends.

If the lovers A and B are of opposite genders, you must first print the friend of A who is of the same gender of A, then the friend of B, who is of the same gender of B. If they are of the same gender, then both friends must be in the same gender as theirs. It is guaranteed that each person has only one gender.

The friends must be printed in non-decreasing order of the first IDs, and for the same first ones, in increasing order of the seconds ones.

**Sample Input:**

```in
10 18
-2001 1001
-2002 -2001
1004 1001
-2004 -2001
-2003 1005
1005 -2001
1001 -2003
1002 1001
1002 -2004
-2004 1001
1003 -2002
-2003 1003
1004 -2002
-2001 -2003
1001 1003
1003 -2001
1002 -2001
-2002 -2003
5
1001 -2001
-2003 1001
1005 -2001
-2002 -2004
1111 -2003
```

**Sample Output:**

```out
4
1002 2004
1003 2002
1003 2003
1004 2002
4
2001 1002
2001 1003
2002 1003
2002 1004
0
1
2003 2001
0
```

**Solution:**

```C++
#include<bits/stdc++.h>

using namespace std;

int N,M,K;
const int maxn=1e5;

struct MD{
    int f1=-1,f2=-1;
};

vector<MD> media;

bool isMale[maxn];

unordered_set<int> relations[maxn];

void init();

int setGender(string x);

void queries();

void lookup(int a,int b);

bool cmp(MD a,MD b);

void print(int x);

int main(){
    init();
    
    //if(N==300) return -1;
    
    queries();
    
    return 0;
}

void init(){
    cin>>N>>M;
    int tempM=M,a,b;
    string aa,bb;
    while(tempM--){
        cin>>aa>>bb;
        a=setGender(aa);
        b=setGender(bb);
        //cout<<a<<' '<<b<<endl;
        relations[a].insert(b);
        relations[b].insert(a);
    }
    
    cin>>K;
}

int setGender(string x){
    int k,res=0;
    if(x[0]=='-') k=1;
    else k=0;
    
    for(int i=k;i<x.size();i++){
        res*=10;
        res+=x[i]-'0';
    }
    
    if(x[0]=='-') {
        isMale[res]=false;
    }
    else {
        isMale[res]=true;
    }
    
    return res;
}

void queries(){
    
    int a,b;
    while(K--){
        cin>>a>>b;
        a=a>0?a:-a;
        b=b>0?b:-b;
        lookup(a,b);
    }
}

void lookup(int a,int b){
    media.clear();
    
    for(int f1:relations[a]){
        if(isMale[a]!=isMale[f1] || f1==b) continue;
        for(int f2:relations[b]){
            if(isMale[b]!=isMale[f2] || f2==a) continue;
            if(relations[f1].find(f2)!=relations[f1].end()){
                media.push_back({f1,f2});
            }
        }
    }
    
    cout<<media.size()<<endl;
    
    sort(media.begin(),media.end(),cmp);
    
    for(MD x:media){
        print(x.f1);
        cout<<' ';
        print(x.f2);
        cout<<endl;
    }
}

bool cmp(MD a,MD b){
    if(a.f1!=b.f1) return a.f1<b.f1;
    else return a.f2<b.f2;
}

void print(int x){
    cout<<setw(4)<<setfill('0')<<x;
}
```



### A1143 Lowest Common Ancestor

The lowest common ancestor (LCA) of two nodes U and V in a tree is the deepest node that has both U and V as descendants.

A binary search tree (BST) is recursively defined as a binary tree which has the following properties:

- The left subtree of a node contains only nodes with keys less than the node's key.
- The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
- Both the left and right subtrees must also be binary search trees.

Given any two nodes in a BST, you are supposed to find their LCA.

**Input Specification:**

Each input file contains one test case. For each case, the first line gives two positive integers: M (≤ 1,000), the number of pairs of nodes to be tested; and N (≤ 10,000), the number of keys in the BST, respectively. In the second line, N distinct integers are given as the preorder traversal sequence of the BST. Then M lines follow, each contains a pair of integer keys U and V. All the keys are in the range of **int**.

**Output Specification:**

For each given pair of U and V, print in a line `LCA of U and V is A.` if the LCA is found and `A` is the key. But if `A` is one of U and V, print `X is an ancestor of Y.` where `X` is `A` and `Y` is the other node. If U or V is not found in the BST, print in a line `ERROR: U is not found.` or `ERROR: V is not found.` or `ERROR: U and V are not found.`.

**Sample Input:**

```in
6 8
6 3 1 2 5 4 8 7
2 5
8 7
1 9
12 -3
0 8
99 99
```

**Sample Output:**

```out
LCA of 2 and 5 is 3.
8 is an ancestor of 7.
ERROR: 9 is not found.
ERROR: 12 and -3 are not found.
ERROR: 0 is not found.
ERROR: 99 and 99 are not found.
```

**Solution:**

```C++
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
```



###A1147 Heaps

In computer science, a **heap** is a specialized tree-based data structure that satisfies the heap property: if P is a parent node of C, then the key (the value) of P is either greater than or equal to (in a max heap) or less than or equal to (in a min heap) the key of C. A common implementation of a heap is the binary heap, in which the tree is a complete binary tree. (Quoted from Wikipedia at https://en.wikipedia.org/wiki/Heap_(data_structure))

Your job is to tell if a given complete binary tree is a heap.

**Input Specification:**

Each input file contains one test case. For each case, the first line gives two positive integers: M (≤ 100), the number of trees to be tested; and N (1 < N ≤ 1,000), the number of keys in each tree, respectively. Then M lines follow, each contains N distinct integer keys (all in the range of **int**), which gives the level order traversal sequence of a complete binary tree.

**Output Specification:**

For each given tree, print in a line `Max Heap` if it is a max heap, or `Min Heap` for a min heap, or `Not Heap` if it is not a heap at all. Then in the next line print the tree's postorder traversal sequence. All the numbers are separated by a space, and there must no extra space at the beginning or the end of the line.

**Sample Input:**

```in
3 8
98 72 86 60 65 12 23 50
8 38 25 58 52 82 70 60
10 28 15 12 34 9 8 56
```

**Sample Output:**

```out
Max Heap
50 60 65 72 12 23 86 98
Min Heap
60 58 52 38 82 70 25 8
Not Heap
56 12 34 28 9 8 15 10
```

**Solution:**

```C++
#include<bits/stdc++.h>

using namespace std;

const int maxn=1024;
int M,N,numbers[maxn];
bool maxheap=true,minheap=true;

struct node{
    int val;
    node*left=nullptr;
    node*right=nullptr;
    node(int x): val(x){}
};

node*root=nullptr;

void treeConstruct(node*p,int rk){
    p->val=numbers[rk];
    if(2*rk+1<N){
        if(numbers[rk]>numbers[2*rk+1]) minheap=false;
        if(numbers[rk]<numbers[2*rk+1]) maxheap=false;
        p->left=new node(numbers[2*rk+1]);
        treeConstruct(p->left,2*rk+1);
    }
    if(2*rk+2<N){
        if(numbers[rk]>numbers[2*rk+2]) minheap=false;
        if(numbers[rk]<numbers[2*rk+2]) maxheap=false;
        p->right=new node(numbers[2*rk+2]);
        treeConstruct(p->right,2*rk+2);
    }
}

void preorder(node*p){
    if(p==nullptr) return;
    
    preorder(p->left);
    preorder(p->right);
    
    cout<<p->val;
    if(p==root) cout<<endl;
    else cout<<' ';
}

int main(){
    cin>>M>>N;
    
    while(M--){
        for(int i=0;i<N;i++) scanf("%d",&numbers[i]);
        maxheap=true;
        minheap=true;
        root=new node(numbers[0]);
        treeConstruct(root,0);
        if(maxheap) cout<<"Max Heap"<<endl;
        else if(minheap) cout<<"Min Heap"<<endl;
        else cout<<"Not Heap"<<endl;
        preorder(root);
    }
    
    return 0;
}
```



### A1151 LCA in a Binary Tree

The lowest common ancestor (LCA) of two nodes U and V in a tree is the deepest node that has both U and V as descendants.

Given any two nodes in a binary tree, you are supposed to find their LCA.

**Input Specification:**

Each input file contains one test case. For each case, the first line gives two positive integers: M (≤ 1,000), the number of pairs of nodes to be tested; and N (≤ 10,000), the number of keys in the binary tree, respectively. In each of the following two lines, N distinct integers are given as the inorder and preorder traversal sequences of the binary tree, respectively. It is guaranteed that the binary tree can be uniquely determined by the input sequences. Then M lines follow, each contains a pair of integer keys U and V. All the keys are in the range of **int**.

**Output Specification:**

For each given pair of U and V, print in a line `LCA of U and V is A.` if the LCA is found and `A` is the key. But if `A` is one of U and V, print `X is an ancestor of Y.` where `X` is `A` and `Y` is the other node. If U or V is not found in the binary tree, print in a line `ERROR: U is not found.` or `ERROR: V is not found.` or `ERROR: U and V are not found.`.

**Sample Input:**

```in
6 8
7 2 3 4 6 5 1 8
5 3 7 2 6 4 8 1
2 6
8 1
7 9
12 -3
0 8
99 99
```

**Sample Output:**

```out
LCA of 2 and 6 is 3.
8 is an ancestor of 1.
ERROR: 9 is not found.
ERROR: 12 and -3 are not found.
ERROR: 0 is not found.
ERROR: 99 and 99 are not found.
```

**Solution:**

```C++
#include<bits/stdc++.h>

using namespace std;

const int maxn=10002;

int M,N;
unordered_map<int,int> prerank,inrank;
int preorder[maxn]={0};

struct node{
    int val;
    int lvl;
    int father;
    //int left;
    //int right;
}nd[maxn];//inorder

void queryAncestor(int u,int v);

void treeConstruct(int l,int r,int ftr,int lv,int rt);

int main(){
    cin>>M>>N;
    
    //if(M==1000) return -1;
    
    for(int i=1;i<=N;i++) {
        //cin>>nd[i].val;
        scanf("%d",&nd[i].val);
        inrank[nd[i].val]=i;
    }
    for(int i=0;i<N;i++){
        int x;
        scanf("%d",&x);//cin>>x;
        preorder[i]=x;
        prerank[x]=i;
    }
    
    treeConstruct(1,N+1,0,0,0);
    
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

void treeConstruct(int l,int r,int ftr,int lv,int rt){
    int rnk=inrank[preorder[rt]];
    
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
    
    if(l<rnk) treeConstruct(l,rnk,rnk,lv+1,rt+1);
    if(rnk+1<r) treeConstruct(rnk+1,r,rnk,lv+1,rt+rnk-l+1);
    
    //return rnk;
}

void queryAncestor(int u,int v){
    //cout<<u<<' '<<v<<endl;
    int uid=inrank[u];
    int vid=inrank[v];
    
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
```



###A1155 Heap Paths

In computer science, a **heap** is a specialized tree-based data structure that satisfies the heap property: if P is a parent node of C, then the key (the value) of P is either greater than or equal to (in a max heap) or less than or equal to (in a min heap) the key of C. A common implementation of a heap is the binary heap, in which the tree is a complete binary tree. (Quoted from Wikipedia at https://en.wikipedia.org/wiki/Heap_(data_structure))

One thing for sure is that all the keys along any path from the root to a leaf in a max/min heap must be in non-increasing/non-decreasing order.

Your job is to check every path in a given complete binary tree, in order to tell if it is a heap or not.

**Input Specification:**

Each input file contains one test case. For each case, the first line gives a positive integer *N* (1<*N*≤1,000), the number of keys in the tree. Then the next line contains *N* distinct integer keys (all in the range of **int**), which gives the level order traversal sequence of a complete binary tree.

**Output Specification:**

For each given tree, first print all the paths from the root to the leaves. Each path occupies a line, with all the numbers separated by a space, and no extra space at the beginning or the end of the line. The paths must be printed in the following order: for each node in the tree, all the paths in its right subtree must be printed before those in its left subtree.

Finally print in a line `Max Heap` if it is a max heap, or `Min Heap` for a min heap, or `Not Heap` if it is not a heap at all.

**Sample Input 1:**

```in
8
98 72 86 60 65 12 23 50
```

**Sample Output 1:**

```out
98 86 23
98 86 12
98 72 65
98 72 60 50
Max Heap
```

**Sample Input 2:**

```in
8
8 38 25 58 52 82 70 60
```

**Sample Output 2:**

```out
8 25 70
8 25 82
8 38 52
8 38 58 60
Min Heap
```

**Sample Input 3:**

```in
8
10 28 15 12 34 9 8 56
```

**Sample Output 3:**

```out
10 15 8
10 15 9
10 28 34
10 28 12 56
Not Heap
```

**Solution:**

```C++
#include<bits/stdc++.h>

using namespace std;

const int maxn=1024;
int N;
vector<int> numbers;
vector<int> seq;

bool max_heap=true,min_heap=true;

void readData();

void treeConstruct(int x);

void showResult();

int main(){
    
    readData();
    
    treeConstruct(0);
    
    showResult();
    
    return 0;
}

void readData(){
    cin>>N;
    while(N--) {
        int x; cin>>x;
        numbers.push_back(x);
    }
    N=numbers.size();
}

void treeConstruct(int x){
    seq.push_back(numbers[x]);
    
    if(2*x+2<N) {
        treeConstruct(2*x+2);
        if(numbers[2*x+2]<numbers[x]) min_heap=false;
        if(numbers[2*x+2]>numbers[x]) max_heap=false;
    }
    if(2*x+1<N) {
        treeConstruct(2*x+1);
        if(numbers[2*x+1]<numbers[x]) min_heap=false;
        if(numbers[2*x+1]>numbers[x]) max_heap=false;
    }
    else{
        for(int a:seq){
            cout<<a;
            if(a!=*(seq.end()-1)) cout<<' ';
            else cout<<endl;
        }
    }
    
    seq.pop_back();
}

void showResult(){
    if(max_heap) cout<<"Max Heap"<<endl;
    else if(min_heap) cout<<"Min Heap"<<endl;
    else cout<<"Not Heap"<<endl;
}
```



###A1159 Structure of a Binary Tree

Suppose that all the keys in a binary tree are distinct positive integers. Given the postorder and inorder traversal sequences, a binary tree can be uniquely determined.

Now given a sequence of statements about the structure of the resulting tree, you are supposed to tell if they are correct or not. A statment is one of the following:

- A is the root
- A and B are siblings
- A is the parent of B
- A is the left child of B
- A is the right child of B
- A and B are on the same level
- It is a full tree

Note:

- Two nodes are **on the same level**, means that they have the same depth.
- A **full binary tree** is a tree in which every node other than the leaves has two children.

**Input Specification:**

Each input file contains one test case. For each case, the first line gives a positive integer *N* (≤30), the total number of nodes in the binary tree. The second line gives the postorder sequence and the third line gives the inorder sequence. All the numbers in a line are no more than 103 and are separated by a space.

Then another positive integer *M* (≤30) is given, followed by *M* lines of statements. It is guaranteed that both `A` and `B` in the statements are in the tree.

**Output Specification:**

For each statement, print in a line `Yes` if it is correct, or `No` if not.

**Sample Input:**

```in
9
16 7 11 32 28 2 23 8 15
16 23 7 32 11 2 28 15 8
7
15 is the root
8 and 2 are siblings
32 is the parent of 11
23 is the left child of 16
28 is the right child of 2
7 and 11 are on the same level
It is a full tree
```

**Sample Output:**

```out
Yes
No
Yes
No
Yes
Yes
Yes
```

**Solution:**

```C++
#include<bits/stdc++.h>

using namespace std;

const int maxn=1005;
int N,M,root;
int inorder[maxn],postcode[maxn];

struct node{
    int lvl=0;
    int parent=-1;
    int left=-1;
    int right=-1;
}nd[maxn];

void readData();

void queryInfor();

bool translate(char *s);

int dfs(int l,int r,int lv,int prt);

int main(){
    
    readData();
    
    root=dfs(0,N,0,-1);
    
    queryInfor();
    
    return 0;
}

void readData(){
    cin>>N;
    for(int i=0;i<N;i++) {
        int x;
        cin>>x;
        postcode[x]=i;
    }
    for(int i=0;i<N;i++) {
        cin>>inorder[i];
    }
}

void queryInfor(){
    cin>>M;
    char str[35];
    cin.getline(str,35);
    while(M--){
        cin.getline(str,35);
        bool ans=translate(str);
        if(ans) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
        //cout<<"0 "<<str<<endl;
    }
}

bool translate(char *s){
    if(s[0]=='I'){//It is a full tree
        //cout<<"full"<<endl;
        
        for(int i=0;i<N;i++){
            int x=inorder[i];
            //cout<<x<<' '<<nd[x].left<<' '<<nd[x].right<<endl;
            if(nd[x].left!=-1 && nd[x].right==-1) return false;
            else if(nd[x].left==-1 && nd[x].right!=-1) return false;
        }
        
        return true;
        
    }else{
        int aa=0,k=0;
        for(int i=0;s[i]!=' ';i++){
            aa=10*aa+s[i]-'0';
            k=i;
        }
        
        //cout<<" A="<<aa<<' ';
        
        if(s[k+5]==' '){
            int bb=0;
            for(int i=k+6;s[i]!=' ';i++){
                bb=10*bb+s[i]-'0';
                k=i;
            }
            
            //cout<<" B="<<bb<<' ';
            
            if(s[k+6]=='s'){//A and B are siblings
                //cout<<"siblings"<<endl;
                
                if(nd[aa].parent==nd[bb].parent) return true;
                else return false;
                
            }else{//A and B are on the same level
                //cout<<"same"<<endl;
                
                if(nd[aa].lvl==nd[bb].lvl) return true;
                else return false;
            }
            
        }else{
            if(s[k+9]=='p'){//A is the parent of B
                //cout<<"parent"<<endl;
                
                int bb=0;
                for(int i=k+19;s[i]!='\0';i++){
                    bb=10*bb+s[i]-'0';
                }
                //cout<<" B="<<bb<<' ';
                
                if(nd[bb].parent==aa) return true;
                else return false;
                
            }else if(s[k+9]=='l'){//A is the left child of B
                //cout<<"left"<<endl;
                
                int bb=0;
                for(int i=k+23;s[i]!='\0';i++){
                    bb=10*bb+s[i]-'0';
                }
                //cout<<" B="<<bb<<' ';
                
                if(nd[bb].left==aa) return true;
                else return false;
                
            }else{
                if(s[k+10]=='i'){//A is the right child of B
                    //cout<<"right"<<endl;
                    
                    
                    int bb=0;
                    for(int i=k+24;s[i]!='\0';i++){
                        bb=10*bb+s[i]-'0';
                    }
                    //cout<<" B="<<bb<<' ';
                    
                    if(aa==nd[bb].right) return true;
                    else return false;
                    
                }else{//A is the root
                    //cout<<"root"<<endl;
                    
                    if(aa==root) return true;
                    else return false;
                }
            }
        }
        
    }
    
    return true;
}

int dfs(int l,int r,int lv, int prt){
    int rootid=-1,maxcode=-1;
    
    for(int i=l;i<r;i++){
        int x=inorder[i];
        if(postcode[x]>maxcode){
            maxcode=postcode[x];
            rootid=i;
        }
    }
    
    int val=inorder[rootid];
    
    //cout<<val<<endl;
    
    if(rootid!=-1){
        nd[val].parent=prt;
        nd[val].lvl=lv;
        
        //maxlvl=max(maxlvl,lv);
        
        if(l<rootid)nd[val].left=dfs(l,rootid,lv+1,val);
        if(rootid+1<r)nd[val].right=dfs(rootid+1,r,lv+1,val);
    }
    
    return val;
}
```



###A1163 Dijkstra Sequence

Dijkstra's algorithm is one of the very famous greedy algorithms. It is used for solving the single source shortest path problem which gives the shortest paths from one particular source vertex to all the other vertices of the given graph. It was conceived by computer scientist Edsger W. Dijkstra in 1956 and published three years later.

In this algorithm, a set contains vertices included in shortest path tree is maintained. During each step, we find one vertex which is not yet included and has a minimum distance from the source, and collect it into the set. Hence step by step an ordered sequence of vertices, let's call it **Dijkstra sequence**, is generated by Dijkstra's algorithm.

On the other hand, for a given graph, there could be more than one Dijkstra sequence. For example, both { 5, 1, 3, 4, 2 } and { 5, 3, 1, 2, 4 } are Dijkstra sequences for the graph, where 5 is the source. Your job is to check whether a given sequence is Dijkstra sequence or not.

**Input Specification:**

Each input file contains one test case. For each case, the first line contains two positive integers $N_v$ (≤$10^3$) and $N_e$ (≤105), which are the total numbers of vertices and edges, respectively. Hence the vertices are numbered from 1 to $N_v$.

Then $N_e$ lines follow, each describes an edge by giving the indices of the vertices at the two ends, followed by a positive integer weight (≤100) of the edge. It is guaranteed that the given graph is connected.

Finally the number of queries, *K*, is given as a positive integer no larger than 100, followed by *K* lines of sequences, each contains a permutationof the $N_v$ vertices. It is assumed that the first vertex is the source for each sequence.

All the inputs in a line are separated by a space.

**Output Specification:**

For each of the *K* sequences, print in a line `Yes` if it is a Dijkstra sequence, or `No` if not.

**Sample Input:**

```in
5 7
1 2 2
1 5 1
2 3 1
2 4 1
2 5 2
3 5 1
3 4 1
4
5 1 3 4 2
5 3 1 2 4
2 3 4 5 1
3 2 1 5 4
```

**Sample Output:**

```out
Yes
Yes
Yes
No
```

**Solution:**

```C++
#include<bits/stdc++.h>

using namespace std;

const int maxn=1001;
const int inf=1e9;

int Nv,Ne,K;
int G[maxn][maxn]={0};

void readData();

void querySequence();

bool dijkstra(int*seq);

int main(){
    
    readData();
    
    querySequence();
    
    return 0;
}

void readData(){
    cin>>Nv>>Ne;
    fill(G[0],G[0]+maxn*maxn,inf);
    for(int i=0;i<Ne;i++){
        int s,t,w;
        scanf("%d %d %d",&s,&t,&w);
        G[s][t]=w;
        G[t][s]=w;
    }
}

void querySequence(){
    cin>>K;
    while(K--){
        int temp_seq[maxn];
        for(int i=0;i<Nv;i++) scanf("%d",&temp_seq[i]);
        bool ans=dijkstra(temp_seq);
        if(ans) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }
}

bool dijkstra(int *seq){
    bool is_visited[maxn]={false};
    int dis[maxn];
    
    fill(dis,dis+maxn,inf);
    //fill(pre,pre+Nv,-1);
    
    int k=0;
    
    dis[seq[0]]=0;
    for(int i=0;i<Nv;i++){
        
        int min_dis=inf,source=-1;
        for(int j=1;j<=Nv;j++){
            if(!is_visited[j] && dis[j]<min_dis) {
                min_dis=dis[j];
            }
        }
        
        //cout<<min_dis<<' '<<dis[seq[k]]<<' '<<seq[k]<<endl;
        
        if(min_dis==dis[seq[k]]) {
            source=seq[k];
            k++;
        }else return false;
        
        is_visited[source]=true;
        
        for(int j=1;j<=Nv;j++){
            if(!is_visited[j] && G[source][j]!=inf && dis[source]+G[source][j]<dis[j]){
                dis[j]=dis[source]+G[source][j];
            }
        }
    }
    
    //cout<<k<<endl;
    
    if(k==Nv) return true;
    else return false;
}
```



###A1167 Cartesian Tree

A **Cartesian tree** is a binary tree constructed from a sequence of distinct numbers. The tree is heap-ordered, and an inorder traversal returns the original sequence. For example, given the sequence { 8, 15, 3, 4, 1, 5, 12, 10, 18, 6 }, the min-heap Cartesian tree is shown by the figure.

![CTree.jpg](https://images.ptausercontent.com/6a99f68a-6578-46e0-9232-fbf0adf3691f.jpg)

Your job is to output the level-order traversal sequence of the min-heap Cartesian tree.

**Input Specification:**

Each input file contains one test case. Each case starts from giving a positive integer *N* (≤30), and then *N* distinct numbers in the next line, separated by a space. All the numbers are in the range of **int**.

**Output Specification:**

For each test case, print in a line the level-order traversal sequence of the min-heap Cartesian tree. All the numbers in a line must be separated by exactly one space, and there must be no extra space at the beginning or the end of the line.

**Sample Input:**

```in
10
8 15 3 4 1 5 12 10 18 6
```

**Sample Output:**

```out
1 3 5 8 4 6 15 10 12 18
```

**Solution:**

```C++
#include<bits/stdc++.h>

using namespace std;

const int maxn=35;
int N;

struct node{
    int rk=-1;
    int val=-1;
    int lvl=0;
    int left=-1;
    int right=-1;
}nd[maxn];

int dfs(int l,int r,int lv);

bool cmp(node a,node b);

int main(){
    cin>>N;
    
    for(int i=0;i<N;i++) {
        cin>>nd[i].val;
        nd[i].rk=i;
    }
    
    //if(N==30) return -1;
    
    
    dfs(0,N,0);
    
    if(N>1) sort(nd,nd+N,cmp);
    
    for(int i=0;i<N;i++) {
        cout<<nd[i].val;
        if(i==N-1) cout<<endl;
        else cout<<' ';
    }
    
    return 0;
}

bool cmp(node a,node b){
    if(a.lvl!=b.lvl) return a.lvl<b.lvl;
    else return a.rk<b.rk;
}

int dfs(int l,int r,int lv){
        
    int min=1e9,rt=r;
    
    for(int i=l;i<r;i++){
        if(min>nd[i].val){
            min=nd[i].val;
            rt=i;
        }
    }
    
    if(rt!=r) {
        nd[rt].lvl=lv+1;
        if(l<rt) {
            nd[rt].left=dfs(l,rt,lv+1);
        }
        if(rt+1<r) {
            nd[rt].right=dfs(rt+1,r,lv+1);
        }
        
        return rt;
    }else return -1;
    
    //cout<<lv<<' '<<min<<endl;
    
    
}
```



## **35-scores**

**!!!from 1001 to 1011**

### T1001	Battle Over Cities - Hard Version

It is vitally important to have all the cities connected by highways in a war. If a city is conquered by the enemy, all the highways from/toward that city will be closed. To keep the rest of the cities connected, we must repair some highways with the minimum cost. On the other hand, if losing a city will cost us too much to rebuild the connection, we must pay more attention to that city.

Given the map of cities which have all the destroyed and remaining highways marked, you are supposed to point out the city to which we must pay the most attention.

**Input Specification:**

Each input file contains one test case. Each case starts with a line containing 2 numbers `N` (≤500), and `M`, which are the total number of cities, and the number of highways, respectively. Then `M` lines follow, each describes a highway by 4 integers: `City1 City2 Cost Status` where `City1` and `City2` are the numbers of the cities the highway connects (the cities are numbered from 1 to `N`), `Cost` is the effort taken to repair that highway if necessary, and `Status` is either 0, meaning that highway is destroyed, or 1, meaning that highway is in use.

Note: It is guaranteed that the whole country was connected before the war.

**Output Specification:**

For each test case, just print in a line the city we must protest the most, that is, it will take us the maximum effort to rebuild the connection if that city is conquered by the enemy.

In case there is more than one city to be printed, output them in increasing order of the city numbers, separated by one space, but no extra space at the end of the line. In case there is no need to repair any highway at all, simply output 0.

**Sample Input 1:**

```in
4 5
1 2 1 1
1 3 1 1
2 3 1 0
2 4 1 1
3 4 1 0
```

**Sample Output 1:**

```out
1 2
```

**Sample Input 2:**

```in
4 5
1 2 1 1
1 3 1 1
2 3 1 0
2 4 1 1
3 4 2 1
```

**Sample Output 2:**

```out
0
```

### T1002	Business

### T1003	Universal Travel Sites

After finishing her tour around the Earth, CYLL is now planning a universal travel sites development project. After a careful investigation, she has a list of capacities of all the satellite transportation stations in hand. To estimate a budget, she must know the minimum capacity that a planet station must have to guarantee that every space vessel can dock and download its passengers on arrival.

**Input Specification:**

Each input file contains one test case. For each case, the first line contains the names of the source and the destination planets, and a positive integer `N` (≤500). Then `N` lines follow, each in the format: `source[i] destination[i] capacity[i]` where `source[i]` and `destination[i]` are the names of the satellites and the two involved planets, and `capacity[i]` > 0 is the maximum number of passengers that can be transported at one pass from `source[i]` to `destination[i]`. Each name is a string of 3 uppercase characters chosen from {A-Z}, e.g., ZJU.

Note that the satellite transportation stations have no accommodation facilities for the passengers. Therefore none of the passengers can stay. Such a station will not allow arrivals of space vessels that contain more than its own capacity. It is guaranteed that the list contains neither the routes to the source planet nor that from the destination planet.

**Output Specification:**

For each test case, just print in one line the minimum capacity that a planet station must have to guarantee that every space vessel can dock and download its passengers on arrival.

**Sample Input:**

```in
EAR MAR 11
EAR AAA 300
EAR BBB 400
AAA BBB 100
AAA CCC 400
AAA MAR 300
BBB DDD 400
AAA DDD 400
DDD AAA 100
CCC MAR 400
DDD CCC 200
DDD MAR 300
```

**Sample Output:**

```out
700
```

**Solution:**

```C++
//最大流问题
//      每次只找出一条从source到target的流;累加求和 O(VEE);
//2.每次找到一条通路，这条路的流的大小取决于这条路上最小的容量
//
//3.找到一条局部的解决方案，会不会是全局非最优
//      可能解决方法：每当找到一条路，要建立反向边，提供反悔撤销这样的功能。

#include<bits/stdc++.h>

using namespace std;

const int maxn=1001;

int source,target,edge_num,vertex_num,ans=0;
int capacity_matrix[maxn][maxn]={0};
unordered_map<string,int> M;
int pre_vertex[maxn];
int flow[maxn];

int main(){
    string s1,s2;
    cin>>s1>>s2>>edge_num;
    source=M[s1]=1;
    target=M[s2]=2;
    
    for(int i=0;i<edge_num;i++){
        int j,k,cap;
        cin>>s1>>s2>>cap;
        
        if(M.count(s1)){
            j=M[s1];
        }else j=M[s1]=M.size()+1;
        if(M.count(s2)){
            k=M[s2];
        }else k=M[s2]=M.size()+1;
        
        capacity_matrix[j][k]=cap;
    }
    vertex_num=M.size();
    
    while(true){
        memset(pre_vertex,0,sizeof(pre_vertex));
        queue<int> Q;
        Q.push(source);
        pre_vertex[source]=-1;
        flow[source]=maxn*maxn*maxn;
        
        
        while(Q.size()){
            auto cur=Q.front();
            Q.pop();
            for(int a=1;a<=vertex_num;a++){
                if(capacity_matrix[cur][a]>0 && pre_vertex[a]==0){
                    pre_vertex[a]=cur;
                    flow[a]=min(flow[cur],capacity_matrix[cur][a]);
                    Q.push(a);
                }
            }
            if(pre_vertex[target]) break;
            
        }
        if(pre_vertex[target]==0) break;
        else{
            ans+=flow[target];
            int cur=target;
            while(cur!=source){
                int before=pre_vertex[cur];
                capacity_matrix[before][cur]-=flow[target];
                capacity_matrix[cur][before]+=flow[target];
                cur=before;
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}
```



### T1004	To Buy or Not to Buy - Hard Version

Eva would like to make a string of beads with her favorite colors so she went to a small shop to buy some beads. There were many colorful strings of beads. However the owner of the shop would only sell the strings in whole pieces. Hence in some cases Eva might have to buy several strings to get all the beads she needs. With a hundred strings in the shop, Eva needs your help to tell her whether or not she can get all the beads she needs with the least number of extra beads she has to pay for.

For the sake of simplicity, let's use the characters in the ranges [0-9], [a-z], and [A-Z] to represent the colors. In sample 1, buying the 2nd and the last two strings is the best way since there are only 3 extra beads. In sample 2, buying all the three strings won't help since there are three `R` beads missing.

**Input Specification:**

Each input file contains one test case. Each case first gives in a line the string that Eva wants. Then a positive integer *N* (≤100) is given in the next line, followed by *N* lines of strings that belong to the shop. All the strings contain no more than 1000 beads.

**Output Specification:**

For each test case, print your answer in one line. If the answer is `Yes`, then also output the least number of extra beads Eva has to buy; or if the answer is `No`, then also output the number of beads missing from all the strings. There must be exactly 1 space between the answer and the number.

**Sample Input 1:**

```in
RYg5
8
gY5Ybf
8R5
12346789
gRg8h
5Y37
pRgYgbR52
8Y
8g
```

**Sample Output 1:**

```out
Yes 3
```

**Sample Input 2:**

```in
YrRR8RRrY
3
ppRGrrYB225
8ppGrrB25
Zd6KrY
```

**Sample Output 2:**

```out
No 3
```

**Solution:**

```C++
#include<bits/stdc++.h>

using namespace std;

int N,missing=0,min_extra=100000000;
int eva_need[128]={0};
int shop_num[128]={0};

vector<pair<char,int>> shop_bead[100];

bool can_collect_all_need(){
    for(int i=0;i<128;i++){
        if(eva_need[i]>shop_num[i]) missing+=eva_need[i]-shop_num[i];
    }
    if(missing>0) return false;
    else return true;
}

void dfs(int cur,vector<int>&cur_need,int extra,int rest_need){
    for(auto&p:shop_bead[cur]){
        if(cur_need[p.first]>0){
            if(p.second>cur_need[p.first]){
                extra+=p.second-cur_need[p.first];
                rest_need-=cur_need[p.first];
                cur_need[p.first]-=p.second;
            }else{
                rest_need-=p.second;
                cur_need[p.first]-=p.second;
            }
        }else{
            extra+=p.second;
            cur_need[p.first]-=p.second;
        }
    }
    
    if(extra<min_extra){
        if(!rest_need){
            min_extra=min(min_extra,extra);
        }else{
            for(int i=cur+1;i<N;i++){
                dfs(i,cur_need,extra,rest_need);
            }
        }
    }
    
    for(auto&p:shop_bead[cur]){
        if(cur_need[p.first]>0){
            cur_need[p.first]+=p.second;
            rest_need+=p.second;
        }else{
            if(cur_need[p.first]+p.second>0){
                cur_need[p.first]+=p.second;
                rest_need+=cur_need[p.first];
                extra-=p.second-cur_need[p.first];
                
            }else{
                cur_need[p.first]+=p.second;
                extra-=p.second;
            }
        }
    }
}

int main(){
    string bead;
    cin>>bead;
    for(char c:bead){
        eva_need[c]++;
    }
    cin>>N;
    for(int i=0;i<N;i++){
        cin>>bead;
        for(char c:bead) shop_num[c]++;
        sort(bead.begin(),bead.end());
        for(int j=0,k;j<bead.size();j=k){
            for(k=j+1;k<bead.size() && bead[k]==bead[j];k++);
            shop_bead[i].emplace_back(bead[j],k-j);
        }
    }
    
    if(can_collect_all_need()==false){
        cout<<"No "<<missing<<endl;
    }else{
        
        vector<int> cur_need(eva_need,eva_need+128);
        int sum=0;
        for(int need:cur_need)sum+=need;
        for(int i=0;i<N;i++){
            dfs(i,cur_need,0,sum);
        }
        cout<<"Yes "<<min_extra<<endl;
    }
    
    return 0;
}
```



### T1005	Programming Pattern

### T1006	Tree Traversals - Hard Version

Given the partial results of a binary tree's traversals in in-order, pre-order, and post-order. You are supposed to output the complete results and the level order traversal sequence of the corresponding tree.

**Input Specification:**

Each input file contains one test case. For each case, a positive integer *N* (≤100) is given in the first line. Then three lines follow, containing the incomplete in-order, pre-order and post-order traversal sequences, respectively. It is assumed that the tree nodes are numbered from 1 to *N* and no number is given out of the range. A `-` represents a missing number.

**Output Specification:**

For each case, print in four lines the complete in-order, pre-order and post-order traversal sequences, together with the level order traversal sequence of the corresponding tree. The numbers must be separated by a space, and there must be no extra space at the beginning or the end of each line. If it is impossible to reconstruct the unique tree from the given information, simply print `Impossible`.

**Sample Input 1:**

```in
9
3 - 2 1 7 9 - 4 6
9 - 5 3 2 1 - 6 4
3 1 - - 7 - 6 8 -
```

**Sample Output 1:**

```out
3 5 2 1 7 9 8 4 6
9 7 5 3 2 1 8 6 4
3 1 2 5 7 4 6 8 9
9 7 8 5 6 3 2 4 1
```

**Sample Input 2:**

```in
3
- - -
- 1 -
1 - -
```

**Sample Output 2:**

```out
Impossible
```

**Solution:**

```C++
// 1.大思路 利用遍历的区间作为参数构造树
//      不断递归，每次都是找到根，然后把大区间分成左右两个小区间，进行分治

// 2.排除条件：含两个及以上数字未出现，直接排除

// 3.优化剪枝：出现次数没对上，直接剪枝

#include<bits/stdc++.h>

using namespace std;

int N,missing=0,missing_number;
int inorder[100],preorder[100],postorder[100];
int inorder_complete[100],preorder_complete[100],postorder_complete[100];
int appeartime[101]={0};

bool check(int h1,int h2,int h3,int l){
    if(l==0) return true;
    for(int l1=0;l1<l;l1++){
        int l2=l-1-l1;
        
        unordered_set<int> S;
        int cnt=0;
        if(inorder[h1+l1]>0) S.insert(inorder[h1+l1]),cnt++;
        if(preorder[h2]>0) S.insert(preorder[h2]),cnt++;
        if(postorder[h3+l-1]>0) S.insert(postorder[h3+l-1]),cnt++;
        
        if(S.size()>1) continue;
        if(S.empty()){
            if(!missing) continue;
            inorder_complete[h1+l1]=missing_number;
            preorder_complete[h2]=missing_number;
            postorder_complete[h3+l-1]=missing_number;
            missing--;
        }else{
            int rootnumber=*S.begin();
            if(cnt!=appeartime[*S.begin()])continue;
            inorder_complete[h1+l1]=rootnumber;
            preorder_complete[h2]=rootnumber;
            postorder_complete[h3+l-1]=rootnumber;
        }
        bool b1=check(h1,h2+1,h3,l1);
        bool b2=check(h1+l1+1,h2+l1+1,h3+l1,l2);
        
        if(!cnt) missing=1;
        if(b1&&b2) return true;
    }
    return false;
}

struct node{
    int data;
    node*left,*right;
};

node*makenode(int h1,int h2,int l){
    if(!l) return nullptr;
    node*p=new node;
    p->data=preorder_complete[h2];
    int i;
    for(i=h1;;i++) if(inorder_complete[i]==p->data) break;
    int l1=i-h1;
    int l2=l-1-l1;
    p->left=makenode(h1,h2+1,l1);
    p->right=makenode(i+1,h2+l1+1,l2);
    return p;
}

void levelordertraverse(node*root){
    vector<int> v;
    queue<node*> Q;
    Q.push(root);
    while(Q.size()){
        auto p=Q.front();
        Q.pop();
        v.push_back(p->data);
        if(p->left)Q.push(p->left);
        if(p->right)Q.push(p->right);
    }
    
    for(int i=0;i<v.size();i++){
        cout<<v[i];
        if(i==v.size()-1) cout<<endl;
        else cout<<' ';
    }
}

int main(){
    cin>>N;
    string s;
    
    for(int i=0;i<N;i++){
        cin>>s;
        if(s!="-"){
            inorder[i]=inorder_complete[i]=stoi(s);
            appeartime[inorder[i]]++;
        }
    }
    
    for(int i=0;i<N;i++){
        cin>>s;
        if(s!="-"){
            preorder[i]=preorder_complete[i]=stoi(s);
            appeartime[preorder[i]]++;
        }
    }
    
    for(int i=0;i<N;i++){
        cin>>s;
        if(s!="-"){
            postorder[i]=postorder_complete[i]=stoi(s);
            appeartime[postorder[i]]++;
        }
    }
    
    for(int i=1;i<=N;i++) if(appeartime[i]==0) {
        missing++;
        missing_number=i;
    }
    if(missing>1){
        cout<<"Impossible"<<endl;
    }else{
        bool res=check(0,0,0,N);
        if(!res) cout<<"Impossible"<<endl;
        else{
            for(int i=0;i<N;i++){
                cout<<inorder_complete[i];
                if(i==N-1)cout<<endl;
                else cout<<' ';
            }
            
            for(int i=0;i<N;i++){
                cout<<preorder_complete[i];
                if(i==N-1)cout<<endl;
                else cout<<' ';
            }
            
            for(int i=0;i<N;i++){
                cout<<postorder_complete[i];
                if(i==N-1)cout<<endl;
                else cout<<' ';
            }
        }
        
        node*root=makenode(0,0,N);
        levelordertraverse(root);
    }
    
    return 0;
}
```



### T1007	Red-black Tree

There is a kind of binary tree named **red-black tree** in the data structure. It has the following 5 properties:

- (1) Every node is either red or black.
- (2) The root is black.
- (3) All the leaves are NULL nodes and are colored black.
- (4) Each red node must have 2 black descends (may be NULL).
- (5) All simple paths from any node x to a descendant leaf have the same number of black nodes.

We call a non-NULL node an **internal node**. From property (5) we can define the **black-height** of a red-black tree as the number of nodes on the simple path from the root (excluding the root itself) to any NULL leaf (including the NULL leaf). And we can derive that a red-black tree with black height H has at least 2*H*−1 internal nodes.

Here comes the question: given a positive *N*, how many distinct red-black trees are there that consist of exactly *N* internal nodes?

**Input Specification:**

Each input file contains one test case which gives a positive integer *N* (≤500).

**Output Specification:**

For each case, print in a line the number of distinct red-black tees with *N* internal nodes. Since the answer may be very large, output the remainder of it divided by 1000000007 please.

**Sample Input:**

```in
5
```

**Sample Output:**

```out
8
```

**Solution:**

```C++
// internal node:   non-nullptr
// external node:   nullptr(leaves)
// 自定义黑高度：从某个节点开始到自身nullptr叶节点简单路径上的黑节点数量

/*
(1) Every node is either red or black.
(2) The root is black.
(3) All the leaves are NULL nodes and are colored black.
(4) Each red node must have 2 black descends (may be NULL).
(5) All simple paths from any node x to a descendant leaf have the same number of black nodes.
*/

//  N为节点数   h为自定义黑高度    f(N,h)为红黑树构造种类数
//  fb(N,h)=f(0,h-1)*f(N-1,h-1)+f(1,h-1)*f(N-2,h-1)+...+f(N-1,h-1)*f(0,h-1)
//  fr(N,h)=fb(0,h)*fb(N-1,h)+fb(1,h)*fb(N-2,h)+...+fb(N-1,h)*fb(0,h)
//  f(N,h)=fb(N,h)+fr(N,h)

#include<bits/stdc++.h>
using namespace std;

const int maxn=501;
const long long cell=1000000007;

long long fb[maxn][maxn]={0},fr[maxn][maxn]={0},f[maxn][maxn]={0};

int main(){
    int N;
    cin>>N;
    
    int maxbh[maxn];
    maxbh[0]=1;
    
    fb[0][1]=1;
    fr[0][1]=0;
    f[0][1]=1;
    
    for(int i=1;i<=N;i++){
        maxbh[i]=maxbh[(i-1)/2]+1;
        
        for(int h=1;h<=maxbh[i];h++){
            for(int left=0;left<=i-1;left++){
                fb[i][h]=(fb[i][h]+f[left][h-1]*f[i-1-left][h-1])%cell;
            }
            for(int left=0;left<=i-1;left++){
                fr[i][h]=(fr[i][h]+fb[left][h]*fb[i-1-left][h])%cell;
            }
            f[i][h]=(fb[i][h]+fr[i][h])%cell;
        }
    }
    
    long long ans=0;
    
    for(int h=1;h<=maxbh[N];h++) ans=(ans+fb[N][h])%cell;
    
    cout<<ans<<endl;
    
    return 0;
}


```



### T1008	Airline Routes

Given a map of airline routes, you are supposed to check if a round trip can be planned between any pair of cities.

**Input Specification:**

Each input file contains one test case. For each case, the first line gives two positive integers *N* (2≤*N*≤$10^4$) and *M* (≤6*N*), which are the total number of cities (hence the cities are numbered from 1 to *N*) and the number of airline routes, respectively. Then *M* lines follow, each gives the information of a route in the format of the source city index first, and then the destination city index, separated by a space. It is guaranteed that the source is never the same as the destination.

After the map information, another positive integer *K* is given, which is the number of queries. Then *K* lines of queries follow, each contains a pair of distinct cities' indices.

**Output Specification:**

For each query, output in a line `Yes` if a round trip is possible, or `No` if not.

**Sample Input:**

```in
12 19
3 4
1 3
12 11
5 9
6 2
3 2
10 7
9 1
7 12
2 4
9 5
2 6
12 4
11 10
4 8
8 12
11 8
12 7
1 5
20
11 4
12 7
3 6
2 3
5 3
3 9
4 3
8 3
8 10
10 11
7 8
7 1
9 5
1 9
2 6
3 1
3 12
7 3
6 9
6 8
```

**Sample Output:**

```out
Yes
Yes
No
No
No
No
No
No
Yes
Yes
Yes
No
Yes
Yes
Yes
No
No
No
No
No
```

**Solution:**

```C++
//有向图的———强连通分量
//  当两个点可以划归一个强连通分量时，可以认为可以plan一个round trip
// tarjan算法：dfs 给每个节点维护两个属性
//  dfn属性：到访某个结点时，打下的时间戳
//  low属性：某个结点以及子孙结点所能追溯到的最小的时间戳

//1.一个SCC到访的第一个顶点的dfn值和low值相等的
//      判定时间：只需要自己的子孙都访问完了，这个时候判定

//2.tarjan用于无向图的割点/桥边
//  割点判定：   若parent不为总起点   如果一条边上子节点汇报时，low[child]>=dfn[parent] 则parent为割点
//      若parent为总起点     如果从总起点出发，进行了两路、更多路的dfs，则parent为割点
//  桥边判定：   如果一条边上子结点汇报时，low[child]>dfn[parent],则此边为桥边

#include<bits/stdc++.h>

using namespace std;

const int maxn=10001;
int N,M,curtime=1,curcolor=1;
vector<int> v[maxn];
int DFN[maxn]={0},LOW[maxn],color[maxn]={0};
stack<int> S;

int tarjan(int cur){
    DFN[cur]=LOW[cur]=curtime++;
    S.push(cur);
    
    for(int a:v[cur]){
        if(DFN[a]>0){
            if(color[a]){
                
            }else LOW[cur]=min(DFN[a],LOW[cur]);
        }else{
            LOW[cur]=min(tarjan(a),LOW[cur]);
        }
    }
    
    if(LOW[cur]==DFN[cur]){
        while(S.top()!=cur){
            color[S.top()]=curcolor;
            S.pop();
        }
        color[cur]=curcolor++;
        S.pop();
    }
    
    return LOW[cur];
}

int main(){
    cin>>N>>M;
    
    while(M--){
        int i,j;
        //cin>>i>>j;
        scanf("%d %d",&i,&j);
        v[i].push_back(j);
    }
    
    int temp=tarjan(1);
    
    int K;
    cin>>K;
    while(K--){
        int i,j;
        //cin>>i>>j;
        scanf("%d %d",&i,&j);
        if(color[i]==color[j]) printf("Yes\n");//cout<<"Yes"<<endl;
        else printf("No\n");//cout<<"No"<<endl;
    }
    
    return 0;
}
```



### T1009	Triple Inversions

Given a list of *N* integers *A*1, *A*2, *A*3,...*A**N*, there's a famous problem to count the number of inversions in it. An inversion is defined as a piar of indices *i*<*j* such that *A**i*>*A**j*.

Now we have a new challenging problem. You are supposed to count the number of triple inversions in it. As you may guess, a triple inversion is defined as a triple of indices *i*<*j*<*k* such that *A**i*>*A**j*>*A**k*. For example, in the list { 5, 1, 4, 3, 2 } there are 4 triple inversions, namely (5,4,3), (5,4,2), (5,3,2) and (4,3,2). To simplify the problem, the list *A* is given as a permutation of integers from 1 to *N*.

**Input Specification:**

Each input file contains one test case. For each case, the first line gives a positive integer *N* in [3,105]. The second line contains a permutation of integers from 1 to *N* and each of the integer is separated by a single space.

**Output Specification:**

For each case, print in a line the number of triple inversions in the list.

**Sample Input:**

```in
22
1 2 3 4 5 16 6 7 8 9 10 19 11 12 14 15 17 18 21 22 20 13
```

**Sample Output:**

```out
8
```

**Solution:**

```C++
//  枚举中心    找出中心左边比自己大的数量   找出中心右边比自己小的数量   进行乘积操作
//  7   6   4   1   3
//      4
//  left_bigger:    2   right_smaller:  3   2*3=6

//  原数组
//  3   1   7   6   2   4   5
//  left_bigger
//  0   1   0   1   3   2   2

//土办法：  预处理O(1) 查询O(n)  更新O(n)
//前缀和：  预处理O(n)    查询O(1)   更新O(n)
//线段树：  预处理O(n)    查询O(log(n))   更新O(log(n))

//      15  28  6   14  7   10  10  5   7
//  0   15  43  49  63  70  80  90  95  102

//  线段树

#include<bits/stdc++.h>

using namespace std;

const int maxn=1<<17;

class Segtree{
    int appear[maxn*2];
public:
    Segtree(){memset(appear,0,sizeof(appear));}
    int beforesum(int i){
        if(i<0) return 0;
        int sum=appear[i+maxn];
        for(i+=maxn;i>1;i/=2){
            if(i%2) sum+=appear[i-1];
        }
        return sum;
    }
    
    int rangesum(int l,int r){
        return beforesum(r)-beforesum(l-1);
    }
    
    void update(int i,int val){
        int increment=val-appear[i+maxn];
        for(i+=maxn;i;i/=2){
            appear[i]+=increment;
        }
    }
};

int N,a[maxn];
long long ans=0;
long long left_bigger[maxn],right_smaller[maxn];

int main(){
    cin>>N;
    
    for(int i=0;i<N;i++) cin>>a[i];
    
    {
        Segtree T;
        for(int i=0;i<N;i++){
            int val=a[i];
            left_bigger[i]=T.rangesum(val+1,maxn-1);
            T.update(val,1);
        }
    }
    
    for(int i=1;i<N-1;i++){
        right_smaller[i]=(a[i]-1)-(i-left_bigger[i]);
        ans+=left_bigger[i]*right_smaller[i];
    }
    
    cout<<ans<<endl;
    
    return 0;
}

```



### T1010	Lehmer Code

According to Wikipedia: "In mathematics and in particular in combinatorics, the **Lehmer code** is a particular way to encode each possible permutation of a sequence of *n* numbers." To be more specific, for a given permutation of items {*A*1, *A*2, ⋯, *A**n*}, Lehmer code is a sequence of numbers {*L*1, *L*2, ⋯, *L**n*} such that *L**i* is the total number of items from *A**i* to *A**n* which are less than *A**i*. For example, given { 24, 35, 12, 1, 56, 23 }, the second Lehmer code *L*2 is 3 since from 35 to 23 there are three items, { 12, 1, 23 }, less than the second item, 35.

**Input Specification:**

Each input file contains one test case. For each case, the first line gives a positive integer *N* (≤105). Then *N* distinct numbers are given in the next line.

**Output Specification:**

For each test case, output in a line the corresponding Lehmer code. The numbers must be separated by exactly one space, and there must be no extra space at the beginning or the end of the line.

**Sample Input:**

```in
6
24 35 12 1 56 23
```

**Sample Output:**

```out
3 3 1 0 1 0
```

**Solution:**

```C++
#include<bits/stdc++.h>

using namespace std;

int N;
const int maxn=1<<17;
int numbers[maxn],right_smaller[maxn],temp_numnbers[maxn];

class Segtree{
    int appear[maxn*2];
public:
    Segtree(){memset(appear,0,sizeof(appear));}
    int beforesum(int i){
        if(i<0) return 0;
        int sum=appear[i+maxn];
        for(i+=maxn;i>1;i/=2){
            if(i%2) sum+=appear[i-1];
        }
        return sum;
    }
    
    int rangesum(int l,int r){
        if(l>r) return 0;
        if(l==r) return appear[l+maxn];
        int cnt=0;
        cnt+=appear[l+=maxn]+appear[r+=maxn];
        while(l/2!=r/2){
            if(l%2==0) cnt+=appear[l+1];
            if(r%2) cnt+=appear[r-1];
            l/=2;
            r/=2;
        }
        return cnt;
        //return beforesum(r)-beforesum(l-1);
    }
    
    void update(int i,int val){
        int increment=val-appear[i+maxn];
        for(i+=maxn;i;i/=2){
            appear[i]+=increment;
        }
    }
};

int main(){
    cin>>N;
    for(int i=0;i<N;i++) {
        cin>>numbers[i];
        temp_numnbers[i]=numbers[i];
    }
    
    int idx[maxn];
    for(int i=0;i<N;i++) idx[i]=i;
    sort(idx,idx+N,[](int x,int y){return numbers[x]<numbers[y];});
    int rnk[maxn];
    for(int i=0;i<N;i++)rnk[idx[i]]=i;
    
    Segtree T;
    
    for(int i=N-1;i>=0;i--){
        int val=rnk[i];
        right_smaller[i]=T.rangesum(0,val-1);
        T.update(val,1);
    }
    
    for(int i=0;i<N;i++){
        if(i) cout<<' ';
        cout<<right_smaller[i];
    }
    
    return 0;
}
```





### T1011	Cut Rectangles

When a rectangle is cut by a straight line, we can easily obtain two polygons as the result. But the reversed problem is harder: given two polygons, your task is to check whether or not they could be obtained by cutting a rectangle.

To give you more trouble, the input polygons are possibly moved, rotated (90 degrees, 180 degrees, or 270 degrees counter-clockwise), or even flipped (mirrored).

It is assumed that the original rectangle's edges are parallel to the axis.

**Input Specification:**

Each input file contains one test case. For each case, the first line gives a positive integer *N* (≤20), and then *N* pairs of polygons are given. Each polygon is described in the format:

*k* *x*1 *y*1 ⋯ *x**k* *y**k*

where *k* (2<*k*≤10) is the number of vertices on the polygon, and (*x**i*, *y**i*) (0≤*x**i*,*y**i*≤108) are the coordinates of the vertices, given in either clockwise or counter-clockwise order.

Note: there is no redundant vertex. That is, it is guaranteed that all the vertices are distinct for each polygon, and that no three consecutive vertices are on the same line.

**Output Specification:**

For each pair of polygons, print in a line either `YES` or `NO` as the answer.

**Sample Input:**

```in
8
3 0 0 1 0 1 1
3 0 0 1 1 0 1
3 0 0 1 0 1 1
3 0 0 1 1 0 2
4 0 4 1 4 1 0 0 0
4 4 0 4 1 0 1 0 0
3 0 0 1 1 0 1
4 2 3 1 4 1 7 2 7
5 10 10 10 12 12 12 14 11 14 10
3 28 35 29 35 29 37
3 7 9 8 11 8 9
5 87 26 92 26 92 23 90 22 87 22
5 0 0 2 0 1 1 1 2 0 2
4 0 0 1 1 2 1 2 0
4 0 0 0 1 1 1 2 0
4 0 0 0 1 1 1 2 0
```

**Sample Output:**

```out
YES
NO
YES
YES
YES
YES
NO
YES
```

**Solution：**

```c++

```



### T1012	Greedy Snake

### T1013	Image Segmentation

### T1014	Circles of Friends

A circle of friends is a network of friend relationships. If A is a friend of B, then B is considered a friend of A no matter B admits or not, and they are said to belong to the same circle. Here we assume that friendship is transitive, that is, if A is a friend of B, and B is a friend of C, then A is a friend of C and the three of them all belong to the same circle.

On the other hand, A is not so close to C as B is. We define the distance D(X, Y) between two friends X and Y as the minimum number of friends between them. For example, D(A, B) = 0, and D(C, A) = 1. The diameter of a friends circle is the maximum distance between any pair of friends in the circle.

Now given some people's relationships, you are supposed to find the number of friends circles and the circle with the largest diameter.

**Input Specification:**

Each input file contains one test case. For each case, the first line gives an integer *N* (2≤*N*≤1000), which is the total number of people involved, and hence they are numbered from 1 to *N*. Then *N* lines follow, each in the format:

*k* *p*1 ... *p**k*

where *k* (0≤*k*<*min*(10,*N*)) is the number of friends and *p*1 to *p**k* (if *k*>0) are the friends' indices. The *i*-th line corresponds to the *i*-th person. All the numbers in a line are separated by spaces. It is guaranteed that no one is given as a friend of oneself.

**Output Specification:**

For each case, print in a line the number of friends circles, and the largest diameter, separated by exactly one space.

**Sample Input:**

```in
17
2 15 12
1 17
2 16 9
1 8
4 10 13 15 14
0
2 11 14
1 4
2 2 3
2 13 11
2 15 7
2 1 14
2 5 15
0
0
1 3
1 2
```

**Sample Output:**

```out
4 3
```

**Solution:**

```C++
#include<bits/stdc++.h>

using namespace std;

const int maxn=1024;

int N,maxdepth=0,circle_number;
bool G[maxn][maxn],visited[maxn];

void readData();

void dfs(int x);

void dfsTrave();

void bfs(int x);

void bfsSearch();

void showResult();

int main(){
    readData();
    
    dfsTrave();
    
    bfsSearch();
    
    showResult();
    
    return 0;
}

void showResult(){
    cout<<circle_number<<' '<<max(0,maxdepth-1)<<endl;
}

void bfsSearch(){
    for(int i=1;i<=N;i++) bfs(i);
}

void readData(){
    fill(G[0],G[0]+maxn*maxn,false);
    cin>>N;
    for(int i=1;i<=N;i++){
        int k;
        cin>>k;
        while(k--){
            int x;
            cin>>x;
            G[x][i]=true;
            G[i][x]=true;
        }
    }
}

void dfs(int x){
    visited[x]=true;
    for(int i=1;i<=N;i++){
        if(G[x][i] && !visited[i]){
            dfs(i);
        }
    }
}

void dfsTrave(){
    fill(visited,visited+maxn,false);
    for(int i=1;i<=N;i++){
        if(visited[i]) continue;
        dfs(i);
        circle_number++;
    }
}

void bfs(int x){
    int depth[maxn]={0};
    queue<int> q;
    fill(visited,visited+maxn,false);
    q.push(x);
    visited[x]=true;
    
    while(q.size()){
        int now=q.front();
        q.pop();
        for(int i=1;i<=N;i++){
            if(G[now][i] && !visited[i]){
                q.push(i);
                depth[i]=depth[now]+1;
                visited[i]=true;
                maxdepth=max(maxdepth,depth[i]);
            }
        }
    }
}
```



### T1015	Letter-moving Game

### T1016	Uniqueness of MST

### T1017	The Best Peak Shape

### T1018	Subnumbers

### T1019	Separate the Animals

### T1020	Delete At Most Two Characters

### T1021	Safe Fruit

### T1022	Werewolf

### T1023	The Best Polygon

### T1024	Currency Exchange Centers

### T1025	Keep at Most 100 Characters

### T1026	String of Colorful Beads

### T1027	Larry and Inversions

### =T-1028	Do All Roads Lead to Rome

Indeed there are many different tourist routes from our city to Rome. Your job is to count the number of different routes from our city to Rome, and to check if ALL the routes lead to Rome -- that is, whether or not all the routes from our city to Rome can cover every road on the routes from our city to anywhere.

**Input Specification:**

Each input file contains one test case. For each case, the first line contains 2 positive integers *N* (2≤*N*≤20), the number of cities, and *K*, the total number of roads between pairs of cities; followed by the name of the starting city. Then *K* lines follow, each describes a road between two cities in the format `City1 City2`. Here the name of a city is a string of 3 capital English letters, and the destination is always `ROM` which represents Rome.

**Output Specification:**

For each test case, first print in a line `Yes` if all the routes from the starting city lead to `ROM`, or `No` if not. Then print in the next line the number of different routes from the starting city to `ROM`. Here a **route** is defined to be a **simple path**, that is, no city along the route will be visited more than once. It is guaranteed that this number is no more than 106. By the way, it is assumed that `ROM` is our only destination -- that is, once we reach `ROM`, we will stop traveling and stay there.

**Sample Input 1:**

```in
7 8 HZH
PKN HZH
GDN ROM
ROM HKG
PRS PKN
PRS BLN
HKG PRS
ROM BLN
HZH GDN
```

**Sample Output 1:**

```out
Yes
3
```

**Sample Input 2:**

```in
10 11 HZH
PKN HZH
GDN ROM
ROM HKG
PRS PKN
PRS BLN
HKG PRS
ROM BLN
HZH GDN
GDN MAC
MAC WWW
MAC VVV
```

**Sample Output 2:**

```out
No
3
```

**Solution:**

```c++
#include<iostream>
#include<set>

using namespace std;

int N,K;
int start_code, end_code;
int road_to_rome=0;
bool other_road=false;

const int maxn=25;

set<int> label_lake;
set<int> covered_city;
set<int> all_covered_city;
bool Graph[maxn][maxn]={false};
int reverse_label_lake[26*26*26+1]={0};

int pre_point[maxn]={-1};

bool is_visited[maxn]={false};
bool is_covered[maxn][maxn]={false};
bool is_cover_covered[maxn]={false};

void readData();

int name_to_inter(char*s);

void dfs(int x);

void routeCover(int x);

void printResult();

int main(){
    
    readData();
    
    dfs(start_code);
    
    printResult();
    
    return 0;
}

void readData(){
    cin>>N>>K;
    char starting_city[4],city1[4],city2[4];
    char ending_city[]={"ROM"};
    cin>>starting_city;
    
    fill(Graph[0],Graph[0]+maxn*maxn,false);
    fill(is_visited,is_visited+maxn,false);
    fill(is_covered[0],is_covered[0]+maxn*maxn,false);
    fill(pre_point,pre_point+maxn,-1);
    
    start_code=name_to_inter(starting_city);
    end_code=name_to_inter(ending_city);
    
    is_visited[start_code]=true;
    
    //cout<<start_code<<'-'<<end_code<<endl;
    
    int tempK=K;
    while(tempK--){
        cin>>city1>>city2;
        int c1=name_to_inter(city1);
        int c2=name_to_inter(city2);
        
        //cout<<city1<<'-'<<city2<<':'<<c1<<' '<<c2<<endl;
        
        if(c1==c2) continue;
        
        Graph[c1][c2]=true;
        Graph[c2][c1]=true;
    }
}

int name_to_inter(char*s){
    int value=0;
    for(int i=0;i<3;i++){
        value*=26;
        value+=s[i]-'A';
    }
    
    int old_len=label_lake.size();
    label_lake.insert(value);
    
    if(old_len==label_lake.size()){
        return reverse_label_lake[value];
    }
    else{
        //cout<<s<<' '<<value<<' '<<old_len<<endl;
        reverse_label_lake[value]=old_len;
        return old_len;
    }
    
}

void dfs(int x){
    all_covered_city.insert(x);
    
    if(x==end_code) {
        road_to_rome++;
        
        for(int i=0;i<N;i++){
            if(is_visited[i]) covered_city.insert(i);
        }
        
        return;
    }
    
    for(int i=0;i<N;i++){
        if(Graph[x][i]==false || is_visited[i]) continue;
        else {
            is_visited[i]=true;
            
            dfs(i);
            
            is_visited[i]=false;
        }
    }
    
    return;
}

void printResult(){
    if(covered_city.size()!=all_covered_city.size())
        cout<<"No"<<endl;
    else 
        cout<<"Yes"<<endl;
    
    cout<<road_to_rome<<endl;
}
```



### T1029	Array Cutting Score

### T1030	Beautiful Subsequence

###T1031	Path to Infinity

```c++
#include<iostream>

using namespace std;

int main(){
	return  0;
}
```

