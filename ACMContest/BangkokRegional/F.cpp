#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[128][128], f[128][128][128], g[128][128][128], ff[128], gg[128];
int main() {
	//freopen("in.txt", "r", stdin);
	int T, n, m, ans, cnt;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j) 
				scanf("%d", &a[i][j]);
		memset(f, 0, sizeof(f));
		memset(g, 0x7f, sizeof(g));
		memset(ff, 0, sizeof(ff));
		memset(gg, 0x7f, sizeof(gg));
		ans = 0;
		for (int i = 0; i <= n; ++i)
			for(int j = 0; j <= m; ++j)
				g[0][i][j] = 0;
		cnt = min(n, m);
		for (int t = 1; t <= cnt; ++t) {
			for (int i = t; i <= n; ++i) {
				for (int j = t; j <= m; ++j) {
					f[t][i][j] = max(f[t-1][i-1][j-1] + a[i][j], max(f[t][i-1][j], f[t][i][j-1]));
					ff[t] = max(ff[t], f[t][i][j]);
					g[t][i][j] = min(g[t-1][i-1][j-1] + a[i][j], min(g[t][i-1][j], g[t][i][j-1]));
					gg[t] = min(gg[t], g[t][i][j]);
					//printf("f%d %d %d = %d g = %d\n", t, i, j, f[t][i][j], g[t][i][j]);
				}
			}
		}
		for (int i = 1; i <= cnt/2; ++i) {
			//printf("%d %d\n", ff[i], gg[i]);
			ans = max(ans, ff[i] - gg[2*i]);
		}
		printf("%d\n", ans);
	}
	return 0;
}