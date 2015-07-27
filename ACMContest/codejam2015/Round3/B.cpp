#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

int n, k, sum[10010], cha[10010], mn[10010], mx[10010], l, r, tmp;  

int main() {
	freopen("B-large-practice.in", "r", stdin);
	freopen("B.out", "w", stdout);
	int T;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++cas) {
		scanf("%d%d", &n, &k);
		for (int i = 1; i <= n-k+1; ++i)
			scanf("%d", &sum[i]);
		memset(cha, 0, sizeof(cha));
		memset(mx, 0, sizeof(mx));
		memset(mn, 0, sizeof(mn));
		l = 0;
		for (int i = k+1; i <= n; ++i) {
			cha[i] = sum[i-k+1] - sum[i-k] + cha[i-k];
			mx[i % k] = max(mx[i % k], cha[i]);
			mn[i % k] = min(mn[i % k], cha[i]);
		}
		for (int i = 0; i < k; ++i) {
			l = max(l, mx[i] - mn[i]);
		}
		tmp = 0;
		for (int i = 0; i < k; ++i) {
			tmp += l - (mx[i] - mn[i]);
		}
		for (int i = 1; i < k; ++i) {
			sum[1] += mn[i] - mn[0];
		}
		if ((sum[1] % k + k)%k > tmp) {
			l++;
		}
		printf("Case #%d: %d\n", cas, l);
	}
	return 0;
}