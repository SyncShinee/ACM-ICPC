#include <cstdio>
#include <cmath>
using namespace std;
int n, p, k, f1, f2;
double tp, pa, pb, pab, f[512];
int main() {
	while (~scanf("%d%d%d%d%d", &n, &p, &k, &f1, &f2)) {
		tp = p >= f1 ? (p-f1+1)*1.0/p : 0;
		pa = pow(tp, n);
		tp = p >= f2 ? (p-f2+1)*1.0/p : 0;
		f[0] = 0;
		for (int i = 1; i <= n; ++i) {
			if (i < k)
				f[i] = f[i-1];
			else if (i == k){
				f[i] = pow(tp, k);
			}
			else {
				f[i] = f[i-1] + pow(tp, k)*(1-tp)*(1-f[i-k-1]);
			}
		}
		pb = f[n];
		tp = p >= f2 ? (p-f2+1)*1.0/(p-f1+1) : 0;
		f[0] = 0;
		for (int i = 1; i <= n; ++i) {
			if (i < k)
				f[i] = f[i-1];
			else if (i == k){
				f[i] = pow(tp, k);
			}
			else {
				f[i] = f[i-1] + pow(tp, k)*(1-tp)*(1-f[i-k-1]);
			}
		}
		pab = f[n];
		printf("%.3f\n", pa+pb-pab*pa);
	}
	return 0;
}