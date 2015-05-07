#include <cstdio>
#include <cstring>
#include <vector>
#define MOD 1000000007
using namespace std;
vector<int> tree[16];
int f[2048][128], sub[16], n, m, s, u, v, p[16], c[16];
void dfs(int x) {
	sub[x] = 0;
	for (int i = 0; i < tree[x].size(); ++i) {
		dfs(tree[x][i]);
		sub[x] |= (sub[tree[x][i]] | (1<<(tree[x][i]-1)));
	}
}
int calc(int x, int q) {
	if (m-c[x] < q && c[x] < q)
		return 0;
	if (m-c[x] >= q && c[x] >= q)
		return 2;
	return 1;

}
int main() {
	while (~scanf("%d%d%d", &n, &m, &s)) {
		for (int i = 1; i <= n; ++i)
			tree[i].clear();
		for (int i = 1; i < n; ++i) {
			scanf("%d%d", &u, &v);
			tree[u].push_back(v);
		}
		for (int i = 1; i <= n; ++i) 
			scanf("%d%d", &p[i], &c[i]);
		dfs(1);
		memset(f, 0, sizeof(f));
		for (int i = 0; i < (1 << n); ++i)
			f[i][0] = 1;
		for (int i = 1; i <= m; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (calc(j,i) > 0) {
					for (int t = 0; t < (1<<n); ++t) {
						if (!((1<<(j-1)) & t)) {
							int tmp0 = sub[j] & t, tmp = 0;
							while (tmp0) {
								tmp0 = tmp0 & (tmp0-1);
								tmp++;
							}
							for (int k = 0; k <= s; ++k) {
								if (k+tmp*p[j] <= s) {
									f[t|(1<<(j-1))][k+tmp*p[j]] = (f[t|(1<<(j-1))][k+tmp*p[j]]+(f[t][k]*calc(j,i))%MOD)%MOD;
								}
							}
						}
					}
				}
			}
		}
		printf("%d\n", f[(1<<n)-1][s]);
	}
	return 0;
}