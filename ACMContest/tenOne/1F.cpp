#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 100010, M = 10005, BASE = 10000;
int a[N << 1], b[N];
int C[M];
int get_max(int x){
    x ++;
    int ret = 0;
    while (x) {
        ret = max(ret, C[x]);
        x -= x & -x;
    }
    return ret;
}
void update(int x, int val) {
    x ++;
    while (x < M) {
        C[x] = max(C[x], val);
        x += x & -x;
    }
}
int ans1[N], ans2[N], ans;
int n;
int main() {
    freopen("in.txt", "r", stdin);
    while (~scanf("%d", &n)) {
        for (int i = 1; i <= n; ++ i) {
            scanf("%d", &a[i]);
            a[i + n]= a[i];
        }
        ans = BASE;
        for (int t = 1; t <= n; ++ t){
            if (a[t] != BASE) continue;
            for (int i = 1; i < n; ++ i) {
                b[i] = a[i + t];
            }
            memset(C, 0, sizeof C);
            ans1[0] = ans1[n] = ans2[0] = ans2[n] = 0;
            for (int i = 1; i < n; ++ i) {
                if (b[i] == BASE)  {
                    ans1[i] = 0;
                    continue;
                }
                ans1[i] = get_max(BASE - b[i]) + b[i];
                update(BASE - b[i], ans1[i]);
            }
            for (int i = 1; i < n; ++ i) {
                ans1[i] = max(ans1[i], ans1[i - 1]);
            }
            memset(C, 0, sizeof C);
            for (int i = n - 1; i > 0; -- i) {
                if (b[i] == BASE) {
                    ans2[i] = 0;
                    continue;
                }
                ans2[i] = get_max(BASE - b[i]) + b[i];
                update(BASE - b[i], ans2[i]);
            }
            for (int i = n - 1; i > 0; -- i) {
                ans2[i] = max(ans2[i], ans2[i + 1]);
            }
            for (int i = 1; i <= n; ++ i) {
                ans = max(ans, BASE + ans1[i - 1] + ans2[i]);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}