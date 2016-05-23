#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
int n;
const int INF = 2e9+7;
vector <int> lis[20];
int a[20], p[20];
int f[20][70000][20];
int count(int x) {
    int ret = 0;
    while (x) {
        ret ++;
        x = x & (x - 1);
    }
    return ret;
}
int tt[20];
int main() {
    int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; ++ cas) {
        scanf("%d", &n);
        memset(tt, -1, sizeof tt);
        for (int i = 0; i < n; ++ i) {
            scanf("%d%d", &a[i], &p[i]);
            if (p[i] > -1) {
                tt[p[i]] = i;
            }
        }
        for (int i = 0; i <= n; ++ i) {
            lis[i].clear();
        }
        lis[0].push_back(0);
        for (int i = 1; i < (1 << n); ++ i) {
            lis[count(i)].push_back(i);
        }
        for (int i = 1; i <= n; ++ i) {
            for (int j = 0; j < (1 << n); ++ j) {
                for (int t = 0; t < n; ++ t) {
                    f[i][j][t] = -INF;
                } 
            }
        }
        for (int i = 1; i <= n; ++ i) {
            for (int j = 0; j < lis[i].size(); ++ j) {
                int sta = lis[i][j];
                for (int t = 0; t < n; ++ t) {
                    if (((1 << t) & sta) && (tt[i - 1] == -1 || tt[i - 1] == t)) {
                        if (i == 1) {
                            f[i][sta][t] = 0;
                            continue;
                        }
                        for (int k = 0; k < n; ++ k) {
                            if (k == t) continue;
                            if (((1 << k) & sta) && (tt[i - 2] == -1 || tt[i - 2] == k)) {
                                f[i][sta][t] = max(f[i][sta][t], f[i - 1][sta ^ (1 << t)][k] + a[k] * a[t]);
                            }
                        }
                    }
                }
            }
        }
        printf("Case #%d:\n", cas);
        int ans = f[n][(1 << n) - 1][0];
        for (int i = 0; i < n; ++ i) {
            ans = max(ans, f[n][(1 << n) - 1][i]);
        }
        printf("%d\n", ans);
    }
    return 0;
}
