#pragma comment(linker,"/STACK:102400000,102400000")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <vector>
#define N 100010
#define MOD 1000003
#define M 1000010
#define INF 1000000000
using namespace std;
typedef long long ll;
struct edge {
	int to, next;
}e[N << 1];

int head[N], subtree_size[N], side, n;
bool centroid[N];
int len_tds, w[N], k, inv[M], ds[M];
pair <int, int> ans, tds[N];
vector <int> upd;
void build(int x, int y) {
	e[side].to = y;
	e[side].next = head[x];
	head[x] = side++;
}

pair <int, int> find_centroid(int x, int pre, int sum) {
	pair <int, int> ret = make_pair(INF, -1);
	int m = 0;
	subtree_size[x] = 1;
	for (int i = head[x]; ~i; i = e[i].next) {
		if (centroid[e[i].to] || e[i].to == pre) {
			continue;
		}
		ret = min(ret, find_centroid(e[i].to, x, sum));
		m = max(m, subtree_size[e[i].to]);
		subtree_size[x] += subtree_size[e[i].to];
	}
	m = max(m, sum - subtree_size[x]);
	return min(ret, make_pair(m, x));
}

void deal(int x, int pre, int value) {
	int tmp = ((ll)value * (ll)w[x]) % MOD;
	tds[len_tds++] = make_pair(tmp, x);
	for (int i = head[x]; ~i; i = e[i].next) {
		if (centroid[e[i].to] || e[i].to == pre) {
			continue;
		}
		deal(e[i].to, x, tmp);
	}
}

pair<int, int> mp(int x, int y) {
	if (x < y)
		return make_pair(x, y);
	else {
		return make_pair(y, x);
	}
}

void solve_subproblem(int x) {
	int u = find_centroid(x, -1, subtree_size[x]).second;
	centroid[u] = true;
	ds[1] = u;
	upd.push_back(1);
	for (int i = head[u]; ~i; i = e[i].next) {
		if (centroid[e[i].to]) {
			continue;
		}
		len_tds = 0;
		deal(e[i].to, u, 1);
		subtree_size[e[i].to] = len_tds;
		for (int j = 0; j < len_tds; ++j) {
			int t = ((ll)tds[j].first * (ll)w[u]) % MOD;
			t = ((ll)inv[t] * (ll)k) % MOD;
			if (ds[t] > -1) {
				ans = min(ans, mp(tds[j].second, ds[t]));
			}
		}
		for (int j = 0; j < len_tds; ++j) {
			if (ds[tds[j].first] == -1) {
				ds[tds[j].first] = tds[j].second;
				upd.push_back(tds[j].first);
			}
			else if (ds[tds[j].first] > tds[j].second) {
				ds[tds[j].first] = tds[j].second;
			}
		}
	}
	while(!upd.empty()){
        ds[upd.back()] = -1, upd.pop_back();
    }
	for (int i = head[u]; ~i; i = e[i].next) {
		if (centroid[e[i].to])
			continue;
		solve_subproblem(e[i].to);
	}
}

void get_inverse() {
	inv[1] = 1;
	for (int i = 2; i < MOD; ++i) {
		inv[i] = ((ll)(MOD - MOD / i) * (ll)inv[MOD % i]) % MOD;
	}
}

int main() {
	int x, y;
	get_inverse();
	memset(ds, -1, sizeof(ds));
	while (~scanf("%d%d", &n, &k)) {
		memset(head, -1, sizeof(head));
		side = 0;
		memset(centroid, 0, sizeof(centroid));
		ans = make_pair(MOD, MOD);
		for (int i = 1; i <= n; ++i)
			scanf("%d", &w[i]);
		for (int i = 1; i < n; ++i) {
			scanf("%d%d", &x, &y);
			build(x, y);
			build(y, x);
		}
		subtree_size[1] = n;
		solve_subproblem(1);
		if (ans.first < MOD) {
			printf("%d %d\n", ans.first, ans.second);
		}
		else {
			puts("No solution");
		}
	}
}