#include <cstdio>
#include <algorithm>
#include <cstring>
#include <stack>
#include <vector>
#define N 50010
using namespace std;
/* vis[N]记录该点是否被访问到 dfn[N]记录该点的时序 
 * low[N]记录该点可追溯到的最小时序 now作为时间戳 
 * num记录强连通分量的个数 size[N]记录每个强连通分量中包含的点的个数 
 * idx[N]记录每个点属于哪个强连通分量
 * gra[N]是图 sta是tarjan算法中的栈
 */
int vis[N], dfn[N], low[N], now, num, size[N], idx[N], xuhao[N], n, u, v;
vector<int> gra[N]; stack<int> sta;
vector <int> G[N];
struct node {
	int sum, id;
	friend bool operator < (node x, node y) {
		return x.sum < y.sum || x.sum == y.sum && x.id > y.id;
	}
	node (int _sum = 0, int _id = 0) {
		sum = _sum, id = _id;
	}
}ans, f[N];
void tarjan(int x) {
	vis[x] = 2;
    dfn[x] = low[x] = ++now;
    sta.push(x);
    for(int i = 0; i < gra[x].size(); ++i) {
        if(vis[gra[x][i]] == 0) {
            tarjan(gra[x][i]);
			low[x] = low[gra[x][i]] < low[x] ? low[gra[x][i]] : low[x];
		}
        else if(vis[gra[x][i]] == 2)
			low[x] = dfn[gra[x][i]] < low[x] ? dfn[gra[x][i]] : low[x];
    } 
    if(low[x] == dfn[x]) {
        num++;
        while(1) {
            int t = sta.top();
            idx[t] = num;
            xuhao[num] = xuhao[num] == -1 ? t : min(t, xuhao[num]);
            vis[t] = 1;
            sta.pop();
            size[num]++;
            if(t== x)
            	break;
        }
    }
}

node dfs(int x) {
	if (f[x].sum > 0) {
		return f[x];
	}
	f[x].sum = size[x];
	f[x].id = xuhao[x];
	node tmp;
	for (int i = 0; i < G[x].size(); ++i) {
		tmp = max(dfs(G[x][i]), tmp);
	}
	f[x].sum += tmp.sum;
	return f[x];
}

int main() {
	int T;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++cas) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			gra[i].clear();
		}
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d", &u, &v);
			gra[u].push_back(v);
		}
		memset(vis, 0, sizeof vis);
		memset(xuhao, -1, sizeof xuhao);
		now = num = 0;
		memset(dfn, 0, sizeof dfn);
		memset(low, 0, sizeof low);
		memset(size, 0, sizeof size);
		memset(idx, 0, sizeof idx);
		while (!sta.empty()) {
			sta.pop();
		}
		for (int i = 1; i <= n; ++i) {
			if (vis[i] == 0)
				tarjan(i);
		}
		for (int i = 0; i <= num; ++i) {
			G[i].clear();
		}
		memset(f, 0, sizeof f);
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < gra[i].size(); ++j) {
				if (idx[i] != idx[gra[i][j]])
					G[idx[i]].push_back(idx[gra[i][j]]);
			}
		}
		ans = node(0, 100000);
		for (int i = 1; i <= num; ++i) {
			ans = max(ans, dfs(i));
		}
		printf("Case %d: %d\n", cas, ans.id);
	}
	return 0;
}