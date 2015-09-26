#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;
const int N = 20010, M = 200010, INF = 1e9;
int head[N], C[N], n, m, ans, side, pos, son[N], top[N],edge_p[N], fedge_p[N];
struct edge {
	int to, nxt;
}e[N << 1];
struct Edge {
	int u, v;
}E[M];
void build(int x, int y) {
	e[side].to = y;
	e[side].nxt = head[x];
	head[x] = side++;
}
void upd(int x, int val) {
	for (;x <= pos; x += x & -x) {
		C[x] += val;
	}
}
void update(int x, int y) {
	upd(x, 1);
	upd(y + 1, -1);
}
int getsum(int x) {
	int ret = 0;
	for (; x; x -= x & -x) {
		ret += C[x];
	}
	return ret;
}
inline bool scan_d(int &ret) {
char c; int sgn;
if(c=getchar(),c==EOF) return 0; //EOF
while(c!='-'&&(c<'0'||c>'9')) c=getchar();
sgn=(c=='-')?-1:1;
ret=(c=='-')?0:(c-'0');
while(c=getchar(),c>='0'&&c<='9') ret=ret*10+(c-'0');
ret*=sgn;
return 1;
}
int deep[N], fa[N], subtree_size[N];
void dfs1(int x, int pre) {
	deep[x] = deep[pre] + 1;
	fa[x] = pre;
	subtree_size[x] = 1;
	for (int i = head[x]; ~i; i = e[i].nxt) {
		if (e[i].to == pre) continue;
		dfs1(e[i].to, x);
		subtree_size[x] += subtree_size[e[i].to];
		if (son[x] != -1 || subtree_size[son[x]] < subtree_size[e[i].to]) {
			son[x] = e[i].to;
		}
	}
}
void get_pos(int x, int pre) {
	top[x] = pre;
	if (son[x] != -1) {
		edge_p[x] = pos++;
		fedge_p[edge_p[x]] = x;
		get_pos(son[x], pre);
	}
	else {
		edge_p[x] = pos++;
		fedge_p[edge_p[x]] = x;
		return;
	}
	for (int i = head[x]; ~i; i = e[i].nxt) {
		if (e[i].to == son[x] || e[i].to == fa[x]) continue;
		get_pos(e[i].to, e[i].to);
	}
}
void modify(int u, int v) {
	int f1 = top[u], f2 = top[v];
	while (f1 != f2) {
		if (deep[f1] < deep[f2]) {
			swap(f1, f2);
			swap(u, v);
		}
		update(edge_p[f1], edge_p[u]);
		u = fa[f1];
		f1 = top[u];
	}
	if (u == v) return;
	if (deep[u] > deep[v]) swap(u, v);
	update(edge_p[son[u]], edge_p[v]);
}
int main() {
	int T;
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++ cas) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++ i)
			head[i] = son[i] = -1;
		side = 0;
		for (int i = 0; i < m; ++ i) {
			//scanf("%d%d", &E[i].u, &E[i].v);
			scan_d(E[i].u);
			scan_d(E[i].v);
			if (i < n - 1) {
				build(E[i].u, E[i].v);
				build(E[i].v, E[i].u);
			}
		}
		deep[0] = 0;
		pos = 0;
		dfs1(1, 0);
		get_pos(1, 0);
		pos--;
		for (int i = 1; i <= pos; ++ i)
			C[i] = 0;
		for (int i = m - 1; i >= 0; -- i) {
			modify(E[i].u, E[i].v);
		}
		ans = INF;
		for (int i = 1; i <= pos; ++ i) {
			ans = min(ans, getsum(i));
			if (ans == 1) break;
		}
		printf("Case #%d: %d\n", cas, ans);
	}
	return 0;
}