#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>
using namespace std;

int main() {
	int n, m, p, q, ans, T;
	scanf("%d", &T);
	while (T--) {
	scanf("%d%d%d%d", &n, &m, &p, &q);
	if (p * m <= q) {
		printf("%d\n", n * p);
	}
	else {
		if (n < m) {
			ans = min(q, n * p);
		}
		else {
			ans = (n + m - 1) / m * q;
			ans = min((n / m) * q + (n % m) * p, ans);
		}
		printf("%d\n", ans);
	}
}
	return 0;
}