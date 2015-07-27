#include <cstdio>
#include <cstring>
#define N 1024
using namespace std;
/*int miu[N], p[N], tot;
bool flag[N];
void mobius() {
	memset(flag, 0, sizeof(flag));
	tot = 0;
	miu[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (!flag[i]) {
			p[tot++] = i;
			miu[i] = -1;
		}
		for (int j = 0; j < tot && i * p[j] < N; ++j) {
			flag[i * p[j]] = true;
			if (i % p[j]) {
				miu[i * p[j]] = -miu[i];
			}
			else {
				miu[i * p[j]] = 0;
				break;
			}
		}
	}
}

int main() {
	mobius();
	int T, ans, n;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++cas) {
		scanf("%d", &n);
		ans = 2;
		for (int i = 1; i <= n; ++i)
			ans += miu[i] * (n / i) * (n / i);
		printf("%d %d %d\n", cas, n, ans);
	}
}*/

int num[N], dp[N], n;
int main() {
	int T, ans;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++cas) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i)
			num[i] = (n / i) * (n / i);
		for (int i = n; i > 0; --i) {
			dp[i] = num[i];
			for (int j = 2 * i; j <= n; j += i)
				dp[i] -= dp[j];
		}
		printf("%d %d %d\n", cas, n, dp[1] + 2);
	}
}