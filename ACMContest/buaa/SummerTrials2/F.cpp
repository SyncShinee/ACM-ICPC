#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
typedef long long ll;
ll n;
vector<int> gra[100010];
ll ans, child[100010];

void dp(ll x, ll fa) {
	ll tmp = 0, sum = 0;
	child[x] = 1;
	for(ll i = 0; i < gra[x].size(); ++i) {
		ll v = gra[x][i];
		if(v == fa)
			continue;
		dp(v, x);
		child[x] += child[v];
		sum += tmp * child[v];
		tmp += child[v];
	}
	sum += (n - child[x]) * tmp;
	ans += sum;
}

int main() {
	ll x, y;
	while (~scanf("%I64d", &n)) {
		ans = 0;
		for (ll i = 1; i <= n; ++i)
			gra[i].clear();
		for (ll i = 1; i < n; ++i) {
			scanf("%I64d%I64d", &x, &y);
			gra[x].push_back(y);
			gra[y].push_back(x);
		}
		dp(1, 0);
		printf("%I64d\n", n*(n-1)*(n-2)/6 - ans);
	}
	return 0;
}