#include <cstdio>
#include <algorithm>
#include <cstring>
#define N 50010
using namespace std;
typedef long long ll;
int p[N], miu[N], tot, sum[N];
bool flag[N];

void mobius() {
	miu[1] = 1;
	tot = 0;
	for (int i = 2; i < N; ++ i) {
		if (!flag[i]) {
			p[tot ++] = i;
			miu[i] = -1;
		}
		for (int j = 0; j < tot && i * p[j] < N; ++ j) {
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

ll calc(int x, int y) {
	int nxt, lim = min(x, y);
	ll ret = 0;
	for (int i = 1; i <= lim; i = nxt + 1) {
		nxt = min(x / (x / i), y / (y / i));
		ret += 1ll * (sum[nxt] - sum[i - 1]) * (x / i) * (y / i);
	}
	return ret;
}

int main() {
	mobius();
	int T, a, b, c, d, k;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
		a --, c --;
		a /= k, b /= k, c /= k, d /= k;
		printf("%lld\n", calc(b, d) - calc(a, d) - calc(b, c) + calc(a, c));
	}
	return 0;
}