#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
const int N = 256;
int a[N][N];
bool flag;
struct Edge{
    int y, val;
    Edge (int _y = 0, int _val = 0) : y(_y), val(_val){}
};
vector <Edge> gra[N];
bool vis[N];
int dist[N];
void dfs(int x) {
    vis[x] = true;
    for (int i = 0; i < gra[x].size(); ++ i) {
	if (vis[gra[x][i].y]) {
	    if (dist[gra[x][i].y] == dist[x] + gra[x][i].val) {
		continue;
	    }
	    else {
		flag = false;
		return;
	    }
	}
	dist[gra[x][i].y] = dist[x] + gra[x][i].val;
	dfs(gra[x][i].y);
    }
}
int main() {
    flag = true;
    int n, m, x, y, z;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) {
	for (int j = 1; j <= n; ++ j) {
	    scanf("%d", &a[i][j]);
	}
    }
    scanf("%d", &m);
    while (m --) {
	scanf("%d%d%d", &x, &y, &z);
	gra[x].push_back(Edge(y, z));
	gra[y].push_back(Edge(x, -z));
    }
    for (int i = 1; i <= n; ++ i) {
	if (!vis[i]) {
	    dist[i] = 0;
	    dfs(i);
	}
    }
    if (!flag) {
	puts("Impossible");
    }
    else {
	for (int i = 1; i <= n; ++ i) {
	    for (int j = 1; j <= n; ++ j) {
		printf("%d%c", dist[j] - dist[i] + a[i][j], " \n"[j == n]);
	    }
	}
    }
    return 0;
}
