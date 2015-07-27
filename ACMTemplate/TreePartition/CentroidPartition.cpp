#include <cstdio>
#include <algorithm>
#include <cstring>
#define INF 1000000000
#define N 10010
using namespace std;
struct edge {
	int to, val, next;
}e[N << 1];

int head[N], subtree_size[N], side, n;
bool centroid[N];
int ds[N], tds[N], len_ds, len_tds, k, ans;

void build(int x, int y, int z) {
	e[side].to = y;
	e[side].val = z;
	e[side].next = head[x];
	head[x] = side++;
}

void compute_subtree_size(int x, int pre) {
	subtree_size[x] = 1;
	for (int i = head[x]; ~i; i = e[i].next) {
		if (centroid[e[i].to] || e[i].to == pre) {
			continue;
		}
		compute_subtree_size(e[i].to, x);
		subtree_size[x] += subtree_size[e[i].to];
	}
}

pair <int, int> find_centroid(int x, int pre, int sum) {
	pair <int, int> ret = make_pair(INF, -1);
	int m = 0;
	for (int i = head[x]; ~i; i = e[i].next) {
		if (centroid[e[i].to] || e[i].to == pre) {
			continue;
		}
		ret = min(ret, find_centroid(e[i].to, x, sum));
		m = max(m, subtree_size[e[i].to]);
	}
	m = max(m, sum - subtree_size[x]);
	return min(ret, make_pair(m, x));
}

void deal(int x, int pre, int value) {
	tds[len_tds++] = value;
	for (int i = head[x]; ~i; i = e[i].next) {
		if (centroid[e[i].to] || e[i].to == pre) {
			continue;
		}
		deal(e[i].to, x, e[i].val + value);
	}
}

int count_pairs(int a[], int len) {
	int ret = 0;
	sort(a, a + len);
	int l = 0, r = len - 1;
	while (l < r) {
		while (l < r && a[l] + a[r] > k) {
			r--;
		}
		ret += r - l;
		l++;
	}
	return ret;
}

void solve_subproblem(int x) {
	compute_subtree_size(x, -1);
	int u = find_centroid(x, -1, subtree_size[x]).second;
	centroid[u] = true;
	len_ds = 0;
	ds[len_ds++] = 0;
	for (int i = head[u]; ~i; i = e[i].next) {
		if (centroid[e[i].to])
			continue;
		len_tds = 0;
		deal(e[i].to, u, e[i].val);
		ans -= count_pairs(tds, len_tds);
		for (int j = 0; j < len_tds; ++j)
			ds[len_ds++] = tds[j];
	}
	ans += count_pairs(ds, len_ds);
	for (int i = head[u]; ~i; i = e[i].next) {
		if (centroid[e[i].to])
			continue;
		solve_subproblem(e[i].to);
	}
}
int main() {
	int x, y, z;
	while (scanf("%d%d", &n, &k), n | k) {
		memset(head, -1, sizeof(head));
		memset(centroid, 0, sizeof centroid);
		side = 0;
		for (int i = 1; i < n; ++i) {
			scanf("%d%d%d", &x, &y, &z);
			build(x, y, z);
			build(y, x, z);
		}
		ans = 0;
		solve_subproblem(1);
		printf("%d\n", ans);
	}
	return 0;
}