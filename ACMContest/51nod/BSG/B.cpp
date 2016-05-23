#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cmath>
using namespace std;
typedef long long ll;
ll f[2048][20];
const int MOD = 1000000007;
int fi[20];
int po[20];
int main() {
    int n;
    scanf("%d", &n);
    f[1][1] = 1;
    f[0][0] = 1;
    fi[0] = 0, fi[1] = 1;
    for (int i = 2; i < 20; ++ i) {
        fi[i] = fi[i - 1] + fi[i - 2] + 1;
        //printf("%d -- %d\n",i, fi[i]);
    }
    po[0] = 0;
    po[1] = 1;
    for (int i = 2; i < 20; ++ i) {
        po[i] = ((po[i - 1] + 1) << 1) - 1;
        //printf("%d---%d\n", i, po[i]);
    }
    for (int i = 2; i <= n; ++ i) {
        int mx = upper_bound(fi, fi + 20, i) - fi;
        mx --;
        int mn = lower_bound(po, po + 20, i) - po;
        //printf("%d ---%d %d\n", i, mn, mx);
        for (int j = mn; j <= mx; ++ j) {
            int t1 = j - 1, t2 = j - 2;
            for (int nl = fi[t1]; nl <= po[t1] && i - 1 - nl >= 0; ++ nl) {
                //printf("%d %d\n", nl, t1);
                f[i][j] = (f[nl][t1] * f[i - 1 - nl][t2] % MOD + f[i][j]) % MOD;
                //printf("%d %d %d\n", f[nl][t1], f[i - 1 - nl][t2], f[i][j]);
            }
            t1 = j - 2, t2 = j - 1;
            for (int nl = fi[t1]; nl <= po[t1] && i - 1 - nl >= 0; ++ nl) {
                //printf("%d %d\n", nl, t1);
                f[i][j] = (f[i][j] + f[nl][t1] * f[i - 1 - nl][t2] % MOD) % MOD;
            }
            t1 = j - 1, t2 - j - 1;
            for (int nl = fi[t1]; nl <= po[t1] && i - 1 - nl >= 0; ++ nl) {
                //printf("%d %d\n", nl, t1);
                f[i][j] = (f[i][j] + f[nl][t1] * f[i - 1 - nl][t2] % MOD) % MOD;
            }
            
        }
        //printf("$$$$$$$$$$$%d\n", f[2][2]);
    }
    ll ans = 0;
    for (int i = 0; i < 20; ++ i) ans = (ans + f[n][i]) % MOD;
    int _ans = ans;
    printf("%d\n", _ans);
    return 0;
}
