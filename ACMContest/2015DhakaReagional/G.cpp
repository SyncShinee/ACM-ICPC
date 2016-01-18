#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
long long n, x, y, xmax, xmin, ymax, ymin, zmax, zmin;
struct Point {
    long long x, y;
}a, b, c, d, e, f;
int main() {
    int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; ++ cas) {
        scanf("%lld", &n);
        xmax = ymax = zmax = -1e5 - 7;
        xmin = ymin = zmin = 1e5 + 7;
        for (int i = 1; i <= n; ++ i) {
            scanf("%lld%lld", &x, &y);
            xmax = max(xmax, x);
            xmin = min(xmin, x);
            ymax = max(ymax, y);
            ymin = min(ymin, y);
            zmax = max(zmax, x + y);
            zmin = min(zmin, x + y);
        }
        a.x = xmax, a.y = ymin;
        b.x = xmax, b.y = zmax - xmax;
        c.x = zmax - ymax, c.y = ymax;
        d.x = xmin, d.y = ymax;
        e.x = xmin, e.y = zmin - xmin;
        f.x = zmin - ymin, f.y = ymin;
        printf("a:%lld %lld ##b: %lld %lld ##c: %lld %lld ##d: %lld %lld ##e: %lld %lld ##f: %lld %lld\n", a.x, a.y, b.x, b.y, c.x, c.y, d.x, d.y, e.x, e.y, f.x, f.y);
        long long dist = b.y - a.y;
        dist = max(dist, c.y - b.y);
        dist = max(dist, c.x - d.x);
        dist = max(dist, d.y - e.y);
        dist = max(dist, e.y - f.y);
        dist = max(dist, a.x - f.x);
        printf("%lld\n", dist);
        long long ans = (dist + 1) * dist * 3 + 1;
        printf("%lld\n", ans);
    }
    return 0;
}