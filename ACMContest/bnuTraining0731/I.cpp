#include <cstdio>
#include <algorithm>
#define N 10010
using namespace std;
typedef long long ll;
ll inv[N];
ll C(ll a, ll b, ll p) {
	ll ret = 1;
	for (ll i = 1; i <= b; ++i) {
		ret = ret * (a - i + 1) % p * inv[i] % p;
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
		ret = ret * C(a, b, p) % p;
		n /= p;
		m /= p;
	}
	return ret;
}

int main() {
	ll ans, n, m, p;
	while (~scanf("%lld%lld%lld", &n, &m, &p)) {
		ans = 1;
		inv[1] = 1;
		for (ll i = 2; i <= min(m, p); ++i){
			inv[i] = (p - p / i) * inv[p % i] % p;
		}
		if (m >= p) {
			ans = lucas(n - m + 1, m, p);
		}
		else {
			ans = C(n - m + 1, m, p);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
