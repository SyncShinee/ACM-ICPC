#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cassert>
using namespace std;
typedef long long ll;
ll a[16], k;
vector <pair <ll, ll> > ans, ans1;
void dfs(ll x, ll l, ll r) {
	if (x == 0) {
		ans.push_back(make_pair(l, r));
		return;
	}
	if (l < 0)
		l = 0;
	if (r < 0)
		r = 0;
	dfs(x - 1, a[x] + l, a[x] + r);
	dfs(x - 1, a[x] - r, a[x] - l);
}
int main() {
	while (~scanf("%lld", &k)) {
		ans1.clear();
		ans.clear();
		for (ll i = 1; i <= k; ++i) {
			scanf("%lld", &a[i]);
		}
		dfs(k, 0, 1);
		sort(ans.begin(), ans.end());
		ll x = 0;
		while (x < ans.size()) {
			ll curl = ans[x].first, curr = ans[x].second;
			x++;
			while (x < ans.size() && ans[x].first <= curr) {
				curr = max(ans[x].second, curr);
				x++;
			}
			ans1.push_back(make_pair(curl, curr));
		}
		printf("%d\n", ans1.size());
		for (ll i = 0; i < ans1.size(); ++i) {
			printf("%lld %lld\n", ans1[i].first, ans1[i].second);
		}
	}
	return 0;
}