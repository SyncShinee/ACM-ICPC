#include <cstdio>
#include <cstring>
#include <algorithm>
#define make_pair MP
using namespace std;
const int N = 100010;
typedef pair <int, int> PII;
struct edge {
	int to, nxt;
}e[N << 1];

struct node {
	int val, int len;
	node (int _v = 0, int _l = 0) : val(_v), len(_l) {}
	void update(int x) {
		len++;
		val = x;
	}
}tds_inc[N], tds_dec[N];

int n, head[N], side, centroid[N], subtree_size[N], len_tds_inc, len_tds_dec;
int C_inc[N], C_dec[N];
int hs[N], len_hs;
int upd_inc[N], len_upd_inc, upd_dec[N], len_upd_dec;

void build(int x, int y) {
	e[side].to = y;
	e[side].nxt = head[x];
	head[x] = side ++;
}

void get_subtree_size(int x, int pre) {
	subtree_size[x] = 1;
	hs[len_hs ++] = v[x];
	for (int i = head[x]; ~i; i = e[i].nxt) {
		if (centroid[e[i].to] || centroid[e[i].to]) {
			continue;
		}
		get_subtree_size(e[i].to, x);
		subtree_size[x] += subtree_size[e[i].to];
	}
}

PII find_centriod(int x, int pre, int sum) {
	PII ret = MP(INF, -1);
	int m = 0;
	subtree_size[x] = 1;
	for (int i = head[x]; ~i; i = e[i].nxt) {
		if (e[i].to == pre || centroid[e[i].to]) {
			continue;
		}
		ret = min(ret, find_centriod(e[i].to, x, sum));
		subtree_size[x] += subtree_size[e[i].to];
		m = max(subtree_size[e[i].to], m); 
	}
	m = max(sum - subtree_size[x], m);
	return min(ret, MP(m, x));
}

void deal_inc(int x, int pre, node value) {
	if (v[x] < value.val) return;
	value.update(v[x]);
	tds_inc[len_tds_inc ++] = value;
	for (int i = head[x]; ~i; i = e[i].nxt) {
		if (e[i].to == pre || centroid[e[i].to]) {
			continue;
		}
		deal_inc(e[i].to, x, value);
	}
}

void deal_dec(int x, int pre, node value) {
	if (v[x] > value.val) return;
	value.update(v[x]);
	tds_dec[len_tds_dec ++] = value;
	for (int i = head[x]; ~i; i = e[i].nxt) {
		if (e[i].to == pre || centroid[e[i].to]) {
			continue;
		}
		deal_dec(e[i].to, x, value);
	}
}

void solve_subproblem(int x) {
	int pos;
	len_hs = 0;
	get_subtree_size(x, -1);
	sort(hs, hs + len_hs);
	len_hs = unqiue(hs, hs + len_hs) - hs;

	int u = find_centriod(x, -1, subtree_size[x]).second;
	centroid[u] = true;
	len_upd_inc = len_upd_dec = 0;

	for (int i = head[u]; ~i; i = e[i].nxt) {
		if (centroid[e[i].to]) {
			continue;
		}
		deal_inc(e[i].to, x, node(v[x], 0));
		deal_dec(e[i].to, x, node(v[x], 0));
		for (int j = 0; j < len_tds_dec; ++ j) {
			pos = lower_bound(hs, hs + len_hs, tds_dec[j].val + L);
			ans = max(ans, tds_dec[j].len + get_max_inc(pos) + 1);
		}
		for (int j = 0; j < len_tds_inc; ++ j) {
			pos = lower_bound(hs, hs + len_hs, tds_inc[j].val - L);
			ans = max(ans, tds_dec[j].len + get_max_inc(pos) + 1);
		}
		for (int j = 0; j < len_tds_dec; ++ j) {

		}
		for (int j = 0; j < len_tds_incl ++ j) {

		}
	}
	for (int i = 0; i < len_upd; ++ i) {
		clean(upd[i]);
	}
	for (int i = head[u]; ~i; i = e[i].nxt) {
		if (centroid[e[i].to]) {
			continue;
		}
		solve_subproblem(e[i].to);
	}
}

int main() {
	int T;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++ cas) {
		scanf("%d%d", &n, &d);
		for (int i = 1; i <= n; ++ i) {
			scanf("%d", &v[i]);
		}
		for (int i = 1; i < n; ++ i) {
			scanf("%d%d", &x, &y);
			build(x, y);
			build(y, x);
		}
		solve_subproblem(1);
		printf("Case #%d: %d\n", cas, ans);
	}
	return 0;
}