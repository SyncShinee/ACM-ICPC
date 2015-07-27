#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <queue>
#define N 300010
#define M 1000010
#define MOD 1000000007
#define EPS 1e-9
using namespace std;
typedef long long ll;
ll n, m, a[N], sum[N], l[N], r[N], remain, ans;
vector <ll> rem[M];

ll find(ll x, ll val) {
	ll l = 0, r = rem[x].size() - 1, mid;
	while (l <= r) {
		mid = (l + r) >> 1;
		if (rem[x][mid] > val) {
			r = mid - 1;
		}
		else {
			l = mid + 1;
		}
	}
	return r;
}

int main() {
	scanf("%I64d%I64d", &n, &m);
	sum[0] = 0;
	rem[0].push_back(0);
	for (ll i = 1; i <= n; ++i) {
		scanf("%I64d", &a[i]);
		sum[i] = (sum[i-1] + a[i]) % m;
		rem[sum[i]].push_back(i);
	}
	a[0] = a[n+1] = MOD;
	for (ll i = n; i > 0; --i) {
		r[i] = i+1;
		while (a[i] >= a[r[i]]) {
			r[i] = r[r[i]];
		}
	}
	for (ll i = 1; i <= n; ++i) {
		l[i] = i-1;
		while (a[i] > a[l[i]]) {
			l[i] = l[l[i]];
		}
	}
	for (ll i = 1; i <= n; ++i) {
		if (i - l[i] < r[i] - i) {
			for (ll j = l[i] + 1; j <= i; ++j) {
				remain = (sum[j-1] + a[i]) % m;
				ans += find(remain, r[i] - 1) - find(remain, i-1);
			}
		}
		else {
			for (ll j = i; j < r[i]; ++j) {
				remain = ((sum[j] - a[i]) % m + m) % m;
				ans += find(remain, i-1) - find(remain, l[i]-1);
			}
		}
	}
	printf("%I64d\n", ans-n);
	return 0;
}