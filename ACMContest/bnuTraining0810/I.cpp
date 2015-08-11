#include <cstdio>
#include <algorithm>
using namespace std;
const int MOD = 1000000007;
int f[2][5010], sum[2][5010], n;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		f[1][i] = 1;
		sum[1][i] = sum[1][i - 1] + f[1][i];
	}
	for (int i = 2; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			f[i & 1][j] = (sum[(i - 1) & 1][j] - sum[(i - 1) & 1][i - 1] + MOD) % MOD;
			f[i & 1][j] = (f[i & 1][j] + 1ll * f[(i - 1) & 1][j] * (j - 1) % MOD) % MOD;
			sum[i&1][j] = (sum[i & 1][j - 1] + f[i & 1][j]) % MOD;
		}
	printf("%d\n", f[n & 1][n]);
	return 0;
}