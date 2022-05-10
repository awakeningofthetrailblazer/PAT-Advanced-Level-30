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
