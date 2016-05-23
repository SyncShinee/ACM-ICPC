#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, m, num;
const int MOD = 1000000007;
ll dp[17][70000];
ll f[17][17];
ll g[17][17];
ll ans[17][17];
int path[2100000][2];
int _m;
void dfs(int l, int now, int pre) {
    if (l > _m) return;
    if (l == _m) {
        path[num][0] = pre;
        path[num++][1] = now;
        return;
    }
    dfs(l + 2, (now << 2) | 3, (pre << 2) | 3);
    dfs(l + 1, (now << 1) | 1, (pre << 1));
    dfs(l + 1, now << 1, (pre << 1) | 1);
}
int main() {
    while (~scanf("%d%d", &n, &m)) {
        if (n < m) swap(n, m);
        _m = m;
        for (_m = 1; _m <= m; ++ _m) {
            num = 0;
            dfs(0, 0, 0);
            memset(dp, 0, sizeof dp);
            dp[0][(1 << _m) - 1] = 1;
            for (int i = 0; i < n; ++ i) {
                for (int j = 0; j < num; ++ j) {
                    dp[i + 1][path[j][1]] = (dp[i + 1][path[j][1]] + dp[i][path[j][0]]) % MOD;
                }
            }
            for (int i = 1; i < _m; ++ i) {
                f[i][_m] = f[_m][i];
            }
            for (int i = _m; i <= n; ++ i) {
                f[i][_m] = dp[i][(1 << _m) - 1];
            }
        }
        memset(g, 0, sizeof g);
        for (int i = 0; i < (m - 1); ++ i) log2[1 << i] = i;
        for (int mask = 0; mask < (1 << (m - 1)); ++ mask) {
            int sgn = (CountOne(mask) & 1) ? -1 : 1, delta = 0;
            for (int x1 = 0; x1 < n; ++ x1)
                for (int x2 = x1; x2 < n; ++ x2) {
                    t[x1][x2] = 1;
                    int now = mask, p, las = -1;
                    while (now) {
                        p = now & -now;
                        now -= p;
                        p = log2[p];
                        t[x1][x2] = ((long long)t[x1][x2] * s[x1][las + 1][x2][p]) % kMod;
                        las = p;
                    }
                    t[x1][x2] = ((long long)t[x1][x2] * s[x1][las + 1][x2][m - 1]) % kMod;    
                }
            f[0] = t[0][0];
            for (int i = 1; i < n; ++ i) {
                f[i] = t[0][i];
                for (int j = 0; j < i; ++ j) {
                    int d = ((long long)f[j] * t[j + 1][i]) % kMod;
                    UPT(f[i], -d);
                }
            }
            delta = sgn * f[n - 1];
            UPT(ans, delta);
        }
        printf("%lld\n", ans[n][m]);
    }
}
