#include <cstdio>
using namespace std;
int n, a[1024], ans, ans2, sum[1024];
int main() {
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
			sum[i] = sum[i - 1] + a[i];
		}
		for (int i = 3; i <= n; ++i) {
			if (sum[i] - sum[i - 3] > ans) {
				ans = sum[i] - sum[i - 3];
				ans2 = i - 1;
			}
		}
		printf("%d %d\n", ans, ans2);
	}
	return 0;
}