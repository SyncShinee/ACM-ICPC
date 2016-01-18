#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 256;
const int INF = 1e5 + 7;
int a[N][N];
int hs[N], hs_len;
int b[N][N];
int q, r, c, h;
int C[N];

int get_min(int x) {
    int ret = INF;
    while (x) {
        ret = min(ret, C[x]);
        x -= x & -x;
    }
    return ret;
}

void update(int x, int val) {
    while (x < hs_len) {
        C[x] = min(C[x], val);
        x += x & -x;
    }
}

int main() {
    int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; ++ cas) {
        printf("Case %d:\n", cas);
        scanf("%d%d", &r, &c);
        for (int i = 1; i <= r; ++ i) {
            for (int j = 1; j <= c; ++ j) {
                scanf("%d", &a[i][j]);
            }
        }
        scanf("%d", &q);
        while (q--) {
            scanf("%d", &h);
            for (int i = 1; i <= r; ++ i) {
                for (int j = 1; j <= c; ++ j) {
                    b[i][j] = a[i][j] >= h ? 1 : -1;
                }
            }
            for (int i = 1; i <= r; ++ i) {
                for (int j = 1; j <= c; ++ j) {
                    b[i][j] += b[i][j- 1];
                }
            }
            for (int i = 1; i <= r; ++ i) {
                for (int j = 1; j <= c; ++ j) {
                    b[i][j] += b[i - 1][j];
                }
            }
            int ans = 0;
            for (int i = 1; i <= r; ++ i) {
                for (int j = i; j <= r; ++ j) {
                    hs[1] = 0;
                    for (int t = 1; t <= c; ++ t) {
                        hs[t + 1] = b[j][t] - b[i - 1][t];
                    }
                    hs_len = c + 2;
                    sort(hs + 1, hs + hs_len);
                    hs_len = unique(hs + 1, hs + hs_len) - hs;
                    /*
                    printf("%d--- %d\n", i, j);
                    for (int t = 1; t < hs_len; ++ t) {
                        printf("%d%c", hs[t], " \n"[t == hs_len - 1]);
                    }
                    */
                    for (int t = 0; t < hs_len; ++ t) {
                        C[t] = INF;
                    }
                    update(lower_bound(hs + 1, hs + hs_len, 0) - hs, 0);
                    /*
                    for (int t = 1; t < hs_len; ++ t) {
                        printf("%d%c", get_min(t), " \n"[t == hs_len - 1]);
                    }
                    */
                    for (int t = 1; t <= c; ++ t) {
                        int nw = b[j][t] - b[i - 1][t];
                        int pos = lower_bound(hs + 1, hs + hs_len, nw) - hs;
                        //printf("%d get_min %d ==== %d\n", t, pos, get_min(pos));
                        ans = max(ans, (t - get_min(pos)) * (j - i + 1));
                        update(pos, t);
                    }
                    //printf("ans === %d\n", ans);
                }
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}