#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;

const int N = 20000001;

int main() {
    int n;
    while (scanf("%d", &n), n) {
        ll ans = 0;
        int nxt;
        for (int i = 1; i <= n; i = nxt + 1) {
            nxt = n / (n / i);
            ans += 1ll * (i + nxt)* (nxt - i + 1) / 2 * (n / i);
        }
        ans--;
        printf("%lld\n", ans);
    }
    return 0;
}
