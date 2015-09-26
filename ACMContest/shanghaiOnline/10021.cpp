#include <cstdio>
#include <cstring>
#include <algorithm>
#define MP make_pair
using namespace std;
const int N = 10010;
const int INF = 1e9 + 7;
const int M1 = 115151, M2 = 115153;
const int base1 = 5, base2 = 17;
typedef long long ll;
typedef pair <int, int> PII;
struct node {
	node (int _val1 = 0, int _val2 = 0, int _len = 0) : val1(_val1), val2(_val2), len(_len) {}
	int val1, val2, len;
}upd_up[N], upd_down[N], tds_down[N], tds_up[N], zero, prefix[N], subfix[N];
int p1[N], p2[N];
void get_pow() {
	p1[0] = p2[0] = 1;
	for (int i = 1; i < N; ++ i) {
		p1[i] = 1ll * p1[i - 1] * base1 % M1;
		p2[i] = 1ll * p2[i - 1] * base2 % M2;
	}
}
bool operator == (const node &A, const node &B) {
	return A.val1 == B.val1 && A.val2 == B.val2;
}
node update_back(node old, char ch) {
	old.val1 = (1ll * old.val1 * base1 % M1 + ch) % M1;
	old.val2 = (1ll * p2[old.len] * ch % M2 + old.val2) % M2;
	old.len ++;
	return old;
}
node update_front(node old, char ch) {
	old.val1 = (1ll * p1[old.len] * ch % M1 + old.val1) % M1;
	old.val2 = (1ll * old.val2 * base2 % M2 + ch) % M2;
	old.len ++;
	return old;
}
struct edge {
	int to, nxt;
}e[N << 1];
int len_tds_down, len_tds_up, n, side, len_tplt, subtree_sum;
int len_upd_up, len_upd_down;
int head[N], subtree_size[N], ds1_up[M1], ds2_up[M2], ds1_down[M1], ds2_down[M2];
bool centroid[N], ans;
char val[N], tplt[N];
void build(int x, int y) {
	e[side].to = y;
	e[side].nxt = head[x];
	head[x] = side ++;
}
PII find_centroid(int x, int pre, int sum) {
	PII ret = MP(INF, -1);
	int m = 0;
	subtree_size[x] = 1;
	for (int i = head[x]; ~i; i = e[i].nxt) {
		int v = e[i].to;
		if (v == pre || centroid[v]) {
			continue;
		}
		ret = min(ret, find_centroid(v, x, sum));
		m = max(m, subtree_size[v]);
		subtree_size[x] += subtree_size[v];
	}
	m = max(m, sum - subtree_size[x]);
	return min(ret, MP(m, x));
}
void deal(int x, int pre, node hs_down, node hs_up) {
	//printf("x === %d\n", x);
	subtree_sum++;
	hs_down = update_back(hs_down, val[x]);
	hs_up = update_front(hs_up, val[x]);
	/*printf("downlen === %d\n", hs_down.len);
	printf("down = %d %d\n", hs_down.val1, hs_down.val2);
	printf("subfix = %d %d\n", subfix[hs_down.len].val1, subfix[hs_down.len].val2);
	printf("uplen === %d\n", hs_up.len);
	printf("up = %d %d\n", hs_up.val1, hs_up.val2);
	printf("prefix = %d %d\n", prefix[hs_up.len].val1, prefix[hs_up.len].val2);*/
	if (hs_down == subfix[hs_down.len]) {
		//printf("down = %d %d\n", hs_down.val1, hs_down.val2);
		tds_down[len_tds_down ++] = hs_down;
	}
	if (hs_up == prefix[hs_up.len]) {
		//printf("up = %d %d\n", hs_up.val1, hs_up.val2);
		tds_up[len_tds_up ++] = hs_up;
	}
	for (int i = head[x]; ~i; i = e[i].nxt) {
		if (centroid[e[i].to] || e[i].to == pre) {
			continue;
		}
		deal(e[i].to, x, hs_down, hs_up);
	}
}
bool judge(int tag, node hs) {
	if (tag == 1) {
		return ds1_down[hs.val1] && ds2_down[hs.val2];
	}
	else {
		return ds1_up[hs.val1] && ds2_up[hs.val2];
	}
}
void sove_subproblem(int x) {
	if (ans) {
		return;
	}
	int u = find_centroid(x, -1, subtree_size[x]).second;
	//printf("centroid = %d\n", u);
	centroid[u] = true;
	len_upd_down = len_upd_up = 0;
	node now = update_front(zero, val[u]);
	ds1_up[now.val1] = true;
	ds2_up[now.val2] = true;
	upd_up[len_upd_up ++] = now;
	now = update_back(zero, val[u]);
	ds1_down[now.val1] = true;
	ds2_down[now.val2] = true;
	upd_down[len_upd_down ++] = now;
	for (int i = head[u]; ~i; i = e[i].nxt) {
		int v = e[i].to;
		if (centroid[v]) {
			continue;
		}
		len_tds_up = len_tds_down = 0;
		subtree_sum = 1;
		deal(v, u, zero, zero);
		subtree_size[v] = subtree_sum;
		for (int j = 0; j < len_tds_up; ++ j) {
			if (judge(1, subfix[len_tplt - tds_up[j].len])) {
				ans = true;
				return;
			}
		}
		for (int j = 0; j < len_tds_down; ++ j) {
			if (judge(2, prefix[len_tplt - tds_down[j].len])) {
				ans = true;
				return;
			}
		}
		for (int j = 0; j < len_tds_up; ++ j) {
			now = update_back(tds_up[j], val[u]);
			ds1_up[now.val1] = true;
			ds2_up[now.val2] = true;
			upd_up[len_upd_up ++] = now;
		}
		for (int j = 0; j < len_tds_down; ++ j) {
			now = update_front(tds_down[j], val[u]);
			ds1_down[now.val1] = true;
			ds2_down[now.val2] = true;
			upd_down[len_upd_down ++] = now;
		}
	}
	for (int i = 0; i < len_upd_up; ++ i) {
		ds1_up[upd_up[i].val1] = ds2_up[upd_up[i].val2] = 0;
	}
	for (int i = 0; i < len_upd_down; ++ i) {
		ds1_down[upd_down[i].val1] = ds2_down[upd_down[i].val2] = 0;
	}
	for (int i = head[u]; ~i; i = e[i].nxt) {
		if (centroid[e[i].to]) {
			continue;
		}
		sove_subproblem(e[i].to);
	}
}
int main() {
	freopen("in.txt", "r", stdin);
	int T, x, y;
	scanf("%d", &T);
	get_pow();
	for (int cas = 1; cas <= T; ++ cas) {
		scanf("%d", &n);
		side = ans = 0;
		memset(head, -1, sizeof head);
		memset(centroid, 0, sizeof centroid);
		for (int i = 1; i < n; ++ i) {
			scanf("%d%d", &x, &y);
			build(x, y);
			build(y, x);
		}
		scanf("%s", val + 1);
		scanf("%s", tplt);
		len_tplt = strlen(tplt);
		node now = zero;
		for (int i = 0; i < len_tplt; ++ i) {
			now = update_back(now, tplt[i]);
			prefix[i + 1] = now;
		}
		now = zero;
		for (int i = len_tplt - 1; i >= 0; -- i) {
			now = update_front(now, tplt[i]);
			subfix[len_tplt - i] = now;
		}
		subtree_size[1] = n;
		sove_subproblem(1);
		printf("Case #%d: ", cas);
		if (ans) {
			puts("Find");
		}
		else {
			puts("Impossible");
		}
	}
}