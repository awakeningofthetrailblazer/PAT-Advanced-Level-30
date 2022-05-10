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
