#include <cstdio>
#include <cstring>
#include <algorithm>
#define MP make_pair
#define lson l, mid, rt << 1
#define rson mid + 1, r, rt << 1 | 1
using namespace std;
const int N = 100010, INF = 1e9 + 7;
typedef pair <int, int> PII;
struct edge {
	int to, nxt;
}e[N << 1];

struct node {
	int val, len;
	node (int _v = 0, int _l = 0) : val(_v), len(_l) {}
	void update(int x) {
		len++;
		val = x;
	}
}tds_inc[N], tds_dec[N];

int n, ans, v[N], L, head[N], side, centroid[N], subtree_size[N], len_tds_inc, len_tds_dec;
int C_inc[N << 2], C_dec[N << 2];
int hs[N], len_hs;

void build(int x, int y) {
	e[side].to = y;
	e[side].nxt = head[x];
	head[x] = side ++;
}

void pushup(int C[], int rt) {
    C[rt] = max(C[rt << 1], C[rt << 1 | 1]);
}

void buildT(int l, int r, int rt) {
    C_inc[rt] = C_dec[rt] = 0;
    if (l == r) return;
    int mid = l + r >> 1;
    buildT(lson), buildT(rson);
}

int get_max(int C[], int la, int ra, int l, int r, int rt) {
    if (la <= l && r <= ra) {
        return C[rt];
    }
    int mid = l + r >> 1;
    int ret = 0;
    if (la <= mid) {
        ret = max(ret, get_max(C, la, ra, lson));
    }
    if (mid < ra) {
        ret = max(ret, get_max(C, la, ra, rson));
    }
    return ret;
}

void update(int C[], int pos, int val, int l, int r, int rt) {
    if (l == r && l == pos) {
        C[rt] = max(C[rt], val);
        return;
    }
    int mid = l + r >> 1;
    if (pos <= mid) update(C, pos, val, lson);
    else update(C, pos, val, rson);
    pushup(C, rt);
}
void get_subtree_size(int x, int pre) {
	subtree_size[x] = 1;
	hs[len_hs ++] = v[x];
	for (int i = head[x]; ~i; i = e[i].nxt) {
		if (centroid[e[i].to] || e[i].to == pre) {
			continue;
		}
		get_subtree_size(e[i].to, x);
		subtree_size[x] += subtree_size[e[i].to];
	}
}

PII find_centriod(int x, int pre, int sum) {
	PII ret = MP(INF, -1);
	int m = sum - subtree_size[x];
	for (int i = head[x]; ~i; i = e[i].nxt) {
		if (e[i].to == pre || centroid[e[i].to]) {
			continue;
		}
		ret = min(ret, find_centriod(e[i].to, x, sum));
		m = max(subtree_size[e[i].to], m);
	}
	return min(ret, MP(m, x));
}

void deal_inc(int x, int pre, node value, int base) {
	if (v[x] < value.val || v[x] - base > L) return;
	value.update(v[x]);
	tds_inc[len_tds_inc ++] = value;
	for (int i = head[x]; ~i; i = e[i].nxt) {
		if (e[i].to == pre || centroid[e[i].to]) {
			continue;
		}
		deal_inc(e[i].to, x, value, base);
	}
}

void deal_dec(int x, int pre, node value, int base) {
	if (v[x] > value.val || base - v[x] > L) return;
	value.update(v[x]);
	tds_dec[len_tds_dec ++] = value;
	for (int i = head[x]; ~i; i = e[i].nxt) {
		if (e[i].to == pre || centroid[e[i].to]) {
			continue;
		}
		deal_dec(e[i].to, x, value, base);
	}
}

void solve_subproblem(int x) {
	int pos, mx;
	len_hs = 1;
	get_subtree_size(x, -1);
	sort(hs + 1, hs + len_hs);
	len_hs = unique(hs + 1, hs + len_hs) - hs;

	int u = find_centriod(x, -1, subtree_size[x]).second;
	centroid[u] = true;
    buildT(0, len_hs, 1);
	for (int i = head[u]; ~i; i = e[i].nxt) {
		if (centroid[e[i].to]) {
			continue;
		}
        len_tds_dec = len_tds_inc = 0;
		deal_inc(e[i].to, u, node(v[u], 0), v[u]);
		deal_dec(e[i].to, u, node(v[u], 0), v[u]);
		for (int j = 0; j < len_tds_dec; ++ j) {
			pos = upper_bound(hs + 1, hs + len_hs, tds_dec[j].val + L) - hs - 1;
            mx = get_max(C_inc, 0, pos, 0, len_hs, 1);
			ans = max(ans, mx + tds_dec[j].len + 1);
		}
		for (int j = 0; j < len_tds_inc; ++ j) {
			pos = lower_bound(hs + 1, hs + len_hs, tds_inc[j].val - L) - hs;
            mx = get_max(C_dec, pos, len_hs, 0, len_hs, 1);
			ans = max(ans, tds_inc[j].len + mx + 1);
		}
		for (int j = 0; j < len_tds_dec; ++ j) {
            pos = lower_bound(hs + 1, hs + len_hs, tds_dec[j].val) - hs;
            update(C_dec, pos, tds_dec[j].len, 0, len_hs, 1);
		}
		for (int j = 0; j < len_tds_inc; ++ j) {
            pos = lower_bound(hs + 1, hs + len_hs, tds_inc[j].val) - hs;
            update(C_inc, pos, tds_inc[j].len, 0, len_hs, 1);
		}
	}
	for (int i = head[u]; ~i; i = e[i].nxt) {
		if (centroid[e[i].to]) {
			continue;
		}
		solve_subproblem(e[i].to);
	}
}

int main() {
	int T, x, y;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++ cas) {
		scanf("%d%d", &n, &L);
        ans = 1;
        memset(head, -1, sizeof head);
        memset(centroid, 0, sizeof centroid);
        side = 0;
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