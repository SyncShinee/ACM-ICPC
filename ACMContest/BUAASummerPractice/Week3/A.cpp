#pragma comment(linker,"/STACK:102400000,102400000")
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 50010;
typedef long long ll;
struct edge {
	int to, id, nxt;
}e[N << 1];
int head[N], side, n, m, w[N];
ll C[N << 1];
int in[N], out[N], belong[N], dfs_clock;
void build(int x, int y, int z) {
	e[side].to = y;
	e[side].id = z;
	e[side].nxt = head[x];
	head[x] = side ++;
}
int deep[N], anc[N][20];
struct LCA_online {
	void initial(){
	    side = deep[1] = 0;
	    memset(head, -1, sizeof head);
	}
	void dfs(int x, int pre) {
	    for(int i = head[x]; ~i; i = e[i].nxt) {
	        int v = e[i].to;
	        if(v != pre) {
	        	anc[v][0] = x;
	            deep[v] = deep[x] + 1;
	            dfs(v, x);
	        }
	    }
	}
	void prepare() {
		dfs(1, -1);
		for(int i = 1; i <= n; i++) {
	        for(int j = 1; (1 << j) <= n; j++) anc[i][j] = -1;
	    }
	    for(int j = 1; (1 << j) <= n; j++) {
			for(int i = 1; i <= n; i++) {
	    		if(anc[i][j - 1] != -1) {
	        		int a = anc[i][j - 1];
	        		anc[i][j] = anc[a][j - 1];
	    		}
	    	}
	    }
	}
	int Lca(int p, int q) {
	    int lo;
	    if(deep[p] < deep[q]) swap(p, q);
	    for(lo = 1; (1 << lo) <= deep[p]; lo++); lo--;
	    for(int i = lo; i >= 0; i--)
	        if(deep[p] - (1 << i) >= deep[q]) 
				p = anc[p][i];
	    if(p == q)
			return p;
	    for(int i = lo; i >= 0; i--)
	    	if(anc[p][i] != -1 && anc[p][i] != anc[q][i]) {
	        	p = anc[p][i];
	        	q = anc[q][i];
	    	}
	   	return anc[p][0];
	}
}g;
void get_dfs(int x, int pre, int idx) {
	in[idx] = ++dfs_clock;
	belong[x] = idx;
	for (int i = head[x]; ~i; i = e[i].nxt) {
		if (pre != e[i].to) {
			get_dfs(e[i].to, x, e[i].id);
		}
	}
	out[idx] = ++dfs_clock;
}
ll getSum(int x) {
	ll ret = 0;
	while (x) {
		ret += C[x];
		x -= x & -x;
	}
	return ret;
}
void update(int x, ll y) {
	while (x <= (n << 1)) {
		C[x] += y;
		x += x & -x;
	}
}
int main() {
	int x, y, z;
	while (~scanf("%d%d", &n, &m)) {
		g.initial();
		dfs_clock = 0;
		for (int i = 1; i < n; ++ i) {
			scanf("%d%d%d", &x, &y, &z);
			build(x, y, i);
			build(y, x, i);
			w[i] = z;
		}
		g.prepare();
		get_dfs(1, 0, 0);
		memset(C, 0, sizeof C);
		for (int i = 1; i < n; ++i) {
			update(in[i], w[i]);
			update(out[i], -w[i]);
		}
		while (m --) {
			scanf("%d%d%d", &x, &y, &z);
			if (x) {
				printf("%I64d\n", getSum(in[belong[y]]) + getSum(in[belong[z]]) - 2 * getSum(in[belong[g.Lca(y, z)]]));
			}
			else {
				ll change = z - w[y];
				w[y] = z;
				update(in[y], change);
				update(out[y], -change);
			}
		}
	}
	return 0;
}