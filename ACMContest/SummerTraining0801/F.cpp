#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int a[700][10010], sz, n, m, k;
double sum[700][10010], num[10010];
int main() {
	int T;
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &m, &n, &k);
		for (int i = 1; i <= m; ++i)
			for (int j = 1; j <= n; ++j)
				scanf("%d", &a[i][j]);
		double l = 0, r = 5000, mid;
		memset(sum, 0, sizeof sum);
		while (r - l > 1e-7) {
			mid = (l + r) / 2;
			for (int i = 1; i <= m; ++i) {
				for (int j = 1; j <= n; ++j) {
					sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + 1.0 * a[i][j] - mid;
				}
			}
			double ans = -1e11;
			for (int i = 1; i <= m; ++i) {
				for (int j = i; j <= m; ++j) {
					sz = j - i + 1;
					for (int t = 1; t <= n; ++t) {
						num[t] = sum[j][t] - sum[i - 1][t];
					}
					int len = 1;
					double mn = 0;
					for (int t = 1; t <= n; ++t) {
						if (1ll * t * sz < k)
							continue;
						while (1ll*(t - len + 1) * sz >= k) {
							mn = min(mn, num[len-1]);
							len ++;
						}
						ans = max(ans, num[t] - mn);
					}
				}
			}
			if (ans < 0) {
				r = mid;
			}
			else {
				l = mid;
			}
		}
		printf("%.3f\n", mid);
	}
	return 0;
}