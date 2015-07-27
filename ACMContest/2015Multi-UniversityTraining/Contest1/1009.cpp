#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cmath>
#include <vector>
#include <set>
#define N 100010
using namespace std;
struct edge {
	int to, val;
}e;
vector <edge> gra[N];
set <int> st;
int n, q, lmq[N << 2], first[N], pos[N], idx[N], dfn, mn[N << 2][32], dist[N], len_lmq;
bool vis[N];
void dfs(int x, int pre) {
	pos[dfn] = x;
	idx[x] = dfn++;
	first[x] = len_lmq;
	lmq[len_lmq++] = idx[x];
	for (int i = 0; i < gra[x].size(); ++i) {
		if (pre == gra[x][i].to) {
			continue;
		}
		dist[gra[x][i].to] = dist[x] + gra[x][i].val;
		dfs(gra[x][i].to, x);
		lmq[len_lmq++] = idx[x];
	}
}

void lmq_init() {
	for (int i = 1; i < len_lmq; ++i) {
		mn[i][0] = lmq[i]; 
	}
	for (int j = 1; (1 << j) < len_lmq; ++j) {
		for (int i = 1; i + (1 << j) - 1 < len_lmq; ++i) {
			int tmp1 = mn[i][j-1], tmp2 = mn[i + (1 << j-1)][j-1];
			if (tmp1 < tmp2)
				mn[i][j] = tmp1;
			else 
				mn[i][j] = tmp2; 
		}
	}
}

int lca(int x, int y) {

	int l = first[x], r = first[y];
	if (l > r) {
		int t = l;
		l = r;
		r = t;
	} 
	int tmp = (int)(log((r - l + 1)*1.0) / log(2.0));
	return pos[min(mn[l][tmp], mn[r - (1 << tmp) + 1][tmp])];
}

int add(int x) {
	set <int>:: iterator rit = st.lower_bound(x), lit = rit;
	lit--;
	if (rit == st.begin() || rit == st.end()) {
		rit = st.end();
		lit = st.begin();
		rit--;
	}
	int l = pos[*lit], r = pos[*rit];
	return dist[pos[x]] - dist[lca(pos[x], l)] - dist[lca(pos[x], r)] + dist[lca(l, r)];
}

int main() {
	int T, x, y, z, sum;
	freopen("1009.in", "r", stdin);
	freopen("1009.out", "w", stdout);
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++cas) {
		scanf("%d%d", &n, &q);
		printf("Case #%d:\n", cas);
		for (int i = 1; i <= n; ++i) {
			gra[i].clear();
		}
		st.clear();
		memset(vis, 0, sizeof vis);
		for (int i = 1; i < n; ++i) {
			scanf("%d%d%d", &x, &y, &z);
			e.to = y;
			e.val = z;
			gra[x].push_back(e);
			e.to = x;
			gra[y].push_back(e);
		}
		dfn = 1;
		memset(dist, 0, sizeof dist);
		len_lmq = 1;
		dfs(1, 0);
		lmq_init();
		sum = 0;
		while (q--) {
			scanf("%d%d", &y, &x);
			x = idx[x];
			if (y == 1) {
				if (st.empty()) {
					st.insert(x);
					vis[x] = true;

				}
				else if (!vis[x]) {
					sum += add(x);
					vis[x] = true;
					st.insert(x);
				}
			}
			else {
				if (vis[x]) {
					vis[x] = false;
					st.erase(x);
					if (!st.empty()) {
						sum -= add(x);
					}
				}
			}
			printf("%d\n", sum);
		}
	}
	return 0;
}