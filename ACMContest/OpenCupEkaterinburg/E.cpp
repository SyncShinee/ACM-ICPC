#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>

using namespace std;

const double eps = 1e-8;
const int maxn = 1e5;
int dcmp(double x) {
    if(fabs(x) < eps) {
	return 0;
    }
    if(x > eps) {
	return 1;
    }
    if(x < eps) {
	return -1;
    }
}

struct Point {
    double x, y;
    Point(double _x = 0, double _y = 0) {
	x = _x;
	y = _y;
    }
    Point operator + (Point b) const {
	Point t;
	t.x = x + b.x;
	t.y = y + b.y;
	return t;
    }
    Point operator - (Point b) const {
	Point t;
	t.x = x - b.x;
	t.y = y - b.y;
	return t;
    }
    Point operator / (double b) const {
	Point t;
	t.x = x / b;
	t.y = y / b;
	return t;
    }
    double operator ^ (Point b) const {
	double t = 0;
	t = x * b.y - y * b.x;
	return t;
    }
};
double dist(Point a, Point b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}
struct Line {
    Point s, e;
};

Point inter_Point(Line l1, Line l2) {
    Point res = l1.s;
    double t = ((l1.s - l2.s) ^ (l2.s - l2.e)) / ((l1.s - l1.e) ^ (l2.s - l2.e));
    res.x += (l1.e.x - l1.s.x) * t;
    res.y += (l1.e.y - l1.s.y) * t;
    return res;
}

Line getLine(Point a, Point b) {
    Line l;
    l.s = (a + b) / 2.0;
    Point t;
    t.x = (b - a).y;
    t.y = -(b - a).x;
    l.e = l.s + t;
    //printf("%lf %lf %lf %lf %lf %lf %lf %lf\n", a.x, a.y, b.x, b.y, l.s.x, l.s.y, l.e.x, l.e.y);
    return l;
}
Point calcu(Point a, Point b, Point c) {
    Line l1, l2;
    
    l1 = getLine(a, b);
    l2 = getLine(a, c);
    Point ans = inter_Point(l1, l2);
    return ans;
}
Point p[maxn][3];
int n;
void solve() {
    int flag = 1;
    for(int i = 0; i < n; i++) {
	Point th = calcu(p[i][0], p[i][1], p[i][2]);
	double r = dist(th, p[i][0]);
	//printf("%f  %f  %f\n", th.x, th.y, r);
	for(int j = 0; j < n; j++) {
	    if(j == i)
		continue;
	    for(int k = 0; k < 3; k++) {
		if(dcmp(dist(p[j][k], th) - r) < 0) {
		    flag = 0;
		}
	    }
	}
    }
    if(flag) {
	printf("YES\n");
    }
    else {
	printf("NO\n");
    }
}
int main() {
    //freopen("E.txt", "r", stdin);
    while(scanf("%d", &n) != EOF) {
	for(int i = 0; i < n; i++) {
	    for(int j = 0; j < 3; j++) {
		scanf("%lf%lf", &p[i][j].x, &p[i][j].y);
	    }
	}
	solve();
    }
    return 0;
}
