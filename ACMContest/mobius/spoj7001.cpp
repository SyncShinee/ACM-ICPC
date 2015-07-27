#include <cstdio>
#include <cstring>
#define N 1000024
using namespace std;
/*long long miu[N], p[N], tot;
bool flag[N];
void mobius() {
	memset(flag, 0, sizeof(flag));
	tot = 0;
	miu[1] = 1;
	for (long long i = 2; i < N; ++i) {
		if (!flag[i]) {
			p[tot++] = i;
			miu[i] = -1;
		}
		for (long long j = 0; j < tot && i * p[j] < N; ++j) {
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
	long long T, ans, n;
	scanf("%lld", &T);
	while(T--) {
		scanf("%lld", &n);
		ans = 3;
		for (long long i = 1; i <= n; ++i)
			ans += miu[i] * (n / i) * (n / i) * ((n / i) + 3);
		printf("%lld\n",ans);
	}
}*/

typedef long long ll;

ll dp[N], num[N];

int main() {
	ll T, n;
	scanf("%lld", &T);
	while (T--) {
		scanf("%lld", &n);
		for (ll i = 1; i <= n; ++i)
			num[i] = (n / i) * (n / i) * (n / i + 3);
		for (ll i = n; i > 0; --i) {
			dp[i] = num[i];
			for (ll j = 2 * i; j <= n; j += i)
				dp[i] -= dp[j];
		}
		printf("%lld\n", dp[1] + 3);
	}
	return 0;
}