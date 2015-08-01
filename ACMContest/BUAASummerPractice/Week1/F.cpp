#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
#include <stack>
#define N 100010
using namespace std;
typedef long long ll;
struct edge {
	ll to, next;
}e[N << 1];
ll vis[N], head[N], n, side, u, v, pre[N], nxt[N], deep[N], dmt1, dmt2, dmt_len, f[N][2];
queue <ll> q;
void build(ll x, ll y) {
	e[side].to = y;
	e[side].next = head[x];
	head[x] = side++;
}

int main() {
	scanf("%lld", &n);
	side = 0;
	memset(head, -1, sizeof head);
	for (ll i = 1; i < n; ++i) {
		scanf("%lld%lld", &u, &v);
		build(u, v);
		build(v, u);
	}
	memset(vis, 0, sizeof vis);
	memset(deep, 0, sizeof deep);
	q.push(1);
	vis[1] = 1;
	while (!q.empty()) {
		u = q.front();
		q.pop();
		for (ll i = head[u]; ~i; i = e[i].next) {
			if (!vis[e[i].to]) {
				vis[e[i].to] = 1;
				q.push(e[i].to);
			}
		}
	}
	dmt2 = u;
	q.push(u);
	vis[u] = 2;
	while (!q.empty()) {
		u = q.front();
		q.pop();
		for (ll i = head[u]; ~i; i = e[i].next) {
			if (vis[e[i].to] < 2) {
				vis[e[i].to] = 2;
				pre[e[i].to] = u;
				q.push(e[i].to);
			}
		}
	}
	dmt1 = u;
	memset(vis, 0, sizeof vis);
	dmt_len = 0;
	for (ll i = dmt1; i != dmt2; i = pre[i]) {
		vis[i] = 3;
		dmt_len++;
		nxt[pre[i]] = i;
	}
	vis[dmt2] = 3;
	v = 0;
	ll ans = (dmt_len / 2) * ((dmt_len - 1) / 2);
	for (ll x = dmt1; x != dmt2; x = pre[x]) {
		f[x][0] = v;
		f[x][1] = dmt_len - v;
		for (ll y = head[x]; ~y; y = e[y].next) {
			if (vis[e[y].to]) { 
				continue;
			}
			q.push(e[y].to);
			vis[e[y].to] = 1;
			deep[e[y].to] = 1;
			while (!q.empty()) {
				u = q.front();
				q.pop();
				for (ll i = head[u]; ~i; i = e[i].next) {
					if (!vis[e[i].to]) {
						vis[e[i].to] = 1;
						q.push(e[i].to);
						deep[e[i].to] = deep[u] + 1;
					}
				}
			}
			f[x][0] = max(deep[u] + v, f[x][0]);
			f[x][1] = max(deep[u] + dmt_len - v, f[x][1]);

			q.push(u);
			vis[u] = 2;
			deep[u] = 0;
			while (!q.empty()) {
				u = q.front();
				q.pop();
				for (ll i = head[u]; ~i; i = e[i].next) {
					if (vis[e[i].to] < 2) {
						vis[e[i].to] = 2;
						deep[e[i].to] = deep[u] + 1;
						q.push(e[i].to);
					}
				}
			}
			ans = max(ans, dmt_len * deep[u]);
		}
		v++;
	}
	ll mx = 0;
	for (ll i = dmt1; i != dmt2; i = pre[i]) {
		mx = max(mx, f[i][0]);
		ans = max(ans,  mx * f[pre[i]][1]);
	}
	mx = 0;
	for (ll i = dmt2; i != dmt1; i = nxt[i]) {
		mx = max(mx, f[i][1]);
		ans = max(ans, mx * f[nxt[i]][0]);
	}
	printf("%lld\n", ans);
	return 0;
}