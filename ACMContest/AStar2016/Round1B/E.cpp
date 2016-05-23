#include <cstdio>
#include <algorithm>
#include <cstring>
#define lson l, mid, rt << 1
#define rson mid + 1, r, rt << 1 | 1
#define FI first
#define SE second
using namespace std;
const int N = 100010;
typedef long long ll;
pair <int, int> line[N];
ll a[N];
int T[N << 2];
void build(int l, int r, int rt) {
    T[rt] = 0;
    if (l == r) return;
    int mid = l + r >> 1;
    build(lson);
    build(rson);
}
void pushup(int rt) {
    T[rt] = T[rt << 1] + T[rt << 1 | 1];
}
void update(int x, int l, int r, int rt) {
    if (l == r && l == x) {
        T[rt] ++;
        return;
    }
    int mid = l + r >> 1;
    if (x <= mid) {
        update(x, lson);
    } else {
        update(x, rson);
    }
    pushup(rt);
}
int query(int k, int l, int r, int rt) {
    //printf("%d %d %d\n", T[rt], l, r);
    if (T[rt] < k) {
        return -1;
    }
    if (l == r) {
        return l;
    }
    int mid = l + r >> 1;
    if (T[rt << 1 | 1] < k) {
        return query(k - T[rt << 1 | 1], lson);
    }
    return query(k, rson);
}
int main() {
    int n, k, m;
    while (~scanf("%d%d%d", &n, &k, &m)) {
        a[0] = 0;
        for (int i = 1; i <= n; ++ i) {
            scanf("%lld", &a[i]);
            a[i] += a[i - 1];
        }
        for (int i = 0; i < m; ++ i) {
            scanf("%d%d", &line[i].FI, &line[i].SE);
        }
        sort(line, line + m);
        build(1, n, 1);
        ll ans = 0;
        for (int i = 0; i < m; ++ i) {
            update(line[i].SE, 1, n, 1);
            int r = query(k, 1, n, 1);
            //printf("%d\n", r);
            if (line[i].FI <= r) {
                ans = max(ans, a[r] - a[line[i].FI - 1]);
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
