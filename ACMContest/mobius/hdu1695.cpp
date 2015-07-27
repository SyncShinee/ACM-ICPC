#include <cstdio>
#include <algorithm>
#define N 100010
using namespace std;
typedef long long ll;
int miu[N], p[N], tot, sum[N];
bool flag[N];
ll ans, ans2;
void mobius() {
	miu[1] = 1;
	tot = 0;
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
	sum[0] = 0;
	for (int i = 1; i < N; ++i)
		sum[i] = sum[i - 1] + miu[i];
}

int main() {
	mobius();
	int T, a, b, c, d, k;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++cas) {
		scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
		if (k == 0) {
			printf("Case %d: 0\n", cas);
			continue;
		}
		b /= k;
		d /= k;
		int lim = min(b, d), nxt;
		ans = ans2 = 0;
		for (int i = 1; i <= lim; i = nxt + 1) {
			nxt = min(b / (b / i), d / (d / i));
			ans += (ll) (sum[nxt] - sum[i - 1]) * (b / i) * (d / i);
		}

		for (int i = 1; i <= lim; i = nxt + 1) {
			nxt = min(b / (b / i), d / (d / i));
			ans2 += (ll) (sum[nxt] - sum[i - 1]) * (lim / i) * (lim / i);
		}
		ans -= ans2 / 2;
		printf("Case %d: %I64d\n", cas, ans);
	}
	return 0;
}