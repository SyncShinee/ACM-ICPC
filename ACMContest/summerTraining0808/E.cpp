#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#include <stack>
using namespace std;
double w, h, x, xe, ye, u, sina, sinb;
double calc(double tt) {
	return w - sinb * tt / sqrt(1.0 - sinb * sinb) - (xe - w) * (h - tt) / (ye - h);
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%lf%lf%lf%lf%lf%lf", &w, &h, &x, &xe, &ye, &u);
		if (ye < h - 1e-9) {
			printf("0.00\n");
			continue;
		}
		if (xe < w - 1e-10) {
			printf("Impossible\n");
			continue;
		} 
		sina = (xe - w) / sqrt((xe - w) * (xe - w) + (ye - h) * (ye - h));
		sinb = sina / u;
		//printf("%f %f\n", sina, sinb);
		if (w - sinb * h / sqrt(1.0 - sinb * sinb) < x - 1e-10) {
			printf("Impossible\n");
			continue;
		}
		//printf("%f\n", w - sinb * h * sqrt(1.0 - sinb * sinb));
		double l = 0.0, r = h, mid;
		while (r - l > 1e-7) {
			mid = (l + r) / 2;
			double len = calc(mid);
			//printf("%f %f\n",mid, len);
			if (fabs(len - x) < 1e-10) {
				break;
			}
			if (len < x - 1e-10) {
				l = mid;
			}
			else {
				r = mid;
			}
		}
		printf("%.4f\n", mid);
	}
	return 0;
}