#include <cstdio>
#include <algorithm>
#include <set>
#include <map>
#include <cstring>
#include <vector>
#include <stack>
using namespace std;
const int N = 2048;

/* vis[N]记录该点是否被访问到 dfn[N]记录该点的时序 
* low[N]记录该点可追溯到的最小时序 now作为时间戳 
 * num记录强连通分量的个数 size[N]记录每个强连通分量中包含的点的个数 
* index[N]记录每个点属于哪个强连通分量
 * gra[N]是图 sta是tarjan算法中的栈
 */
int vis[N], dfn[N], low[N], now, num, size[N], index[N];
int n;
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
        while(1) {
            int t = sta.top();
            index[t] = num;
            vis[t] = 1;
            sta.pop();
            size[num]++;
            if(t == x)
            	break;
        }
    }
}
vector <int> tre[N];
int dp[N][2];
void dfs(int x, int pre) {
	dp[x][0] = dp[x][1] = 1;
	int mx = 0;
	for (int i = 0; i < tre[x].size(); ++ i) {
		if (tre[x][i] == pre || index[tre[x][i]] == index[x]) {
			continue;
		}
		dfs(tre[x][i], x);
		dp[x][0] = max(dp[x][0], dp[tre[x][i]][0] + 1);
		dp[x][1] = max(dp[x][1], dp[tre[x][i]][0] + mx + 1);
		mx = max(mx, dp[tre[x][i]][0]);
	}
}
int main() {
	int T;
	freopen("C-large.in", "r", stdin);
	freopen("out.txt" ,"w", stdout);
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++ cas) {
		int x;
		scanf("%d", &n);
		memset(vis, 0, sizeof vis);
		num = now = 0;
		memset(dfn, 0, sizeof dfn);
		memset(low, 0, sizeof low);
		memset(size, 0, sizeof size);
		memset(index, 0, sizeof index);
		memset(dp, 0, sizeof dp);
		while (!sta.empty()) sta.pop();
		for (int i = 1; i <= n; ++ i) {
			tre[i].clear();
			gra[i].clear();
		}
		for (int i = 1; i <= n; ++ i) {
			scanf("%d", &x);
			gra[i].push_back(x);
			tre[x].push_back(i);
		}
		for (int i = 1; i <= n; ++i) {
			if (vis[i] == 0)
				tarjan(i);
		}
		int ans = 0;
		int ew = 0;
		for (int i = 1; i <= num; ++ i) {
			if (size[i] > 2) {
				ans = max(ans, size[i]);
			}
			if (size[i] == 2) {
				int tmp = 0;
				for (int j = 1; j <= n; ++ j) {
					if (index[j] == i) {
						dfs(j, -1);
						tmp += dp[j][0];
					}
					//printf("%d %d\n", dp[j][0], j);
				}
				ew += tmp;
				//printf("------%d\n", ans);
			}
		}
		printf("Case #%d: %d\n", cas, max(ans, ew));
	}
	
	return 0;
}