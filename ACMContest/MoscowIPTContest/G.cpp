#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 2e5 + 100;
int n;
vector <int> g[N];
ll d[N], f[N][30], dep[N], fs[N], fsum[N];
ll dsum[N], s[N];
void dfs(int u, int fa){
    f[u][0] = fa;
    if (fa > 0) dep[u] = dep[fa] + 1;
    ll &res = d[u] = 0;
    int num = 1;
    if (u != 1) s[u] = 1;
    for (auto &v : g[u]){
	if (v == fa) continue;
	dfs(v, u);
	num ++;
	s[u] ++;
	dsum[u] += d[v];
	res += d[v];
    }
    res += num;
}
void dfs2(int u, int fa){
    if (fa >= 0){
	//	if (u == 2) printf("%d %d %d\n", fsum[u], d[u], s[fa]);
	fs[u] = dsum[fa] - d[u] + fs[fa] + s[fa];
	fsum[u] = fs[u] + fsum[fa];
	d[u] += d[fa];
    }
    for (auto &v : g[u]){
	if (v == fa) continue;
	dfs2(v, u);
    }
}

void init(){
    for (int i = 1; i <= 20; ++ i){
	for (int j = 1; j <= n; ++ j){
	    if (f[f[j][i - 1]][i - 1] > 0){
		f[j][i] = f[f[j][i - 1]][i - 1];
	    }else{
		f[j][i] = -1;
	    }
	}
    }
}
int lca(int u, int v){
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = 20; i >= 0; -- i){
	if (f[u][i] > 0 && dep[f[u][i]] >= dep[v]){
	    u = f[u][i];
	}
    }
    if (u == v) return u;
    for (int i = 20; i >= 0; -- i){
	if (f[u][i] != f[v][i]){
	    u = f[u][i];
	    v = f[v][i];
	}
    }
    return f[u][0];
}
int main(){
    // freopen("E.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i < n; ++ i){
	int u, v;
	scanf("%d %d", &u, &v);
	g[u].push_back(v);
	g[v].push_back(u);
    }
    dfs(1, -1);
    fs[1] = fsum[1] = 0;
    d[1] = 0;
   
    dfs2(1, -1);
    init();
    //   printf("%d %d\n", fsum[2], d[2]);
    int q; scanf("%d", &q);
    for (int i = 1; i <= q; ++ i){
	int u, v; scanf("%d %d", &u, &v);
	int lc = lca(u, v);
	printf("%lld\n", d[u] + fsum[v] - d[lc] - fsum[lc]);
    }
}
