#include <cstdio>
#include <algorithm>
#include <cmath>
#define EPS 1e-9
using namespace std;
double p[32], h[32];
bool flag;
int main() {
	int n, b, tim, tmp;
	double d;
	while (~scanf("%lf%d%d", &d, &n, &b)) {
		for (int i = 0; i < n; ++i)
			scanf("%lf%lf", &p[i], &h[i]);
		double ans = -1;
		for (int i = 0; i <= b; ++i) {
			double x0 = d / (i + 1), a = -1.0 / x0;
			flag = true;
			for (int j = 0; j < n; ++j) {
				tim = (int) ((p[j] / x0)+EPS);
				if (a * (p[j]- tim * x0) * (p[j] - (tim + 1) * x0) < h[j] - EPS) {
					flag = false;
					break;
				}
			}
			if (flag) {
				if ((ans + 1.0) < EPS)
					ans = sqrt((-1.0 / a - a * x0 * x0) / 2.0);
				else
					ans = min(ans, sqrt((-1.0 / a - a * x0 * x0) / 2.0));
			}
			else {
				for (int j = 0; j < n; ++j) {
					tmp = (int) ((p[j] / x0) + EPS);
					a = h[j] / (p[j] - tmp * x0) / (p[j] - (tmp + 1) * x0);
					flag = true;
					for (int t = 0; t < n; ++t) {
						tim = (int) ((p[t] / x0)+EPS);
						if (a * (p[t] - tim * x0) * (p[t] - (tim + 1) * x0) < h[t] - EPS) {
							flag = false;
							break;
						}
					}
					if (flag) {
						if ((ans + 1.0) < EPS)
							ans = sqrt((-1.0 / a - a * x0 * x0) / 2.0);
						else
							ans = min(ans, sqrt((-1.0 / a - a * x0 * x0) / 2.0));
					}
				}
			}
		}
		printf("%f\n", ans);
	}
	return 0;
}