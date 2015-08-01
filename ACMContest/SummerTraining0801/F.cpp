#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
typedef long long ll;
ll n, m, k;
ll a[700][10010], sum[700][10010], num[10010], sz, head, tail, q[10010];

struct node {
	double sm, nm;
	node (double _sm = 0, double _nm = 0){
		sm = _sm;
		nm = _nm;
	}
	friend bool operator < (node x, node y) {
		return x.sm < y.sm - 1e-9 || fabs(x.sm - y.sm) < 1e-9 && x.nm - 1e-9 > y.nm;
	}
}ans, tmp;

int main() {
	ll T;
	freopen("in.txt", "r", stdin);
	scanf("%lld", &T);
	while (T--) {
		scanf("%lld%lld%lld", &m, &n, &k);
		memset(sum, 0, sizeof sum);
		memset(num, 0, sizeof num);
		memset(a, 0, sizeof a);
		for (ll i = 1; i <= m; ++i)
			for (ll j = 1; j <= n; ++j) {
				scanf("%lld", &a[i][j]);
			}
		double l = 0, r = 5000, mid;
		while (r - l > 1e-6) { 
			mid = (l + r) / 2;
			ans = node(-1e10, 0);
			for (ll i = 1; i <= m; ++i) {
				for (ll j = 1; j <= n; ++j) {
					sum[i][j] = sum[i-1][j] + a[i][j] - mid;
				}
			}
			for (ll i = 1; i <= m; ++i) {
				for (ll j = i; j <= m; ++j) {
					if ((j - i + 1) * n < k) {
						continue;
					}
					sz = j - i + 1;
					for (ll t = 1; t <= n; ++t) {
						num[t] = sum[j][t] - sum[i - 1][t];
					}
					for (ll t = 2; t <- n; ++t) {
						num[t] += num[t - 1];
					}
					head = tail = 1;
					q[head] = 1;
					for (ll t = 1; t <= n; ++t) {
						if ((t - q[head] + 1) * sz >= k) {
							ans = max(ans, node(num[t] - num[q[head] - 1], (t - q[head] + 1) * sz));
						}
						while (head <= tail && num[q[tail]] > num[t]) {
							tail--;
						}
						q[++tail] = t;
					}
				}
			}
			if (ans.sm > 0) {
				l = mid;
			}
			else {
				r = mid;
			}
		}
		printf("%f\n", l);
	}
	return 0;
}
