#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1000010;
ll a[64];
ll p[N];
ll len;
bool flag[N];
int ans[16];
int n;
void prime() {
	len = 0;
	for (ll i = 2; i < N; ++ i) {
		if (!flag[i]) {
			p[len ++] = i;
		}
		for (ll j = 0; j < len && i * p[j] < N; ++ j) {
			flag[i * p[j]] = true;
			if (i % p[j] == 0) break;
		}
	}
}
bool judge(ll x) {
	ll nw = 0;
	while (x) {
		a[nw] = x & 1;
		x >>= 1;
		nw ++;
	}
	for (ll i = 2; i <= 10; ++ i) {
		ll tmp = 0, fac = 1;
		for (int j = 0; j < n; ++ j) {
			tmp += a[j] * fac;
			fac *= i;
		}
		ans[i] = -1;
		for (ll j = 0; j < len; ++ j) {
			if (tmp % p[j] == 0) {
				if (tmp / p[j] > 1) {
					ans[i] = p[j];
					break;
				}
				else {
					return 0;
				}
			}
		}
		if (ans[i] == -1) {
			return 0;
		}
	}
	return 1;
}
int main() {
	int T, J;
	freopen("small.txt", "w", stdout);
	prime();
	//scanf("%d", &T);
	//scanf("%d%d", &N, &J);
	T = 1;
	n = 16;
	J = 50;
	T--;
	printf("Case #%d:\n", 1);
	ll base = (1u << (n - 1)) + 1;
	while (J) {
		if (judge(base)) {
			for (int i = n - 1; i >= 0; -- i) {
				printf("%lld", a[i]);
			}
			for (int i = 2; i <= 10; ++ i) {
				printf(" %lld", ans[i]);
			}
			puts("");
			J--;
		}
		/*
		printf("%u", base);
		for (int i = n; i >= 0; -- i) {
			printf("%u", a[i]);
		}
		puts("");
		*/
		base += 2;
	}
	return 0;
}