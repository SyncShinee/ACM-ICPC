#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

const int maxn = 50 * 50 + 100;
const int INF = 1000 * maxn;

int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};

struct edge {
    int from, to, cap, flow;
    edge(int _from = 0, int _to = 0, int _cap = 0, int _flow = 0) {
        from = _from;
        to = _to;
        cap = _cap;
        flow = _flow;
    }
};
vector<edge> edges;
vector<int> G[maxn];
queue<int> myq;
int d[maxn], cur[maxn];

int bfs(int s, int t) {
    while(!myq.empty()) {
        myq.pop();
    }
    memset(d, -1, sizeof(d));
    d[s] = 0;
    myq.push(s);
    while(!myq.empty()) {
        int u = myq.front();
        myq.pop();
        for(int i = 0; i < G[u].size(); i++) {
            int v = edges[G[u][i]].to, flow = edges[G[u][i]].flow, cap = edges[G[u][i]].cap;
            if(d[v] == -1 && cap > flow) {
                d[v] = d[u] + 1;
                myq.push(v);
            }
        }
    }
    if(d[t] == -1)
    return -1;
    return 1;
}
int dfs(int u, int exflow, int t) {
    if(u == t || exflow == 0) return exflow;
    int tot = 0;
    for(int &i = cur[u]; i < G[u].size(); i++) {
        int v = edges[G[u][i]].to, flow = edges[G[u][i]].flow, cap = edges[G[u][i]].cap;
        int f;
        if(d[v] == d[u] + 1 && flow < cap && (f = dfs(v, min(cap - flow, exflow), t)) > 0) {
            tot += f;
            edges[G[u][i]].flow += f;
            edges[(G[u][i] ^ 1)].flow -= f;
            exflow -= f;
            if(exflow == 0)
            break;
        }
    }
    return tot;
}
int maxFlow(int s, int t) {
    int flow = 0;
    //printf("******");
    while(bfs(s, t) != -1) {
        memset(cur, 0, sizeof(cur));
        flow += dfs(s, INF, t);
    }
    return flow;
}
void addEdge(int from, int to, int cap) {
    //printf("%d  %d  %d\n", from, to, cap);
    G[from].push_back(edges.size());
    G[to].push_back(edges.size() + 1);
    edges.push_back(edge(from, to, cap, 0));
    edges.push_back(edge(to, from, 0, 0));
}
int n, m, a[maxn][maxn];
int check(int x, int y) {
    if(x >= 0 && x < n && y >= 0 && y < m)
    return 1;
    return 0;
}

void solve() {
    int S = n * m, T = S + 1;
    for(int i = 0; i <= T; i++) {
        G[i].clear();
    }
    edges.clear();
    int sum = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &a[i][j]);
            sum += a[i][j];
            if((i + j) % 2 == 0) {
                addEdge(S, i * m + j, a[i][j]);
                int ni, nj;
                for(int k = 0; k < 4; k++) {
                    ni = i + dx[k];
                    nj = j + dy[k];
                    if(check(ni, nj)) {
                        addEdge(i * m + j, ni * m + nj, INF);
                    }
                }
            }
            else {
                addEdge(i * m + j, T, a[i][j]);
            }
        }
    }
    int ans = maxFlow(S, T);
    //int ans = 0;
    printf("%d\n", sum - ans);
    
}
int main() {
    freopen("c.txt", "r", stdin);
    int ncase;
    scanf("%d", &ncase);
    while(ncase--) {
        scanf("%d%d", &n, &m);
        solve();
    }
    return 0;
}