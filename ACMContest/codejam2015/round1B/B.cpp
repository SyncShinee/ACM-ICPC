#include <cstdio>
#include <algorithm>
using namespace std;
int T, r, c, n, ans, cnt, a[10010], tmp, remain;
int main() {
	freopen("B-large-practice.in", "r", stdin);
	freopen("Bout.txt", "w", stdout);
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++ cas) {
		scanf("%d%d%d", &r, &c, &n);
		if (n <= (r * c + 1) >> 1)
			printf("Case #%d: 0\n", cas);
		else {
			cnt = 0;
			ans = 0;
			for (int i = 1; i <= r; ++ i)
				for (int j = 1; j <= c; ++ j) {
					if ((i + j) & 1) {
						a[cnt++] = (i > 1) + (i < r) + (j > 1) + (j < c);
					}
				}
			sort(a, a+cnt);
			remain = n - ((r * c + 1) >> 1);
			
			for (int i = 0; i < remain; ++ i)
				ans += a[i];
			cnt = 0;
			tmp = 0;
			for (int i = 1; i <= r; ++ i)
				for (int j = 1; j <= c; ++ j) {
					if (!((i + j) & 1)) {
						a[cnt++] = (i > 1) + (i < r) + (j > 1) + (j < c);
					}
				}
			sort(a, a+cnt);
			remain = n - ((r * c) >> 1);
			for (int i = 0; i < remain; ++ i) {
				tmp += a[i];
			}
			
			ans = min(ans, tmp);
			printf("Case #%d: %d\n", cas, ans);
		}
	}
	return 0;
}