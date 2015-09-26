#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
const int N = 20010, M = 200010;
int head[N], side, ans, n, m, sum, sumn;
vector <int> gra[N];
bool b[N];
struct edge {
	int to, nxt;
}e[N << 1];
struct Edge {
	int u, v;
}E[M];
void build(int x, int y) {
	e[side].to = y;
	e[side].nxt = head[x];
	head[x] = side++;
}
void dfs(int x) {
	b[x] = true;
	sum += gra[x].size();
	for (int i = 0; i < gra[x].size(); ++ i) {
		if (b[gra[x][i]]) {
			sum--;
			sumn++;
		}
	}
	for (int i = head[x]; ~i; i = e[i].nxt) {
		if (b[e[i].to]) continue;
		ans = min(ans, sum - sumn);
		dfs(e[i].to);
	}
}
int main() {
	int T, x, y;
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++ cas) {
		sum = sumn = 0;
		ans = 1e9;
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++ i) head[i] = -1, gra[i].clear(), b[i] = false;
		side = 0;
		for (int i = 1; i <= m; ++ i) {
			scanf("%d%d", &x, &y);
			if (i < n) {
				build(x, y);
				build(y, x);
			}
			gra[x].push_back(y);
			gra[y].push_back(x);
		}
		dfs(1);
		printf("Case #%d: %d\n", cas, ans);
	}
	return 0;
}