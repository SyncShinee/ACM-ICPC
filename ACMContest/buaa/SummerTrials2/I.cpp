#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
int main() {
	//freopen("in.txt", "r", stdin);
    //freopen("my.out", "w", stdout);
	ll n, ans, tmp, cas = 0;
	while (~scanf("%I64d", &n)) {
		cas++;
		ans = 0;
		for (ll i = 1; i*i*i <= n; ++i) {
			ans++;
		}
		for (ll i = 1; i*i <= n; ++i) {
			tmp = n/i/i;
			if (tmp >= i) 
				ans += (tmp-1) * 3;
			else
				ans += tmp * 3;
		}
		for (ll i = 1; i*i*i <= n; ++i) {
			for (ll j = i+1; i*j*j <= n; ++j) {
				tmp = n/i/j;
				if (tmp > j)
					ans += 6*(tmp-j);
			}
		}
		printf("Case %I64d: %I64d\n", cas, ans);
	}
	return 0;
}