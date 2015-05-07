#include <cstdio>
#include <algorithm>
#include <cstring>
#define MOD 1000000007
using namespace std;
long long f[2048][2048], sum[2048][2048], ex[2048];
long long n, d, x, ans, tmp;
long long ks(long long x) {
	long long kk = MOD - 2;
	long long ret = 1;
	while (kk > 0) {
		if (kk & 1) {
			ret = (ret * x) % MOD;
		}
		x = (x * x) % MOD;
		kk >>= 1;
	}
	return ret;
}
int main() {
	freopen("std.txt", "w", stdout);
	for (long long i = 1; i < 2048; ++i) {
		ex[i] = ks(i);
	}
	while (scanf("%lld%lld%lld", &n, &d, &x), n+d+x > 0) {
		memset(f, 0, sizeof(f));
		memset(sum, 0, sizeof(sum));
		if (x == 1) {
			printf("0\n");
			continue;
		}
		for (long long i = 1; i <= min(x-1, n); ++i) {
			f[1][i] = 1;
			sum[1][i] = (f[1][i] + sum[1][i-1]) % MOD;
		}
		for (long long i = 2; i <= min(d, n); ++i)
			for (long long j = i; j <= min(n, i*(x-1)); ++j) {
				f[i][j] = ((sum[i-1][min(j-1, (i-1)*(x-1))] - sum[i-1][max(j-x, i-2)]) % MOD + MOD) % MOD;
				sum[i][j] = (f[i][j] + sum[i][j-1]) % MOD;
				//printf("%lld %lld %lld\n", i, j, f[i][j]);
			}
		ans = 0;
		for (long long i = (n+x-2)/(x-1); i <= min(d, n); ++i) {
			tmp = f[i][n];
			for (long long j = 1; j <= i; ++j){
				tmp = (tmp * ((d-j+1) % MOD)) % MOD;
				tmp = (tmp * ex[j]) % MOD;

			}
			//printf("%lld %lld\n",f[i][n], tmp);
			ans = (ans + tmp) % MOD;
		}
		printf("%lld\n", ans);
	}
	return 0;
}