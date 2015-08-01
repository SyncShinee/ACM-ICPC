#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;
int q[32], len;
int calc(int x) {
	int ret = 0;
	while (x) {
		ret++;
		x &= x - 1;
	}
	return ret;
}
int b[32], n, a;
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int ans = 1001, p;
		int flag =  0;
		scanf("%d%d", &n, &a);
		for (int i = 0; i < n; ++i) {
			scanf("%d", &b[i]);
			if (b[i] == 1)
				flag = 1;
		}
		if (flag) {
			printf("1\n");
			continue;
		}
		sort(b, b + n);
		for (int sta = 1; sta < (1 << n); ++sta) {
			len = 0;
			for (int i = 0; i < n; ++i) {
				if (sta & (1 << i)) {
					q[len++] = b[i];
				} 
			}
			p = a;
			for (int i = len - 1; i >= 0; --i) {
				p %= q[i];
			}
			if (p == 0) {
				ans = min(ans, calc(sta));
			}
		}
		if (ans == 1001)
			ans = -1;
		printf("%d\n", ans);
	}
	return 0;
}