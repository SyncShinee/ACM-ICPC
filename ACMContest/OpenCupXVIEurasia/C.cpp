#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <cstring>
#include <queue>

using namespace std;

const int maxn = 4e5 + 100;
const int INF = 2e9 - 100;
int n, k;
int id;
map<int, int> mp;
int num[maxn];
int f[maxn][8], a[maxn], r[maxn], su[maxn];
struct node {
    int to, sta;
    node(int _to = 0, int _sta = 0) {
	to = _to;
	sta = _sta;
    }
};
vector<node> G[maxn], rG[maxn], nG[maxn];
int tim[maxn];
queue<int> q;
int now;
int color[maxn], vis[maxn];
vector<int> no;
void dfs1(int u) {
    vis[u] = 1;
    for(int i = 0; i < G[u].size(); i++) {
	int v = G[u][i].to;
	if(vis[v] == 0) {
	    dfs1(v);
	}
    }
    no.push_back(u);
}
void dfs2(int u, int k) {
    vis[u] = 1;
    color[u] = k;
    for(int i = 0; i < rG[u].size(); i++) {
	int v = rG[u][i].to;
	if(vis[v] == 0) {
	    dfs2(v, k);
	}
    }
}
int topu() {
    while(!q.empty()) {
	q.pop();
    }
    memset(tim, 0, sizeof(tim));
    for(int i = 1; i <= id; i++) {
	for(int j = 0; j < nG[i].size(); j++) {
	    tim[nG[i][j].to]++;
	}
    }
    for(int i = 1; i <= id; i++) {
	if(tim[i] == 0) {
	    q.push(i);
	}
    }
    while(!q.empty()) {
	int u = q.front();
	q.pop();
	for(int i = 0; i < nG[u].size(); i++) {
	    int v = nG[u][i].to, sta = nG[u][i].sta;
	    tim[v]--;
	    if(sta == 0) {
		if(su[v] == 0) {
		    r[v] = max(r[v], r[u]);
		}
		else {
		    if(r[v] < r[u])
			return 0;
		}
	    }
	    else {
		if(su[v] == 0) {
		    r[v] = max(r[v], r[u] + 1);
		}
		else {
		    if(r[v] <= r[u])
			return 0;
		}
	    }
	    if(tim[v] == 0) {
		q.push(v);
	    }
	}
    }
    return 1;
}

void solve() {
    mp.clear();
    now = k;
    for(int i = 1; i <= n; i++) {
	if(f[i][2] == 1) {
	    if(mp[f[i][3]] == 0) {
		now++;
		mp[f[i][3]] = now;
		a[now] = f[i][3];
	    }
	}
	if(f[i][4] == 1) {
	    if(mp[f[i][5]] == 0) {
		now++;
		mp[f[i][5]] = now;
		a[now] = f[i][5];
	    }
	}
    }
    for(int i = 1; i <= now; i++) {
	G[i].clear();
	rG[i].clear();
    }
    for(int i = 1; i <= n; i++) {
	int a = f[i][3];
	if(f[i][2] == 1) {
	    a = mp[a];
	}
	int b = f[i][5];
	if(f[i][4] == 1) {
	    b = mp[b];
	}
	G[b].push_back(node(a, f[i][1]));
	rG[a].push_back(node(b, f[i][1]));
    }

    memset(vis, 0, sizeof(vis));
    no.clear();
    for(int i = 1; i <= now; i++) {
	if(vis[i] == 0) {
	    dfs1(i);
	}
    }
    memset(vis, 0, sizeof(vis));
    id = 0;
    for(int i = no.size() - 1; i >= 0; i--) {
	int u = no[i];
	if(vis[u] == 0) {
	    id++;
	    dfs2(u, id);
	}
    }
    
    int flag = 1;
    for(int i = 1; i <= n; i++) {
	int a = f[i][3];
	if(f[i][2] == 1)
	    a = mp[a];
	int b = f[i][5];
	if(f[i][4] == 1)
	    b = mp[b];
	if(color[a] == color[b] && f[i][1] == 1) {
	    flag = 0;
	    break;
	}
    }
    //printf("11   %d\n", flag);
    if(flag == 1) {
	for(int i = 1; i <= id; i++) {
	    nG[i].clear();
	    r[i] = -INF;
	    su[i] = 0;
	}
	for(int i = 1; i <= now; i++) {
	    if(i > k) {
		r[color[i]] = a[i];
		su[color[i]] = 1;
	    }
	    for(int j = 0; j < rG[i].size(); j++) {
		int a = i, b = rG[i][j].to;
		if(color[a] != color[b]) {
		    nG[color[a]].push_back(node(color[b], rG[i][j].sta));
		}
	    }
	}
	flag = topu();
    }

    if(flag == 0) {
	printf("NO\n");
    }
    else {
	printf("YES\n");
	for(int i = 1; i <= k; i++) {
	    printf("%d\n", r[color[i]]);
	}
    }
}

int main() {
    //freopen("C.txt", "r", stdin);
    while(scanf("%d%d", &n, &k) != EOF) {
	for(int i = 1; i <= n; i++) {
	    for(int j = 1; j <= 5; j++) {
		scanf("%d", &f[i][j]);
	    }
	}
	solve();
    }
    return 0;
}
