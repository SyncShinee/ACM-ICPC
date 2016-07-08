#include <bits/stdc++.h>
using namespace std;
//先确定s,t,(从不从0没关系).调用init.然后建边.之后跑
//MAXN为顶点个数,每个边的flow为此边跑了多少流.正向边为正数,而反向边为负数,但只看差值即可.
//复杂度V^2E;
const int maxV = 5000 + 10;//点的个数
const int maxE = 100000 + 10;//边的个数
const int INF = 1000000000;//最大值,一般没用.用于初始化limit

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
    Edge edges[2 * maxE];    // 边数的两倍,注意啊啊啊
    int tot; //边的放的位置
    int head[maxV];   // 邻接表，head[u]代表最后一条边在edges里面的位置。
    int cur[maxV];         // 当前弧指针，每次从head中拷贝过去。
    bool vis[maxV];        // BFS使用
    int d[maxV];           // 从起点到i的距离
    int que[maxV], fro, tail;//BFS用的queue

    void init() {
        tot = 0;
        memset(head, -1, sizeof(head));
    }

    void addEdge(int from, int to, int cap) {
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
int tag[maxV];
int main() {
    int T, n, m, s, t1, t2, x, y;
    scanf("%d", &T);
    while (T --) {
        scanf("%d%d", &n, &m);
        g.init();
        scanf("%d%d%d", &t1, &t2, &s);
        for (int i = 0; i < m; ++ i) {
            scanf("%d%d", &x, &y);
            g.addEdge(x + n, y, 1);
            g.addEdge(y + n, x, 1);
        }
        for (int i = 1; i <= n; ++ i) {
            if (i == s) g.addEdge(i, i + n, 2);
            else g.addEdge(i, i + n, 1);
        }
                memset(tag, 0, sizeof tag);
        g.addEdge(t1 + n, n + n + 1, 1);
        g.addEdge(t2 + n, n + n + 1, 1);
        int mf = g.Maxflow(s, n + n + 1, 2);
        for (int i = 0; i < g.tot; ++ i) {
            if (g.edges[i].flow == -1) {
                if (g.edges[i].from != g.edges[i].to + n)
                tag[g.edges[i].from] = g.edges[i].to - n;
            }
        }
        printf("%d", t1);

        while (t1 != s && t1 != 0) {
            int tmp = tag[t1];
            tag[t1] = 0;
            t1 = tmp;
            printf(" %d", t1);
        }
        while (s != t2) {
            int i = 1;
            for (i = 1; i <= n; ++ i) {
                if (tag[i] == s) break; 
            }
            printf(" %d", i);
            s = i;
        }
        puts("");
    }
    return 0;
}
