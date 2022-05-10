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
