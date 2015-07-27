#include <cstdio>
#include <cmath>
#include <cstring>
#define EPS 1e-9
#define pi 3.1415926535
using namespace std;
int main() {
	int T, n;
	double d, r;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++cas) {
		scanf("%d%lf%lf", &n, &d, &r);
		printf("Case #%d:\n", cas);
		if (r < 1.0*d/2.0/tan(pi/n) + EPS) {
			printf("Give me a kiss!\n");
		}
		else {
			printf("I want to kiss you!\n");
		}
	}
	return 0;
}