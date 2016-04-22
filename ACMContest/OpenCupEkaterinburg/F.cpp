#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>
#include <cassert>
using namespace std;
const int N = 102400;
int vis[N], dfn[N], low[N], now = 0, num = 0, size[N], Index[N];

vector <int> gra[N];
stack <int> sta;
vector <int> G[N];
vector <int> st[N];
int edge[N][2];
int n, m;
void tarjan(int x) {
    vis[x] = 2;
    dfn[x] = low[x] = ++now;
    sta.push(x);
    for (int i = 0; i < gra[x].size(); ++ i) {
	if (vis[gra[x][i]] == 0) {
	    tarjan(gra[x][i]);
	    low[x] = min(low[x], low[gra[x][i]]);
	}
	else if (vis[gra[x][i]] == 2) {
	    low[x] = min(low[x], dfn[gra[x][i]]);
	}
    }
    if (low[x] == dfn[x]) {
	num++;
	while (1) {
	    int t = sta.top();
	    Index[t] = num;
	    st[num].push_back(t);
	    vis[t] = 1;
	    sta.pop();
	    size[num] ++;
	    if (t == x) {
		break;
	    }
	}
    }
}
int mat[321][321];
int d[N];
queue <int> q;
vector <pair<int, int> > ans;
int main() {
    //freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++ i) {
	scanf("%d%d", &edge[i][0], &edge[i][1]);
	gra[edge[i][0]].push_back(edge[i][1]);
    }
    for (int i = 1; i <= n; ++ i) {
	if (vis[i] == 0) {
	    tarjan(i);
	}
    }
    int sum = 0;
    for (int i = 1; i <= num; ++ i) {
	if (size[i] == 1) continue;
	sum += size[i];
    }
    for (int i = 0; i < m; ++ i) {
	if (Index[edge[i][0]] != Index[edge[i][1]]) {
	    if (mat[Index[edge[i][0]]][Index[edge[i][1]]] == 0) {
		G[Index[edge[i][0]]].push_back(Index[edge[i][1]]);
		mat[Index[edge[i][0]]][Index[edge[i][1]]] = 1;
	    }
	}
    }
    for (int t = 1; t <= n; ++ t) {
	for (int i = 1; i <= n; ++ i) {
	    if (i == t) continue;
	    for (int j = 1; j <= n; ++ j) {
		if (j == t || j == i) continue;
		if (mat[i][t] == 0 || mat[t][j] == 0) continue;
		mat[i][j] = max(mat[i][j], mat[i][t] + mat[t][j]);
	    }
	}
    }
    for (int i = 1; i <= n; ++ i) {
	for (int j = 0; j < G[i].size(); ++ j) {
	    if (mat[i][G[i][j]] == 1) {
		ans.push_back(make_pair(i, G[i][j]));
	    }
	}
    }
    printf("%d %d\n", n, sum + ans.size());
    for (int i = 1; i <= num; ++ i) {
	if (size[i] == 1) {
	    continue;
	}
	st[i].push_back(st[i][0]);
	for (int j = 0; j < st[i].size() - 1; ++ j) {
	    printf("%d %d\n", st[i][j], st[i][j + 1]);
	}
    }
    for (int i = 0; i < ans.size(); ++ i) {
	printf("%d %d\n", st[ans[i].first][0], st[ans[i].second][0]);
    }
    return 0;
}
