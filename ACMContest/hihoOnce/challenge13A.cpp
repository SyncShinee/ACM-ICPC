#include <cstdio>
#include <cstring>
#include <algorithm>
#define MOD 1000000007
using namespace std;
long long factor[512], invf[512], ans;
long long quick_inverse(long long n, long long p) {
	long long ret = 1;
	long long exponent = p - 2;
	for (long long i = exponent; i; i >>= 1, n = 1ll * n * n % p) {
		if (i & 1) {
			ret = 1ll * ret * n % p;
		}
	}
	return ret;
}

long long C(long long a, long long b) {
	return 1ll * factor[a] * invf[b] % MOD * invf[a - b] % MOD;
}

int main() {
	long long n, m, x, y;
	factor[0] = 1;
	for (int i = 1; i <= 500; ++i) {
		factor[i] = factor[i - 1] * i % MOD;
		//if (i < 10)printf("%lld\n", factor[i]);
	}
	invf[500] =  quick_inverse(factor[500], MOD);
	for (int i = 499; i >= 0; --i) {
		invf[i] = invf[i + 1] * (i + 1) % MOD;
	}
	while (~scanf("%lld%lld%lld%lld", &n, &m, &x, &y)) {
		ans = 0;
		for (long long i = 1; i <= n; ++i)
			for (long long j = 1; j <= m; ++j) {
				if (i == 1 || i == n || j == 1 || j == m) {
					ans = (ans + C(abs(y - j)+abs(x - i), abs(y - j))) % MOD;
				}
			}
		printf("%lld\n", (ans + MOD) % MOD);
	}
	return 0;
}