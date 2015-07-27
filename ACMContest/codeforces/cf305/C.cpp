#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#define N 200010
#define M 500010
using namespace std;
typedef long long ll;
ll cnt[M], miu[M], tot, p[M], pi[M][16];
void mobius() {
	tot = 0;
	miu[1] = 1;
	cnt[1] = 0;
	for (ll i = 2; i < M; ++i) {
		if (cnt[i] == 0) {
			p[tot++] = i;
			miu[i] = -1;
			cnt[i] = 1;
			pi[i][0] = i;
		}
		for (ll j = 0; j < tot && i * p[j] < M; ++j) {
			if (i % p[j]) {
				cnt[i * p[j]] = cnt[i] +1;
				miu[i * p[j]] = -miu[i];
				for (ll t = 0; t < cnt[i]; ++t) {
					pi[i * p[j]][t] = pi[i][t];
				}
				pi[i * p[j]][cnt[i]] = p[j];
			}
			else {
				cnt[i * p[j]] = cnt[i];
				miu[i * p[j]] = 0;
				for (ll t = 0; t < cnt[i]; ++t) {
					pi[i * p[j]][t] = pi[i][t];
				}
				break;
			}
		}
	}
}
ll col[N], num[M], a[N], n, q, x, ret, ans;
int main() {
	mobius();
	scanf("%I64d%I64d", &n, &q);
	for (ll i = 1; i <= n; ++i)
		scanf("%I64d", &a[i]);
	ans = 0;
	memset(col, -1, sizeof(col));
	memset(num, 0, sizeof(num));
	while (q--) {
		scanf("%I64d", &x);
		ret = 0;
		for (ll i = 0; i < (1 << cnt[a[x]]); ++i) {
			ll tmp = 1;
			for (ll j = 0; j < cnt[a[x]]; ++j) {
				if (i & (1 << j))
					tmp *= pi[a[x]][j];
			}
			if (col[x] == 1) {
				num[tmp]--;
			}
			ret += miu[tmp]*num[tmp];
			if (col[x] == -1)
				num[tmp]++;
		}
		if (col[x] == 1) {
			ans -= ret;
			col[x] = -1;
		}
		else {
			ans += ret;
			col[x] = 1;
		}
		printf("%I64d\n", ans);
	}
	return 0;
}