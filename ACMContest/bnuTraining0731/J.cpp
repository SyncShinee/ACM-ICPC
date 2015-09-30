#include <cstdio>
using namespace std;
typedef long long ll;
int main() {
	freopen("out.txt", "w", stdout);
	ll sum = 0;
	for (ll i = 1; i < 100000; ++i) {
		ll nxt, ans = 0;
		for (ll j = 1; j <= i; j = nxt + 1) {
			nxt = i / (i / j);
			ans += (i / j) * (nxt - j + 1);
		}
		sum += ans;
		printf("%lld %lld\n",i, sum);
	}
	return 0;
}