#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define FI first
#define SE second
using namespace std;
const int INF = 1e9+7;
const int N = 1000010;
pair <int, int> P[N];
int n, m;
bool check(int x) {
    int x1 = -INF, x2 = INF, y1 = -INF, y2 = INF;
    for (int i = 0; i < m; ++ i) {
        int l = P[i].FI, r = P[i].SE;
        if (l > r) swap(l, r);
        if (r - l <= x) continue;
        x1 = max(x1, l + r - x);
        x2 = min(x2, l + r + x);
        y1 = max(y1, l - r - x);
        y2 = min(y2, l - r + x);
    }
    x2 = min(x1 + 1, x2);
    y2 = min(y1 + 1, y2);
    for (int i = y1; i <= y2; ++ i) {
        for (int j = x1; j <= x2; ++ j) {
            if (!((i + j) & 1)) return 1;
        }
    }
    return 0;
}
int main() {
    while (~scanf("%d%d", &n, &m)) {
        for (int i = 0; i < m; ++ i) {
            scanf("%d%d", &P[i].FI, &P[i].SE);
        }
        int l = 0, r = n - 1, mid;
        while (l <= r) {
            mid = l + r >> 1;
            if (check(mid)) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        printf("%d\n", l);
    }
    return 0;
}
