#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 100010;
const int MOD = 1000000007;
ll inv[N];
void get_inverse(ll n, ll p) {
    inv[1] = 1;
    for (ll i = 2; i <= n; ++i) {
        inv[i] = (p - p / i) * inv[p % i] % p;
    }
}
int main() {
    int n, m;
    get_inverse(N, MOD);
    while (~scanf("%d%d", &n, &m)) {
        n -= 2;
        m -= 2;
        ll cn = 1, cm = 1;
        ll ans = 1;
        int len = min(n, m);
        for (int i = 1; i <= len; ++ i) {
            cn = cn * (n - i + 1) % MOD * inv[i] % MOD;
            cm = cm * (m - i + 1) % MOD * inv[i] % MOD;
            ans = (ans + cn * cm % MOD) % MOD;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
