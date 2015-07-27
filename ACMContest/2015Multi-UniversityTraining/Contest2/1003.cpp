#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[100010], w0, w1, w2, b0, b1, b2;
int main() {
	int T;
	//freopen("c.in", "r", stdin);
	//freopen("1003.out", "w", stdout);
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d%d%d%d", &w0, &w1, &w2, &b0, &b1, &b2);
		int n = w0 + w1 + w2;
		if ((w1 & 1) || (b1 & 1) || (w1 == 0 && w2 == 2) || (b1 == 0 && b2 == 2) || (w1 + 2*w2 + b1 + 2*b2) > n*(n-1)) {
			printf("-1\n");
			continue;
		}
		printf("%d\n", (w1 + 2 * w2 + b1 + 2 * b2)/2);
		for (int i = 1; i <= w2+1; ++i) {
			printf("%d %d 0\n", i, i + 1);
		}
		for (int i = w2 + 3; i < w1 + w2; i += 2) {
			printf("%d %d 0\n", i, i + 1);
		}
		int len = 1;
		for (int i = 2; i <= n; i += 2)
			a[len++] = i;
		for (int i = 1; i <= n; i += 2)
			a[len++] = i;
		for (int i = 1; i <= b2+1; ++i) {
			printf("%d %d 1\n", a[i], a[i+1]);
		}
		for (int i = b2 + 3; i < b1 + b2; i+= 2) {
			printf("%d %d 1\n", a[i], a[i+1]);
		}
	}
	return 0;
}