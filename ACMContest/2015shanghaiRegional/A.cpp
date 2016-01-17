#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

const double eps = 1e-6;
const double PI = acos(-1.0);

int dcmp(double x) {
    if(fabs(x) < eps)
        return 0;
    if(x > eps) {
        return 1;
    }
    return -1;
}

struct Point {
    double x, y;
    Point(double _x = 0, double _y = 0) {
        x = _x;
        y = _y;
    }
    Point operator + (const Point &b) const {
        return Point(x + b.x, y + b.y);
    }
    Point operator - (const Point &b) const {
        return Point(x - b.x, y - b.y);
    }
    double operator ^ (const Point &b) const {
        return x * b.y - y * b.x;
    }
    double operator * (const Point &b) const {
        return x * b.x + y * b.y;
    }
    double mo() {
        return sqrt(x * x + y * y);
    }
    Point operator * (double d) const {
        Point ans;
        ans.x = d * x;
        ans.y = d * y;
        return ans;
    }
};

double dist(Point a, Point b) {
    double ans = (a.x - b.x)*(a.x - b.x) + (a.y - b.y) * (a.y - b.y);
    ans = sqrt(ans);
    return ans;
}

Point th, a, b, c, d, v, goal;
double r;
struct PointX {
    Point a[4];
    int num;
};

PointX circle_cross_line(Point a, Point v, double r) {
    PointX res;
    double xa = a.x, ya = a.y;
    double dx = v.x, dy = v.y;
    double A = dx * dx + dy * dy, B = 2 * dx * xa + 2 * dy * ya, C = xa * xa + ya * ya - r * r;
    double delta = B * B - 4 * A * C;
    if(dcmp(delta) <= 0) {
        res.num = 0;
        return res;
    }
    else if(dcmp(delta) > 0) {
        res.num = 1;
        double t = (-B - sqrt(delta))/(2*A);
        if(dcmp(t) < 0) {
            res.num = 0;
            return res;
        }
        //printf("** %lf %lf %lf %lf %lf\n", a.x, a.y, b.x, b.y, t);
        res.a[0] = Point(xa + t * dx, ya + t * dy);
        return res;
    }
}

Point reflect(Point a, Point c, Point th) {
    Point dir;
    dir.x = -(c - th).y;
    dir.y = (c - th).x;
    double len = fabs(((a - c) * dir)/dir.mo());
    len *= 2;
    double tmp = dir.mo();
    tmp = len / tmp;
    Point ans1 = a + dir * tmp, ans2 = a - dir * tmp;
    // printf("11 is %f %f\n 22 is %f %f\n", ans1.x, ans1.y, ans2.x, ans2.y);
    if(dcmp(fabs((th - ans1) ^ (c - ans1)) - fabs((th - ans2) ^ (c - ans2))) >= 0 ) {
        return ans2;
    }
    else {
        return ans1;
    }
}

int onSeg(Point a, Point b, Point c) {
    double flag = (b - c) ^ (a - c);
    if(dcmp(flag) != 0)
    return 0;
    double t1, t2;
    t1 = c.x - a.x;
    t2 = b.x - a.x;
    double t3, t4;
    t3 = c.y - a.y;
    t4 = b.y - a.y;
    if(dcmp(t1 * t2) >= 0 && dcmp(t3 * t4) >= 0)
    return 1;
    return 0;
}

int onSegLine(Point a, Point b, Point p) {
    return dcmp((a - p) ^ (b - p)) == 0 && dcmp((p.x - a.x) * (p.x - b.x)) <= 0 && dcmp((p.y - a.y) * (p.y - b.y)) <= 0;
}

void solve() {
    b = b - th;
    goal = goal - th;
    th.x = 0;
    th.y = 0;
    a = b - v;
    PointX ans;
    ans = circle_cross_line(a, v, r);
    // printf("%d  %lf %lf", ans.num, ans.a[0].x, ans.a[0].y);
    if(ans.num == 0) {
        Point tmpa = b + v;
        if(onSeg(b, tmpa, goal)) {
            printf("Yes\n");
        }
        else {
            printf("No\n");
        }
    }
    else {
        if(onSegLine(b, ans.a[0], goal)) {
            // printf("dsfa");
            printf("Yes\n");
            return;
        }
        d = reflect(a, ans.a[0], th);
        // printf("%lf %lf\n", d.x, d.y);
        if(onSeg(ans.a[0], d, goal)) {
            printf("Yes\n");
            return;
        }
        printf("No\n");
    }
}
int main() {
    freopen("A.txt", "r", stdin);
    int ncase;
    scanf("%d", &ncase);
    for(int _ = 1; _ <= ncase; _++) {
        printf("Case #%d: ", _);
        scanf("%lf%lf%lf", &th.x, &th.y, &r);
        scanf("%lf%lf%lf%lf", &b.x, &b.y, &v.x, &v.y);
        scanf("%lf%lf", &goal.x, &goal.y);
        solve();
    }
    return 0;
}