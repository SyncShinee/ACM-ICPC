#include <cstdio>
#include <cstring>
using namespace std;
int factor[30010], ans[30010], cnt;
bool flag[30010];
int main() {
	int T, a, b, p, q, n, f;
	scanf("%d", &T);
	ans[0] = 1;
	for (int i = 1; i <= 30000; ++i) {
		cnt = 0;
		memset(flag, 0, sizeof(flag));
		for (int j = 2; j*j <= i; ++j) {
			if (i % j == 0)
				factor[cnt++] = j;
		}
		f = cnt == 0 ? i : factor[0];
		p = 2;
		for (int j = 0; j < cnt; ++j) {
			a = factor[j];
			b = i / a;
			while (p < a) {
				for (q = b - 1; q >= 1; --q)
					flag[p*q] = true;
				p++;
			}
		}
		ans[i] = ans[i-1];
		for (int j = i/f; j <= i; ++j)
			if (!flag[j])
				ans[i]++;
	}
	while (T--) {

		scanf("%d", &n);
		printf("%d\n", ans[n]);
	}
	return 0;
}