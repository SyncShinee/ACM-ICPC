#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
bool f[128][128][128];
int a[128][128];
int main() {
	int n, m, k;
	while (~scanf("%d%d%d", &n, &m, &k)) {
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				scanf("%d", &a[i][j]);
		memset(f, 0, sizeof(f));
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				f[i][j][0] = true;
				for (int t = 1; t <= k; ++t)
					f[i][j][t] = f[i-1][j][t] | f[i][j-1][t];
				for (int t = k; t >= a[i][j]; --t) {
					f[i][j][t] |= f[i][j][t-a[i][j]];
				}
			}
		}
		for (int i = k; i >= 0; --i) {
			if (f[n][m][i]) {
				printf("%d\n", i);
				break;
			}
		}
	}
	return 0;
}