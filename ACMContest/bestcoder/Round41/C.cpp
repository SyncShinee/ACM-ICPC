#include <cstdio>
#include <cstring>
#define N 100010
#define MOD  998244353
using namespace std;
typedef long long ll;
ll f[2][N], ans;
int main() {
	int T, n, c, l, r;
	scanf("%d", &T);
	while (T--) {
		memset(f, 0, sizeof(f));
		scanf("%d %d %d %d", &n, &c, &l, &r);
		f[0][0] = 1;
		ans = 0;
		l -= c;
		r -= c;
		for (int i = 1; i * (i - 1) / 2 <= n; ++i) {
			for (int j = i*(i + 1) / 2; j <= n; ++j) {
				f[i & 1][j] = f[(i-1) & 1][j - i];
				if (j >= i * (3 + i) / 2)
					f[i & 1][j] = (f[i & 1][j] + f[i & 1][j - i]) % MOD;
				if (j <= r && j >= l)
					ans = (ans + f[i & 1][j]) % MOD;
			}
		}
		if (l == 0) ans = (ans + 1) % MOD;
		printf("%I64d\n", ans);
	}
	return 0;
}