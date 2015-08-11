#include <cstdio>
#include <cstring>
#include <algorithm>
#define lson l, m, k << 1
#define rson m + 1, r, k << 1 | 1
using namespace std;

const int INF = 0x7fffffff;
const int N = 100010;

struct edge{
	int to, nxt;
}e[N << 1];

struct T {
	int mn, tag;
}f[N << 3];

int head[N], side, anc[N][18], dep[N], sz[N], son[N], top[N], root, in[N], out[N], dfs_clock, n, q, w[N], b[N << 1];


void build(int x, int y){
	e[side].to = y;
	e[side].nxt = head[x];
	head[x] = side++;
}

void dfs1(int x) {
	sz[x] = 1;
	for (int i = head[x]; ~i; i = e[i].nxt) {
		int v = e[i].to; 
		if(v == anc[x][0]) 
			continue;
		anc[v][0] = x; 
		dep[v] = dep[x] + 1; 
		for (int i = 1; i < 18; ++i) 
			anc[v][i] = anc[anc[v][i-1]][i-1];
		dfs1(v);
		sz[x] += sz[v];
		if(sz[son[x]] < sz[v]) 
			son[x] = v;
	}
}

void dfs2(int x, int tp) {
	in[x] = ++dfs_clock; 
	b[dfs_clock] = w[x];
	top[x] = tp;
	if(son[x]) 
		dfs2(son[x], tp);
	for (int i = head[x]; ~i; i = e[i].nxt) {
		int v = e[i].to; 
		if(v == anc[x][0] || v == son[x]) 
			continue;
		dfs2(v, v);
	}
	out[x] = ++dfs_clock;
	b[dfs_clock] = INF;
}

int getanc(int x, int d) {
	d = dep[x] - d;
	for (int i = 0; i < 18; ++i) { 
		if(d & (1 << i)) { 
			x = anc[x][i];
		}
	}
	return x;
}

T put(T a, T b) {
	T c;
	c.mn = min(a.mn, b.mn);
	c.tag = 0;
	return c;
}

void mk(int l, int r, int k) {
	if (l == r) {
		f[k].mn = b[l];
		return;
	}
	int m = (l + r) >> 1;
	mk(lson);
	mk(rson);
	f[k] = put(f[k << 1], f[k << 1 | 1]);
}

void pushDown(int k) {
	if (f[k].tag) {
		f[k << 1].tag = f[k << 1 | 1].tag = f[k].tag;
		f[k << 1].mn = f[k].tag;
		f[k << 1 | 1].mn = f[k].tag;
		f[k].tag = 0;
	}
}

void update(int la, int ra, int l, int r, int k, int val) {
	if(la <= l && r <= ra) {
		f[k].tag = f[k].mn = val;
		return;
	}
	pushDown(k);
	int m = (l + r) >> 1;
	if (la <= m) {
		update(la, ra, lson, val);
	}
	if (ra > m) {
		update(la, ra, rson, val);
	}
	f[k] = put(f[k << 1], f[k << 1 | 1]);
}

T query(int la, int ra, int l, int r, int k) {
	if(la <= l && r <= ra) 
		return f[k];
	pushDown(k);
	int m = (l + r) >> 1;
	if(ra <= m) { 
		return query(la, ra, lson);
	}
	if(la > m) { 
		return query(la, ra, rson); 
	}
	T t1 = query(la, ra, lson), t2 = query(la, ra, rson);
	return put(t1, t2);
}

void modify(int a, int b, int x) {
	for(int ta = top[a], tb = top[b]; ta != tb; a = anc[ta][0], ta = top[a]) {
		if(dep[ta] < dep[tb]) {
			swap(a,b), swap(ta,tb);
		}
		update(in[ta], in[a], 1, n << 1, 1, x);
	}
	if(dep[a] > dep[b]) { 
		swap(a, b);
	}
	update(in[a], in[b], 1, n << 1, 1, x);
}

int main() {
	int x, y, z, op;
    memset(head, -1, sizeof head);
    side = 0;
    scanf("%d%d", &n, &q);
    for (int i = 1; i < n; ++i) {
    	scanf("%d%d", &x, &y);
    	build(x, y);
    	build(y, x);
    }
    for (int i = 1; i <= n; ++i) {
    	scanf("%d", &w[i]);
    }
    scanf("%d", &root);
    dfs1(root);
    dfs2(root, root);
    mk(1, n << 1, 1);
    while (q --) {
    	scanf("%d", &op);
    	if (op == 1) {
    		scanf("%d", &root);
    	}
    	else if (op == 2) {
    		scanf("%d%d%d", &x, &y, &z);
    		modify(x, y, z);
    	}
    	else {
    		scanf("%d", &x);
    		if (x == root) {
    			printf("%d\n", query(1, n << 1, 1, n << 1, 1).mn);
    		}
    		else if (dep[x] < dep[root] && getanc(root, dep[x]) == x) {
    			x = getanc(root, dep[x] + 1);
				int ans = query(1, in[x] - 1, 1, n << 1, 1).mn;
				ans = min(ans, query(out[x] + 1, n << 1, 1, n << 1, 1).mn);
				printf("%d\n",ans);
    		}
    		else {
    			printf("%d\n", query(in[x], out[x], 1, n << 1, 1).mn);
    		}
    	}
    }
    return 0;
}
