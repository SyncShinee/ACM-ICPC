#include <cstdio>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <vector>
#include <stack>
using namespace std;
const int N = 100010;
const int SZ = 16383;
int vis[N], dfn[N], low[N], now, num, size[N], idex[N];
vector <int> g[N], G[N];
stack <int> sta;
void tarjan(int x) {
    vis[x] = 2;
    dfn[x] = low[x] = ++ now;
    sta.push(x);
    for (int i = 0; i < g[x].size(); ++ i) {
	if (vis[g[x][i]] == 0) {
	    tarjan(g[x][i]);
	    low[x] = min(low[x], low[g[x][i]]);
	}
	else if (vis[g[x][i]] == 2) {
	    low[x] = min(low[x], dfn[g[x][i]]);
	}
    }
    if (low[x] == dfn[x]) {
	num++;
	while (1) {
	    int t = sta.top();
	    sta.pop();
	    vis[t]= 1;
	    idex[t] = num;
	    size[num] ++;
	    if (t == x) {
		break;
	    }
	}
    }
}
struct node {
    int l, r;
    node (int _l = 0, int _r = 0) : l(_l), r(_r) {}
};

bool operator < (const node &A, const node &B) {
    return A.r < B.r;
}
vector <node> q;

bitset <16384> bit[N];

void dfs(int x, int block) {
    //printf("----------%d\n", x);
    vis[x] = 1;
    bit[x].reset();
    if (x / SZ == block) {
	bit[x].set(x % SZ);
    }
    for (int i = 0; i < G[x].size(); ++ i) {
	if (!vis[G[x][i]]) {
	    dfs(G[x][i], block);
	}
	bit[x] |= bit[G[x][i]];
    }
    //printf("%llu\n", bit[x].to_ulong());
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int x, y, ans, t, n;
    scanf("%d", &n);
    scanf("%d", &ans);
    for (int i = 0; i < ans; ++ i) {
	scanf("%d%d", &x, &y);
	g[x].push_back(y);
    }
    for (int i = 1; i <= n; ++ i) {
	if (vis[i] == 0) {
	    tarjan(i);
	}
    }
    for (int i = 1; i <= n; ++ i) {
	for (int j = 0; j < g[i].size(); ++ j){
	    if (idex[i] != idex[g[i][j]]) {
		G[idex[i]].push_back(idex[g[i][j]]);
	    }
	}
    }
    scanf("%d", &t);
    while (t --) {
	scanf("%d%d", &x, &y);
	if (idex[x] == idex[y]) {
	    puts("NO");
	    return 0;
	}
	q.push_back(node(idex[x], idex[y]));
    }
    sort(q.begin(), q.end());
    //printf("%d %d\n", q[0].l, q[0].r);
    vector <node> :: iterator it = q.begin();
    for (int block = 0; block <= num / SZ; ++ block) {
	memset(vis, 0, sizeof vis);
	for (int i = 1; i <= num; ++ i) {
	    if (!vis[i]) dfs(i, block);
	}
	while (it != q.end() && it -> r / SZ == block) {
	    if (bit[it -> l][it -> r % SZ]) {
		puts("NO");
		return 0;
	    }
	    it ++;
	}
    }
    puts("YES");
    printf("%d\n", ans);
    for (int i = 1; i <= n; ++ i) {
	for (int j = 0; j < g[i].size(); ++ j){
	    printf("%d %d\n", i, g[i][j]);
	}
    }
    return 0;
}
