#include <cstdio>
#include <cstring>
#define MOD 1000000007
#define inv 500000004
using namespace std;
typedef long long ll;
bool used[128];
ll factor[128], f[128], ans, a[128], n;
ll dfs(ll x) {
	if (x > n)
		return 1;
	//printf("in-----------x=%I64d\n", x);
	ll num = 0, ret = 0;
	for (ll i = 1; i <= a[x]; ++i) {
		if (used[i]) {
			num++;
			continue;
		}
		if (a[x] == i) {
			used[a[x]] = true;
			ll tmp = dfs(x+1);
			//printf("tmp------%I64d\n", tmp);
			ans = (ans + (tmp * (i - num - 1)) % MOD) % MOD;
			ret = (tmp + ret) % MOD;
			//printf("xxxx%I64d %I64d %I64d\n", x, i, ans);
			continue;
		}
		ans = ((ans + f[n-x]) % MOD + (factor[n-x] * (i - num - 1)) % MOD) % MOD;
		ret = (factor[n-x] + ret) % MOD; 
		//printf("xxxx%I64d  %I64d %I64d -----f[n-x]%d\n", x, i, ans, f[n-x]);
	}
	return ret;
}
int main() {
	ll T;
	factor[0] = 1;
	for (ll i = 1; i <= 100; ++i)
		factor[i] = (factor[i-1] * i) % MOD;
	f[1] = 0; f[2] = 1;
	for (ll i = 3; i <= 100; ++i)
		f[i] = (((i * (i-1) * inv) % MOD * factor[i-1]) % MOD + (f[i-1] * i) % MOD) % MOD;
	//for (ll i = 1; i <= 10; ++i)
	//		printf("%d\n", f[i]);
	while (~scanf("%I64d", &n)) {
		memset(used, 0, sizeof(used));
		ans = 0;
		for (ll i = 1; i <= n; ++i)
			scanf("%I64d", &a[i]);
		dfs(1);
		ll tmp1 = 0;
		for (int i = 1; i <= n; ++i)
			for (int j = i+1; j <= n; ++j)
				if (a[i] > a[j])
					tmp1++;
		ans = ((ans - tmp1) % MOD + MOD) % MOD;
		printf("%I64d\n", ans);
	}
	return 0;
}