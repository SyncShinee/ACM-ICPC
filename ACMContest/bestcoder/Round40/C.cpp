#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
ll x1, y1, x2, y2, p, factor[100010];
ll ks(ll x, ll p) {
	ll ret = 1;
	ll po = p-2;
	while (po > 0) {
		if (po & 1) {
			ret = (ret * x) % p;
		}
		x = (x * x) % p;
		po /= 2;
	}
	return ret;
}

ll lucas(ll n, ll m, ll p) {
	if (n < m)
		return 0;
	if (n == m)
		return 1;
	ll ret = 1, a, b;
	while (n && m) {
		a = n % p;
		b = m % p;
		if (a < b)
			return 0;
		ret = (ret * factor[a] * ks((factor[b] * factor[a-b]) % p, p)) % p;
		n /= p;
		m /= p;
	}
	return ret;
}
int main() {
	while (~scanf("%I64d%I64d%I64d%I64d%I64d", &x1, &y1, &x2, &y2, &p)) {
		ll tmp = x2;
		if (tmp < y2)
			tmp = y2;
		factor[0] = 1;
		for (ll i = 1; i <= tmp+1; ++i)
			factor[i] = (factor[i-1] * i) % p;
		ll ans = 0;
		for (ll i = y1 + 1; i <= y2 + 1; ++i) {
			ans = ((ans + lucas(x2 + 1, i, p) - lucas(x1, i, p)) % p + p) % p;
			//printf("%I64d %I64d %I64d %I64d\n", i, x2+1, x1, ans);
		}
		printf("%I64d\n", ans);
	}
}