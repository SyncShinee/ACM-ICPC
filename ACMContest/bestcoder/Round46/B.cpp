#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

int n, m, x, y;
struct node {
	int u, v;
}e;
vector<node> gra;
int ans;
bool sta[1024][1024];

int main() {
	while (~scanf("%d%d", &n, &m)) {
		for (int i = 0; i < n; ++i) {
			scanf("%d%d", &x, &y);
		}
		gra.clear();
		memset(sta, 0, sizeof(sta));
		for (int i = 0; i < m; ++i) {
			scanf("%d%d", &e.u, &e.v);
			sta[e.u][e.v] = sta[e.v][e.u] = 1;
			gra.push_back(e);

		}
		ans = 0;
		for (int i = 0; i < gra.size(); ++i)
			for (int j = i + 1; j < gra.size(); ++j) {
				int u1 = gra[i].u, v1 = gra[i].v, u2 = gra[j].u, v2 = gra[j].v;
				if (u1 == u2 || u1 == v2 || v1 == u2 || v1 == v2)
					continue;
				if (sta[u1][u2] && sta[u1][v2] && sta[v1][u2] && sta[v1][v2])
					ans++;
			}
		if (ans > 0) {
			printf("4 %d\n", ans / 3);
			continue;
		}
		ans = 0;
		for (int i = 0; i < gra.size(); ++i)
			for (int j = 1; j <= n; ++j) {
				if (j == gra[i].u || j == gra[i].v)
					continue;
				if (sta[j][gra[i].u] && sta[j][gra[i].v]) {
					ans++;
				}
			}
		if (ans > 0)
			printf("3 %d\n", ans / 3);
		else if (m > 0)
			printf("2 %d\n", m);
		else 
			printf("1 %d\n", n);
	}
	return 0;
}