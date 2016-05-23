#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long ll;
const int N = 100010;
ll a[N];
ll ans[N];
void gao(int l, int r) {
    int mx = l;
    for (int i = l + 1; i <= r; ++ i) {
        if (a[mx] < a[i]) mx = i;
    }
    int pl = mx, pr = mx;
    ll mn = a[mx];
    ans[1] = max(ans[1], a[mx] * a[mx]);
    while (pl > l || pr < r) {
        if (pl > l && pr < r) {
            if (a[pl - 1] < a[pr + 1]) {
                pr ++;
                mn = min(mn, a[pr]);
            } else {
                pl --;
                mn = min(mn, a[pl]);
            }
        } else if (pl > l) {
            pl --;
            mn = min(mn, a[pl]);
        } else {
            pr ++;
            mn = min(mn, a[pr]);
        }
        ans[pr - pl + 1] = max(ans[pr - pl + 1], a[mx] * mn);
    }
    if (mx > l) gao(l, mx - 1);
    if (mx < r) gao(mx + 1, r);
}
int main() {
    int n;
    while (~scanf("%d", &n)) {
        for (int i = 1; i <= n; ++ i) {
            scanf("%lld", &a[i]);
            ans[i] = 0;
        }
        gao(1, n);
        for (int i = 1; i <= n; ++ i) {
            printf("%lld\n", ans[i]);
        }
    }
    return 0;
}
