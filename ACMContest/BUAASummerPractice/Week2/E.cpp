#pragma comment(linker,"/STACK:102400000,102400000")
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
#define N 100010
#define MOD 1000003
#define INF 1000000007
using namespace std;

struct edge {
	int to, nxt;
}e[N << 1];

struct node {
	int v, id;
	node(int _v = 0, int _id = 0) : v(_v), id(_id) {}
}tds[N];

int side, head[N], subtree_size[N], len_tds, n, k, w[N], inv[MOD], mp[MOD], upd[N], len_upd;
bool centroid[N];
pair <int, int> ans;
void build(int x, int y) {
	e[side].to = y;
	e[side].nxt = head[x];
	head[x] = side ++;
}

pair <int ,int> find_centroid(int x, int pre, int sum) {
	subtree_size[x] = 1;
	pair <int, int> ret = make_pair(INF, -1);
	int mx = 0;
	for (int i = head[x]; ~i; i = e[i].nxt) {
		if (centroid[e[i].to] || e[i].to == pre) {
			continue;
		}
		ret = min(ret, find_centroid(e[i].to, x, sum));
		mx = max(mx, subtree_size[e[i].to]);
		subtree_size[x] += subtree_size[e[i].to];
	}
	mx = max(mx, sum - subtree_size[x]);
	return min(ret, make_pair(mx, x));
}

void deal(int x, int pre, int val) {
	val = 1ll * val * w[x] % MOD;
	tds[len_tds ++] = node(val, x);
	for (int i = head[x]; ~i; i = e[i].nxt) {
		if (centroid[e[i].to] || e[i].to == pre) {
			continue;
		}
		deal(e[i].to, x, val);
	}
}

void solve_subproblem(int x) {
	int u = find_centroid(x, -1, subtree_size[x]).second;
	centroid[u] = true;
	len_upd = 0;
	mp[1] = u;
	upd[len_upd ++] = 1;
	for (int i = head[u]; ~i; i = e[i].nxt) {
		if (centroid[e[i].to]) {
			continue;
		}
		len_tds = 0;
		deal(e[i].to, u, 1);
		subtree_size[e[i].to] = len_tds;
		for (int j = 0; j < len_tds; ++ j) {
			int fd = 1ll * tds[j].v * w[u] % MOD;
			fd = 1ll * inv[fd] * k % MOD;
			if (mp[fd] > -1) {
				int ans1 = mp[fd], ans2 = tds[j].id;
				if (ans1 > ans2) {
					swap(ans1, ans2);
				}
				ans = min(ans, make_pair(ans1, ans2));
			}
		}
		for (int j = 0; j < len_tds; ++ j) {
			if (mp[tds[j].v] > -1) {
				mp[tds[j].v] = min(tds[j].id, mp[tds[j].v]);
			}
			else {
				mp[tds[j].v] = tds[j].id;
				upd[len_upd ++] = tds[j].v;
			}
		}
	}
	for (int i = 0; i < len_upd; ++ i) {
		mp[upd[i]] = -1;
	}
	for (int i = head[u]; ~i; i = e[i].nxt) {
		if (centroid[e[i].to]) {
			continue;
		}
		solve_subproblem(e[i].to);
	}
}
int main() {
	int x, y;
	inv[1] = 1;
	for (int i = 2; i < MOD; ++i) 
		inv[i] = 1ll * (MOD - MOD / i) * inv[MOD % i] % MOD;
	while (~scanf("%d%d", &n, &k)) {
		memset(mp, -1, sizeof mp);
		memset(centroid, 0, sizeof centroid);
		for (int i = 1; i <= n; ++ i) {
			scanf("%d", &w[i]);
			head[i] = -1;
		}
		side = 0;
		for (int i = 1; i < n; ++ i) {
			scanf("%d%d", &x, &y);
			build(x, y);
			build(y, x);
		}
		ans = make_pair(n + 1, n + 1);
		subtree_size[1] = n;
		solve_subproblem(1);
		if (ans.first == n + 1) {
			printf("No solution\n");
		}
		else {
			printf("%d %d\n", ans.first, ans.second);
		}
	}
	return 0;
}