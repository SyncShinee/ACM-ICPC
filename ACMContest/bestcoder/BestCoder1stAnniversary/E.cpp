#pragma comment(linker, "/STACK:102400000,102400000")
#include <cstdio>
#include <algorithm>
#include <cstring>
#define N 100010
#define INF 1000000007

using namespace std;
typedef long long ll;
struct edge {
	int to, next;
}e[N << 1];

int w[N], n, k, x, y;
int head[N], subtree_size[N], side, len_tds, len_ds, idx[N], que[N], Tsize;
ll ans, C[N];
bool centroid[N];
struct node {
	int l, r;
	node () {}
	node (int _l, int _r) {
		l = _l; 
		r = _r;
	}
	friend bool operator < (node x, node y) {
		return x.l < y.l || x.l == y.l && x.r < y.r;
	}
}ds[N], tds[N];

ll getSum(int x) {
	ll ret = 0;
	while (x > 0) {
		ret += C[x];
		x -= x & (-x);
	}
	return ret;
}

void build(int x, int y) {
	e[side].to = y;
	e[side].next = head[x];
	head[x] = side++;
}

pair <int , int> find_centroid(int x, int pre, int sum) {
	pair <int ,int> ret = make_pair(INF, -1);
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

void deal(int x, int pre, int mn, int mx) {
	mn = min(mn, w[x]);
	mx = max(mx, w[x]);
	if (mx - mn <= k)
		tds[len_tds++] = node(mn, mx);
	Tsize++;
	for (int i = head[x]; ~i; i = e[i].next) {
		if (centroid[e[i].to] || e[i].to == pre) {
			continue;
		}
		deal(e[i].to, x, mn, mx);
	}
}

ll count_pair(node a[], int len) {
	if (len <= 1)
		return 0;
	ll ret = 0;
	sort(a, a + len);
	for (int i = 0; i < len; ++i) {
		idx[i + 1] = a[i].r;
	}
	sort(idx + 1, idx + len + 1);
	int len_idx = unique(idx + 1, idx + len + 1) - idx;
	for (int i = len - 1; i >= 0; --i) {
		int tmp = max(a[i].l + k, a[i].r);
		int pos1 = upper_bound(idx + 1, idx + len_idx, tmp) - idx - 1;
		//int pos2 = lower_bound(idx + 1, idx + len_idx, a[i].r - k) - idx - 1;
		que[i] = lower_bound(idx + 1, idx + len_idx, a[i].r) - idx;
		ret += getSum(pos1);
		for (int j = que[i]; j < len_idx; j += j & (-j)) {
			C[j]++;
		}
	}
	for (int i = 0; i < len; ++i) {
		for (int j = que[i]; j < len_idx; j += j & (-j)) {
			C[j]--;
		}
	}
	return ret;
}

void solve_subproblem(int x) {
	int u = find_centroid(x, -1, subtree_size[x]).second;
	centroid[u] = true;
	len_ds = 0;
	ds[len_ds++] = node(w[u], w[u]);
	for (int i = head[u]; ~i; i = e[i].next) {
		if (centroid[e[i].to]) {
			continue;
		}
		len_tds = Tsize = 0;
		deal(e[i].to, u, w[u], w[u]);
		subtree_size[e[i].to] = Tsize;
		ans -= count_pair(tds, len_tds);
		for (int j = 0; j < len_tds; ++j) {
			ds[len_ds++] = tds[j];
		}
	}
	ans += count_pair(ds, len_ds);
	for (int i = head[u]; ~i; i = e[i].next) {
		if (centroid[e[i].to]) {
			continue;
		}
		solve_subproblem(e[i].to);
	}
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &k);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &w[i]);
		}
		side = 0;
		memset(head, -1, sizeof head);
		for (int i = 1; i < n; ++i) {
			scanf("%d%d", &x, &y);
			build(x, y);
			build(y, x);
		}
		ans = 0;
		memset(centroid, 0, sizeof centroid);
		subtree_size[1] = n;
		solve_subproblem(1);
		printf("%I64d\n", ans + ans);
	}
	return 0;
}