#include <cstdio>
#include <algorithm>
using namespace std;
struct node1 {
	int high, l, r;
}t1n, a[32];
struct node2 {
	int dd, hi, lo;
}t2n, b[32];
int t1len, t2len, num, ans;
int main() {
	int T;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++cas) {
		printf("Case #%d:\n", cas);
		int n, x, y, z, t, tmph, tmpl, tmpll, tmprr;
		t1len = t2len = ans = 0;
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			scanf("%d%d%d%d", &x, &y, &z, &t);
			if (x == z) {
				b[t2len].dd = x;
				b[t2len].hi = max(y, t);
				b[t2len].lo = min(y, t);
				t2len++;
			}
			else {
				a[t1len].high = y;
				a[t1len].l = min(x, z);
				a[t1len].r = max(x, z);
				t1len++;
			}
		}
		for (int i = 0; i < t1len; ++i) {
			for (int j = i+1; j < t1len; ++j) {
				tmph = max(a[i].high, a[j].high);
				tmpl = min(a[i].high, a[j].high);
				tmpll = max(a[i].l, a[j].l);
				tmprr = min(a[i].r, a[j].r);
				if (tmpll >= tmprr) {
					continue;
				}
				num = 0;
				for (int t = 0; t < t2len; ++t) {
					if (b[t].dd > tmpll && b[t].dd < tmprr && b[t].hi > tmph && b[t].lo < tmpl) {
						num++;
					}
				}
				ans += num * (num-1) / 2;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}