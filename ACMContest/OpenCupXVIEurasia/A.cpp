#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

const int maxn = 1e5 + 100;
const double eps = 1e-7;

int dcmp(double x) {
    if(fabs(x) < eps)
	return 0;
    if(x > eps)
	return 1;
    return -1;
}
struct Point {
    double x, y;
    Point(double _x = 0, double _y = 0) {
	x = _x;
	y = _y;
    }
    double operator ^ (const Point b) const {
	double ans = 0;
	ans = x * b.y - y * b.x;
	return ans;
    }
    Point operator + (const Point b) const {
	Point t;
	t.x = x + b.x;
	t.y = y + b.y;
	return t;
    }
    Point operator - (const Point b) const {
	Point t;
	t.x = x - b.x;
	t.y = y - b.y;
	return t;
    }
    Point operator * (double b) {
	Point t;
	t.x = b * x;
	t.y = b * y;
	return t;
    }
    double mo() {
	double ans;
	ans = x * x + y * y;
	ans = sqrt(ans);
	return ans;
    }
};
double dist(Point a, Point b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}
Point p[maxn];
Point s[maxn], t[maxn];
int n, m;

void solve() {
    for(int k = 0; k < m; k++) {
	for(int i = 0; i < n; i++) {
	    if(dcmp((p[i] - s[k]) ^ (t[k] - s[k])) > 0) {
		double d = fabs((s[k] - p[i]) ^ (t[k] - p[i]))/dist(s[k], t[k]);
		d *= 2;
		Point tmp1, tmp2, tmp;
		tmp.x = s[k].x - t[k].x;
		tmp.y = s[k].y - t[k].y;
		tmp1.x = tmp.y;
		tmp1.y = -tmp.x;
		tmp2.x = -tmp.y;
		tmp2.y = tmp.x;
		//printf("11  %lf\n", d);
		Point a1, a2;
		a1 = p[i] + tmp1 * (d / tmp1.mo());
		a2 = p[i] + tmp2 * (d / tmp2.mo());
		if(fabs((s[k] - a1) ^ (t[k] - a1)) < fabs((s[k] - a2) ^ (t[k] - a2))) {
		    p[i] = a1;
		}
		else {
		    p[i] = a2;
		}
	    }
	}
    }
}

int main() {
    //freopen("A.txt", "r", stdin);
    while(scanf("%d%d", &n, &m) != EOF) {
	for(int i = 0; i < n; i++)
	    scanf("%lf %lf", &p[i].x, &p[i].y);
	for(int i = 0; i < m; i++) {
	    scanf("%lf %lf %lf %lf", &s[i].x, &s[i].y, &t[i].x, &t[i].y);
	}
	solve();
	    for(int i = 0; i < n; i++) {
		printf("%lf %lf\n", p[i].x, p[i].y);
	    }
    }
    return 0;
}
