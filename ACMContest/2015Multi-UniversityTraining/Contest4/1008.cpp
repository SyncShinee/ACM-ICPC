#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#define N 100010
using namespace std;
typedef long long ll;
ll a[N], k;
int main() {
	for (ll i = 1; i <= 100000; ++i) {
		a[i] = i * (i + 1) / 2;
	}
	while (~scanf("%I64d", &k)) {
		if (k <= 100000) {
			printf("%d\n", k);
			for (ll i = 1; i <= k; ++i) {
				printf("1%c", i == k ? '\n' : ' ');
			}
			continue;
		}
		ll n = lower_bound(a + 1, a + 100000, k) - a;
		ll remain = a[n] - k;
		if (remain == 0) {
			printf("%I64d\n", n);
			for (ll i = 1; i <= n; ++i) 
				printf("%I64d%c", i, i == n ? '\n' : ' ');
			continue;
		}
		ll newn = lower_bound(a + 1, a + n, remain) - a;
		if (a[newn] == remain) {
			printf("%I64d\n", n);
			for (ll i = 1; i <= newn + 1; ++i) {
				printf("1%c", i == n ? '\n' : ' ');
			}
			for (ll i = newn + 2; i <= n; ++i) {
				printf("%I64d%c", i, i == n ? '\n' : ' ');
			}
			continue;
		}
		else {
			ll flag = 0;
			for (ll i = 1; i < newn; ++i) {
				ll k1 = remain - a[i], pos = lower_bound(a, a + newn, k1) - a;
				if (k1 < 0)
					break;
				if (a[pos] == k1) {
					flag = 1;
					printf("%I64d\n", n);
					//printf("---%I64d %I64d %I64d\n", i, j, pos1);
					for (ll j = 1; j <= i + 1; ++j) {
						printf("1 ");
					}
					for (ll j = i + 2; j <= i + pos + 2; ++j) {
						printf("2%c", j == n ? '\n' : ' ');
					}
					for (ll j = i + pos + 3; j <= n; ++j) {
						printf("%I64d%c", j, j == n ? '\n' : ' ' );
					}
					break;
				}
			}
			if (flag) {
				continue;
			}
			for (ll i = 1; i < newn; ++i) {
				if (flag) {
					break;
				}
				if (remain - a[i] < 0)
					continue;
				for (ll j = i; j < newn; ++j) {
					ll k2 = remain - a[i] - a[j];
					if (k2 < 0) {
						continue;
					}
					ll pos1 = lower_bound(a, a + newn, k2) - a;
					if (a[pos1] == k2) {
						flag = 1;
						printf("%I64d\n", n);
						//printf("---%I64d %I64d %I64d\n", i, j, pos1);
						for (ll t = 1; t <= i + 1; ++t) {
							printf("1 ");
						}
						for (ll t = i + 2; t <= i + j + 2; ++t) {
							printf("2 ");
						}
						for (ll t = i + j + 3; t <= i + j + pos1 + 3; ++t) {
							printf("3%c", t == n ? '\n' : ' ');
						}
						for (ll t = i + j + pos1 + 4; t <= n; ++t) {
							printf("%I64d%c", t, t == n ? '\n' : ' ' );
						}
						break;
					}
				}
			}
		}
	}
	return 0;
}