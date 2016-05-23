#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;
typedef long long ll;
const int N = 512;
const int M = 1024;
const ll INF = 1ll << 60;
int v[N], x[N], y[N], V;
ll w[N];
ll f[M];
int n, Less;
ll ans;
struct Point {
    ll x, y;
};
Point sta[M];
Point calc(int a, int b) {
    for (int i = 1; i <= n; ++ i) {
        w[i] = a * x[i] + b * y[i];
    }
    for (int i = 0; i <= V; ++ i) f[i] = INF;
    f[0] = 0;
    sta[0].x = sta[0].y = 0;
    for (int i = 1; i <= n; ++ i) {
        for (int j = V; j >= v[i]; -- j) {
            if (f[j - v[i]] == INF) continue;
            if (f[j] > f[j - v[i]] + w[i]) {
                f[j] = f[j - v[i]] + w[i];
                sta[j].x = sta[j - v[i]].x + x[i];
                sta[j].y = sta[j - v[i]].y + y[i];
            }
        }
    }
    Point mx; ll mf = INF;
    mx.x = mx.y = INF;
    for (int i = Less; i <= V; ++ i) {
        if (mf > f[i]) {
            mf = f[i];
            mx = sta[i];
        }
    }
    ans = min(ans, mx.x * mx.y);
    return mx;
}

ll cross(const Point &a, const Point &b, const Point &c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

void gao(const Point &a, const Point &b) {
    Point c = calc(a.y - b.y, b.x - a.x);
    if (cross(a, b, c) >= 0) return;
    gao(a, c), gao(c, b);
}

int main() {
    while (~scanf("%d%d", &n, &Less)) {
        ans = INF;
        V = 0;
        for (int i = 1; i <= n; ++ i) {
            scanf("%d%d%d", &v[i], &x[i], &y[i]);
            V += v[i];
        }
        Point a = calc(1, 0);
        Point b = calc(0, 1);
        gao(a, b);
        printf("%lld\n", ans);
    }
    return 0;
}
