#include <cstdio>
#include <algorithm>
#define POS_POS 0
#define POS_NEG 1
#define NEG_POS 2
#define NEG_NEG 3
#define EPS		1e-8
using namespace std;
struct flw {
	double vw, pf, vf, th, change, need;
	int status;
	friend bool operator < (flw x, flw y) {
		if (x.need < 0)
			return false;
		if (y.need < 0)
			return true;
		return x.need < y.need;
	}
}a[300010];
int main() {
	int n;
	double ans, vol, tmp, pw;
	while (scanf("%d", &n), n>0) {
		ans = 0;
		scanf("%lf", &pw);
		for (int i = 0; i < n; ++i) {
			scanf("%lf%lf%lf%lf", &a[i].vw, &a[i].pf, &a[i].vf, &a[i].th);
			a[i].vw += EPS;
			if (a[i].vw > 0) {
				if (a[i].th > 0)
					a[i].status = POS_POS;
				else
					a[i].status = POS_NEG;
			}
			else {
				if (a[i].th > 0)
					a[i].status = NEG_POS;
				else
					a[i].status = NEG_NEG;
			}
			a[i].need = a[i].th / a[i].vw;
			a[i].change = a[i].vw / a[i].vf * a[i].pf;
		}
		sort(a, a+n);
		vol = 0;
		tmp = 0;
		for (int j = 0; j < n; ++j) {
			if (a[j].status == POS_POS || a[j].status == NEG_POS)
				tmp += a[j].change;
		}
		for (int i = 0; i < n; ++i) {
			if (a[i].need < 0)
				break;
			if (pw > tmp) {
				break;
			}
			if (a[i].status == POS_POS)
				tmp -= a[i].change;
			if (a[i].status == NEG_NEG)
				tmp += a[i].change;
			vol = a[i].need;
		}
		for (int i = 0; i < n; ++i) {
			tmp = a[i].th - a[i].vw*vol;
			if (tmp > 0) {
				ans += tmp / a[i].vf * a[i].pf;
			}
		}
		ans += vol * pw;
		printf("%f\n", ans);
	}
	return 0;
}