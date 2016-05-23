#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
ll x, m, k, c;

ll tag[10010];
int main() {
    int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; ++ cas) {
        scanf("%lld%lld%lld%lld", &x, &m, &k, &c);
        ll p = 1, pn = 0;
        memset(tag, -1, sizeof tag);
        while (tag[p] == -1) {
            tag[p] = pn;
            p = p * 10 % k;
            pn ++;
        }
        ll beg = tag[p];
        ll num = pn - tag[p];
        ll ans = 0;
        ll pk = 1;
        for (ll i = 0; i < beg; ++ i) {
            ans = (ans + pk) % k;
            pk = pk * 10 % k;
            m --;
            if (m == 0) break;
        }
        ll mm = m / num;
        ll nn = m % num;
        //printf("%d %d\n", num, nn);
        ll cyc = 0;
        p = pk;
        for (ll i = 0; i < num; ++ i) {
            cyc = (cyc + pk) % k;
            pk = pk * 10 % k;
        }
        for (ll i = 0; i < nn; ++ i) {
            ans = (ans + p) % k;
            p = p * 10 % k;
        }
        ans = (ans + mm * cyc % k) % k;
        ans = ans * x % k;
        printf("Case #%d:\n", cas);
        if (ans == c % k) {
            puts("Yes");
        } else {
            puts("No");
        }
    }
    return 0;
}
