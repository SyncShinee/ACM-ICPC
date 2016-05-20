#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
const int N = 100010;
const double EPS = 1e-9;
int n;
int px[N], py[N];
struct node {
    int id;
    double dis;
}a[N], b[N];
bool operator < (const node &A, const node &B) {
    return A.dis > B.dis;
}
double dist (double a, double b, double c, double d) {
    return sqrt((a - c) * (a - c) + (b - d) * (b - d));
}
int main() {
    int ax, ay, bx, by, tx, ty;
    scanf("%d%d%d%d%d%d", &ax, &ay, &bx, &by, &tx, &ty);
    scanf("%d", &n);
    double ans = 0.0;
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d", &px[i], &py[i]);
        a[i].id = b[i].id = i;
        ans += 2.0 * dist(tx, ty, px[i], py[i]);
        a[i].dis = dist(tx, ty, px[i], py[i]) - dist(ax, ay, px[i], py[i]);
        b[i].dis = dist(tx, ty, px[i], py[i]) - dist(bx, by, px[i], py[i]);
    }
    sort(a, a + n);
    sort(b, b + n);
    if (a[0].dis < -EPS && b[0].dis < -EPS) {
        ans -= max(a[0].dis, b[0].dis);
    }
    else {
        if (a[0].id != b[0].id) {
            ans -= max(a[0].dis, 0.0);
            ans -= max(b[0].dis, 0.0);
        }
        else {
            if (a[0].dis < -EPS) {
                ans -= b[0].dis;
            }
            else if (b[0].dis < -EPS) {
                ans -= a[0].dis;
            }
            else {
                if (n == 1) {
                    ans -= max(a[0].dis, b[0].dis);
                }
                else {
                    double tmp1 = a[0].dis + max(b[1].dis, 0.0);
                    double tmp2 = b[0].dis + max(a[1].dis, 0.0);
                    ans -= max(tmp1, tmp2);
                }
            }
        }
    }
    printf("%.10f\n", ans);
    return 0;
}

