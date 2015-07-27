#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 100010
#define inv2 500000004
#define MOD 1000000007
using namespace std;
typedef long long ll;
ll n, p[N], tot, flag[N];
ll f[N], sum[2 * N], num[N], ans, a[N];
void get_prime() {
	tot = 0;
	flag[1] = 1;
	for (ll i = 2; i < N; ++i) {
		if (!flag[i]) {
			flag[i] = 1;
			p[tot++] = i;
		}
		for (ll j = 0; j < tot && i * p[j] < N; ++j) {
			if (i % p[j])
				flag[i * p[j]] = flag[i] + 1;
			else {
				flag[i * p[j]] = flag[i];
				break;
			}
		}
	}
}

ll inv[N];
void get_inverse(ll n, ll p) {
	inv[1] = 1;
	for (ll i = 2; i <= n; ++i) {
		inv[i] = (p - p / i) * inv[p % i] % p;
	}
}
int main() {
	get_prime();
	get_inverse(N-1, MOD);
	while (~scanf("%I64d", &n)) {
		for (ll i = 0; i < n; ++i) {
			scanf("%I64d", &a[i]);
		}
		sort(a, a + n);
		ll tmp = 0;
		sum[0] = 0;
		for (ll i = 0; i < n; ++i)
			sum[0] = (sum[0]  + inv[a[i]]) % MOD;
		for (ll i = 1; i <= a[n-1]; ++i) {
			sum[i] = sum[0];
			while (i == a[tmp]) {
				sum[0] = ((sum[0] - inv[a[tmp]]) % MOD + MOD) % MOD;
				tmp++;
			}
		}
		for (ll i = 1; i <= a[n-1]; ++i) {
			num[i] = 0;
			for (ll j = i; j <= a[n-1]; j += i)
				num[i] = (num[i] + sum[j]) % MOD;
			num[i] = (num[i] * num[i]) % MOD;
		}
		//printf("%lld-----inv=%lld------%lld----biao=%lld\n", num[2], inv[100000], (inv[100000] * 50000)% MOD, ((inv[100000] * 50000)% MOD * ((inv[100000] * 50000) % MOD)) % MOD);
		memset(sum, 0, sizeof(sum));
		for (ll i = 0; i < n; ++i) {
			sum[a[i]] = (sum[a[i]] + (inv[a[i]] * inv[a[i]]) % MOD) % MOD;
		}

		for (ll i = 1; i <= 2 * a[n-1]; ++i)
			sum[i] = (sum[i] + sum[i-1])% MOD;
		/*		for (ll i = a[n-1]; i <= 2*a[n-1]; ++i)
		{
			printf("num[i]====%lld    sum[i] = %lld\n", num[i], sum[i]);
		}*/
		for (ll i = 1; i <= a[n-1]; ++i) {
			for (ll j = i; j <= a[n-1]; j += i) {
				ll tmp, tmp1;
				tmp = ((j/i) * (j/i)) % MOD;
				tmp1 = ((sum[j + i - 1] - sum[j - 1]) % MOD + MOD) % MOD;
				tmp = (tmp * tmp1) % MOD;
				//if (j == 100000)
				//printf("%lld %lld\n", tmp, tmp1);
				//num[i] = ((num[i] - ( * (((j/i) * (j/i)) % MOD)) % MOD) % MOD + MOD) % MOD;
				num[i] = ((num[i] - tmp) % MOD + MOD) % MOD;
			//	printf("---dev%d %d--------num[i] = %lld\n", i, j, num[i]);
			}
			num[i] = (num[i] * inv2) % MOD;
		}
		/*for (ll i = 1; i <= a[n-1]; ++i)
			printf("num---%lld\n", num[i]);*/
		for (ll i = a[n-1]; i > 0; --i) {
			f[i] = num[i];
			for (ll j = 2 * i; j <= a[n-1]; j += i) {
				f[i] = ((f[i] - f[j]) % MOD + MOD) % MOD;
			}
		}
		//printf("2222\n");
		ans = 0;
		for (ll i = 1; i <= a[n-1]; ++i)
			if (flag[i] == 1) {
				//printf("%d %lld\n", i, ans);
				ans = (ans + f[i]) % MOD;
			}
		for (ll i = 0; i < n; ++i)
			ans = (ans * a[i]) % MOD;
		printf("%I64d\n", ans);
	}
	return 0;
}