#include <cstdio>
#include <algorithm>
#define N 500010
using namespace std;
typedef long long ll;
int miu[N], p[N], tot, flag[N];
ll ans, sum[N][32];
void mobius() {
	miu[1] = 1;
	tot = 0;
	flag[1] = 0;
	for (int i = 2; i < N; ++i) {
		if (!flag[i]) {
			p[tot++] = i;
			miu[i] = -1;
			flag[i] = 1;
		}
		for (int j = 0; j < tot && i * p[j] < N; ++j) {
			flag[i * p[j]] = flag[i] + 1;
			if (i % p[j]) {
				miu[i * p[j]] = -miu[i];
			}
			else {
				miu[i * p[j]] = 0;
				break;
			}
		}
	}
	for (int i = 1; i < N; ++i)
		for (int j = i; j < N; j += i) {
			sum[j][flag[i]] += miu[j / i];
		}
	for (int i = 1; i < N; ++i)
		for (int j = 0; j < 20; ++j) {
			sum[i][j] += sum[i - 1][j];
			if (j)
				sum[i][j] += sum[i][j - 1] - sum[i - 1][j - 1];
		}
}

int main() {
	mobius();
	int T, a, b, k;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &a, &b, &k);
		int lim = min(a, b), nxt;
		ans = 0;
		k = min(k, 19);
		for (int i = 1; i <= lim; i = nxt + 1) {
			nxt = min(b / (b / i), a / (a / i));
			ans += (ll) (sum[nxt][k] - sum[i - 1][k]) * (b / i) * (a / i);
		}
		printf("%I64d\n",  ans);
	}
	return 0;
}