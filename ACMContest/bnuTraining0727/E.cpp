#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;
int n, m, Q, x, y, maxd[10010], tot;
int vis[10010], deep[10010];
struct node {
	int num, d;
	node (int _num = 0, int _d = 0) {
		num = _num;
		d = _d;
	}
	friend bool operator < (node x, node y) {
		return x.num < y.num;
	} 
}p[10010];
vector <int> gra[10010];
queue<int> q;
using namespace std;
int main() {
	int T;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++cas) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i) {
			gra[i].clear();
		}
		for (int i = 0; i < m; ++i) {
			scanf("%d%d", &x, &y);
			gra[x].push_back(y);
			gra[y].push_back(x);
		}
		memset(vis, 0, sizeof vis);
		memset(deep, 0, sizeof deep);
		tot = 0;
		for (int start = 1; start <= n; ++start) {
			if (vis[start]) {
				continue;
			}
			q.push(start);
			vis[start] = 1;
			while (!q.empty()) {
				x = q.front();
				q.pop();
				for (int i = 0; i < gra[x].size(); ++i) {
					if (!vis[gra[x][i]]) {
						vis[gra[x][i]] = 1;
						q.push(gra[x][i]);
					}
				}
			}
			vis[x] = 2;
			q.push(x);
			p[tot].num = 0;
			deep[x] = 0;
			while (!q.empty()) {
				x = q.front();
				q.pop();
				p[tot].num++;
				for (int i = 0; i < gra[x].size(); ++i) {
					if (vis[gra[x][i]] < 2) {
						vis[gra[x][i]] = 2;
						deep[gra[x][i]] = deep[x] + 1;
						q.push(gra[x][i]);
					}
				}
			}
			p[tot].d = deep[x];
			tot++;
		}
		sort(p, p + tot);
		maxd[tot] = 0;
		for (int i = tot - 1; i >= 0; --i) {
			maxd[i] = p[i].d;
			maxd[i] = max(maxd[i], maxd[i + 1]);
		}
		scanf("%d", &Q);
		printf("Case %d:\n", cas);
		while (Q--) {
			scanf("%d", &x);
			int pos = lower_bound(p, p + tot, node(x, 0)) - p;
			if (pos == tot) {
				printf("impossible\n");
			}
			else {
				if (maxd[pos] >= x - 1) {
					printf("%d\n", x - 1);
				}
				else {
					printf("%d\n", (x - maxd[pos] - 1) * 2 + maxd[pos]);
				}
			}
		}
	}
	return 0;
}