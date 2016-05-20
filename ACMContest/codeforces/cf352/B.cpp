#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
const int N = 500010;
ll sum, ave, rev;
ll a[N];
int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; ++ i) {
        scanf("%lld", &a[i]);
        sum += a[i];
    }
    ave = sum / n;
    rev = sum % n;
    sort(a, a + n);
    ll tmp = 0;
    for (int i = 0; i < n; ++ i) {
        if (a[i] > ave + (i >= n - rev ? 1 : 0)) {
            tmp += a[i] - (ave + (i >= n - rev ? 1 : 0));
        }
    }
    if (tmp <= k) {
        printf("%d\n", rev == 0 ? 0 : 1);
    }
    else {
        ll mn = 0, mx = 0;
        ll k1 = k;
        for (int i = 0; i < n - 1; ++ i) {
            if (k1 > (i + 1) * (a[i + 1] - a[i])) {
                k1 -= (i + 1) * (a[i + 1] - a[i]);
            }
            else {
                int t1 = k1 / (i + 1);
                mn = a[i] + t1;
                break;
            }
        }
        k1 = k;
        for (int i = n - 1; i > 0; -- i) {
            if (k1 > (n - i) * (a[i] - a[i - 1])) {
                k1 -= (n - i) * (a[i] - a[i - 1]);
            }
            else {
                int t1 = k1 / (n - i);
                mx = a[i] - t1;
                break;
            }
        }
        printf("%lld\n", mx - mn);
    }
    return 0;
}
