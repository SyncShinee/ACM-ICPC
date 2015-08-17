#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <map>
#include <set>
using namespace std;
typedef unsigned long long ll;
ll MOD = 3221225473llu;
ll ans, n, a[3000010], pos, num;
ll gcd(ll x, ll y) {
	return y == 0 ? x : gcd(y, x % y);
}
ll quick_inverse(ll n, ll p) {
	ll ret = 1;
	ll exponent = p - 2;
	for (ll i = exponent; i; i >>= 1, n = n * n % p) {
		if (i & 1) {
			ret = ret * n % p;
		}
	} 
	return ret;
}
ll lcm(ll x, ll y) {
	if(x == 0)return y;
	if (y == 0) return x;
	return x * y % MOD * quick_inverse(gcd(x, y), MOD) % MOD;
}

bool flag[3000010];
int main() {
	ll T;
	freopen("in.txt", "r", stdin);
	scanf("%I64u", &T);
	while (T--) {
		scanf("%I64u", &n);
		ans = 0;
		for (int i = 1; i <= n; ++i)
			scanf("%I64u", &a[i]);
		for (int i = 1; i <= n; ++i)
			flag[i] = 0;
		for (int i = 1; i <= n; ++i) {
			pos = i;
			num = 0;
			while (!flag[pos]) {
				flag[pos] = true;
				pos = a[pos];
				num++;
			}
			ans = lcm(ans, num);
		}
		printf("%I64u\n", ans);
	}
	return 0;
}