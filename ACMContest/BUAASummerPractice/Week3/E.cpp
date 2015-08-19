#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
const int N = 256;
#define  EPS  1e-5
int n;
struct point {
    double x, y;
}p[N], p1, p2;
double  ans;
int r;
double calc(double x) {
    double xk = r * cos(x), yk = r * sin(x);
    double a = sqrt((p1.x - xk) * (p1.x - xk) + (p1.y - yk) * (p1.y - yk));
    double b = sqrt((p2.x - xk) * (p2.x - xk) + (p2.y - yk) * (p2.y - yk));
    double c = sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    return acos((a * a + b * b - c * c) / (2 * a * b));
}
double solve(int i, int j) {
    p1 = p[i], p2 = p[j];
    point pl, pr, pt;
    double dy = p1.y - p2.y, dx = p1.x - p2.x, a, b, c, derta, ml, mr, tmp, mid1, mid2;
    a = dx * dx + dy * dy;
    b = 2.0 * dy * p2.y + 2.0 * dx * p2.x;
    c = p2.x * p2.x + p2.y * p2.y - r * r;
    derta = sqrt(b * b - 4 * a * c);
    pt.x = (-b - derta) / 2.0 / a; pt.y = (-b + derta) / 2.0 / a;
    pl.x = p2.x + pt.x * dx; pl.y = p2.y + pt.x * dy;
    pr.x = p2.x + pt.y * dx; pr.y = p2.y + pt.y * dy;
    ml = asin(pl.y / r); mr = asin(pr.y / r);
    if (pl.x < 0) {
        ml = M_PI - ml;
    }
    if (pr.x < 0) {
        mr = M_PI - mr;
    }
    if (ml > mr) {
        swap(ml, mr);
    }
    if (mr - ml > M_PI) {
        ml += 2 * M_PI;
        swap(ml, mr);
    }
    while(ml + EPS < mr) {
        tmp = (mr - ml) / 3.0;
        mid1 = ml + tmp;
        mid2 = mr - tmp;
        calc(mid1) < calc(mid2) ? ml = mid1 : mr = mid2;
    }
    return calc(ml);
}
int main() {
    while (~scanf("%d%d", &n, &r)) {
        ans = 0;
        for (int i = 1; i <= n; ++ i) {
            scanf("%lf%lf", &p[i].x, &p[i].y);
        }
        for (int i = 1; i <= n; ++ i) {
            for (int j = i + 1; j <= n; ++ j) {
                ans = max(ans, solve(i, j));
            }
        }
        printf("%.10lf\n", ans);
    }
    return 0;
}