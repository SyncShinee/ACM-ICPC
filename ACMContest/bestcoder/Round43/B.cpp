#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
ll l, r, mid, n, k, a[100010], ans;
int main() {
	while (~scanf("%I64d%I64d", &n, &k)) {
		ans = 0;
		memset(a, 0, sizeof(a));
		for (ll i = 1; i <= n; ++i) {
			scanf("%I64d", &a[i]);
			a[i] %= k;
		}
		sort(a + 1, a + n + 1);
		l = 1; r = n;
		while (l < r) {
			while (l < r && a[l] + a[r] > k-1) {
				r--;
			}
			if (l == r) {
				break;
			}
			ans = max(ans, a[l] + a[r]);
			l++;
		}
		ans = max(ans, (a[n-1] + a[n]) % k);
		printf("%I64d\n", ans);
	}
	return 0;
}