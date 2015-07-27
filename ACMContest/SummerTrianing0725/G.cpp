#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;
int a[1024], b[1024], n, k;
int main() {
	int T;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++cas) {
		scanf("%d%d", &n, &k);
		for (int i = 0; i < k; ++i) 
			scanf("%d", &a[i]);
		sort(a, a + k);
		k = unique(a, a + k) - a;
		int limit = k;
		for (int i = 1; i < k; ++i) {
			if (a[i] > 35) {
				limit = i;
				break;
			}
		}
		int ret = 0;
		for (int sta = 0; sta < (1 << limit); ++sta) {
			int ans = 0;
			memset(b, 0, sizeof b);
			for (int i = 0; i < limit; ++i) {
				if ((1 << i) & sta) {
					for (int j = a[i]; j <= n; j += a[i]) {
						b[j] ^= 1;
						if (b[j]) {
							ans++;
						}
						else {
							ans--;
						}
					}
				}
			}
			for (int i = limit; i < k; ++i) {
				int tmp = 0;
				for (int j = a[i]; j <= n; j += a[i]) {
					if (b[j]) {
						tmp--;
					}
					else {
						tmp++;
					}
				}
				if (tmp > 0)
					ans += tmp;
			}
			if (ans > ret)
				ret = ans;
		}
		printf("Case #%d: %d\n", cas, ret);
	}
	return 0;
}