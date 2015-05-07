#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
	while (~scanf("%d%d" &n, &k)) {
		if (k == 1) {
			for (i = 0; i < n; ++i) {
				scanf("%d%d%d", &y, &z, &p);
				printf("%lld\n", qpow(y, z, p));
			}
		}
		else if (k == 2) {
			for (i = 0; i < n; ++i) {
				scanf("%d%d%d", &y, &z, &p);
				exgcd(y, p);
				k1 = (((k1 % p) * z) % p + p) % p;
				printf("%lld\n", k1);
			}
		}
		else {
			for (i = 0; i < n; ++i) {
				scanf("%d%d%d", &x, &y, &p);
				k1 = 0;
				p
				while (k1)
			}
		}
	}
	return 0;
}