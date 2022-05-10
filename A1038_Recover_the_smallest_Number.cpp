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
