#include <cstdio>
#include <algorithm>
using namespace std;
struct node {
	long long x, y;
}p[4096], x1, x2;
long long cross(node a, node b, node c) {
	return (a.x - c.x) * (b.y - c.y) - (a.y - c.y) * (b.x - c.x);
}
int main() {
	freopen("C-large-practice.in", "r", stdin);
	freopen("out.txt", "w", stdout);
	long long T, tmp1, tmp2, ans, n;
	scanf("%lld", &T);
	for (long long cas = 1; cas <= T; ++cas) {
		scanf("%lld", &n);
		for (long long i = 0; i < n; ++i) {
			scanf("%lld %lld", &p[i].x, &p[i].y);
		}
		printf("Case #%lld:\n", cas);
		for (long long i = 0; i < n; ++i) {
			ans = 3000;
			for (long long j = 0; j < n; ++j) {
				if (i == j)
					continue;
				tmp1 = tmp2 = 0;
				for (long long t = 0; t < n; ++t) {
					if (t == i || t == j)
						continue;
					if (cross(p[j], p[t], p[i]) < 0)
						tmp1++;
					else if (cross(p[j], p[t], p[i]) > 0)
						tmp2++;
				}
				ans = min (ans, tmp1);
				ans = min (ans, tmp2);
			}
			printf("%lld\n", ans);
		}
	}
	return 0;
}