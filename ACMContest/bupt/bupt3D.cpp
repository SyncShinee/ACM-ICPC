#include<cstdio>
#include<cmath>
using namespace std;
typedef long long ll;
ll qpow(ll bottom, int exp, int MOD) {
	ll ans = 1;
	while (exp > 0) {
		if ((exp & 1) == 1)
			ans = (ans * bottom) % MOD;
		bottom = (bottom * bottom) % MOD;
		exp >>= 1;
	}
	return ans;
}
int main() {
	int T, n;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		printf("%lld\n", qpow(4, n-1, 1000000007));
	}
	return 0;
}