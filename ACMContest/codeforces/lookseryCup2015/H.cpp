#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <string>
#include <queue>
#define N 1024
#define M 1024
#define MOD 1000000007
#define EPS 1e-19
using namespace std;
int n, m;
double tmpal, tmpar, tmpbl, tmpbr, tmpcl, tmpcr, tmpdl, tmpdr, tmpl1, tmpr1, tmpl2, tmpr2;
int main() {
	int a, b, c, d;
	scanf("%d%d%d%d", &a, &b, &c, &d);
	double l = 0, r = 2e9, mid;
	while ((r - l)/l > 1e-9) {
		mid = (l + r) / 2;
		tmpal = a*1.0 - mid;
		tmpbl = b*1.0 - mid;
		tmpcl = c*1.0 - mid;
		tmpdl = d*1.0 - mid;
		tmpar = a*1.0 + mid;
		tmpbr = b*1.0 + mid;
		tmpcr = c*1.0 + mid;
		tmpdr = d*1.0 + mid;
		tmpl1 = min(tmpal * tmpdl, tmpal * tmpdr);
		tmpl1 = min(tmpl1, tmpar * tmpdl);
		tmpl1 = min(tmpl1, tmpar * tmpdr);
		tmpl2 = min(tmpbl * tmpcl, tmpbl* tmpcr);
		tmpl2 = min(tmpl2, tmpbr * tmpcl);
		tmpl2 = min(tmpl2, tmpbr * tmpcr);
		tmpr1 = max(tmpal * tmpdl, tmpal * tmpdr);
		tmpr1 = max(tmpr1, tmpar * tmpdl);
		tmpr1 = max(tmpr1, tmpar * tmpdr);
		tmpr2 = max(tmpbl * tmpcl, tmpbl * tmpcr);
		tmpr2 = max(tmpr2, tmpbr * tmpcl);
		tmpr2 = max(tmpr2, tmpbr * tmpcr);
		tmpl1 = max(tmpl1, tmpl2);
		tmpr1 = min(tmpr1, tmpr2);
		if (tmpl1 < tmpr1 + EPS) {
			r = mid;
		}
		else {
			l = mid;
		}		
	}
	printf("%.9f\n", mid);
	return 0;
}