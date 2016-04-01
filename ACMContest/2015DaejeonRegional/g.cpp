#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const int maxn = 2e5 + 100;
const double eps = 1e-8;
int dcmp(double x) {
    if(fabs(x) < eps)
    return 0;
    if(x > 0)
    return 1;
    return -1;
}

struct Point {
    double x, y, len;
    int id;
    int tag;
    Point(double _x = 0, double _y = 0, double _len = 0, int _tag = 0, int _id = 0) {
        x = _x;
        y = _y;
        len = _len;
        tag = _tag;
        id = _id;
    }
    double operator ^ (const Point &b) const {
        double t;
        t = x * b.y - y * b.x;
        return t;
    }
    Point operator - (const Point &b) const {
        Point t;
        t.x = x - b.x;
        t.y = y - b.y;
        return t;
    }
};

double dist(Point a, Point b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}
Point p[maxn];
int n, pn;
Point s[maxn];
int st;
int can[maxn];

int cmp(Point a, Point b) {
    if(dcmp(a.x - b.x) == 0) {
        if(a.id == b.id) {
            if(can[a.id] == 1)
            return a.y < b.y;
            return a.y > b.y;
        }
        return a.id > b.id;
    }
    return a.x < b.x;
}
int check(Point a, Point b, Point c) {
    Point t1 = b - a, t2 = c - b;
    if(dcmp(t1 ^ t2) <= 0)
    return 0;
    return 1;
}

void solve(double ans) {
    sort(p + 1, p + pn, cmp);
    s[0] = p[0];
    st = 0;
    for(int i = 1; i < pn; i++) {
        while(st >= 1 && check(s[st - 1], s[st], p[i]) == 0) {
            st--;
        }
        double t =  dist(p[i], s[st]) + s[st].len;
    if(p[i].tag == 1) {
        //printf("%f  %f   %f  %f\n", p[i].x, p[i].y, s[st].x, s[st].y);
        ans += t;
    }
        st++;
        s[st] = p[i];
        s[st].len = t;
    }
    printf("%.1f\n", ans);
}

int main() {
    freopen("g.txt", "r", stdin);
    int ncase;
    scanf("%d", &ncase);
    while(ncase--) {
        double ans = 0;
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            scanf("%lf %lf", &p[i].x, &p[i].y);
            p[i].tag = 0;
            p[i].id = i;
        }
        for(int i = 0; i < n; i++) {
            if(i % 2 == 1) {
                if(dcmp(p[(i + 1) % n].y - p[i].y) < 0)
                can[i] = 1;
                else
                can[i] = -1;
            }
        }
        pn = n;
        int m;
        scanf("%d", &m);
        int cnt = 0;
        for(int i = 0; i < m; i++) {
            int k;
            double d;
            scanf("%d %lf", &k, &d);
            if(k == 0) {
                ans += d;
                continue;
            }
            if(k % 2 == 0) {
                p[pn + cnt].y = p[k].y;
                p[pn + cnt].x = p[k].x + dcmp(p[(k + 1) % pn].x - p[k].x) * d;
            }
            else {
                p[pn + cnt].x = p[k].x;
                p[pn + cnt].y = p[k].y + dcmp(p[(k + 1) % pn].y - p[k].y) * d;
            }
            p[pn + cnt].tag = 1;
            p[pn + cnt].id = k;
            cnt++;
        }
        pn = n + cnt;
        solve(ans);
    }
    return 0;
}