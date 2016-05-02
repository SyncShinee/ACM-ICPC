#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 100;
int n, k, m;
int vis[N], ans;
vector <int> g[N];
void dfs(int u){
    vis[u] = 1;
    ans ++;
    for (int i = 0; i < g[u].size(); ++ i){
	int v = g[u][i];
	if (vis[v]) continue;
	dfs(v);
    }
}
int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%d %d %d", &n, &k, &m);
    for (int i = 1; i <= k; ++ i){
	int x; scanf("%d", &x);
	vis[x] = 1;
    }
    ans = k;
    for (int i = 1; i <= m; ++ i){
	int u, v; scanf("%d %d", &u, &v);
	g[v].push_back(u);
	if (!vis[u] && vis[v]){
	    dfs(u);
	}
	printf("%d\n", ans);
    }
}
