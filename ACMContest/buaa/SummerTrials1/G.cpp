#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#define EPS 1e-8
using namespace std;
double x[100010], r[100010];
int n;
struct node {
	double l, r;
	friend bool operator < (node a, node b) {
		return (a.l < b.l || fabs(a.l - b.l) < EPS && a.r < b.r);
	}
}tmp[100010];

bool judge(double p) {
	memset(tmp, 0, sizeof(tmp));
	for (int i = 0; i < n; ++i) {
		if (r[i] < p - EPS)
			continue;
		tmp[i].l = x[i] - sqrt(r[i]*r[i] - p*p);
		tmp[i].r = x[i] + sqrt(r[i]*r[i] - p*p);
	}
	sort(tmp, tmp+n);
	double start = tmp[0].l, end = tmp[0].r, len = end - start;
	for (int i = 1; i < n; ++i) {
		if (tmp[i].l > end + EPS) {
			start = tmp[i].l;
		}
		end = max(end, tmp[i].r);
		len = max(len, end - start);
	}
	if (len > 2*p - EPS)
		return true;
	return false;
}

int main() {
	double mx, ll, rr, mid;
	while (scanf("%d", &n), n) {
		mx = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%lf%lf", &x[i], &r[i]);
			mx = max(mx, r[i]);
		}
		ll = 0; rr = mx;
		while (fabs(ll - rr) > EPS) {
			mid = (ll + rr) / 2;
			if (judge(mid))
				ll = mid;
			else
				rr = mid;
		}

		printf("%f\n", 2*mid);
	}
	return 0;
}