#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
int n, m;
const int N = 100010;
queue <int> q;
vector <int> G[N];
bool vis[N];
typedef long long ll;
int main() {
    int T, x, y;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; ++ cas) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++ i) {
            G[i].clear();
        }
        memset(vis, 0, sizeof vis);
        for (int i = 0; i < m; ++ i) {
            scanf("%d%d", &x, &y);
            G[x].push_back(y);
        }
        ll ans = 0;
        for (int i = 1; i <= n; ++ i) {
            if (!vis[i]) {
                q.push(i);
                vis[i] = true;
                ll num = 1;
                while (!q.empty()) {
                    int u = q.front();
                    q.pop();
                    for (int j = 0; j < G[u].size(); ++ j) {
                        int v = G[u][j];
                        if (vis[v]) continue;
                        q.push(v);
                        vis[v] = true;
                        num ++;
                    }
                }
                //printf("%d %d\n", num, i);
                ans += num * i;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
