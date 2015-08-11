#include <cstdio>
#include <queue>
#include <cstring>
#include <set>
#include <vector>
#include <map>
#define N 200010
using namespace std;
bool vis[N];
struct edge {
	int to, idx;
	edge(int _to = 0, int _idx = 0) : to(_to), idx(_idx) {}
};
vector<edge> gra[N];
map <int, int> mp[N];
queue<int> q;
int n, m, A, B, C, D, st, ed, pre[N], prev[N], ans[N];
using namespace std;
int main() {
	while (~scanf("%d%d", &n, &m)) {
		int num = 1, side = 1;
		for (int i = 0; i < m; ++i) {
			scanf("%d%d%d%d", &A, &B, &C, &D);
			if (mp[A].count(C)) {
				if (mp[B].count(D)) {
					gra[mp[A][C]].push_back(edge(mp[B][D], side++));
				}
				else {
					mp[B][D] = num++;
					gra[mp[A][C]].push_back(edge(num - 1, side++));
				}
			}
			else {
				mp[A][C] = num++;
				int tmp = num - 1;
				if (mp[B].count(D)) {
					gra[tmp].push_back(edge(mp[B][D], side++));
				}
				else {
					mp[B][D] = num ++;
					gra[tmp].push_back(edge(num - 1, side++));
				}
			}
		}
		scanf("%d%d%d%d", &A, &B, &C, &D);
		if (mp[A].count(C)) {
			st = mp[A][C];
		}
		else {
			mp[A][C] = num++;
			st = num - 1;
		}
		if (mp[B].count(D)) {
			ed = mp[B][D];
		}
		else {
			mp[B][D] = num ++;
			ed = num - 1;
		}
		for (int i = 1; i <= n; ++i) {
			for (map <int, int> :: iterator iter = mp[i].begin(); iter != mp[i].end(); ++iter) {
				map <int, int> :: iterator it = iter;
				it++;
				if (it != mp[i].end()) {
					gra[iter->second].push_back(edge(it->second, 0));
				}
			}
		}
		q.push(st);
		vis[st] = 1;
		pre[st] = -1;
		prev[st] = -1;
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			for (int i = 0; i < gra[u].size(); ++i) {
				if (vis[gra[u][i].to]) {
					continue;
				}
				else {
					vis[gra[u][i].to] = 1;
					q.push(gra[u][i].to);
					pre[gra[u][i].to] = u;
					prev[gra[u][i].to] = gra[u][i].idx;
				}
			}
		}
		if (!vis[ed]) {
			printf("Impossible\n");
		}
		else {
			int len = 0;
			for (int i = ed; i != -1; i = pre[i]) {
				if (prev[i] > 0) {
					ans[len++] = prev[i];
				}
			}
			printf("%d\n", len);
			for (int i = len - 1; i >= 0; --i) {
				printf("%d%c", ans[i], " \n"[i == 0]);
			}
		}
	}
	return 0;
}