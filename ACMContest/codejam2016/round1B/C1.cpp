#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <map>
#include <string>
#include <vector>

using namespace std;

const int maxV = 5000 + 10;//点的个数
const int maxE = 2000000 + 10;//边的个数
const int INF = 1000000000;//最大值,一般没用.用于初始化limit
const int maxn = 2e3 + 10;

struct Edge {
    int from, to, cap, flow, next;
    Edge(int _from = 0, int _to = 0, int _cap = 0, int _flow = 0, int _next = 0) {
        from = _from;
        to = _to;
        cap = _cap;
        flow = _flow;
        next = _next;
    }
};
struct Dinic {
    int s, t;
    Edge edges[2 * maxE]; // 边数的两倍,注意啊啊啊
    int tot; //边的放的位置
    int head[maxV]; // 邻接表， head[u]代表最后一条边在edges里面的位置。
    int cur[maxV]; // 当前弧指针，每次从head中拷贝过去。
    bool vis[maxV]; // BFS使用
    int d[maxV]; // 从起点到i的距离
    int que[maxV], fro, tail;//BFS用的queue
    void init() {
        tot = 0;
        memset(head, -1, sizeof(head));
    }
    void addEdge(int from, int to, int cap) { //第一条边的下标一定是偶数好
        edges[tot] = Edge(from, to, cap, 0, head[from]);
        head[from] = tot;
        tot++;
        edges[tot] = Edge(to, from, 0, 0, head[to]);
        head[to] = tot;
        tot++;
    }
    bool BFS() {
        memset(vis, 0, sizeof(vis));
        fro = tail = 0;
        que[tail] = s;
        tail++;
        vis[s] = 1;
        d[s] = 0;
        while (fro < tail) {
            int u = que[fro];
            fro++;
            for (int i = head[u]; i != -1; i = edges[i].next) {
                Edge &e = edges[i];
                if (!vis[e.to] && e.cap > e.flow) {
                    vis[e.to] = 1;
                    d[e.to] = d[u] + 1;
                    que[tail] = e.to;
                    tail++;
                }
            }
        }
        return vis[t];
    }
    int DFS(int u, int exFlow) {
        if (u == t || exFlow == 0) return exFlow;
        int flow = 0, f;
        for (int &i = cur[u]; i != -1; i = edges[i].next) {
            Edge &e = edges[i];
            if (d[u] + 1 == d[e.to]) {
                f = DFS(e.to, min(exFlow, e.cap - e.flow));
                if (f > 0) {
                    e.flow += f;
                    edges[i ^ 1].flow -= f;
                    flow += f;
                    exFlow -= f;
                    if (exFlow == 0)
                        break;
                }
            }
        }
        return flow;
    }
// 求s-t最大流。如果最大流超过limit，则只找一个流量为limit的流
    int Maxflow(int s, int t, int limit) {
        this->s = s;
        this->t = t;
        int flow = 0;
        while (BFS()) {
            memcpy(cur, head, sizeof(cur));
            flow += DFS(s, limit - flow);
            if (flow == limit) break; // 达到流量限制，直接退出
        }
        return flow;
    }
};
Dinic g;

map<string, int> mp[3];
int b[maxn][3];

string a[maxn][3];
int n;
void solve() {
    mp[1].clear();
    mp[2].clear();
    int n1 = 0, n2 = 0;
    for(int i = 1; i <= n; i++) {
        if(mp[1][a[i][1]] == 0) {
            n1++;
            mp[1][a[i][1]] = n1;
            b[i][1] = n1;
        }
        else {
            b[i][1] = mp[1][a[i][1]];
        }
        if(mp[2][a[i][2]] == 0) {
            n2++;
            mp[2][a[i][2]] = n2;
            b[i][2] = n2;
        }
        else {
            b[i][2] = mp[2][a[i][2]];
        }
    }
    g.init();
    int st = n1 + n2 + 1, ed = st + 1;
    for(int i = 1; i <= n1; i++) {
        g.addEdge(st, i, 1);
    }
    for(int i = 1; i <= n2; i++) {
        g.addEdge(i + n1, ed, 1);
    }
    for(int i = 1; i <= n; i++) {
        g.addEdge(b[i][1], n1 + b[i][2], 1);
    }
    int ans = g.Maxflow(st, ed, INF);
    //printf("%d  %d %d\n", n1, n2, ans);
    printf("%d\n", n - (n2 - ans) - n1);
}

char s[maxn];


int main() {
    freopen("C-small-attempt0.in", "r", stdin);
    freopen("Cout.txt", "w", stdout);
    int t;
    scanf("%d", &t);
    for(int _ = 1; _ <= t; _++) {
        printf("Case #%d: ", _);
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) {
            scanf("%s", s);
            a[i][1] = s;
            scanf("%s", s);
            a[i][2] = s;
        }
        solve();
    }
    return 0;
}