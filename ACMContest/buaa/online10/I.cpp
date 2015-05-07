#include <cstdio>
#include <map>
#include <cstring>
using namespace std;
typedef long long ll;
map<ll, ll> f[20];
ll len, l, r, x;
int dig[20];
ll dp(ll pos, ll sta, ll lim, ll zero) {
	ll ans = 0;
	if (pos < 0 ) {
		//printf("%lld %lld %lld %lld %d\n", pos, sta, lim, zero, sta==1);
		if (zero)
			return 0;
		return sta == 1;
	}
	if (!lim && f[pos].count(sta) && !zero)
		return f[pos][sta];
	if (!zero) {
		int last = lim ? dig[pos] : 9;
		for (int i = 1; i <= last; ++i) {
			if (sta % i == 0) {
				if (i == dig[pos] && lim) {
					//printf("%lld %lld %lld %lld\n", pos-1, sta/i, 1, 0);
					ans += dp(pos-1, sta/i, 1, 0);
				}
				else {
					//printf("%lld %lld %lld %lld\n", pos-1, sta/i, 0, 0);
					ans += dp(pos-1, sta/i, 0, 0);
				}
			}
		}
	}
	else {
		ans += dp(pos-1, sta, 0, 1);
		for (int i = 1; i <= 9; ++i) {
			if (sta % i == 0) {
				//printf("%lld %lld %lld %lld\n", pos-1, sta/i, 0, 0);
				ans += dp(pos-1, sta/i, 0, 0);
			}
		}
	}
	//printf("%lld %lld %lld %lld %lld\n", pos, sta, lim, zero, ans);
	if (!lim && !zero)
		f[pos][sta] = ans;
	return ans;
}

ll solve(ll num) {
	if (num <= 0)
		return 0;
	len = 0;
	while (num > 0) {
		dig[len] = num % 10;
		num /= 10;
		len++;
	}
	//printf("%lld\n", len);
	return dp(len-1, x, 1, 0) + dp(len-2, x, 0, 1);
}
int main() {
	while (~scanf("%lld%lld%lld", &l, &r, &x)) {
			printf("%lld\n", solve(r) - solve(l-1));
	}
	return 0;
}
