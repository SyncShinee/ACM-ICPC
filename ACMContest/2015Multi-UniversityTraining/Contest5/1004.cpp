#include <cstdio>
#include <cstring>
#define N 2048
#define MOD 258280327
using namespace std;
typedef long long ll;
int f[N][N], pw[N];

int quick_inverse(int n, int p) {
    int ret = 1;
    int exponent = p - 2;
    for (int i = exponent; i; i >>= 1, n = 1ll * n * n % p) {
        if (i & 1) {
            ret = 1ll * ret * n % p;
        }
    } 
    return ret;
}

int T, n, x, y, sum, invn, ans;

void solve1() {
    sum = 0;
    for (int i = 1; i <= n; ++i) sum = (sum + f[n][i]) % MOD;
    for (int i = 0; i < n; ++i) {
    	ans = 1ll * sum * invn % MOD;
    	printf("%d%c", ans, " \n"[i == n - 1]);
    	sum -= f[n][i + 1];
    	if (sum < 0) sum += MOD;
    }
}

void solve2() {
	for (int i = 0; i < n; ++i) {
        sum = 0;
        for (int j = i; j < n; ++j) {
            sum = (sum + f[j][i]) % MOD;
        }
        ans = 1ll * sum * pw[i] % MOD * invn % MOD;
        printf("%d%c", ans, " \n"[i == n - 1]);
    }
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &x, &y);
        invn = quick_inverse(n, MOD);
        int p = 1ll * x * quick_inverse(y, MOD) % MOD;
        p = MOD + 1 - p;
        pw[0] = 1;
        for (int i = 1; i <= n; ++i) pw[i] = 1ll * pw[i - 1] * p % MOD;
        memset(f, 0, sizeof f);
        f[0][0] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= i; ++j) {
                f[i][j] = 1ll * f[i - 1][j] * (MOD + 1 - pw[j]) % MOD;
                if (j > 0) f[i][j] = (f[i][j] + 1ll * f[i - 1][j - 1] * pw[j - 1] % MOD) % MOD;
             }
        }
        //solve1();
        solve2();
    }
    return 0;
}