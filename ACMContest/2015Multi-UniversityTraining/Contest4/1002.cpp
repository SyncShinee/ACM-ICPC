#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, a[1000010], f[1000010], g[1000010], ans;
int main() {
	int T;
	scanf("%d", &T);
	while (T --) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++ i) {
			scanf("%d", &a[i]);
		}
		if (n <= 2) {
			printf("%d\n", n);
			continue;
		}
		f[1] = g[1] = 1, f[2] = g[2] = 2;
		ans = 2;
		for (int i = 3; i <= n; ++ i) {
			if (a[i] + a[i - 2] == a[i - 1] + a[i - 1]) {
				f[i] = f[i - 1] + 1;
			}
			else {
				f[i] = 2;
			}
			if (1ll * a[i] * a[i - 2] == 1ll * a[i - 1] * a[i - 1]) {
				g[i] = g[i - 1] + 1;
			}
			else {
				g[i] = 2;
			}
			ans = max(ans, f[i]);
			ans = max(ans, g[i]);
		}
		printf("%d\n", ans);
	}
	return 0;
}