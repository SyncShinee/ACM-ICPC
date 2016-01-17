#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
char s[100010];
ll llen[100010], rlen[100010];
ll lsum[100010], rsum[100010];
int main() {
    int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; ++ cas) {
        scanf("%s", s);
        int len = strlen(s);
        llen[0] = 1;
        lsum[0] = 1;
        for (int i = 1; i < len; ++ i) {
            if (s[i] == s[i - 1]) {
                llen[i] = llen[i - 1] + 1;
                lsum[i] = lsum[i - 1] - llen[i - 1] * llen[i - 1] + llen[i] * llen[i];
            }
            else {
                llen[i] = 1;
                lsum[i] = lsum[i - 1] + 1;
            }
        }
        rlen[len - 1] = 1;
        rsum[len - 1] = 1;
        for (int i = len - 2; i >= 0; -- i) {
            if (s[i] == s[i + 1]) {
                rlen[i] = rlen[i + 1] + 1;
                rsum[i] = rsum[i + 1] - rlen[i + 1] * rlen[i + 1] + rlen[i] * rlen[i];
            }
            else {
                rlen[i] = 1;
                rsum[i] = rsum[i + 1] + 1;
            }
        }
        ll ans = rsum[0];
        for (int i = 0; i < len; ++ i) {
            ll tmp = 0;
            ll ll, rr;
            if (i > 0) {
                if (s[i] != s[i - 1]) {
                    ll = llen[i - 1] + 1;
                    if (i - 1 - llen[i - 1] >= 0)
                    tmp += lsum[i - 1 - llen[i - 1]];
                }
                else {
                    ll = 1;
                    tmp += lsum[i - 1];
                }
            }
            else {
                ll = 1;
            }
            if (i < len - 1) {
                if (s[i] != s[i + 1]) {
                    rr = rlen[i + 1] + 1;
                    if (i + 1 + rlen[i + 1] < len)
                    tmp += rsum[i + 1 + rlen[i + 1]];
                }
                else {
                    rr = 1;
                    tmp += rsum[i + 1];
                }
            }
            else {
                rr = 1;
            }
            tmp += (rr + ll - 1) * (rr + ll - 1);
            ans = max(ans, tmp);
        }
        printf("Case #%d: %lld\n", cas, ans);
    }
    return 0;
}