#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <queue>
#define N 128
#define EPS 1e-10
#define EPS1 1e-7
using namespace std;
typedef long long ll;
struct node1{
	double v, x;
	friend bool operator < (node1 aa, node1 bb) {
		return aa.x < bb.x;
	}
}a[N];
struct node2{
	double v, x;
	friend bool operator < (node2 aa, node2 bb) {
		return aa.x > bb.x;
	}
}b[N];
int n;
double V, X;
void init() {
	scanf("%d%lf%lf", &n, &V, &X);
	for (int i = 0; i < n; ++i) {
		scanf("%lf%lf", &a[i].v, &a[i].x);
		b[i].v = a[i].v;
		b[i].x = a[i].x;
	}
	sort(a, a+n);
	sort(b, b+n);
}

void stress() {

}

bool judge(double x) {
	double vx = 0, tx = 0;
	for (int i = 0; i < n; ++i) {
		if (vx + a[i].v * x < V - EPS) {
			vx += a[i].v * x;
			tx += a[i].v * x * a[i].x;
		}
		else {
			tx += (V - vx) * a[i].x;
			vx = V;
			break;
		}
	}
	if (vx < V - EPS || tx/V > X + EPS) {
		return false;
	}
	vx = tx = 0;
	for (int i = 0; i < n; ++i) {
		if (vx + b[i].v * x < V - EPS) {
			vx += b[i].v * x;
			tx += b[i].v * x * b[i].x;
		}
		else {
			tx += (V - vx) * b[i].x;
			vx = V;
			break;
		}
	}
	if (vx < V - EPS || tx/V < X - EPS) {
		return false;
	}
	return true;
}

double solve() {
	double l = 0, r = 100000000.0, mid;
	if (a[0].x > X)
		return -1;
	if (a[n-1].x < X)
		return -1;
	while (r-l > EPS1) {
		mid = (r + l) / 2;
		if (judge(mid))
			r = mid;
		else
			l = mid;
	}
	return mid;
}

int main() {
	int T;
	freopen("B-large.in", "r", stdin);
	freopen("B.out", "w", stdout);
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++cas) {
		init();
		double tmp = solve();
		if (tmp < 0)
			printf("Case #%d: IMPOSSIBLE\n", cas);
		else
			printf("Case #%d: %f\n", cas, solve());
	}
	return 0;
}