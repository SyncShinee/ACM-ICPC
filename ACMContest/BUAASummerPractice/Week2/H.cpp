#pragma comment(linker,"/STACK:102400000,102400000")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define N 100010
#define M 200010
using namespace std;
struct edge { int to, nxt; }e[N << 1];
struct node { int a, b, c, id, lca; }qq[M];
typedef vector <int> :: iterator ITI;
typedef vector <node> :: iterator ITN;
int side, n, m, head[N], serial, v[N], st[N], ed[N], C[N << 1], f[N], rk[N], anc[N];
bool ans[M], vit[N];
vector <int> vex[N], q_v[N];
vector <node> q[N];
void build(int x, int y) { e[side].to = y; e[side].nxt = head[x]; head[x] = side ++; }
void update(int x, int y) { while (x <= serial) { C[x] += y; x += x & -x; } }
int getSum(int x) { int ret = 0; while (x > 0) { ret += C[x]; x -= x & -x; } return ret; }
int gf(int x) {
    if(f[x] == x) return x;
    return f[x] = gf(f[x]);
}
void merge(int x, int y) {
    x = gf(x); y = gf(y);
    if(x == y) return;
    if(rk[x] < rk[y]) f[x] = y;
    else f[y] = x, rk[x] == rk[y] ? rk[x] ++ : 0;
}
void tarjan(int x, int pre) {
    f[x] = anc[x] = x;
    st[x] = ++ serial;
    for(int i = head[x]; ~i; i = e[i].nxt) {
    	if (e[i].to == pre) {
    		continue;
    	}
        tarjan(e[i].to, x);
        merge(x, e[i].to);
        anc[gf(x)] = x;
    }
    vit[x] = true;
    for(ITI i = q_v[x].begin(); i != q_v[x].end(); ++ i) {
        int v = qq[*i].a;
        if (v == x) {
        	v = qq[*i].b;
        }
        if(vit[v]) {
        	qq[*i].lca = anc[gf(v)];
	    }
	}
	ed[x] = ++ serial;
}
int main() {
	int x, y;
	while (~scanf("%d%d", &n, &m)) {
		for (int i = 0; i <= n; ++i) {
			vex[i].clear();
			head[i] = -1;
			rk[i] = 0;
			q_v[i].clear();
			q[i].clear();
			vit[i] = 0;
		}
		for (int i = 1; i <= n; ++ i) {
			scanf("%d", &v[i]);
			if (v[i] <= n) {
				vex[v[i]].push_back(i);
			}
		}
		side = 0;
		for (int i = 1; i < n; ++ i) {
			scanf("%d%d", &x, &y);
			build(x, y);
			build(y, x);
		}
		for (int i = 0; i < m; ++ i) {
			scanf("%d%d%d", &qq[i].a, &qq[i].b, &qq[i].c);
			qq[i].id = i;
			q_v[qq[i].a].push_back(i);
			q_v[qq[i].b].push_back(i);
		}
		serial = 0;
		tarjan(1, 0);
		for (int i = 0; i < m; ++ i) {
			q[qq[i].c].push_back(qq[i]);
		}
		for(int c = 0; c <= n; ++ c) {
			for (ITI i = vex[c].begin(); i != vex[c].end(); ++ i) {
				update(st[*i], 1);
				update(ed[*i], -1);
			}
			for (ITN i = q[c].begin(); i != q[c].end(); ++ i) {
				int aa = (*i).a, bb = (*i).b, Lca = (*i).lca;
				int tmp = getSum(st[aa]) + getSum(st[bb]) - (getSum(st[Lca]) << 1);
				tmp += (v[Lca] == c);
				ans[(*i).id] = (tmp > 0);
			}
			for (ITI i = vex[c].begin(); i != vex[c].end(); ++i) {
				update(st[*i], -1);
				update(ed[*i], 1);
			}
		}
		for (int i = 0; i < m; ++i) {
			ans[i] ? puts("Find") : puts("NotFind");
		}
		puts("");
	}
	return 0;
}