#include <cstdio>
#include <queue>
#include <map>
using namespace std;
queue<int> q[100010];
map<int, int> mp;
int main() {
	int tot = 0, h, tmp, n, m;
	while (~scanf("%d%d", &n, &m)) {
		mp.clear();
		for (int i = 1; i <= n; ++i) {
			while (!q[i].empty()) {
				q[i].pop();
			}
		}
		for (int i = 0; i < n; ++i) {
			scanf("%d", &h);
			tmp = mp[h];
			if (tmp) {
				q[tmp].push(i+1);
			}
			else {
				mp[h] = ++tot;
				q[tot].push(i+1);
			}
		}
		for (int i = 0; i < m; ++i) {
			scanf("%d", &h);
			tmp = mp[h];
			if (!q[tmp].empty()) {
				printf("%d\n", q[tmp].front());
				q[tmp].pop();
			}
			else {
				printf("-1\n");
			}
		}
	}
}