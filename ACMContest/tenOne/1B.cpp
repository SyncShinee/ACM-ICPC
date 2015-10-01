#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 100010;
int a[N], b[N];
int n;
int main() {
    freopen("in.txt", "r", stdin);
    while (~scanf("%d", &n)) {
        for (int i = 1; i <= n; ++ i) {
            scanf("%d", &a[i]);
        }
        int BASE = 1;
        long long ans = 0;
        for (int i = 1; i < 10; ++ i) {
            BASE *= 10;
            for (int i = 1; i <= n; ++ i) {
                b[i] = a[i] % BASE;
            }
            sort(b + 1, b + n + 1);
            int r = n;
            for (int i = 1; i <= n; ++ i) {
                while (r >= i && b[r] + b[i] >= BASE) {
                    r --;
                }
                if (r < i) ans += n - i;
                else ans += n - r;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}