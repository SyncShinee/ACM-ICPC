#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;
vector <int> gra[128];
queue <int> q;
bool vis[128];
int degree[128];
int main() {
	int n, m, x, y, ans;
	while (~scanf("%d%d", &n, &m)) {
		ans = 0;
		memset(degree, 0, sizeof(degree));
		memset(vis, 0, sizeof(vis));
		for (int i = 1; i <= n; ++i)
			gra[i].clear();
		for (int i = 0; i < m; ++i) {
			scanf("%d%d", &x, &y);
			gra[y].push_back(x);
			degree[x]++;
		}
		for (int i = 1; i <= n; ++i) {
			if (degree[i] == 0) {
				q.push(i);
				vis[i] = true;
				ans++;
			}
		}
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			for (int i = 0; i < gra[u].size(); ++i) {
				degree[gra[u][i]]--;
				if (degree[gra[u][i]] == 0) {
					q.push(gra[u][i]);
					vis[gra[u][i]] = true;
					ans++;
				}
			}
		}
		if (ans == n)
			printf("YES\n");
		else {
			printf("NO\n");
		}
	}
	return 0;
}