#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>
using namespace std;
typedef long long ll;
const int N = 32;
const int MOD = 1e9 + 9.01;
int nn, C;
ll M;
int k[N], f[N];
struct matrix {
    int n, m;
    int a[N][N];
    matrix() {
        n = m = 0;
        memset(a, 0, sizeof a);
    }
    friend matrix operator * (matrix x, matrix y) {
        assert(x.m == y.n);
        matrix ret;
        ret.n = x.n;
        ret.m =y.m;
        for (int i = 1; i <= x.n; ++ i) {
            for (int j = 1; j <= x.m; ++ j) {
                for (int t = 1; t <= y.m; ++ t) {
                    ret.a[i][t] = (1ll * x.a[i][j] * y.a[j][t] % MOD + ret.a[i][t]) % MOD;
                }
            }
        }
        return ret;
    }
};
matrix power_mod(matrix fac, ll po) {
    matrix ret;
    ret.n = ret.m = fac.n;
    for (int i = 1; i <= ret.n; ++ i) {
        ret.a[i][i] = 1;
    }
    while (po) {
        if (po & 1ll) {
            ret = ret * fac;
        }
        fac = fac * fac;
        po >>= 1;
    }
    return ret;
}
int main() {
    scanf("%d%lld%d", &nn, &M, &C);
    for (int i = 1; i <= nn; ++ i) {
        scanf("%d", &f[i]);
    }
    for (int i = 1; i <= C; ++ i) {
        scanf("%d", &k[i]);
    }
    matrix ans;
    ans.n = 1;
    ans.m = nn;
    for (int i = 1; i <= nn; ++ i) {
        ans.a[1][i] = f[i];
    }
    matrix p;
    p.n = p.m = nn;
    for (int i = 1; i < nn; ++ i) {
        p.a[i + 1][i] = 1;
    }
    for (int i = 1; i <= C; ++ i) {
        p.a[nn + 1 - k[i]][nn] = 1;
    }
    p = power_mod(p, M - 1);
    ans = ans * p;
    printf("%d\n", ans.a[1][1]);
    return 0;
}