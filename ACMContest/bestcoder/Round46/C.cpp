#include <cstdio>
#include <cstring>
#include <algorithm>
#define MOD 998244353
using namespace std;
typedef long long ll;
ll a[100010], n, ans;
ll pow_mod(ll a, ll b) {
	ll ret = 1;
	while (b > 0) {
		if (b & 1)
			ret = (ret * a) % MOD;
		b /= 2;
		a = a * a % MOD;
	}
	return ret;
}
int main() {
	ll T;
	scanf("%I64d", &T);
	while (T--) {
		scanf("%I64d", &n);
		for (ll i = 0; i < n; ++i)
			scanf("%d", &a[i]);
		ans = n % MOD;
		for (ll i = 0; i < n; ++i) {
			ans = ans * pow_mod(a[i], a[i] - 2);
		}
		printf("%I64d\n", ans);
	}
	return 0;
}