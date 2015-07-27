#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <cmath>
#define N 100010
#define INF 1000000007
#define MOD 1000000007

using namespace std;
const double eps = 1e-6;
int sgn(double x){
	if(fabs(x) <= eps) return 0;
	return x > 0 ? 1 : -1;
}
struct Point {
	double x, y;
	Point (double _x = 0, double _y = 0) {
		x = _x;
		y = _y;
	}
	void set(double _x, double _y) {
		x = _x;
		y = _y;
	}
	void print() {
		printf("%f %f\n", x, y);
	}
	Point operator + (Point a) {
		return Point(a.x + x, a.y + y);
	} 
	Point operator - (Point a) {
		return Point(x - a.x, y - a.y);
	}
	Point operator * (double a) {
		return Point(x * a, y * a);
	}
	bool operator == (const Point&b) const{
		return sgn(x - b.x) == 0 && sgn(y - b.y) == 0;
	}
	double lenq(){
		return x*x + y*y;
	}
	double len(){
		return sqrt(lenq());
	}
};

struct Circle {
	Point o;
	double r;
	Circle(Point _o,double _r = 0.0){
		o = _o , r = _r;
	}
	void set(Point _o,double _r){
		o = _o , r = _r;
	}
	bool operator == (const Circle &b) const{
		return o == b.o && sgn(r - b.r) == 0;
	}
};
Point x, y;
Point G;
void CircleCross(Circle o1, Circle o2, Point &x, Point &y) {
	if (o1 == o2) {
		x = o1.o - Point(0, o1.r);
		y = o1.o + Point(0, o1.r);
		return;
	}
	Point dist = o2.o - o1.o;
	Point d = dist*((dist.lenq() - o2.r * o2.r + o1.r * o1.r) / (dist.lenq() * 2.0));
	Point f = Point(dist.y, -dist.x);
	if (o1.r * o1.r - d.lenq() < -eps) {
		x = o1.o + d;
		y = o1.o + d;
		return;
	}
	if (o1.r * o1.r - d.lenq() < -eps)
	{
		printf("asdfadg ---  %f\n", o1.r * o1.r - d.lenq());
	}
	Point t = f * (sqrt(o1.r * o1.r - d.lenq()) / f.len());
	x = o1.o + d + t;
	y = o1.o + d - t;
}
Point A, B, C, D;
double AB, BC, CD, DA, EF;

int main() {
	int T;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++cas) {
		printf("Case #%d:\n", cas);
		C.set(0.0, 0.0);
		scanf("%lf%lf%lf%lf%lf", &AB, &BC, &CD, &DA, &EF);
		B = C + Point(BC, 0.0);
		Circle c1 = Circle(B, 2.0 *EF);
		Circle c2 = Circle(C, DA);
		CircleCross(c1, c2, x, y);
		G = B + y;
		c1.set(C, CD);
		c2.set(G, AB);
		CircleCross(c1, c2, D, x);
		A = D - y;
		A.print();
		B.print();
		C.print();
		D.print();
	}
	return 0;
}