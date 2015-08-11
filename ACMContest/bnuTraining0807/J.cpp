#pragma comment(linker,"/STACK:102400000,102400000")
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <stack>
#include <queue>
#include <vector>
#include <cmath>
#define N 100010
using namespace std;
/* vis[N]记录该点是否被访问到 dfn[N]记录该点的时序 
 * low[N]记录该点可追溯到的最小时序 now作为时间戳 
 * num记录强连通分量的个数 size[N]记录每个强连通分量中包含的点的个数 
 * indx[N]记录每个点属于哪个强连通分量
 * gra[N]是图 sta是tarjan算法中的栈
 */
int vis[N], dfn[N], low[N], now, num, size[N], indx[N], serial[N], ser, n;
vector<int> gra[N]; stack<int> sta;
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
        ser = 0;
        while(1) {
            int t = sta.top();
            serial[t] = ++ ser;
            indx[t] = num;
            vis[t] = 1;
            sta.pop();
            size[num]++;
            if(t == x) break;
        }
    }
}
int deep[N], anc[N][20];
struct LCA_online {
    void dfs(int x, int pre) {
        for(int i = 0; i < gra[x].size(); ++ i) {
            int v = gra[x][i];
            if(v != pre && indx[v] != indx[x]) {
                anc[v][0] = x;
                deep[v] = deep[x] + 1;
                dfs(v, x);
            }
        }
    }
    void prepare() {
        dfs(n + 1, -1);
        for(int i = 1; i <= n+1; i++) {
            for(int j = 1; (1 << j) <= n+1; j++) anc[i][j] = -1;
        }
        for(int j = 1; (1 << j) <= n; j++) {
            for(int i = 1; i <= n+1; i++) {
                if(anc[i][j - 1] != -1) {
                    int a = anc[i][j - 1];
                    anc[i][j] = anc[a][j - 1];
                }
            }
        }
    }
    pair <int, int> Lca(int p, int q) {
        int lo;
        if(deep[p] < deep[q]) swap(p, q);
        for(lo = 1; (1 << lo) <= deep[p]; lo++); lo--;
        for(int i = lo; i >= 0; i--)
            if(deep[p] - (1 << i) >= deep[q]) 
                p = anc[p][i];
        if(indx[p] == indx[q])
            return make_pair(p, q);
        for(int i = lo; i >= 0; i--)
            if(anc[p][i] != -1 && indx[anc[p][i]] != indx[anc[q][i]]) {
                p = anc[p][i];
                q = anc[q][i];
            }
        return make_pair(anc[p][0], anc[q][0]);
    }
}g;
int main() {
    int x, y, q;
	while (~scanf("%d", &n)) {
        for (int i = 1; i <= n+1; ++i) {
            gra[i].clear();
        }
        memset(vis, 0, sizeof vis);
        memset(size, 0, sizeof size);
        now = 0, num = 1;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &x);
            gra[x].push_back(i);
        }
    	for (int i = 1; i <= n; ++i) {
    		if (vis[i] == 0)
    			tarjan(i);
    	}
    	size[1] = 1;
        indx[n + 1] = 1;

        for (int i = 1; i <= n; ++i) {
            if (size[indx[i]] > 1) {
                gra[n + 1].push_back(i);
            }
        }
        deep[n + 1] = 0;
        g.prepare();
        scanf("%d", &q);
        while (q --)  {
            scanf("%d%d", &x, &y);
            pair<int, int> lca = g.Lca(x, y);
            int ans;
            if (lca.first == lca.second) {
                if (lca.first == n + 1) {
                    ans = -1;
                }
                else { 
                    ans = deep[x] + deep[y] - (deep[lca.first] << 1);
                }
            }
            else {
                ans = deep[x] + deep[y] - (deep[lca.first] << 1);
                int hao1 = serial[lca.first], hao2 = serial[lca.second];
                if (hao1 > hao2) {
                    swap(hao1, hao2);
                }
                ans += min(hao2 - hao1, hao1 - hao2 + size[indx[lca.first]]);
            }
            printf("%d\n", ans);
        }
    }
	return 0;
}
