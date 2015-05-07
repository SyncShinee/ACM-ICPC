#include <cstdio>
#include <algorithm>
#include <cmath>
#define EPS 1e-9
using namespace std;
double p[32], h[32];
bool flag;
int main() {
	int n, b, doub, doubPre;
	double d, dist, mul, ans;
	while (~scanf("%lf%d%d", &d, &n, &b)) {
		for (int i = 0; i < n; ++i)
			scanf("%lf%lf", &p[i], &h[i]);
		ans = -1;
		for (int i = 0; i <= b; ++i) {
			dist = d / (i+1);
			mul = -1.0/dist;
			flag = true;
			for (int t = 0; t < n; ++t) {
				doub = (int) ((p[t] / dist)+EPS);
				//printf("pre---h[t]%f\n", mul*(p[t]- doub*dist)*(p[t] - (doub+1)*dist));
				if (mul*(p[t]- doub*dist)*(p[t] - (doub+1)*dist) < h[t] - EPS) {
					//printf("h can't pass------%d\n", h[t]);
					flag = false;
					//printf("lll\n");
					break;
				}
			}
			if (flag) {
				if ((ans + 1.0) < EPS)
					ans = sqrt(-0.5/mul - mul*dist*dist/2.0);
				else
					ans = min(ans,sqrt(-0.5/mul - mul*dist*dist/2.0));
			}
			else {
				for (int j = 0; j < n; ++j) {
					doubPre = (int) ((p[j] / dist)+EPS);
					mul = h[j] / (p[j] - doubPre*dist) / (p[j] - (doubPre+1)*dist);
					flag = true;
					//printf("--- mul %f----dist %f----\n", mul, dist);
					for (int t = 0; t < n; ++t) {
						doub = (int) ((p[t] / dist)+EPS);
						//printf("beishu----%d\n", doub);
						//printf("-----h[t]%f\n", mul*(p[t]- doub*dist)*(p[t] - (doub+1)*dist));
						if (mul*(p[t]- doub*dist)*(p[t] - (doub+1)*dist) < h[t] - EPS) {
						//	printf("h------%d\n", h[t]);
							flag = false;
						//	printf("lll\n");
							break;
						}
					}
					if (flag) {
						//printf("okokok----- mul %f----dist %f----\n", mul, dist);
						//printf("vx---%f   vy----%f\n", sqrt(-0.5/mul), sqrt(-mul*dist*dist/2.0));
						if ((ans + 1.0) < EPS)
							ans = sqrt(-0.5/mul - mul*dist*dist/2.0);
						else
							ans = min(ans,sqrt(-0.5/mul - mul*dist*dist/2.0));
					}
				}
			}
		}
		printf("%f\n", ans);
	}
	return 0;
}