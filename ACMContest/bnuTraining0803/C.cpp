#include <cstdio>
#include <cmath>
using namespace std;
double t, s0, s[128], sub, len;
int main() {
	int n;
	while (~scanf("%d", &n)) {
		scanf("%lf%lf", &t, &s0);
		for (int i = 0; i < n; ++i) {
			scanf("%lf", &s[i]);
		}
		for (int i = 0; i < n; ++i) {
			sub = s[i] - s0;
			len = (t + sub) / 2;
			printf("%f\n", s0 + len);
		}
	}
	return 0;
}