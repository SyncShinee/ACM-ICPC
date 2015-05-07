#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
ll f[2000010];
int main() {
	ll n, s1, v1, s2, v2, T, remain, ans, tmp, sum, ans1;
	scanf("%I64d", &T);
	for (ll cas = 1; cas <= T; ++cas) {
		ans = 0;
		scanf("%I64d%I64d%I64d%I64d%I64d", &n, &v1, &s1, &v2, &s2);
		if (v1 < 1000 && v2 < 1000 && n > v1 * v2) {
			memset(f, 0, sizeof(f));
			remain = n - v1 * v2;
			if (s1 * v2 > s2 * v1) {
				ans = (remain / v1) * s1;
				remain = remain % v1;
			}
			else {
				ans = (remain / v2) * s2;
				remain = remain % v2;
			}
			n = v1 * v2 + remain;
			for (int j = v1; j <= n; ++j)
				if (f[j] < f[j - v1] + s1)
					f[j] = f[j - v1] + s1;
			for (int j = v2; j <= n; ++j)
				if (f[j] < f[j - v2] + s2)
					f[j] = f[j -v2] + s2;
			printf("Case #%I64d: %I64d\n", cas, ans + f[n]);
		}
		else {
			sum = 0;
			if (v1 < v2) {
				ans1 = n / v1 * s1;
				while (n >= v2) {
					n -= v2;
					sum += s2;
					tmp = sum + n / v1 * s1;
					if (tmp > ans1)
						ans1 = tmp;
				}
			}
			else {
				ans1 = n / v2 * s2;
				while (n >= v1) {
					n -= v1;
					sum += s1;
					tmp = sum + n / v2 * s2;
					if (tmp > ans1)
						ans1 = tmp;
				}
			}
			printf("Case #%I64d: %I64d\n", cas, ans + ans1);
		}
	}
	return 0;
}