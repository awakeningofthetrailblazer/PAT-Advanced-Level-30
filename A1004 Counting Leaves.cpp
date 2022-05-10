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
