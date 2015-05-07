#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
int f[200][200][16], n;
int main() {
	int T, tmp, ans;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		ans = 1;
		memset(f,0,sizeof(f));
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &tmp);
			f[i][i][tmp] = 1;
		}
		for (int i = n-1; i > 0; --i) {
			for (int j = i+1; j <= n; ++j) {
				f[i][j][0] = max(f[i+1][j][0], f[i][j-1][0]);
				for (int t = 1; t <= 15; ++t) {
					f[i][j][t] = max(f[i+1][j][t], f[i][j-1][t]);
					for (int k = i; k < j; ++k) 
						if (f[i][k][t-1] && f[k+1][j][t-1])
							f[i][j][t] = max(f[i][j][t], f[i][k][t-1] + f[k+1][j][t-1]);
				}
			}
		}
		for (int i = 1; i <= 15; ++i)
			ans = max(ans, f[1][n][i]);
		printf("%d\n", ans);
	}
	return 0;
}