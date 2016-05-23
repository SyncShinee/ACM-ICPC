#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 400;
const int INF = 1e5+7;
bool G[N][N];
int n, m, a[N], d[N], f[N][N];
int main() {
    int T;
    scanf("%d", &T);
    while (T --) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++ i) {
            scanf("%d", &a[i]);
        }
        for (int i = 0; i < m; ++ i) {
            scanf("%d", &d[i]);
        }
        memset(G, 0, sizeof G);
        for (int i = 1; i <= n; ++ i) {
            for (int j = i + 1; j <= n; ++ j) {
                for (int t = 0; t < m; ++ t) {
                    if (a[j] - a[i] == d[t]) {
                        G[i][j] = true;
                        break;
                    }
                }
            }
        }
        for (int i = n; i > 0; -- i) {
            for (int j = i; j <= n; ++ j) {
                if (i == j) {
                    f[i][j] = 1;
                    continue;
                }
                f[i][j] = INF;
                if (G[i][j]) {
                    if (i + 1 == j || !f[i + 1][j - 1]) {
                        f[i][j] = 0;
                        continue;
                    }
                }
                for (int k = i + 1; k < j; ++ k) {
                    if (G[i][k] && G[k][j] &&
                        a[j] - a[k] == a[k] - a[i]) {
                        if ((i + 1 == k || !f[i + 1][k - 1]) &&
                            (k + 1 == j || !f[k + 1][j - 1])) {
                            f[i][j] = 0;
                            break;
                        }
                    }
                }
                for (int k = i; k < j; ++ k) {
                    f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j]);
                }
            }
        }
        printf("%d\n", n - f[1][n]);
    }
    return 0;
}
