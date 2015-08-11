#pragma comment(linker,"/STACK:102400000,102400000")
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 40010;
const int INF = (int)1e9;

struct edge {
    int to, val, nxt;
}e[N << 1];
int head[N], side, dist[N], n, m;

void build(int x, int y, int z){
	e[side].to = y;
	e[side].val = z;
	e[side].nxt = head[x];
	head[x] = side++;
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

void get_dist(int x, int pre, int value) {
    dist[x] = value;
    for (int i = head[x]; ~i; i = e[i].nxt) {
        if (e[i].to == pre) {
            continue;
        }
        get_dist(e[i].to, x, value + e[i].val);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
    	g.initial();
        scanf("%d%d", &n, &m);
       	for(int i = 1; i < n; ++i) {
	    	int a, b, w;
			scanf("%d%d%d", &a, &b, &w);
			build(a, b, w);
			build(b, a, w);   	
     	}
        g.prepare();
        get_dist(1, -1, 0);
        while(m--) {
        	int a, b;
        	scanf("%d%d", &a, &b);
        	int anc = g.Lca(a, b);
			int ans = dist[a] + dist[b] - dist[anc] * 2;
			printf("%d\n", ans);
        }
    }
    return 0;
}