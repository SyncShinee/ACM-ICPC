#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#define N 1000010
using namespace std;

typedef long long ll;

struct node {
	ll s, m, idx;
	friend bool operator < (node a, node b) {
		return a.s < b.s;
	}
}a[N], b[N];

vector <ll> gra[N];

ll n, d, s0, As, cs, rs, m0, Am, cm, rm, l, r, kk, ans, num;

bool vis[N];
ll dfs(ll x, ll tl, ll tr) {
	ll ret = 1;
	vis[x] = true;
	for (ll i = 0; i < gra[x].size(); ++i) {
		if (!vis[gra[x][i]] && b[gra[x][i]].s >= a[tl].s && b[gra[x][i]].s <= a[tr-1].s) {
			ret += dfs(gra[x][i], tl, tr);
		}
	}
	return ret;
}

ll dfs2(ll x) {
	ll ret = 1;
	vis[x] = false;
	for (ll i = 0; i < gra[x].size(); ++i) {
		if (vis[gra[x][i]]) {
			ret += dfs2(gra[x][i]);

		}
	}
	return ret;
}

int main() {
	ll T;
	freopen("A-large.in", "r", stdin);
	freopen("a.out", "w", stdout);
	scanf("%lld", &T);
	for (ll cas = 1; cas <= T; ++cas) {
		scanf("%lld%lld", &n, &d);
		scanf("%lld%lld%lld%lld", &s0, &As, &cs, &rs);
		scanf("%lld%lld%lld%lld", &m0, &Am, &cm, &rm);
		printf("Case #%lld: ", cas);
		memset(vis, 0, sizeof (vis));
		num = 0;
		a[0].idx = 0;
		a[0].s = s0;
		a[0].m = m0;
		for (ll i = 1; i < n; ++i) {
			a[i].idx = i;
			a[i].s = (a[i-1].s * As + cs) % rs;
			a[i].m = (a[i-1].m * Am + cm) % rm;
		}
		for (ll i = 1; i < n; ++i) {
			a[i].m %= i;
		}
		a[0].m = n+1;
		for (ll i = 0; i < n; ++i) {
			b[i] = a[i];
			//printf("bsdf%lld %lld %lld\n", i, a[i].s, a[i].m);
			gra[i].clear();
		}
		sort(a, a+n);
		/*for (int i = 0; i < n; ++i) {
			printf("asdf%lld %lld %lld\n", a[i].idx, a[i].s, a[i].m);
		}*/
		for (ll i = 1; i < n; ++i) {
			gra[a[i].m].push_back(a[i].idx);
		}
		l = r = 0;
		while (r < n && a[r].s - a[l].s <= d) {
			r++;
		}
		if (r == n) {
			printf("%lld\n", n);
		}
		else {
			//printf("lr ==%lld %lld\n", l, r);
			vis[n+1] = true;
			for (int i = l; i < r; ++i) {
				if (!vis[a[i].idx] && vis[a[i].m]) {
					kk = dfs(a[i].idx, l, r);
					num += kk;
				}
			}
			ans = num;
			//printf("ans===%d\n", ans);
			while (r < n) {
				ll ltmp = l;
				ltmp++;
				while (ltmp < n && a[ltmp].s == a[l].s) {
					ltmp++;
				}
				if (ltmp == n)
					break;
				ll rtmp = r;
				while (rtmp < n && a[rtmp].s - a[ltmp].s <= d) {
					rtmp++;
				}
				for (int i = l; i < ltmp; ++i) {
					if (vis[a[i].idx]) {
						kk = dfs2(a[i].idx);
						num -= kk;
					}
				}
				for (int i = r; i < rtmp; ++i) {
					if (!vis[a[i].idx] && vis[a[i].m]) {
						kk = dfs(a[i].idx, ltmp, rtmp);
						num += kk;
					}
				}
				l = ltmp;
				r = rtmp;
				ans = max(ans, num);
				//printf("ltmp rtmp num===%lld %lld %lld\n",ltmp, rtmp, num);
			}
			printf("%lld\n", ans);
		}
	}
	return 0;
}