#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
int ans[100010], a[100010], d[100010], u, v, n, m;
vector <int> gra[100010];
queue <int> q;
int main() {
	while (~scanf("%d%d", &n, &m)) {
		memset(d, 0, sizeof(d));
		memset(ans, 0, sizeof(ans));
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
			ans[i] = a[i];
			gra[i].clear();
		}
		for (int i = 1; i <= m; ++i) {
			scanf("%d%d", &u, &v);
			gra[u].push_back(v);
			d[v]++;
		}
		for (int i = 1; i <= n; ++i) 
			if (d[i] == 0)
				q.push(i);
		while (!q.empty()) {
			u = q.front();
			q.pop();
			for (int i = 0; i < gra[u].size(); ++i) {
				d[gra[u][i]]--;
				if (d[gra[u][i]] == 0)
					q.push(gra[u][i]);
				ans[gra[u][i]] = max(ans[gra[u][i]], ans[u]+a[gra[u][i]]);
			}
		}
		int k = 0;
		for (int i = 1; i <= n; ++i)
			if (ans[i] > k)
				k = ans[i];
		printf("%d\n", k);
	}
	return 0;
}