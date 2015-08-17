#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 128;
struct node {
    ll v;
    ll a[N], len;
};
bool operator < (const node &A, const node &B) {
    if (A.v < B.v) return true;
    if (A.v > B.v) return false;
    return true;
}
ll gcd(ll x, ll y) {
    return y == 0 ? x : gcd(y, x % y);
}
ll lcm(ll x, ll y) {
    if (y == 0) return x;
    if (x == 0) return y;
    return x * y / gcd(x, y);
}
node insert(const node &A, ll x) {
    node ret = A;
    ret.v = lcm(ret.v, x);
    ll pos = ret.len - 1;
    while (pos >= 0 && ret.a[pos] > x) {
        ret.a[pos + 1] = ret.a[pos];
        pos --;
    }
    pos ++;
    ret.a[pos] = x;
    ret.len ++;
    return ret;
}

node f[N][N];
int main() {
    ll T, n;
    node tmp;
    scanf("%lld", &T);
    f[0][0].v = f[0][0].len = 0;
    for (int i = 1; i <= 100; ++i)
        f[i][0] = insert(f[i][0], i);
    for (int i = 1; i <= 100; ++i) {
        for (int j = 1; j <= i; ++j)
            for (int t = j - 1; t < i; ++t) {
                tmp = insert(f[t][j - 1], i - t);
                f[i][j] = max(f[i][j], tmp);
            }
    }
    while (T --) {
        scanf("%lld", &n);
        node ans;
        ans.v = 0;
        for (int i = 0; i < n; ++i)
            ans = max(ans, f[n][i]);
        printf("%lld", ans.v);
        ll num = 0;
        for (ll i = 0; i < ans.len; ++ i) {
            for (ll j = num + 1; j <= num + ans.a[i]; ++ j) {
                printf(" %lld", j == num + ans.a[i] ? num + 1 : j + 1);
            }
            num += ans.a[i];
        }
        printf("\n");
    }
    return 0;
}